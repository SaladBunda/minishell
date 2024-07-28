/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_bunda.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:04:57 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/28 12:05:12 by ael-maaz         ###   ########.fr       */
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
		if (ittr->type != SPACE)
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

void	last_io(t_family *cmd_row)
{
	char	*infile;
	char	*outfile;
	int		i;

	infile = NULL;
	outfile = NULL;
	i = 0;
	while (cmd_row->files[i].path != NULL)
	{
		if (cmd_row->files[i].type == HEREDOC || cmd_row->files[i].type == LESS)
			infile = cmd_row->files[i].path;
		if (cmd_row->files[i].type == APPEND || cmd_row->files[i].type == GREAT)
			outfile = cmd_row->files[i].path;
		i++;
	}
	if (infile)
		cmd_row->last_infile = ft_strdup(infile);
	if (outfile)
		cmd_row->last_outfile = ft_strdup(outfile);
}


void	fill_files_array(t_family *family, t_token *start, t_token *end, int *i)
{
	int	type;

	while (start != end)
	{
		if (start->next && (start->type == HEREDOC || start->type == APPEND
				|| start->type == GREAT || start->type == LESS))
		{
			type = start->type;
			start = start->next;
			if (start->next && start->type == SPACE)
				start = start->next;
			if (start != end)
			{
				family->files[*i].path = ft_strdup(start->value);
				family->files[*i].lim = ft_strdup(start->value);
				family->files[*i].type = type;
				family->files[*i].is_var = start->type;
				(*i)++;
			}
		}
		if (start->next->type != E_CMD || start->next != end)
			start = start->next;
		else
			break ;
	}
}

char	*create_name_2(char *limiter,int i)
{
	char	*str;
	char	*str2;
	char	*free_var;
	char *number;

	str = "/tmp/";
	str2 = ft_strjoin(".", limiter);
	str = ft_strjoin(str, str2);
	free_var = str;
	number = ft_itoa(i);
	str = ft_strjoin(str, number);
	
	free(number);
	free(free_var);
	free(str2);
	// i = 0;
	// while (access(str, F_OK) == 0)
	// {
	// 	free_var = str;
	// 	free(free_var);
	// 	i++;
	return (str);
}

void change_name(t_family * head)
{
	t_family *tmp;
	tmp = head;
	int i;
	int j = 0;
	while(tmp->type != E_CMD)
	{
		if(tmp->type == CMD_ROW)
		{
			i = 0;
			while(tmp->files[i].path != NULL)
			{
				if(tmp->files[i].type == HEREDOC)
				{
					free(tmp->files[i].path);
					tmp->files[i].path = create_name_2(tmp->files[i].lim, j++);
				}		
				i++;
			}
		}
		tmp = tmp->next;
	}
	
}

void	extract_files(t_family *family_ll)
{
	t_family *ittr_node;
	int file_count;
	if (family_ll->next->type == E_CMD)
		return ;
	ittr_node = family_ll->next;
	t_token *tmp;
	int i;

	while (ittr_node->type != E_CMD)
	{
		if (ittr_node->type == CMD_ROW)
		{
			file_count = count_files(ittr_node);
			ittr_node->files = ft_calloc((file_count + 1) , sizeof(t_files));
			ft_memset(ittr_node->files, 0, (file_count + 1));
			tmp = ittr_node->start;
			i = 0;
			fill_files_array(ittr_node, tmp, ittr_node->end->next, &i);
			
			ittr_node->files[i].path = NULL;
			last_io(ittr_node);
		}
		ittr_node = ittr_node->next;
	}
	change_name(family_ll);
}