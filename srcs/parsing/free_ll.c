/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ll.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:27:05 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/04 16:08:18 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_all_family(t_family *head)
{
	t_family	*tmp;
	t_family	*next;

	tmp = head;
	while (tmp->type != E_CMD)
	{
		next = tmp->next;
		free_family_node(tmp);
		tmp = next;
	}
	free_family_node(tmp);
}

void	free_list(t_token *head, int flag)
{
	t_token	*tmp;

	if (flag == 1)
	{
		head = head->prev;
		while (head->type != E_CMD)
		{
			tmp = head;
			head = head->next;
			free_token(tmp);
		}
		free(head);
		return ;
	}
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free_token(tmp);
	}
}

void	free_list2(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free_token2(tmp);
	}
}
