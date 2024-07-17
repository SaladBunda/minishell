/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:42:57 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/05 19:56:05 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void level_checker(t_family *head)
{
	int level = 0;
	t_family *tmp;

	tmp = head->next;
	while(tmp->type != E_CMD)
	{
		// printf("tmp type: %d\n",tmp->type);
		if(tmp->type == LEFT_ROW)
			level++;
		if(tmp->type == RIGHT_ROW)
			level--;
		if(tmp->type == OR_ROW || tmp->type == AND_ROW)
			tmp->level = level;
		else if (tmp->type != OR_ROW || tmp->type != AND_ROW)
			tmp->level = level + 1;
		// printf("Node type: %d, Level: %d\n", tmp->type, tmp->level);
		tmp = tmp->next;
	}
	tmp = tmp->prev;
	if(tmp->type == RIGHT_ROW)
		tmp->level = tmp->level + 1;
	// printf("tmp final value/ type and level: %d     %d\n",tmp->type, tmp->level);
}