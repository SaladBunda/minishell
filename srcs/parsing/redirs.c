/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:39:59 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/19 18:26:31 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


//fucntion returns a new linked list that has no spaces


int	n_files(t_family *cmd_row, int op_type)
{
	t_token	*ittr;
	int		files;

	files = 0;
	ittr = cmd_row->start;
	while (ittr != cmd_row->end->next)
	{
		if (ittr->type == op_type)
			files++;
		ittr = ittr->next;
	}
	return (files);
}

int	fill_arr(t_family *cmd_row, int type, int *index, char ***arr)
{
	t_token	*ittr_node;

	ittr_node = cmd_row->start;
	while (ittr_node != cmd_row->end->next)
	{
		if (ittr_node && ittr_node->next && ittr_node->type == type && *arr)
		{
			if (ittr_node->next->type == SPACE)
				ittr_node = ittr_node->next;
			(*arr)[*index] = ft_strdup(ittr_node->next->value);
			*index += 1;
		}
		ittr_node = ittr_node->next;
	}
	return (*index);
}

void	create_ios(t_family *cmd_row, int type, char ***arr, int nof)
{
	int	i;

	i = 0;
	nof = n_files(cmd_row, type);
	*arr = (char **)malloc(sizeof(char *) * (nof + 1));
	fill_arr(cmd_row, type, &i, arr);
	(*arr)[i] = NULL;
}

void	fill_ios(t_family *cmd_row)
{
	int	in_files;
	int	out_files;
	int	append_files;
	int	heredoc_files;

	in_files = n_files(cmd_row, LESS);
	out_files = n_files(cmd_row, GREAT);
	heredoc_files = n_files(cmd_row, HEREDOC);
	append_files = n_files(cmd_row, APPEND);
	if (in_files)
		create_ios(cmd_row, LESS, &cmd_row->in_files, in_files);
	if (out_files)
		create_ios(cmd_row, GREAT, &cmd_row->out_files, out_files);
	if (heredoc_files)
		create_ios(cmd_row, HEREDOC, &cmd_row->here_docs, heredoc_files);
	if (append_files)
		create_ios(cmd_row, APPEND, &cmd_row->appends, append_files);
}

// void	last_io(t_family *cmd_row)
// {
// 	t_token	*last_infile;
// 	t_token	*last_outfile;
// 	t_token	*ittr_node;

// 	ittr_node = cmd_row->start;
// 	last_infile = NULL;
// 	last_outfile = NULL;
// 	while (ittr_node != cmd_row->end->next)
// 	{
// 		if (ittr_node->type == GREAT || ittr_node->type == APPEND)
// 			last_outfile = ittr_node;
// 		else if (ittr_node->type == LESS || ittr_node->type == HEREDOC)
// 			last_infile = ittr_node;
// 		ittr_node = ittr_node->next;
// 	}
// 	if (last_infile)
// 	{
// 		if (last_infile->next->type == SPACE)
// 			last_infile = last_infile->next;
// 		cmd_row->last_infile = ft_strdup(last_infile->next->value);
// 	}
// 	if (last_outfile)
// 	{
// 		if (last_outfile->next->type == SPACE)
// 			last_outfile = last_outfile->next;
// 		cmd_row->last_outfile = ft_strdup(last_outfile->next->value);
// 	}
// }

/* Extracts the names of input output files into cmd_row type family */
// void	extract_files(t_family *family_ll)
// {
// 	t_family	*ittr_node;

// 	ittr_node = family_ll->next;
// 	while (ittr_node->type != E_CMD)
// 	{
// 		if (ittr_node->type == CMD_ROW)
// 		{
// 			fill_ios(ittr_node);
// 			last_io(ittr_node);
// 			//	if (ittr_node->in_files)
// 			//		print_2d(ittr_node->in_files);
// 			//	if (ittr_node->out_files)
// 			//		print_2d(ittr_node->out_files);
// 			//	if (ittr_node->here_docs)
// 			//		print_2d(ittr_node->here_docs);
// 			//	if (ittr_node->appends)
// 			//		print_2d(ittr_node->appends);
// 		}
// 		ittr_node = ittr_node->next;
// 	}
// 	// printf("%s\n", ittr_node->in_files[0]);
// }

/*
	< input redirection operator:
		takes the file name on the right and uses it as input to the command on the left
		i.e:   command < file
	> output redirection operator
		takes the file name on the right and uses it as the destination for the output
		of the command on the left
*/