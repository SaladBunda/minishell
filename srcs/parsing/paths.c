/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:39:08 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/04 15:01:54 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path_var(t_token *env)
{
	char	*result;
	t_token	*tmp;
	char	*tmp2;

	tmp = env->next;
	while (tmp->type != E_CMD)
	{
		if (ft_strnstr(tmp->value, "PATH", 4))
			break ;
		tmp = tmp->next;
	}
	result = ft_strdup(tmp->value);
	tmp2 = result;
	result = ft_strtrim(result, "PATH=");
	free(tmp2);
	return (result);
}

int	_empty(t_family *token, char *tmp)
{
	if (tmp[0] == '\0')
	{
		token->cmd_path = NULL;
		return (free(tmp), 1);
	}
	return (0);
}

void	treat_path(t_family *token, t_token *env, int i, char *joined)
{
	char	**path_array;
	char	*path_var;
	char	*tmp;

	tmp = token->cmd_path;
	if (_empty(token, tmp))
		return ;
	path_var = get_path_var(env);
	path_array = ft_split(path_var, ':');
	free(path_var);
	if (!path_array)
		return ;
	while (path_array[++i])
	{
		joined = ft_strjoin_cmd(path_array[i], tmp);
		if (access(joined, X_OK) == 0)
		{
			token->cmd_path = joined;
			return ((free_darr(path_array), free(tmp)));
		}
		free(joined);
	}
	(free_darr(path_array), free(tmp));
	token->cmd_path = NULL;
}

void	process_group(t_family **group_ptr, t_token **token_ptr)
{
	t_family	*group;
	t_token		*ittr;
	int			i;

	i = 1;
	group = *group_ptr;
	ittr = *token_ptr;
	while (ittr != group->end->next)
	{
		if (is_empty(ittr) == 0)
		{
			if (ittr->group == COMMAND)
				group->args[0] = ft_strdup(ittr->value);
			if (ittr->type != SPC && ittr->group == PARAM)
				group->args[i++] = ft_strdup(ittr->value);
		}
		ittr = ittr->next;
	}
	group->args[i] = NULL;
	group->cmd_path = ft_strdup(group->args[0]);
}

void	extract_paths(t_family *head, t_token *env)
{
	t_family	*group;
	t_token		*ittr;
	int			i;

	group = head->next;
	while (group->type != E_CMD)
	{
		if (group->type != PIPE_ROW)
		{
			ittr = group->start;
			if (!count_args(ittr, group->end->next))
			{
				group = group->next;
				continue ;
			}
			group->args = malloc((count_args(ittr, group->end->next) + 1)
					* sizeof(char *));
			i = 1;
			process_group(&group, &ittr);
			treat_path(group, env, -1, NULL);
		}
		group = group->next;
	}
}
