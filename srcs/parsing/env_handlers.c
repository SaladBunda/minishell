/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:17:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/11 14:39:55 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	delete_var(t_token *env_head, char *unset_var)
{
	t_token	*matched;
	char	**current_var;

	if (unset_var[0] != '_' && !ft_isalpha(unset_var[0]))
		return (0);
	matched = env_head->next;
	while (matched && matched->value)
	{
		current_var = ft_split(matched->value, '=');
		if (!ft_fcmp(current_var[0], unset_var))
		{
			matched->next->prev = matched->prev;
			matched->prev->next = matched->next;
			matched->prev = NULL;
			matched->next = NULL;
			free(matched->value);
			free_darr(current_var);
			free(matched);
			return (1);
		}
		free_darr(current_var);
		matched = matched->next;
	}
	return (0);
}

int	env_overwrite(t_token *env_tail, char *export_var)
{
	char	**var_value;
	char	**export_var_value;
	t_token	*current_env;
	char	*to_free;

	to_free = NULL;
	current_env = env_tail->prev;
	var_value = NULL;
	export_var_value = ft_split(export_var, '=');
	while (current_env->type != S_CMD)
	{
		var_value = ft_split(current_env->value, '=');
		if (!ft_fcmp(export_var_value[0], var_value[0]))
		{
			to_free = current_env->value;
			current_env->value = ft_strdup(export_var);
			free(to_free);
			free_darr(var_value);
			free_darr(export_var_value);
			return (1);
		}
		free_darr(var_value);
		current_env = current_env->prev;
	}
	free_darr(export_var_value);
	return (0);
}

int	append_var(t_token *env_head, t_token *env_tail, char *export_var)
{
	t_token	*new_var;

	new_var = NULL;
	(void)env_head;
	if ((!ft_isalpha(export_var[0]) && export_var[0] != '_'))
		return (printf("export: %s: not a valid identifier", export_var), 0);
	if (ft_strchr(export_var, '='))
	{
		if (env_overwrite(env_tail, export_var))
			return (1);
		new_var = new_token(export_var, ENV);
		append_token(env_tail, new_var);
		return (1);
	}
	else
	{
		if (env_overwrite(env_tail, export_var))
			return (1);
		else
		{
			new_var = new_token(export_var, ENV);
			append_token(env_tail, new_var);
		}
	}
	return (1);
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
		//! protect malloc failure plz
		append_token(tail, token);
	}
	if (flag)
		free_darr(env);
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
