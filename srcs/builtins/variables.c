/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:41:39 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/28 18:30:12 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_listing(t_token *env_list)
{
	t_token	*current_var;
	int		i;
	char	*var_name;
	current_var = env_list->next;
	i = 0;
	while (current_var->type != E_CMD)
	{
		printf("declare -x ");
		if (current_var->value && !ft_strchr(current_var->value, '='))
			printf("%s\n", current_var->value);
		else		
		{
			i = 0;
			while (current_var->value[i] && current_var->value[i] != '=')
				i++;
			var_name = ft_substr(current_var->value, 0, i + 1);
			printf("%s", var_name);
			free(var_name);
			printf("\"%s\"\n", ft_strchr(current_var->value, '=') + 1);
		}
		current_var = current_var->next;
	}
}

void	export_builtin(t_token *env_list, t_family *cmd_family)
{
	char **args;
	int i;

	i = 0;
	args = cmd_family->args;
	while (args[i])
		i++;
	if (i == 1)
		export_listing(env_list);
	else
	{
		i = 1;
		while (args[i])
		{
			append_var(env_list, list_tail(env_list), args[i]);
			i++;
		}
	}
}

void	env_builtin(t_token *env_list /* , t_family *cmd_family */)
{
	t_token	*node;

	node = env_list->next;
	while (node->type != E_CMD)
	{
		if (node->value && ft_strchr(node->value, '='))
			printf("%s\n", node->value);
		node = node->next;
	}
}

void	unset_builtin(t_token *env_list, t_family *cmd_family)
{
	char	**args;
	int		i;

	i = 1;
	args = cmd_family->args;
	while (args[i])
	{
		delete_var(env_list, args[i]);
		i++;
	}
}

int	variables_handler(t_token *env_list, t_family *cmd_family)
{
	t_token	*builtin;

	builtin = cmd_family->start;
	if (ft_fcmp(builtin->value, "unset") == 0)
		unset_builtin(env_list, cmd_family);
	else if (ft_fcmp(builtin->value, "export") == 0)
		export_builtin(env_list, cmd_family);
	else if (ft_fcmp(builtin->value, "env") == 0)
		env_builtin(env_list /* , cmd_family */);
	else
		return (1);
	return (0);
}

/*
-> export would add a variable regardless whether it has been assigned a value
	check at first if the node is the start and the end
	then simply display the list of variables
	if there's an equal sign then a value is null
	otherwise we just display the variable
	-> env would only display the variables that have
	Go through each node within the CMD_ROW family
	for each node
*/
