/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:18:32 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/26 17:57:35 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(char *value, int type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->family = NULL;
	new_token->value = value;
	new_token->level = 0;
	new_token->group = 0;
	new_token->hidden = 0;
	return (new_token);
}

t_token	*create_list(void)
{
	t_token	*head;
	t_token	*tail;

	head = new_token(NULL, S_CMD);
	tail = new_token(NULL, E_CMD);
	head->next = tail;
	tail->prev = head;

	return (tail);
}

void	append_token(t_token *tail, t_token *token)
{
	t_token	*penultimate;

	if (!tail || !token)
		return ;
	penultimate = tail->prev;
	penultimate->next = token;
	token->next = tail;
	token->prev = penultimate;
	tail->prev = token;
}

void	print_tokens(t_token *head)
{
	t_token	*node;
	int		i;

	node = head->next;
	i = 0;
	while (node)
	{
		printf("#:%d of type %d with value: -%s- and group: %d\n", i, node->type, node->value, node->group);
		printf("-----------\n");
		node = node->next;
		i++;
	}
	printf("\n\n");
}

t_token	*list_tail(t_token *node)
{
	t_token	*tmp;

	tmp = node;
	while (tmp->type != E_CMD)
		tmp = tmp->next;
	return (tmp);
}
