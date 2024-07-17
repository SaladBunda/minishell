/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:21:57 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/02 14:52:10 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*angle_bracket(int state, char *cmd, int *index)
{
	t_token	*token;

	token = NULL;
	if (state == GREAT)
	{
		if (cmd[*index + 1] && cmd[*index + 1] == '>')
		{
			token = new_token(ft_strdup(">>"), APPEND);
			*index += 1;
		}
		else
			token = new_token(ft_strdup(">"), GREAT);
	}
	else if (state == LESS)
	{
		if (cmd[*index + 1] && cmd[*index + 1] == '<')
		{
			token = new_token(ft_strdup("<<"), HEREDOC);
			*index += 1;
		}
		else
			token = new_token(ft_strdup("<"), LESS);
	}
	return (token);
}

t_token	*q_handler(char *cmd, int *index, char q_type)
{
	int		i;
	int		j;
	char	*str;
	t_token	*token;

	i = *index;
	str = NULL;
	token = NULL;
	if (cmd[i] == q_type)
	{
		i++;
		j = i;
		while (cmd && cmd[i] && cmd[i] != q_type)
			i++;
		if (cmd[i] == q_type)
			str = ft_substr(cmd, j, i - j);
	}
	*index = i;
	if (q_type == '\'')
		token = new_token(str, SQUOTE);
	else if (q_type == '\"')
		token = new_token(str, DQUOTE);
	return (token);
}

t_token	*single_handlers(char *cmd, int *index, int state, char c)
{
	t_token	*token;

	token = NULL;
	if (state == LEFT_PAR || state == RIGHT_PAR)
		token = new_token(ft_strdup(&c), state);
	else if (state == AND)
	{
		if (cmd[*index + 1] && cmd[*index + 1] == '&')
			token = new_token(ft_strdup("&&"), AND);
		else
			token = new_token(ft_strdup("&"), STR);
		*index += 1;
	}
	else if (state == PIPE)
	{
		if (cmd[*index + 1] && cmd[*index + 1] == '|')
		{
			token = new_token(ft_strdup("||"), OR);
			*index += 1;
		}
		else
			token = new_token(ft_strdup("|"), PIPE);
	}
	return (token);
}

t_token	*wide_handlers(char *cmd, int *index, char c)
{
	t_token	*token;

	token = NULL;
	while (cmd[*index] == c)
		(*index)++;
	if (c == ' ')
		token = new_token(ft_strdup(" "), SPACE);
	else if (c == '*')
		token = new_token(ft_strdup("*"), WILD);
	(*index)--;
	return (token);
}

t_token	*words_handler(char *cmd, int *index, int state)
{
	int		i;
	t_token	*token;
	char	*str;

	i = *index;
	token = NULL;
	if (state == VAR)
		(*index)++;
	while (cmd[*index] && is_special(cmd[*index]) == 0)
		(*index)++;
	str = ft_substr(cmd, i, (*index) - i);
	(*index)--;
	token = new_token(str, state);
	return (token);
}
