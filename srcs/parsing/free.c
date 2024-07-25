/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:20:18 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/25 20:00:40 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(t_token *token)
{
	token->next = NULL;
	token->prev = NULL;
	free(token->value);
	free(token);
}

void	free_darr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void free_files(t_family *node)
{
	int i = 0;
	while(node->files[i].path != NULL)
	{
		free(node->files[i].lim);
		free(node->files[i].path);
		i++;
	}
	free(node->files);
}

void free_family_node(t_family *node)
{
	dprintf(2,"path address:%p\n", node->cmd_path);
	free(node->cmd_path);
	free(node->last_infile);
	free(node->last_outfile);
	free_darr(node->args);
	free_files(node);
	free(node);
}

void free_all_family(t_family *head)
{
	t_family *tmp = head;
	t_family *next;

	while(tmp->type != E_CMD)
	{
		if(tmp->type == S_CMD)
			tmp = tmp->next;
		next = tmp->next;
		free_family_node(tmp);
		tmp=tmp->next;
	}
}