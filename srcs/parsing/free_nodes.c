/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:27:08 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/04 18:03:37 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(t_token *token)
{
	token->next = NULL;
	token->prev = NULL;
	if (token->value)
		free(token->value);
	free(token);
}

void	free_token2(t_token *token)
{
	token->next = NULL;
	token->prev = NULL;
	free(token);
}

void	free_family_node(t_family *node)
{
	if (node->cmd_path)
		free(node->cmd_path);
	if (node->last_in)
		free(node->last_in);
	if (node->last_out)
		free(node->last_out);
	if (node->args)
		free_darr(node->args);
	if (node->type != PIPE_ROW && node->type != S_CMD)
		free_files(node);
	node->start = NULL;
	node->end = NULL;
	free(node);
}
