/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:58:14 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/20 19:42:41 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	echo_builtin(t_family *cmd_row)
// {
// 	t_token *tmp;
// 	int new_line;

// 	tmp = cmd_row->start->next;

// 	if (tmp->type == SPACE || !ft_fcmp(tmp->value, "echo"))
// 		tmp = tmp->next;
// 	new_line = 1;
// 	while (tmp->next && (!ft_fcmp(tmp->value, "-n") || tmp->type == SPACE))
// 	{
// 		tmp = tmp->next;
// 		new_line = 0;
// 	}
// 	if (tmp && tmp->type == SPACE)
// 		tmp = tmp->next;
// 	while (tmp && tmp->next && tmp != cmd_row->end && (tmp->type != OP || tmp->type != FILE_NAME))
// 	{
// 		printf("%s", tmp->value);
// 		tmp = tmp->next;
// 	}
// 	if (tmp->value && tmp->type != SPACE)
// 		printf("%s", tmp->value);
// 	if (new_line == 1)
// 		printf("\n");
// }

void	echo_builtin(t_family *cmd_row)
{
	// t_token *tmp;
	int new_line;
	int i = 1;
	new_line = 1;
	// tmp = cmd_row->start->next;

	// if (tmp->type == SPACE || !ft_fcmp(tmp->value, "echo"))
	// 	tmp = tmp->next;
	// new_line = 1;
	// while (tmp->next && (!ft_fcmp(tmp->value, "-n") || tmp->type == SPACE))
	// {
	// 	tmp = tmp->next;
	// 	new_line = 0;
	// }
	// if (tmp && tmp->type == SPACE)
	// 	tmp = tmp->next;
	// while (tmp && tmp->next && tmp != cmd_row->end && (tmp->type != OP || tmp->type != FILE_NAME))
	// {
	// 	printf("%s", tmp->value);
	// 	tmp = tmp->next;
	// }
	// if (tmp->value && tmp->type != SPACE)
	// 	printf("%s", tmp->value);
	// if (new_line == 1)
	// 	printf("\n");
	dprintf(2,"first param:%s\n",cmd_row->args[i]);
	while(cmd_row->args[i] && ft_fcmp(cmd_row->args[i],"-n") == 0)
		(new_line = 0, i++);
	while(cmd_row->args[i])
	{
		printf("%s",cmd_row->args[i]);
		if(cmd_row->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("-");
	if(new_line == 1)
		printf("\n");
}
