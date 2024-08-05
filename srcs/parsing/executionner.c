/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executionner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:57:31 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/08/05 11:33:07 by ael-maaz         ###   ########.fr       */
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
	else if (ft_fcmp(cmd->value, "env") == 0 || !ft_fcmp(cmd->value, "export")
		|| ft_fcmp(cmd->value, "unset") == 0)
		return (variables_handler(cmd, env, family_node), 0);
	else if (ft_fcmp(cmd->value, "exit") == 0)
		exit_builtin(family_node);
	else
		return (1);
	return (0);
}

int	fake_ex(t_family *family_head, t_token *env)
{
	t_family	*tmp;
	t_token		*indexer;

	tmp = family_head;
	while (tmp->type != E_CMD)
	{
		if (tmp->type != PIPE_ROW)
		{
			indexer = tmp->start;
			while (indexer != tmp->end->next)
			{
				if (indexer->group == COMMAND)
					return (which_command(indexer, tmp, env));
				indexer = indexer->next;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
