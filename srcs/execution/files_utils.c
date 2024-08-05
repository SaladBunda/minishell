/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:27:08 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/08/05 18:20:27 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

int	test_var_file(t_files file)
{
	int	i;

	i = 0;
	if (file.is_var == 4)
	{
		while (file.path[i] && is_whitespace(file.path[i]) == 1)
			i++;
		if (file.path[i] == '\0')
			return (1);
		else
		{
			while (file.path[i] && is_whitespace(file.path[i]) == 0)
				i++;
			while (file.path[i] && is_whitespace(file.path[i]) == 1)
				i++;
			if (file.path[i] == '\0')
				return (0);
			else if (is_whitespace(file.path[i]) == 0)
				return (1);
		}
	}
	return (0);
}

int	handle_fds(t_family *head)
{
	int			i;
	t_family	*tmp;

	i = -1;
	tmp = head;
	while (tmp->files[++i].lim)
	{
		if (test_var_file(tmp->files[i]) == 0)
		{
			if (tmp->files[i].type == APPEND)
				tmp->files[i].fd = open(tmp->files[i].lim,
						O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (tmp->files[i].type == LESS)
				tmp->files[i].fd = open(tmp->files[i].lim, O_RDONLY);
			if (tmp->files[i].type == GREAT)
				tmp->files[i].fd = open(tmp->files[i].lim,
						O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (tmp->files[i].fd < 0)
				return (edit_global(1), perror("minishell_fd"), 1);
		}
		else
			return (write(2, "ambigiuous redirect\n", 20), 1);
	}
	return (0);
}

void	get_io_single(t_family *cmd_row)
{
	t_family	*tmp;
	int			i;

	i = 0;
	tmp = cmd_row;
	tmp->in = -1;
	tmp->out = -1;
	tmp->prev_fd = -1;
	while (tmp->files[i].path)
	{
		if (tmp->last_in && (tmp->files[i].type == HEREDOC
				|| tmp->files[i].type == LESS) && ft_fcmp(tmp->files[i].lim,
				tmp->last_in) == 0)
			(ED(&tmp->in, tmp->files[i].fd), dup2(tmp->in, STDIN_FILENO));
		if (tmp->last_out && (tmp->files[i].type == APPEND
				|| tmp->files[i].type == GREAT) && ft_fcmp(tmp->files[i].lim,
				tmp->last_out) == 0)
			(ED(&tmp->out, tmp->files[i].fd), dup2(tmp->out, STDOUT_FILENO));
		i++;
	}
}
