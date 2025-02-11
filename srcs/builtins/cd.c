/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:48:24 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/08/05 20:49:25 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

char	*get_replacement(char *var, char *old_path)
{
	char	*prefixe;
	char	buffer[1024];
	char	*duplication;
	char	*result;

	getcwd(buffer, 1024);
	duplication = ft_strdup(buffer);
	prefixe = ft_strdup(var);
	result = NULL;
	if (ft_fcmp(var, "PWD="))
		result = ft_strjoin(var, old_path);
	else if (ft_fcmp(var, "OLDPWD="))
		result = ft_strjoin(var, duplication);
	free(duplication);
	free(prefixe);
	return (result);
}

char	*get_home(t_token *env)
{
	t_token	*tmp;
	char	*var_name;
	char	*str;

	str = NULL;
	tmp = env->next;
	while (tmp->type != E_CMD)
	{
		var_name = get_var_name(tmp->value);
		if (ft_fcmp("HOME", var_name) == 0)
			str = get_var_value(tmp->value);
		free(var_name);
		tmp = tmp->next;
	}
	if (str != NULL)
		return (str);
	else
		return (g_last_exit_status = 1, write(2, "HOME not set\n", 13), NULL);
}

void	add_oldpwd(t_token *env, char *old_path, int flag)
{
	char	*str;

	str = NULL;
	str = ft_strjoin("OLDPWD=", old_path);
	if (!str)
		return ;
	if (flag == 0)
		append_var(env, list_tail(env), str);
	free(str);
}

void	edit_env(t_token *env, char *old_path)
{
	t_token	*tmp;
	char	*var_name;
	int		flag;

	flag = 0;
	tmp = env->next;
	while (tmp->type != E_CMD)
	{
		var_name = get_var_name(tmp->value);
		if (ft_fcmp("PWD", var_name) == 0)
		{
			free(tmp->value);
			tmp->value = get_replacement("PWD=", old_path);
		}
		if (ft_fcmp("OLDPWD", var_name) == 0)
		{
			flag = 1;
			free(tmp->value);
			tmp->value = get_replacement("OLDPWD=", old_path);
		}
		free(var_name);
		tmp = tmp->next;
	}
	add_oldpwd(env, old_path, flag);
}

void	cd_builtin(t_family *token, t_token *env)
{
	t_family	*tmp;
	char		*old_path;
	char		oldpath[1024];
	char		*home;

	tmp = token;
	home = NULL;
	getcwd(oldpath, 1024);
	old_path = ft_strdup(oldpath);
	if (!token->args[1])
	{
		home = get_home(env);
		if (home == NULL)
			return (free(old_path));
		chdir(home);
		(edit_env(env, old_path), free(old_path), free(home), g_last_exit_status = 0/* , edit_global(0) */);
	}
	else
	{
		if (chdir(tmp->args[1]) != 0)
			(printf("minishell: No such file or directory\n"), g_last_exit_status = 1/* , edit_global(1) */);
		else
			edit_env(env, old_path);
		(free(old_path),g_last_exit_status = 0 /* edit_global(0) */);
	}
}
