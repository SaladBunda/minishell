/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:06:46 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/13 15:17:21 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_op(t_token *t)
{
	if (t->type == GREAT || t->type == LESS || t->type == APPEND || t->type == HEREDOC)
		return (1);
	return (0);
}

int	not_string(t_token *t)
{
	if (t->type != VAR && t->type != DQUOTE && t->type != SQUOTE
		&& t->type != STR && t->type != SPACE)
		return (1);
	return (0);
}

int	is_string(t_token *t)
{
	if (t->type == VAR || t->type == DQUOTE || t->type == SQUOTE
		|| t->type == STR)
		return (1);
	return (0);
}

int	syntactic_tester(t_token *head)
{
	t_token	*tmp = space_free(head);
	//print_tokens(tmp);
	// tmp = head->next;
	while (tmp->type != E_CMD)
	{
		if (tmp->type == PIPE && tmp->prev->type == S_CMD)
			return (printf("syntax error near unexpected token %s\n",
						tmp->value), 1);
		if (is_op(tmp) == 1 && tmp->next)
		{
			// if (tmp->next->type == SPACE)
			// 	tmp = tmp->next;
			if (not_string(tmp->next) == 1)
				return (printf("syntax error near unexpected token %s\n",
						tmp->next->value), 1);
		}
		else if (tmp->type == PIPE && tmp->next)
		{
			// if (tmp->next->type == SPACE)
			// 	tmp = tmp->next;
			if ((not_string(tmp->next) == 1 && is_op(tmp->next) == 0)
				|| tmp->next->type == PIPE)
				return (printf("syntax error near unexpected token %s\n",
						tmp->next->value), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
