/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joiner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:49:56 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/03 15:58:04 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	type_returner(t_token *token)
{
	if (token->type == DQUOTE || token->type == SQUOTE || token->type == VAR
		|| token->type == STR)
		return (0);
	return (1);
}

int	nof_var(char *value)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	while (value[i])
	{
		if (value[i] && value[i + 1] && value[i] == '$' && value[i + 1] == '?')
		{
			number += 1;
			i++;
		}
		i++;
	}
	return (number);
}

char	*value_merger(t_token *ptr, int to_merge)
{
	int		i;
	char	*new_value;
	t_token	*node;
	char	*tmp;

	node = ptr;
	i = 0;
	new_value = ft_strdup(ptr->value);
	while (i < to_merge)
	{
		tmp = new_value;
		new_value = ft_strjoin(new_value, node->next->value);
		free(tmp);
		node = node->next;
		i++;
	}
	return (new_value);
}

t_token	*nodes_detash(t_token *ptr, int to_detash, int flag, int i)
{
	t_token	*detash_start;
	t_token	*tmp;
	t_token	*detash_end;
	t_token	*new_node;

	detash_end = NULL;
	new_node = new_token(value_merger(ptr, to_detash), flag);
	detash_start = ptr->prev;
	tmp = detash_start->next;
	while (++i < to_detash)
		tmp = tmp->next;
	detash_end = tmp->next;
	tmp->next = NULL;
	detash_start->next = new_node;
	detash_end->prev = new_node;
	new_node->next = detash_end;
	new_node->prev = detash_start;
	free_list(ptr, 0);
	return (new_node);
}

void	token_merger(t_token *head)
{
	int		i;
	t_token	*tmp;
	t_token	*tmp2;
	int		flag;

	flag = STR;
	tmp = head->next;
	while (tmp)
	{
		tmp2 = tmp;
		i = 0;
		while (type_returner(tmp) == 0 && tmp->next != NULL
			&& type_returner(tmp->next) == 0)
		{
			if (tmp->type == VAR)
				flag = VAR;
			tmp = tmp->next;
			i++;
		}
		if (i > 0)
			tmp = nodes_detash(tmp2, i, flag, -1);
		else
			tmp = tmp->next;
	}
}
