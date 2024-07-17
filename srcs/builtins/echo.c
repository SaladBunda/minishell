/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:58:14 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/16 17:06:59 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo_builtin(t_family *cmd_row)
{
	t_token *tmp;
	int new_line;

	tmp = cmd_row->start->next;

	if (tmp->type == SPACE || !ft_fcmp(tmp->value, "echo"))
		tmp = tmp->next;
	new_line = 1;
	while (tmp->next && (!ft_fcmp(tmp->value, "-n") || tmp->type == SPACE))
	{
		tmp = tmp->next;
		new_line = 0;
	}
	if (tmp && tmp->type == SPACE)
		tmp = tmp->next;
	while (tmp && tmp->next && tmp != cmd_row->end && (tmp->type != OP || tmp->type != FILE_NAME))
	{
		printf("%s", tmp->value);
		tmp = tmp->next;
	}
	if (tmp->value && tmp->type != SPACE)
		printf("%s", tmp->value);
	if (new_line == 1)
		printf("\n");
}
