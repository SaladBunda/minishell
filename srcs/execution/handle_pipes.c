/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:05:45 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/21 19:14:49 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_io(t_family *cmd_row)
{
	t_family	*tmp;
	int			i;

	i = 0;
	tmp = cmd_row;
	tmp->in = 0;
	tmp->out = 1;
	tmp->prev_fd = -1;
	while (tmp->files[i].path)
	{
		printf("current fd: %d\n", tmp->files[i].fd);
		if (tmp->last_infile && ft_fcmp(tmp->files[i].path,
				tmp->last_infile) == 0)
			tmp->in = tmp->files[i].fd;
		if (tmp->last_outfile && ft_fcmp(tmp->files[i].path,
				tmp->last_outfile) == 0)
			tmp->out = tmp->files[i].fd;
		i++;
	}
}

int	nof_pipes(t_family *head)
{
	int			i;
	t_family	*ittr;

	i = 0;
	ittr = head->next;
	while (ittr->type != E_CMD)
	{
		if (ittr->type == CMD_ROW)
			i++;
		ittr = ittr->next;
	}
	return (i);
}

void	close_fds(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}

void	save_pipe(int *prev_fd, int *fds)
{
	close(*prev_fd);
	*prev_fd = fds[0];
	close(fds[1]);
}

void	process_cmd(t_family *cmd_row, t_token *env, int *fds, int pipes, int i,
		int __unused prev_fd, int saved)
{
	if (i == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
	}
	else if (i == pipes - 1)
	{
		if (saved != -1)
			dup2(saved, STDIN_FILENO);
	}
	else
	{
		//if (saved != -1)
			dup2(saved, STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
	}
	if (cmd_row->in != 0)
		(dup2(cmd_row->in, STDIN_FILENO), close(cmd_row->in));
	if (cmd_row->out != 1)
		(dup2(cmd_row->out, STDOUT_FILENO), close(cmd_row->out));
	close(saved);
	close_fds(fds);
	if(!cmd_row->cmd_path && !cmd_row->args)
			exit(0);
		else if (!cmd_row->cmd_path && cmd_row->args[0])
			(dprintf(2,"minishell: %s: command not found\n",cmd_row->args[0]),exit(1));
	if (fake_executionner(cmd_row, env) == 0)
		exit(0);
	if (execve(cmd_row->cmd_path, cmd_row->args, env_decompose(env)) == -1)
		perror("execve");
	exit(1);
}

void	handle_pipes(t_family *cmd_row, t_token *env)
{
	t_family *ittr_node;
	int i;
	int pipes;
	int ps;
	int fds[2];
	int prev_fd = 0;
	int saved = -1;

	pipes = nof_pipes(cmd_row);
	ittr_node = cmd_row->next;
	i = 0;
	while (ittr_node->type != E_CMD)
	{
		if (ittr_node->type == CMD_ROW)
		{
			pipe(fds);
			ps = fork();
			if (!ps)
			{
				handle_fds(ittr_node);
				get_io(ittr_node);
				process_cmd(ittr_node, env, fds, pipes, i, prev_fd, saved);
			}
			else
			{
				close(saved);
				//if (saved == -1)
				saved = fds[0];
				//else
				//	saved = -1;
				close(fds[1]);
				// close(fds[0]);
				// close_fds(fds);
				//  save_pipe(&prev_fd, fds);
			}
			i++;
		}
		ittr_node = ittr_node->next;
	}
	 close_fds(fds);
	close(saved);
	while (wait(NULL) > 0)
		;
}