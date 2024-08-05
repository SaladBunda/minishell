/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:30:57 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/04 20:07:13 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int		g_last_exit_status;

int	valid_exit(char **args, int nof_args)
{
	if (!is_numeric(args[1]) && nof_args >= 2)
		return (1);
	if (!in_range(args[1], 0, 1, 0))
		return (1);
	return (0);
}

unsigned char	wrapper(long n)
{
	return (n % 256);
}

void	exit_arg(int nof_args, char **args)
{
	if (nof_args == 1)
		exit(g_last_exit_status);
	else
	{
		if (ft_atol(args[1]) <= LLONG_MAX && ft_atol(args[1]) >= LLONG_MIN
			&& is_numeric(args[1]))
		{
			g_last_exit_status = 0;
			exit(wrapper(ft_atol(args[1])));
		}
		else
		{
			g_last_exit_status = 255;
			(printf("bash: exit: %s: numeric argument required\n", args[1]),
				exit(255));
		}
	}
}

void	exit_args(char **args)
{
	if (is_numeric(args[1]))
	{
		g_last_exit_status = 1;
		return ((void)(printf("exit\n"),
			printf("bash: exit: too many arguments\n")));
	}
	else
	{
		g_last_exit_status = 255;
		(printf("exit\n"),
			printf("bash: exit: \
				%s: numeric argument required\n",
				args[1]),
			exit(255));
	}
}

void	exit_builtin(t_family *family)
{
	char	**args;
	int		nof_args;

	args = family->args;
	nof_args = 0;
	while (args[nof_args])
		nof_args++;
	if (nof_args == 1 || nof_args == 2)
		exit_arg(nof_args, args);
	else
		exit_args(args);
	printf("bash: exit: too many arguments\n");
	g_last_exit_status = 1;
}
