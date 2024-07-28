/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:09:14 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/28 18:10:27 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_2d(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		printf("%s\n", strs[i]);
		i++;
	}
}

void	print_family(t_family *head)
{
	t_family	*node;

	printf("printing families\n");
	node = head->next;
	while (node)
	{
		if (node->type != PIPE_ROW)
		{
			printf("infiles: \n");
			printf("args: \n");
			if (node->args)
				print_2d(node->args);
			printf("path: \n");
			if (node->cmd_path)
				printf("%s\n", node->cmd_path);
			printf("-----------\n");
		}
		node = node->next;
	}
	printf("\n\n");
}

/*Create new family node*/
t_family	*new_family(int type)
{
	t_family	*new_family;

	new_family = (t_family *)malloc(sizeof(t_family));
	if (!new_family)
		return (NULL);
	new_family->type = type;
	new_family->next = NULL;
	new_family->prev = NULL;
	new_family->start = NULL;
	new_family->end = NULL;
	new_family->last_infile = NULL;
	new_family->last_outfile = NULL;
	new_family->cmd_path = NULL;
	new_family->level = 0;
	new_family->args = NULL;
	new_family->files = NULL;
	return (new_family);
}

/* Initialize Family linked list */
t_family	*init_familyll(void)
{
	t_family	*head;
	t_family	*tail;

	head = new_family(S_CMD);
	head->start = NULL;
	head->end = NULL;
	tail = new_family(E_CMD);
	tail->start = NULL;
	tail->end = NULL;
	head->next = tail;
	tail->prev = head;
	return (tail);
}

void	append_family(t_family *tail, t_family *token)
{
	t_family	*penultimate;

	if (!tail || !token)
		return ;
	penultimate = tail->prev;
	penultimate->next = token;
	token->next = tail;
	token->prev = penultimate;
	tail->prev = token;
}

t_family	*create_family_ll(t_token *ll_head)
{
	t_family *new;
	t_family *tail;
	t_family *head;
	t_token *tmp;

	tmp = ll_head->next;
	tail = init_familyll();
	head = tail->prev;
	tmp = ll_head->next;
	while (tmp->type != E_CMD)
	{
		if (tmp->type != PIPE)
		{
			new = new_family(CMD_ROW);
			new->start = tmp;
			while (tmp->next && tmp->type != PIPE)
				tmp = tmp->next;
			new->end = tmp->prev;
		}
		else if (tmp->type == PIPE)
		{
			new = new_family(PIPE_ROW);
			new->start = tmp;
			new->end = tmp;
			tmp = tmp->next;
		}
		append_family(tail, new);
	}
	return (head);
}
