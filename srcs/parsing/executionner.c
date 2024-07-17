/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executionner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:57:31 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/14 11:29:05 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	which_command(t_token *cmd, t_family *family_node, t_token *env)
{
	if (ft_fcmp(cmd->value, "cd") == 0)
		cd_builtin(family_node, env);
	else if (ft_fcmp(cmd->value, "pwd") == 0)
		pwd_builtin();
	else if (ft_fcmp(cmd->value, "echo") == 0)
		echo_builtin(family_node);
	else if (ft_fcmp(cmd->value, "env") == 0|| !ft_fcmp(cmd->value,"export") || !ft_fcmp(cmd->value, "unset"))
		return(variables_handler(env, family_node));
	else
		return (1);
	return (0);
}

int	fake_executionner(t_family *family_head, t_token *env)
{
	t_family *tmp;
	t_token *indexer;

	tmp = family_head->next;
	while (tmp->type != E_CMD)
	{
		if (tmp->type != PIPE_ROW)
		{
			indexer = tmp->start;
			while (indexer != tmp->end->next)
			{
				if (indexer->group == COMMAND)
					return(which_command(indexer, tmp, env));
				indexer = indexer->next;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}