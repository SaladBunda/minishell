/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:18:47 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/22 22:36:56 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	contains_brackets(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '(' || cmd[i] == ')')
			return (1);
		i++;
	}
	return (0);
}

int	matching_closed(char c)
{
	if (c == '(')
		return (')');
	return (0);
}

int	modify(char *str)
{
	int	i;
	int	j;
	int	opened;
	int	target;

	opened = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!opened && str[i] == ')')
			return (0);
		else if (str[i] == '(')
		{
			j = i;
			target = matching_closed(str[i]);
			opened = 1;
		}
		else if (str[i] == ')' && str[i] != target)
			return (0);
		else if (str[i] == ')' && str[i] == target)
			return (bracket_util(str, i, j, &opened), 1);
		i++;
	}
	return (0);
}

int	brackets(char *cmd)
{
	char	*copy;

	copy = ft_strdup(cmd);
	while (contains_brackets(copy))
	{
		if (modify(copy) == 0)
		{
			printf("Parse Error\n");
			free(copy);
			return (0);
		}
	}
	free(copy);
	return (1);
}
