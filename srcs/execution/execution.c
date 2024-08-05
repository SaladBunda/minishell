/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:32:35 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/05 15:49:18 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

#define E_D env_decompose

void	handle_errors(t_family *cmd)
{
	struct stat	path_stat;

	if (!cmd->cmd_path && !cmd->args)
		exit(0);
	else if (cmd->args && cmd->args[0] != NULL && (cmd->args[0][0] == '/'
		|| (cmd->args[0][0] == '.' && cmd->args[0][1] == '/')))
	{
		if (stat(cmd->args[0], &path_stat) == -1)
			(write(2, "minishell: no such file or directory:\n", 39),
				edit_global(127), exit(127));
		else if (S_ISDIR(path_stat.st_mode))
			(printf("minishell: %s is a directory.\n", cmd->args[0]),
				edit_global(126), exit(126));
		else if (S_ISREG(path_stat.st_mode) && !(path_stat.st_mode & S_IXUSR))
			(write(2, "\n", 18), edit_global(126), exit(126));
		else if (S_ISREG(path_stat.st_mode) && path_stat.st_mode & S_IXUSR)
		{
			cmd->cmd_path = cmd->args[0];
			return ;
		}
	}
	else if (!cmd->cmd_path && cmd->args[0])
		(dprintf(2, "minishell: %s: command not found\n", cmd->args[0]),
			g_last_exit_status = 127, exit(127));
}

void	waiting_sgl(int *status, int fork_id)
{
	waitpid(fork_id, status, 0);
	if (WIFEXITED(*status))
		g_last_exit_status = WEXITSTATUS(*status);
	if (WIFSIGNALED(*status))
		g_last_exit_status = WTERMSIG(*status) + 128;
}

int	initiate_redirs(t_family *cmd, t_token *env, int *in, int *out)
{
	(ED(in, dup(STDIN_FILENO)), ED(out, dup(STDOUT_FILENO)));
	if (handle_heredocs(cmd, env) == 1)
		return (1);
	if (handle_fds(cmd) == 1)
	{
		(close(*in), close(*out));
		return (1);
	}
	get_io_single(cmd);
	return (0);
}

void	single_command(t_family *cmd, t_token *env, int fork_id, int status)
{
	int		in;
	int		out;

	if (initiate_redirs(cmd, env, &in, &out) == 1)
		return ;
	if ((!cmd->cmd_path && !cmd->args) || fake_ex(cmd, env) == 0)
	{
		(close(cmd->in), close(cmd->out), dup2(in, STDIN_FILENO), close(in));
		(dup2(out, STDOUT_FILENO), close(out));
		return ;
	}
	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN), ED(&fork_id, fork()));
	if (fork_id == -1)
		return ;
	if (fork_id == 0)
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, sigquit_reset));
		handle_errors(cmd);
		(execve(cmd->cmd_path, cmd->args, E_D(env)), perror("execve"));
		if (errno == 2)
			(edit_global(127), exit(127));
		exit(1);
	}
	(close(cmd->in), close(cmd->out), dup2(in, STDIN_FILENO), close(in));
	(dup2(out, STDOUT_FILENO), close(out), waiting_sgl(&status, fork_id));
}

void	execution(t_family *head, t_token *env)
{
	int			i;
	t_family	*tmp;
	t_utils		v;

	v.i = 0;
	i = 0;
	tmp = head->next;
	while (tmp->type != E_CMD)
	{
		if (tmp->type == CMD_ROW)
			i++;
		tmp = tmp->next;
	}
	tmp = head->next;
	if (i == 1)
	{
		single_command(tmp, env, 0, -1);
		return ;
	}
	if (handle_heredocs(tmp, env) == 1)
		return ;
	handle_pipes(head, env, 0, v);
}
