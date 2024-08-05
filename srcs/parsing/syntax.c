/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:06:46 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/08/05 16:05:24 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

int	not_string(t_token *t)
{
	if (t->type != VAR && t->type != DQUOTE && t->type != SQUOTE
		&& t->type != STR && t->type != SPC)
		return (1);
	return (0);
}

int	syntactic_tester(t_token *head)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = space_free(head);
	tmp2 = tmp;
	while (tmp2->type != E_CMD)
	{
		if (tmp2->type == PIPE && tmp2->prev->type == S_CMD)
			return (write(2, "syntax error\n", 13), 
				free_list2(tmp), g_last_exit_status = 2, 1);
		if (is_op(tmp2) == 1 && tmp2->next && not_string(tmp2->next) == 1)
			return (write(2, "syntax error\n", 13),
				free_list2(tmp), g_last_exit_status = 2,
				1);
		else if (tmp2->type == PIPE && tmp2->next
			&& ((not_string(tmp2->next) == 1 && is_op(tmp2->next) == 0)
				|| tmp2->next->type == PIPE))
			return (write(2, "syntax error\n", 13),
				free_list2(tmp), g_last_exit_status = 2, 1);
		tmp2 = tmp2->next;
	}
	free_list2(tmp);
	return (0);
}

/* int	is_string(t_token *t)
{
	if (t->type == VAR || t->type == DQUOTE || t->type == SQUOTE
		|| t->type == STR)
		return (1);
	return (0);
}*/
