/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:29:29 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/03 16:56:22 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*space_free(t_token *list)
{
	t_token	*tokens_copy;
	t_token	*head;
	t_token	*node_copy;
	t_token	*ittr;

	tokens_copy = create_list();
	head = tokens_copy->prev;
	ittr = list->next;
	while (ittr->type != E_CMD)
	{
		if (ittr->type != SPC)
		{
			node_copy = new_token(ittr->value, ittr->type);
			append_token(tokens_copy, node_copy);
		}
		ittr = ittr->next;
	}
	return (head);
}

int	count_files(t_family *head)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = head->start;
	while (tmp != head->end->next)
	{
		if (tmp->group == FILE_NAME)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
