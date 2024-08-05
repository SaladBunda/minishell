/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:21:53 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/08/04 12:06:44 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

char	*code_handler2(char *string, int *i, int *j)
{
	int		new_len;
	char	*code;
	char	*new_value;
	int		n;
	int		l;

	n = *i + 2;
	l = -1;
	code = ft_itoa(g_last_exit_status);
	new_len = ft_strlen(string) - 2 + ft_strlen(code);
	new_value = malloc(sizeof(char) * (new_len + 1));
	ft_memset((void *)new_value, 0, new_len);
	while (++l < *j)
		new_value[l] = string[l];
	while (l - *j < (int)ft_strlen(code))
	{
		new_value[l] = code[l - *j];
		l++;
	}
	*i = l - 1;
	while (l < new_len)
		new_value[l++] = string[n++];
	return (new_value[l] = '\0', free(string), new_value);
}

int	expand_line(t_token *env, char **str, int i, int j)
{
	char	*var_value;

	while ((*str)[++i])
	{
		if ((*str)[i] == '$')
		{
			j = i;
			if ((*str)[i + 1] && (*str)[i + 1] == '?')
			{
				*str = code_handler2(*str, &i, &j);
				continue ;
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

void	inside_fork(t_files *file, t_token *env, int status, int fork_id)
{
	char	*line;
	char	*str;

	(void)status;
	(void)fork_id;
	while (1)
	{
		signal(SIGINT, heredoc_sigg);
		line = readline(">");
		if (!line)
			return ;
		line = ft_strjoin_gnl(line, "\n");
		str = ft_strjoin_gnl(file->lim, "\n");
		if (ft_fcmp(line, str) == 0)
			return ;
		if (file->is_var == 2)
			expand_line(env, &line, -1, 0);
		(write(file->fd, line, ft_strlen(line)), free(line), free(str));
	}
}

int	here_handle(t_files *file, t_token *env, int status, int fork_id)
{
	(signal(SIGINT, SIG_IGN), _edit(&fork_id, fork()));
	if (fork_id == -1)
		return (perror("fork"), 1);
	if (fork_id == 0)
	{
		file->fd = open(file->path, O_CREAT | O_TRUNC | O_RDWR, 0644);
		signal(SIGINT, SIG_DFL);
		inside_fork(file, env, status, fork_id);
		(close(file->fd), exit(0));
	}
	(waitpid(fork_id, &status, 0), _edit(&status, status / 256));
	if (WIFSIGNALED(status))
		return (g_last_exit_status = 1, 1);
	return (0);
}

int	handle_heredocs(t_family *head, t_token *env)
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
					if (here_handle(&tmp->files[i], env, 0, -1) == 1)
						return (1);
					tmp->files[i].fd = open(tmp->files[i].path, O_RDONLY);
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
