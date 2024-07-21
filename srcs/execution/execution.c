/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:32:35 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/21 17:05:22 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int test_var_file(t_files file)
{
	int i;
	i = 0;
	if(file.is_var == 4)
	{
		while(file.path[i] && is_whitespace(file.path[i]) == 1)
			i++;
		if(file.path[i] == '\0')
			return 1;
		else
		{
			while(file.path[i] && is_whitespace(file.path[i]) == 0)
				i++;
			while(file.path[i] && is_whitespace(file.path[i]) == 1)
				i++;
			if(file.path[i] == '\0')
				return (0);
			else if(is_whitespace(file.path[i]) == 0)
				return (1);
		}
	}
	return 0;
}

int handle_fds(t_family *head)
{
	int i = -1;
	t_family *tmp;
	tmp = head;
	while(tmp->files[++i].path)
	{
		if(test_var_file(tmp->files[i]) == 0)
		{
			if(tmp->files[i].type == APPEND)
				tmp->files[i].fd = open(tmp->files[i].path, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if(tmp->files[i].type == LESS)
				tmp->files[i].fd = open(tmp->files[i].path, O_RDONLY);
			if(tmp->files[i].type == GREAT)
				tmp->files[i].fd = open(tmp->files[i].path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if(tmp->files[i].fd < 0)
			{
				perror("minishell_fd");
				return (1);
			}
		}
		else
		{
			printf("ambiguious redirect\n");
			return (1);
		}
	}
	return 0;
}

char	*create_name(char *limiter)
{
	char	*str;
	char	*str2;
	char	*free_var;
	int		i;

	str = "/tmp/";
	str2 = ft_strjoin(".", limiter);
	str = ft_strjoin(str, str2);
	i = 0;
	while (access(str, F_OK) == 0)
	{
		free_var = str;
		str = ft_strjoin(str, ft_itoa(i));
		free(free_var);
		i++;
	}
	return (str);
}

void	here_handle(t_files *file)
{
	t_files	*tmp;
	char	*line;
	int		result;
	char	*str;
	char	*name;

	tmp = file;
	name = create_name(tmp->path);
	tmp->fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	while (1)
	{
		line = get_next_line(0);
		str = ft_strjoin_gnl(tmp->path, "\n");
		if (!line)
			break ;
		result = ft_fcmp(line, str);
		if (result == 0)
			break ;
		write(tmp->fd, line, ft_strlen(line));
		free(line);
		free(str);
	}
	close(tmp->fd);
	tmp->fd = open(name, O_RDONLY);
}

void	handle_heredocs(t_family *head)
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
					here_handle(&tmp->files[i]);
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
		if (tmp->last_infile && ft_fcmp(tmp->files[i].path,
				tmp->last_infile) == 0)
			(tmp->in = tmp->files[i].fd, dup2(tmp->in, STDIN_FILENO));
		if (tmp->last_outfile && ft_fcmp(tmp->files[i].path,
				tmp->last_outfile) == 0)
			(tmp->out = tmp->files[i].fd, dup2(tmp->out, STDOUT_FILENO));
		i++;
	}
}

void	single_command(t_family *cmd, t_token *env, int i, int fork_id)
{
	int in = -1;
	int out = -1;
	char **env_arr;


	(in = dup(STDIN_FILENO), out = dup(STDOUT_FILENO), handle_heredocs(cmd));
	if (handle_fds(cmd) == 1)
        return ;
	(i = -1, get_io_single(cmd));
	if (fake_executionner(cmd, env) == 0)
	{
        (close(cmd->in), close(cmd->out),dup2(in, STDIN_FILENO),close(in));
		(dup2(out, STDOUT_FILENO),close(out));
        return;
	}
    fork_id = fork();
    if(fork_id == -1)
        return ;
    if(fork_id == 0)
    {
		if(!cmd->cmd_path && !cmd->args)
			exit(0);
		else if (!cmd->cmd_path && cmd->args[0])
			(dprintf(2,"minishell: %s: command not found\n",cmd->args[0]),exit(1));
		env_arr = env_decompose(env);
		execve(cmd->cmd_path, cmd->args, env_arr);
		perror("single command execve");
		exit(1);
    }
    (close(cmd->in), close(cmd->out),dup2(in, STDIN_FILENO),close(in));
	(dup2(out, STDOUT_FILENO),close(out));
    wait(NULL);
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
	handle_heredocs(tmp);
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
