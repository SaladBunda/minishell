/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joiner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:56:22 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/08/04 10:36:50 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

char	*code_handler(char *string, int *i, int *j, int l)
{
	int		itoa_len;
	int		new_len;
	char	*code;
	char	*new_value;
	int		n;

	n = *i + 2;
	code = ft_itoa(g_last_exit_status);
	itoa_len = ft_strlen(code);
	new_len = ft_strlen(string) - 2 + itoa_len;
	new_value = malloc(sizeof(char) * (new_len + 1));
	ft_memset((void *)new_value, 0, new_len);
	while (++l < *j)
		new_value[l] = string[l];
	while (l - *j < (int)ft_strlen(code))
	{
		new_value[l] = code[l - *j];
		l++;
	}
	*i = l - 1;
	while (l < new_len)
		new_value[l++] = string[n++];
	free(code);
	return (new_value[l] = '\0', free(string), new_value);
}

int	dq_var(t_token *env, t_token *token, int i, int j)
{
	char	*var_value;

	while (token->value[++i])
	{
		if (token->value[i] == '$')
		{
			j = i;
			if (token->value[i + 1] && token->value[i + 1] == '?')
			{
				token->value = code_handler(token->value, &i, &j, -1);
				continue ;
			}
			j = i;
			var_name(token->value, &i, 0);
			if (i != j)
			{
				var_value = search_replace(token->value, j, i, env);
				token->value = substitution(&i, &j, var_value, token);
				free(var_value);
			}
		}
	}
	return (0);
}

int	var_var(t_token *env, t_token *token, int i, int j)
{
	char	*var_value;

	var_name(token->value, &i, 0);
	if (i != j)
	{
		if (ft_fcmp(token->value, "$?") == 0)
			return (free(token->value),
				token->value = ft_itoa(g_last_exit_status), 0);
		var_value = search_replace(token->value, j, i, env);
		token->value = substitution(&i, &j, var_value, token);
		free(var_value);
	}
	else
	{
		free(token->value);
		token->value = ft_strdup("$");
	}
	return (0);
}

void	var_substitutionner(t_token *head, t_token *env)
{
	t_token	*tmp;

	tmp = head->next;
	while (tmp->type != E_CMD)
	{
		if (tmp->type == DQUOTE)
		{
			if (tmp->prev->type == SPC && tmp->prev->prev->type != HEREDOC)
				dq_var(env, tmp, -1, 0);
			else if (tmp->prev->type != HEREDOC)
				dq_var(env, tmp, -1, 0);
		}
		else if (tmp->type == VAR)
		{
			if (tmp->prev->type == SPC && tmp->prev->prev->type != HEREDOC)
				var_var(env, tmp, 0, 0);
			else if (tmp->prev->type != HEREDOC)
				var_var(env, tmp, 0, 0);
		}
		tmp = tmp->next;
	}
}

void	joiner(t_token *head, t_token *env)
{
	var_substitutionner(head, env);
	token_merger(head);
}
