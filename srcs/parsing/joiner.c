/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joiner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:56:22 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/22 16:54:36 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	dq_var(t_token *env, t_token *token, int i, int j)
{
	char	*var_value;

	while (token->value[++i])
	{
		if (token->value[i] == '$')
		{
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

int	type_returner(t_token *token)
{
	if (token->type == DQUOTE || token->type == SQUOTE || token->type == VAR
		|| token->type == STR)
		return (0);
	return (1);
}

void	var_substitutionner(t_token *head, t_token *env)
{
	t_token	*tmp;

	tmp = head->next;
	while (tmp)
	{
		if (tmp->type == DQUOTE)
		{
			if(tmp->prev->type == SPACE)
			{
				if(tmp->prev->prev->type != HEREDOC)	
					dq_var(env, tmp, -1, 0);
			}
			else
				if(tmp->prev->type != HEREDOC)	
					dq_var(env, tmp, -1, 0);
		}
		else if (tmp->type == VAR)
		{
			if(tmp->prev->type == SPACE)
			{
				if(tmp->prev->prev->type != HEREDOC)	
					var_var(env, tmp, 0, 0);
			}
			else
				if(tmp->prev->type != HEREDOC)	
					var_var(env, tmp, 0, 0);
		}
		tmp = tmp->next;
	}
}

char	*value_merger(t_token *ptr, int to_merge)
{
	int		i;
	char	*new_value;
	t_token	*node;
	char	*tmp;

	node = ptr;
	i = 0;
	new_value = ft_strdup(ptr->value);
	while (i < to_merge)
	{
		tmp = new_value;
		new_value = ft_strjoin(new_value, node->next->value);
		free(tmp);
		node = node->next;
		i++;
	}
	return (new_value);
}

t_token	*nodes_detash(t_token *ptr, int to_detash, int flag)
{
	int		i;
	t_token	*detash_start;
	t_token	*tmp;
	t_token	*detash_end;
	t_token	*new_node;

	detash_end = NULL;
	i = 0;
	new_node = new_token(value_merger(ptr, to_detash), flag);
	detash_start = ptr->prev;
	tmp = detash_start->next;
	while (i < to_detash)
	{
		tmp = tmp->next;
		i++;
	}
	detash_end = tmp->next;
	tmp->next = NULL;
	detash_start->next = new_node;
	detash_end->prev = new_node;
	new_node->next = detash_end;
	new_node->prev = detash_start;
	free_list(ptr);
	return (new_node);
}

void	token_merger(t_token *head)
{
	int		i;
	t_token	*tmp;
	t_token	*tmp2;
	int flag;

	flag = STR;
	tmp = head->next;
	while (tmp)
	{
		tmp2 = tmp;
		i = 0;
		while (type_returner(tmp) == 0 && tmp->next != NULL
			&& type_returner(tmp->next) == 0)
		{
			if(tmp->type == VAR)
				flag = VAR;
			tmp = tmp->next;
			i++;
		}
		if (i > 0)
			tmp = nodes_detash(tmp2, i, flag);
		else
			tmp = tmp->next;
	}
}

void	joiner(t_token *head, t_token *env)
{
	var_substitutionner(head, env);
	// replaces variables with their values from env and also inside double quotes
	token_merger(head);
}
