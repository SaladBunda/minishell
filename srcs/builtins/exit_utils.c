/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:34:33 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/04 20:09:02 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == 32)
		i++;
	if (ft_strlen(str) == i)
		return (255);
	else
		return (0);
}

int	all_numeric(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_numeric(args[i]))
			return (0);
	}
	return (1);
}

int	in_range(char *str, unsigned long number, int sign, int i)
{
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	if (number > 9223372036854775807UL && sign == 1)
		return (1);
	else if (number > 9223372036854775807UL + 1UL && sign == -1)
		return (-1);
	else
		return (0);
}
