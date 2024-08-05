/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:05:45 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/05 15:46:29 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

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
		if (tmp->last_in && (tmp->files[i].type == HEREDOC
				|| tmp->files[i].type == LESS) && ft_fcmp(tmp->files[i].lim,
				tmp->last_in) == 0)
			tmp->in = tmp->files[i].fd;
		if (tmp->last_out && (tmp->files[i].type == APPEND
				|| tmp->files[i].type == GREAT) && ft_fcmp(tmp->files[i].lim,
				tmp->last_out) == 0)
			tmp->out = tmp->files[i].fd;
		i++;
	}
}

void	process_cmd(t_family *cmd_row, t_token *env, t_utils var)
{
	if (var.i == 0)
		dup2(var.fds[1], STDOUT_FILENO);
	else if (var.i == var.pipes - 1)
	{
		if (var.saved != -1)
			dup2(var.saved, STDIN_FILENO);
	}
	else
		(dup2(var.saved, STDIN_FILENO), dup2(var.fds[1], STDOUT_FILENO));
	if (cmd_row->in != 0)
		(dup2(cmd_row->in, STDIN_FILENO), close(cmd_row->in));
	if (cmd_row->out != 1)
		(dup2(cmd_row->out, STDOUT_FILENO), close(cmd_row->out));
	(close(var.saved), close_fds(var.fds));
	if ((!cmd_row->cmd_path && !cmd_row->args) || fake_ex(cmd_row, env) == 0)
		exit(g_last_exit_status);
	handle_errors(cmd_row);
	execve(cmd_row->cmd_path, cmd_row->args, env_decompose(env));
	perror("minishell");
	if (errno == 2)
		(edit_global(127), exit(127));
	g_last_exit_status = 1;
	exit(1);
}

void	wtng(int pipes, int *status, pid_t pss[])
{
	int	i;

	i = 0;
	while (i < pipes)
	{
		waitpid(pss[i], status, 0);
		if (WIFEXITED(*status))
			g_last_exit_status = WEXITSTATUS(*status);
		if (WIFSIGNALED(*status))
			g_last_exit_status = WTERMSIG(*status) + 128;
		i++;
	}
}

int	handle_pipes(t_family *cmd_row, t_token *env, int status, t_utils v)
{
	pid_t	pss[ARG_MAX];

	(_edit(&v.i, 0), _edit(&v.saved, -1), _edit(&status, 0));
	_edit(&v.pipes, nof_pipes(cmd_row));
	while (cmd_row->type != E_CMD)
	{
		if (cmd_row->type == CMD_ROW)
		{
			if (pipe(v.fds) == -1)
				return (perror("pipe"), edit_global(1), 1);
			(signals_init(1), _edit(&pss[v.i], fork()));
			if (!pss[v.i])
			{
				(signal(SIGINT, SIG_DFL), signal(SIGQUIT, sigquit_reset));
				if (handle_fds(cmd_row) == 1)
					(edit_global(1), exit(1));
				(get_io(cmd_row), process_cmd(cmd_row, env, v));
			}
			else if (pss[v.i] < 0)
				return (edit_global(1), _edit(&status, -1), perror("fork"), 1);
			(close(v.saved), _edit(&v.saved, v.fds[0]), close(v.fds[1]), v.i++);
		}
		cmd_row = cmd_row->next;
	}
	return (wtng(v.pipes, &status, pss), close_fds(v.fds), close(v.saved), 1);
}
