/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:17:39 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/08/04 15:01:54 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_cmd(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	ptr = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 2));
	if (!ptr)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = '/';
	while (i < (ft_strlen(s1) + ft_strlen(s2) + 1))
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

int	is_empty(t_token *token)
{
	int	i;

	i = 0;
	if (token->type != VAR)
		return (0);
	else
	{
		while (token->value[i] && is_whitespace(token->value[i]) == 1)
			i++;
		if (token->value[i] == '\0')
			return (1);
	}
	return (0);
}

int	count_args(t_token *start, t_token *end)
{
	t_token	*tmp;
	int		count;

	tmp = start;
	count = 0;
	while (tmp != end)
	{
		if (tmp->type != SPC && (tmp->group == COMMAND || tmp->group == PARAM)
			&& is_empty(tmp) == 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
