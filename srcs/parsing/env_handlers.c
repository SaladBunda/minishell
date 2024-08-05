/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:17:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/05 19:42:52 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

int	delete_var(t_token *env_head, char *unset_var)
{
	t_token	*matched;
	char	**current_var;

	if (unset_var[0] != '_' && !ft_isalpha(unset_var[0]))
		return (write(2, "unset: ", 8), write(2, unset_var,
				ft_strlen(unset_var)), write(2, ": invalid parameter name\n",
				26), 0);
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
			(free(matched->value), free_darr(current_var), free(matched));
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
			(free(to_free), free_darr(var_value), free_darr(export_var_value));
			return (1);
		}
		free_darr(var_value);
		current_env = current_env->prev;
	}
	free_darr(export_var_value);
	return (0);
}

t_token	*var_exist(t_token *head, char *export_var)
{
	t_token	*ittr;
	char	**vars;

	vars = NULL;
	ittr = head->next;
	while (ittr->type != E_CMD)
	{
		vars = ft_split(ittr->value, '=');
		if (!ft_fcmp(vars[0], export_var))
		{
			free_darr(vars);
			return (ittr);
		}
		free_darr(vars);
		vars = NULL;
		ittr = ittr->next;
	}
	return (NULL);
}

int	_var_export(t_token *new_var, t_token *env_tail, char *export_var)
{
	if (env_overwrite(env_tail, export_var))
		return (1);
	else
	{
		new_var = new_token(ft_strdup(export_var), ENV);
		append_token(env_tail, new_var);
	}
	return (0);
}

int	append_var(t_token *env_head, t_token *env_tail, char *export_var)
{
	t_token	*new_var;
	t_token	*matched;

	new_var = NULL;
	if ((!ft_isalpha(export_var[0]) && export_var[0] != '_'))
		return (printf("export: %s: not a valid identifier\n", export_var),
			g_last_exit_status = 1, 1);
	if (ft_strchr(export_var, '='))
	{
		if (env_overwrite(env_tail, export_var))
			return (0);
		new_var = new_token(ft_strdup(export_var), ENV);
		append_token(env_tail, new_var);
		return (0);
	}
	else
	{
		matched = var_exist(env_head, export_var);
		if (matched && !ft_strchr(export_var, '=') && ft_strchr(matched->value,
				'='))
			return (0);
		if (_var_export(new_var, env_tail, export_var))
			return (0);
	}
	return (1);
}
