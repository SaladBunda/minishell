/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:32:35 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/28 10:53:46 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int g_last_exit_status;

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
	while (tmp->files[++i].path)
	{
		if (test_var_file(tmp->files[i]) == 0)
		{
			if (tmp->files[i].type == APPEND)
				tmp->files[i].fd = open(tmp->files[i].path,
						O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (tmp->files[i].type == LESS)
				tmp->files[i].fd = open(tmp->files[i].path, O_RDONLY);
			if (tmp->files[i].type == GREAT)
				tmp->files[i].fd = open(tmp->files[i].path,
						O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (tmp->files[i].fd < 0)
			{
				perror("minishell_fd");
				return (1);
			}
		}
		else
		{
			// printf("ambiguious redirect\n");
			write(2,"ambigiuous redirect\n",20);
			return (1);
		}
	}
	return (0);
}

// char	*create_name(char *limiter)
// {
// 	char	*str;
// 	char	*str2;
// 	char	*free_var;
// 	int		i;

// 	str = "/tmp/";
// 	str2 = ft_strjoin(".", limiter);
// 	str = ft_strjoin(str, str2);
// 	i = 0;
// 	while (access(str, F_OK) == 0)
// 	{
// 		free_var = str;
// 		str = ft_strjoin(str, ft_itoa(i));
// 		free(free_var);
// 		i++;
// 	}
// 	return (str);
// }

void	heredoc_sigg(int sig)
{
	(void)sig;
	printf("\n");
	exit(1);
}

int	nof_var2(char *value)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	while (value[i])
	{
		if (value[i] && value[i + 1] && value[i] == '$' && value[i + 1] == '?')
		{
			number += 1;
			i++;
		}
		i++;
	}
	return (number);
}

void	code_handler2(char **string)
{
	int		total_len;
	int		itoa_len;
	int		nof_vars;
	int		new_len;
	char	*code;
	char	*new_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	itoa_len = ft_strlen(ft_itoa(g_last_exit_status));
	total_len = ft_strlen(*string);
	nof_vars = nof_var2(*string);
	code = ft_itoa(g_last_exit_status);
	new_len = total_len - (nof_vars * 2) + (itoa_len * nof_vars) + 1;
	new_value = malloc(sizeof(char) * (new_len + 1));
	 ft_memset((void *)new_value, 0, new_len);
	while (i < new_len)
	{
		if ((*string)[i] && (*string)[i+1] && (*string)[i] == '$'
			&& (*string)[i + 1] == '?')
		{
			ft_memcpy(new_value + j, (void *)code, itoa_len);
			i += 2;
			j += itoa_len;
		}
		else
		{
			new_value[j] = (*string)[i];
			i++;
			j++;
		}
	}
	new_value[i] = '\0';
	free((*string));
	(*string) = new_value;
}

int	expand_line(t_token *env, char **str, int i, int j)
{
	char	*var_value;

	while (str[++i])
	{
		if ((*str)[i] == '$')
		{
			if ((*str)[i + 1] && (*str)[i + 1] == '?')
			{
				code_handler2(str);
				break ;
			}
			j = i;
			var_name(*str, &i, 0);
			if (i != j)
			{
				var_value = search_replace(*str, j, i, env);
				*str = substitution2(&i, &j, var_value, *str);
				free(var_value);
			}
		}
	}
	return (0);
}

void	here_handle(t_files *file, t_token *env)
{
	t_files	*tmp;
	char	*line;
	int		result;
	char	*str;

	int fork_id;
	tmp = file;
	signal(SIGINT, SIG_IGN);
	fork_id = fork();
	if(fork_id == -1)
		return ;
	if(fork_id == 0)
	{
		tmp->fd = open(tmp->path, O_CREAT | O_TRUNC | O_RDWR, 0644);
		signal(SIGINT, SIG_IGN);
		while (1)
		{
			signal(SIGINT, heredoc_sigg);
			line = get_next_line(0);
			str = ft_strjoin_gnl(tmp->lim, "\n");
			if (!line)
				break ;
			result = ft_fcmp(line, str);
			if (result == 0)
				break ;
			if(tmp->is_var == 2)
				expand_line(env, &line, -1, 0);
			(write(tmp->fd, line, ft_strlen(line)), free(line),free(str));
		}
		(close(tmp->fd),exit(0));
	}
	wait(NULL);
}

void	handle_heredocs(t_family *head, t_token *env)
{
	t_family	*tmp;
	int			i;

	tmp = head;
	while (tmp->type != E_CMD)
	{
		i = 0;
		if (tmp->type == CMD_ROW)
		{
			while (tmp->files[i].path)
			{
				if (tmp->files[i].type == HEREDOC)
				{
					here_handle(&tmp->files[i],env);
					tmp->files[i].fd = open(tmp->files[i].path, O_RDONLY);
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
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
		if (tmp->last_infile && ft_fcmp(tmp->files[i].lim,
				tmp->last_infile) == 0)
			(tmp->in = tmp->files[i].fd, dup2(tmp->in, STDIN_FILENO));
		if (tmp->last_outfile && ft_fcmp(tmp->files[i].lim,
				tmp->last_outfile) == 0)
			(tmp->out = tmp->files[i].fd, dup2(tmp->out, STDOUT_FILENO));
		i++;
	}
}

void	single_command(t_family *cmd, t_token *env, int i, int fork_id)
{
	int		in;
	int		out;
	char	**env_arr;
	int status;

	in = -1;
	out = -1;
	(in = dup(STDIN_FILENO), out = dup(STDOUT_FILENO), handle_heredocs(cmd, env));
	if (handle_fds(cmd) == 1)
	{
		close(in);
		close(out);
		return ;
	}
	(i = -1, get_io_single(cmd));
	if ((!cmd->cmd_path && !cmd->args) || fake_executionner(cmd, env) == 0)
	{
		(close(cmd->in), close(cmd->out), dup2(in, STDIN_FILENO), close(in));
		(dup2(out, STDOUT_FILENO), close(out));
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	// if (fake_executionner(cmd, env) == 0)
	// {
	// 	(close(cmd->in), close(cmd->out), dup2(in, STDIN_FILENO), close(in));
	// 	(dup2(out, STDOUT_FILENO), close(out));
	// 	return ;
	// }
	fork_id = fork();
	if (fork_id == -1)
		return ;
	if (fork_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, sigquit_reset);
		if (!cmd->cmd_path && !cmd->args)
			exit(0);
		else if (!cmd->cmd_path && cmd->args[0])
			(dprintf(2, "minishell: %s: command not found\n", cmd->args[0]),
				g_last_exit_status = 127,exit(127));
		env_arr = env_decompose(env);
		execve(cmd->cmd_path, cmd->args, env_arr);
		perror("execve");
		exit(1);
	}
	(close(cmd->in), close(cmd->out), dup2(in, STDIN_FILENO), close(in));
	(dup2(out, STDOUT_FILENO), close(out));
	waitpid(fork_id, &status, 0);
	if (WIFEXITED(status))
		g_last_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_last_exit_status = WTERMSIG(status) + 128;
}

void	execution(t_family *head, t_token *env)
{
	int			i;
	t_family	*tmp;

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
		single_command(tmp, env, -1, 0);
		return ;
	}
	handle_heredocs(tmp,env);
	handle_pipes(head, env);
	// fork_id = fork();
	// if (fork_id == -1)
	//	return ;
	// if (fork_id == 0)
	//{
	//	handle_fds(tmp);
	//	i = 0;
	//	while (tmp->files[i].path)
	//	{
	//		if (tmp->last_infile && ft_fcmp(tmp->files[i].path,
	//				tmp->last_infile) == 0)
	//			dup2(tmp->files[i].fd, STDIN_FILENO);
	//		if (tmp->last_outfile && ft_fcmp(tmp->files[i].path,
	//				tmp->last_outfile) == 0)
	//			dup2(tmp->files[i].fd, STDOUT_FILENO);
	//		i++;
	//	}
	//	env_arr = env_decompose(env);
	//	ft_putstr_fd("Execution\n", 2);
	//	if (fake_executionner(tmp, env) == 0)
	//		return ;
	//	if (!tmp->cmd_path)
	//		exit(0);
	//	printf("%d\n", execve(tmp->cmd_path, tmp->args, env_arr));
	//	perror("execve");
	// }
}

// simulation for a single family command, and also work for 1 infile / outfile
// append file/ heredoc still not working
// if there is a infile inside the in_file double we check it with open if it opens we dup2 with STDIN_FILENO if not it an error file not found/persmission denied
// if no infile inside the double array we just leave it as it is which means it reads from standart input 0
// same for outfiles
