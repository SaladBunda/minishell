/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:42:30 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/05 09:52:50 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	var_name(char *cmd, int *index, int state)
{
	int		i;
	t_token	*token;

	(void)state;
	i = *index;
	token = NULL;
	(*index)++;
	while (cmd[*index] && cmd[*index] != '/' && is_special(cmd[*index]) == 0)
		(*index)++;
	(*index)--;
}

char	*get_var_value(char *str)
{
	char	*result;
	int		i;
	int		j;

	j = ft_strlen(str);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	result = ft_substr(str, i + 1, j - i);
	return (result);
}

char	*search_replace(char *str, int start, int end, t_token *env)
{
	char	*s;
	char	*var_name;
	t_token	*tmp;
	char	*var_value;
	int		i;

	var_value = NULL;
	tmp = env->next;
	s = ft_substr(str, start + 1, end - start);
	while (tmp)
	{
		i = 0;
		while (tmp->value && tmp->value[i] && tmp->value[i] != '=')
			i++;
		var_name = ft_substr(tmp->value, 0, i);
		if (ft_fcmp(var_name, s) == 0)
		{
			var_value = get_var_value(tmp->value);
			break ;
		}
		free(var_name);
		tmp = tmp->next;
	}
	return (free(s), free(var_name), var_value);
}

char	*substitution(int *i, int *j, char *var, t_token *token)
{
	int		new_len;
	char	*str;
	int		l;
	int		n;

	n = *i + 1;
	l = -1;
	new_len = ft_strlen(token->value) - ((*i) - (*j) + 1) + ft_strlen(var);
	str = malloc(sizeof(char) * (new_len + 1));
	if (!str)
		return (NULL);
	while (++l < *j)
		str[l] = token->value[l];
	while (l - *j < (int)ft_strlen(var))
	{
		str[l] = var[l - *j];
		l++;
	}
	*i = l - 1;
	while (l < new_len)
		str[l++] = token->value[n++];
	return (str[l] = '\0', free(token->value), str);
}
