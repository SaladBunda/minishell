/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:17:39 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/25 20:09:39 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_cmd(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	ptr = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 2));
	if (!ptr)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = '/';
	while (i < (ft_strlen(s1) + ft_strlen(s2) + 1))
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

int test_var_empty(t_token *token)
{
	int i = 0;
	if(token->type != VAR)
		return 0;
	else
	{
		while(token->value[i] && is_whitespace(token->value[i]) == 1)
			i++;
		if(token->value[i] == '\0')
			return 1;	
	}
	return 0;
}

int count_args(t_token *start, t_token *end)
{
	t_token *tmp;
	tmp = start;
	int count = 0;
	while(tmp != end)
	{
		if (tmp->type != SPACE && (tmp->group == COMMAND || tmp->group == PARAM) && test_var_empty(tmp) == 0)
			count++;
		tmp = tmp->next;
	}
	return count;
}

void print_args(t_family *head) {
    t_family *tmp = head;

    while (tmp->type != E_CMD) {
        if (tmp->type != PIPE_ROW) {
            printf("Args for family node %p:\n", tmp);
			printf("cmd_path:%s\n",tmp->cmd_path);
            for (int i = 0; tmp->args[i] != NULL; i++) {
                printf("%s\n", tmp->args[i]);
            }
        }
        tmp = tmp->next;
    }
}

char *get_path_var(t_token *env)
{
	char *result;
	t_token *tmp;
	char *tmp2;
	
	tmp =env ->next;
	while(tmp->type != E_CMD)
	{
		if(ft_strnstr(tmp->value, "PATH", 4))
			break ;
		tmp = tmp->next;
	}
	result = ft_strdup(tmp->value);
	tmp2 = result;
	result = ft_strtrim(result, "PATH=");
	free(tmp2);
	return (result);
}

void treat_path(t_family *token, t_token *env)
{
	int i = -1;
	char **path_array;
	char *path_var;
	char *tmp = token->cmd_path;
	char *joined = NULL;
	if(tmp[0] == '\0')
	{
		token->cmd_path = NULL;
		return ;
	}
	(path_var = get_path_var(env), path_array = ft_split(path_var, ':'));
	free(path_var);
	if(!path_array)
		return ;
	if(access(token->cmd_path, X_OK) == 0)
		return ;
	while(path_array[++i])
	{
		joined = ft_strjoin_cmd(path_array[i], tmp);
		if(access(joined, R_OK) == 0)
		{
			token->cmd_path = joined;
			free_darr(path_array);
			free(tmp);
			return ;
		}
		free(joined);
	}
	free_darr(path_array);
	free(tmp);
	token->cmd_path = NULL;
}

void	extract_paths(t_family *head, t_token *env)
{
	t_family *tmp;
	t_token *ittr;
	int i;
	int arg_count;

	(tmp = head->next, 	ittr = head->next->start);
	while(tmp->type != E_CMD)
	{
		if(tmp->type != PIPE_ROW)
		{
			(ittr = tmp->start, arg_count = count_args(ittr, tmp->end->next));
			if(!arg_count)
			{
				tmp = tmp->next;
				continue ;
			}
			tmp->args = malloc((arg_count + 1) * sizeof(char *));
			i = 1;
			while(ittr != tmp->end->next)
			{
				if(test_var_empty(ittr) == 0)
				{
					if(ittr->group == COMMAND)
						tmp->args[0] = ft_strdup(ittr->value); 
					if(ittr->type != SPACE && ittr->group == PARAM)
						tmp->args[i++] = ft_strdup(ittr->value);
				}
				ittr = ittr->next;
			}
			(tmp->args[i] = NULL, tmp->cmd_path = ft_strdup(tmp->args[0]), treat_path(tmp, env));
		}
		tmp = tmp->next;
	}
}