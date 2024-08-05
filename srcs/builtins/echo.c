/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:58:14 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/05 18:20:21 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

void	check_option(t_family *cmd_row, int *i, int *new_line)
{
	int	j;

	j = 0;
	while (cmd_row->args[*i])
	{
		j = 0;
		if (cmd_row->args[*i][j] == '-')
		{
			j++;
			while (cmd_row->args[*i][j] == 'n')
				j++;
			if (cmd_row->args[*i][j] == '\0')
			{
				*new_line = 0;
				(*i)++;
				continue ;
			}
			else
				break ;
		}
		else
			break ;
		(*i)++;
	}
}

void	echo_builtin(t_family *cmd_row)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = 1;
	check_option(cmd_row, &i, &new_line);
	while (cmd_row->args[i])
	{
		write(1, cmd_row->args[i], ft_strlen(cmd_row->args[i]));
		if (cmd_row->args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (new_line == 1)
		write(1, "\n", 1);
	g_last_exit_status = 0;
}
