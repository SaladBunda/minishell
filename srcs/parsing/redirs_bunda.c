/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_bunda.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:04:57 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/19 12:32:19 by ael-maaz         ###   ########.fr       */
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

void fill_files_array(t_family *family, t_token *start, t_token *end, int *i)
{
	int type;
	while(start != end)
	{
		if(start->next && (start->type == HEREDOC || start->type == APPEND || start->type == GREAT || start->type == LESS))
		{
			type = start->type;
			start = start->next;
			if(start->next && start->type == SPACE)
				start = start->next;
			if(start != end)
			{
				family->files[*i].path=ft_strdup(start->value);
				family->files[*i].type = type;
				family->files[*i].is_var = start->type;
				(*i)++;
			}
		}
		if(start->next->type != E_CMD || start->next != end)
			start = start->next;
		else 
			break;
	}
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
	
	while (ittr_node->type != E_CMD)
	{
		if (ittr_node->type == CMD_ROW)
		{
			file_count = count_files(ittr_node);
			ittr_node->files = malloc((file_count + 1) * sizeof(t_files));
			tmp = ittr_node->start;
			i = 0;
			fill_files_array(ittr_node,tmp,ittr_node->end->next,&i);
			ittr_node->files[i].path = NULL;
			last_io(ittr_node);
		}
		ittr_node = ittr_node->next;
	}
}