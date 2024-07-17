/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:15:52 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/13 12:52:38 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_operator(t_token *t)
{
	if (t->type == GREAT || t->type == LESS || t->type == APPEND || t->type == HEREDOC)
		return (1);
	return (0);
}

static int	is_string(t_token *t)
{
	if (t->type == VAR || t->type == DQUOTE || t->type == SQUOTE
		|| t->type == STR)
		return (1);
	return (0);
}

void	organizer(t_family *family)
{
	t_family	*tmp;
	t_token		*tmp2;
	int			flag;

	flag = 0;
	tmp = family->next;
	while (tmp->type != E_CMD)
	{
		flag = 0;
		tmp2 = tmp->start;
		while (tmp2 != tmp->end->next)
		{
			if (flag == 0 && is_string(tmp2) == 1)
			{
				tmp2->group = COMMAND;
				flag++;
			}
			else
				tmp2->group = PARAM;
			if ((is_operator(tmp2) == 1))
			{
				tmp2->group = OP;
				if (tmp2->next != tmp->end->next && tmp2->next->type == SPACE)
					tmp2 = tmp2->next;
				if (tmp2->next != tmp->end->next && is_string(tmp2->next) == 1)
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
		if (ittr->type == SPACE)
			ittr = remove_space(ittr);
		else
			ittr = ittr->next;
	}
}
