/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:41:39 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/14 11:29:26 by ael-maaz         ###   ########.fr       */
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
	t_token	*current_token;

	current_token = cmd_family->start->next;
	if (current_token->type == SPACE)
		current_token = current_token->next;
	if (current_token->type == PIPE
		|| current_token->type == E_CMD)
	{
		export_listing(env_list);
	}
	else
	{
		while (current_token != cmd_family->end->next)
		{
			if (current_token->type == SPACE)
				current_token = current_token->next;
			append_var(env_list, list_tail(env_list), current_token->value);
			current_token = current_token->next;
		}
	}
}

void	env_builtin(t_token *env_list, t_family *cmd_family)
{
	t_token	*node;

	if (cmd_family->start != cmd_family->end)
		return ;
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
	t_token	*current_token;

	current_token = cmd_family->start->next;
	while (current_token != cmd_family->end->next)
	{
		if (current_token->type == SPACE)
			current_token = current_token->next;
		delete_var(env_list, current_token->value);
		current_token = current_token->next;
	}
}

int	variables_handler(t_token *env_list, t_family *cmd_family)
{
	t_token	*builtin;

	builtin = cmd_family->start;
	if (!ft_fcmp(builtin->value, "unset"))
		unset_builtin(env_list, cmd_family);
	else if (!ft_fcmp(builtin->value, "export"))
		export_builtin(env_list, cmd_family);
	else if (!ft_fcmp(builtin->value, "env"))
		env_builtin(env_list, cmd_family);
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
