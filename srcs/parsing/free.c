/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:20:18 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/26 20:33:07 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(t_token *token)
{
	token->next = NULL;
	token->prev = NULL;
	if(token->value)
		free(token->value);
	free(token);
}
void	free_token2(t_token *token)
{
	token->next = NULL;
	token->prev = NULL;
	// if(token->value)
	// 	free(token->value);
	free(token);
}
void	free_list(t_token *head,int flag)
{
	t_token	*tmp;

	if(flag == 1)
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
	// head = head->prev;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free_token(tmp);
	}
	
	// free(tmp);
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
	if(node->files)
	{
		while(node->files[i].path != NULL)
		{
			free(node->files[i].lim);
			free(node->files[i].path);
			i++;
		}
		free(node->files);
	}
}

void free_family_node(t_family *node)
{
	if(node->cmd_path)
		free(node->cmd_path);
	if(node->last_infile)
		free(node->last_infile);
	if(node->last_outfile)
		free(node->last_outfile);
	if(node->args)
		free_darr(node->args);
	if(node->type != PIPE_ROW)
		free_files(node);
	node->start = NULL;
	node->end = NULL;
	free(node);
}

void free_all_family(t_family *head)
{
	t_family *tmp = head;
	t_family *next;

	while(tmp->type != E_CMD)
	{
		// if(tmp->type == S_CMD)
		// {
		// 	tmp = tmp->next;
		// 	free(head);
		// }
		next = tmp->next;
		free_family_node(tmp);
		tmp=next;
	}

	free(tmp);
}