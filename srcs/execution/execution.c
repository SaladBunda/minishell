/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:32:35 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/17 17:01:09 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void single_command(t_family *family, t_token *env)
{
	t_family *tmp;
	tmp = family->next;
	int fork_id;
    fork_id = fork();
    if(fork_id == -1)
        return ;
    if(fork_id == 0)
    {
        int infile = -1;
        int outfile = -1;
        if(tmp->out_files)
        {
            outfile = open(tmp->out_files[0], O_CREAT | O_TRUNC | O_WRONLY, 0666);
            if(outfile > 0)
                dup2(outfile, STDOUT_FILENO);
            else
            {
                perror("outfile");
                exit(1);
            }
        }
        if(tmp->in_files)
        {
            infile = open(tmp->in_files[0], O_RDONLY);
            if(infile > 0)
                dup2(infile, STDIN_FILENO);
            else
            {
                perror("infile");
                exit(1);
            }
        }
        if(outfile > 0)
            dup2(outfile, STDOUT_FILENO);
		if(fake_executionner(family, env) == 0)
			return ;
		(void)env;
		char **env_arr = env_decompose(env);
        ft_putstr_fd("Execution\n", 1);
		if(!tmp->cmd_path)
			exit(0);
		printf("%d\n",execve(tmp->cmd_path, tmp->args, env_arr));
		perror("execve:");
    }
    wait(NULL);
}

void handle_fds(t_family *head)
{
	int i = 0;
	t_family *tmp;
	tmp = head;
	while(tmp->files[i].path)
	{
		if(tmp->files[i].type == APPEND)
			tmp->files[i].fd = open(tmp->files[i].path, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if(tmp->files[i].type == LESS)
			tmp->files[i].fd = open(tmp->files[i].path, O_RDONLY);
		if(tmp->files[i].type == GREAT)
			tmp->files[i].fd = open(tmp->files[i].path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if(tmp->files[i].fd < 0)
		{
			perror("minishell");
			exit(1);
		}
		printf("fd of %s:%d\n",tmp->files[i].path,tmp->files[i].fd);
		i++;
	}
}

char *create_name(char *limiter)
{
	char *str;
	char *str2;
	char *free_var;
	str = "/tmp/";
	str2 = ft_strjoin(".",limiter);
	str = ft_strjoin(str, str2);
	int i = 0;
	while(access(str, F_OK) == 0)
	{
		free_var = str;
		str = ft_strjoin(str,ft_itoa(i));
		free(free_var);
		i++;
	}
	return str;
}

void here_handle(t_files *file)
{
	t_files *tmp;
	tmp = file;
	char	*line;
	int		result;
	char	*str;
	char *name;
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

void handle_heredocs(t_family *head)
{
	t_family *tmp;
	int i;
	tmp = head;
	while(tmp->type != E_CMD)
	{
		i = 0;
		if(tmp->type == CMD_ROW)
		{
			while(tmp->files[i].path)
			{
				if(tmp->files[i].type == HEREDOC)
					here_handle(&tmp->files[i]);
				i++;
			}
		}
		tmp = tmp->next;
	}
}

void    execution(t_family *head, t_token *env)
{
	int i = 0;

	t_family *tmp;
    tmp = head->next;
	while(tmp->type != E_CMD)
	{
		if(tmp->type == CMD_ROW)
			i++;
		tmp = tmp->next;
	}
	tmp = head->next;
	if (i == 1)
	{
		single_command(head, env);
		return ;
	}
	handle_heredocs(tmp);
	int fork_id;
	fork_id = fork();
    if(fork_id == -1)
        return ;
    if(fork_id == 0)
    {
		handle_fds(tmp);
		i = 0;
		while(tmp->files[i].path)
		{
			if(tmp->last_infile && ft_fcmp(tmp->files[i].path, tmp->last_infile) == 0)
				dup2(tmp->files[i].fd,STDIN_FILENO);
			if(tmp->last_outfile && ft_fcmp(tmp->files[i].path, tmp->last_outfile) == 0)
				dup2(tmp->files[i].fd,STDOUT_FILENO);
			i++;
		}
        char **env_arr = env_decompose(env);
        ft_putstr_fd("Execution\n", 2);
		if(fake_executionner(tmp, env) == 0)
			return ;
		if(!tmp->cmd_path)
			exit(0);
        printf("%d\n",execve(tmp->cmd_path, tmp->args, env_arr));
        perror("execve");
    }
    wait(NULL);

}

//simulation for a single family command, and also work for 1 infile / outfile / append file/ heredoc still not working
//if there is a infile inside the in_file double we check it with open if it opens we dup2 with STDIN_FILENO if not it an error file not found/persmission denied
//if no infile inside the double array we just leave it as it is which means it reads from standart input 0
//same for outfiles
