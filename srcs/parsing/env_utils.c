/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:09:37 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/05 18:52:31 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*basic_env(t_token *tail, t_token *head, t_token *token)
{
	char	**vars;
	char	*cwd;
	int		i;

	cwd = NULL;
	tail = create_list();
	head = tail->prev;
	vars = malloc((sizeof(char *) * (3 + 1)));
	i = -1;
	cwd = pwd_extract();
	vars[0] = ft_strjoin("PWD=", cwd);
	if (cwd)
		free(cwd);
	vars[1] = ft_strdup("SHLVL=1");
	vars[2] = ft_strdup("_=/usr/bin/env");
	vars[3] = NULL;
	while (vars[++i])
	{
		token = new_token(ft_strdup(vars[i]), ENV);
		if (!token)
			return (NULL);
		append_token(tail, token);
	}
	(free(vars[0]), free(vars[1]), free(vars[2]), free(vars[3]), free(vars));
	return (head);
}

int	env_size(t_token *env_head)
{
	int		i;
	t_token	*node;

	i = 0;
	node = env_head->next;
	while (node->type != E_CMD)
	{
		node = node->next;
		i++;
	}
	return (i);
}

t_token	*env_process(char **env, int flag)
{
	t_token	*tail;
	t_token	*head;
	t_token	*token;
	int		i;

	i = -1;
	tail = create_list();
	head = tail->prev;
	while (env[++i])
	{
		token = new_token(ft_strdup(env[i]), ENV);
		if (!token)
			return (NULL);
		append_token(tail, token);
	}
	if (flag)
		free_darr(env);
	return (head);
}

/* Turns linked list into a 2d arr */
char	**env_decompose(t_token *env_head)
{
	int		i;
	int		ll_size;
	char	**envp;
	t_token	*env_node;

	envp = NULL;
	ll_size = env_size(env_head);
	i = 0;
	envp = (char **)malloc(sizeof(char *) * (ll_size + 1));
	env_node = env_head->next;
	while (env_node->type != E_CMD)
	{
		envp[i] = ft_strdup(env_node->value);
		env_node = env_node->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
