/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_bunda.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:04:57 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/16 15:54:39 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_files(t_family *head)
{
	int i;
	t_token *tmp;
	
	i = 0;
	tmp = head->start;
	while(tmp != head->end->next)
	{
		if(tmp->group == FILE_NAME)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	last_io(t_family *cmd_row)
{
	char *infile = NULL;
	char *outfile =NULL;
	int i = 0;

	while(cmd_row->files[i].path != NULL)
	{
		if(cmd_row->files[i].type == HEREDOC || cmd_row->files[i].type == LESS)
			infile = cmd_row->files[i].path;
		if(cmd_row->files[i].type == APPEND || cmd_row->files[i].type == GREAT)
			outfile = cmd_row->files[i].path;
		i++;
	}
	if(infile)
		cmd_row->last_infile = ft_strdup(infile);
	if(outfile)
		cmd_row->last_outfile = ft_strdup(outfile);
}


void	extract_files(t_family *family_ll)
{
	t_family	*ittr_node;
	int file_count;
	if(family_ll->next->type == E_CMD)
		return ;
	ittr_node = family_ll->next;
	t_token *tmp;
	int i;
	int type;
	
	while (ittr_node->type != E_CMD)
	{
		if (ittr_node->type == CMD_ROW)
		{
			file_count = 0;
			file_count = count_files(ittr_node);
			ittr_node->files = malloc((file_count + 1) * sizeof(t_files));
			tmp = ittr_node->start;
			i = 0;
			while(tmp != ittr_node->end->next)
			{
				if(tmp->next && (tmp->type == HEREDOC || tmp->type == APPEND || tmp->type == GREAT || tmp->type == LESS))
				{
					type = tmp->type;
					tmp = tmp->next;
					if(tmp->next && tmp->type == SPACE)
						tmp = tmp->next;
					if(tmp != ittr_node->end->next)
					{
						ittr_node->files[i].path=ft_strdup(tmp->value);
						ittr_node->files[i].type = type;
						i++;
					}
				}
				if(tmp->next->type != E_CMD || tmp->next != ittr_node->end->next)
					tmp = tmp->next;
				else 
					break;
			}
			ittr_node->files[i].path = NULL;
			last_io(ittr_node);
		}
		ittr_node = ittr_node->next;
	}
}