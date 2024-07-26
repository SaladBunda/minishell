/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:06:46 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/26 18:41:10 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int g_last_exit_status;

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
	t_token *tmp2 = tmp;
	// t_token *tmp2 = tmp;
	//print_tokens(tmp);
	// tmp = head->next;
	while (tmp2->type != E_CMD)
	{
		if (tmp2->type == PIPE && tmp2->prev->type == S_CMD)
			return (printf("syntax error near unexpected token %s\n",
						tmp2->value), free_list2(tmp),g_last_exit_status = 2,1);
		if (is_op(tmp2) == 1 && tmp2->next)
		{
			// if (tmp2->next->type == SPACE)
			// 	tmp2 = tmp2->next;
			if (not_string(tmp2->next) == 1)
				return (printf("syntax error near unexpected token %s\n",
						tmp2->next->value),free_list2(tmp), g_last_exit_status = 2,1);
		}
		else if (tmp2->type == PIPE && tmp2->next)
		{
			// if (tmp2->next->type == SPACE)
			// 	tmp2 = tmp2->next;
			if ((not_string(tmp2->next) == 1 && is_op(tmp2->next) == 0)
				|| tmp2->next->type == PIPE)
				return (printf("syntax error near unexpected token %s\n",
						tmp2->next->value),  free_list2(tmp),g_last_exit_status = 2,1);
		}
		tmp2 = tmp2->next;
	}
	// if (tmp22 != NULL) {
    free_list2(tmp);
    //     tmp22 = NULL;
    // }
	return (0);
}
