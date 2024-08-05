/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:15:52 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/08/04 20:02:24 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	assign_token(t_token **token, t_family *group, int *flag)
{
	*flag = 0;
	*token = group->start;
}

void	organizer(t_family *tmp, t_token *tmp2, int flag)
{
	while (tmp->type != E_CMD)
	{
		assign_token(&tmp2, tmp, &flag);
		while (tmp2 != tmp->end->next)
		{
			if (!flag && is_str(tmp2) && (tmp2->type != VAR
					|| (tmp2->type == VAR && !is_empty(tmp2))))
				(_edit(&tmp2->group, COMMAND), flag++);
			else
				tmp2->group = PARAM;
			if ((is_op(tmp2) == 1))
			{
				tmp2->group = OP;
				if (tmp2->next != tmp->end->next && tmp2->next->type == SPC)
					tmp2 = tmp2->next;
				if (tmp2->next != tmp->end->next && is_str(tmp2->next) == 1)
				{
					tmp2->next->group = FILE_NAME;
					tmp2 = tmp2->next;
				}
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

t_token	*remove_space(t_token *target)
{
	t_token	*before;
	t_token	*after;

	before = target->prev;
	after = target->next;
	before->next = after;
	after->prev = before;
	free_token(target);
	return (after);
}

void	omit_spaces(t_token *head)
{
	t_token	*ittr;

	ittr = head->next;
	while (ittr->type != E_CMD)
	{
		if (ittr->type == SPC)
			ittr = remove_space(ittr);
		else
			ittr = ittr->next;
	}
}
