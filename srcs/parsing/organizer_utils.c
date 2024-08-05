/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:21:22 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/04 12:26:06 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_op(t_token *t)
{
	if (t->type == GREAT || t->type == LESS || t->type == APPEND
		|| t->type == HEREDOC)
		return (1);
	return (0);
}

int	is_str(t_token *t)
{
	if (t->type == VAR || t->type == DQUOTE || t->type == SQUOTE
		|| t->type == STR)
		return (1);
	return (0);
}
