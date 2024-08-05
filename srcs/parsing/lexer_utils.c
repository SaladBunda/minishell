/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:05:46 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/03 16:07:03 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

int	is_whitespace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_special(char c, int flag)
{
	int		i;
	char	*symbols;

	if (flag)
		symbols = "\"\'|< &$()>*\t\n\r\v\f";
	else
		symbols = "\"\'-?|@< &$()>*\t\n\r\v\f";
	i = 0;
	while (symbols[i])
	{
		if (symbols[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	quo(char *cmd, int *i, int *check, char c)
{
	(*i)++;
	*check = 1;
	while (cmd[*i] && cmd[*i] != c)
		(*i)++;
	if (cmd[*i] == c)
		*check = 0;
}

int	quotes(char *cmd)
{
	int	i;
	int	check;

	check = 0;
	i = -1;
	while (cmd[++i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd[i] == '\'')
			quo(cmd, &i, &check, '\'');
		else if (cmd[i] == '\"')
			quo(cmd, &i, &check, '\"');
	}
	if (check == 1)
		return (g_last_exit_status = 3, write(2, "unclosed quote\n", 15), 1);
	return (0);
}

void	bracket_util(char *str, int i, int j, int *opened)
{
	str[i] = ' ';
	str[j] = ' ';
	*opened = 0;
}
