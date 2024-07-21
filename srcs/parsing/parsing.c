/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:32:27 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/19 18:37:07 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_state(int state, char *cmd, int *index, t_token *list_tail)
{
	t_token	*token;

	token = NULL;
	if (state == GREAT || state == LESS)
		token = angle_bracket(state, cmd, index);
	else if (state == PIPE || state == AND || state == LEFT_PAR
		|| state == RIGHT_PAR)
		token = single_handlers(cmd, index, state, cmd[*index]);
	else if (state == DQUOTE || state == SQUOTE)
		token = q_handler(cmd, index, cmd[*index]);
	else if (state == STR || state == VAR)
		token = words_handler(cmd, index, state);
	else if (state == WILD || state == SPACE)
		token = wide_handlers(cmd, index, cmd[*index]);
	append_token(list_tail, token);
}

void	lexer2(char *cmd, int *state, int *i)
{
	if (cmd[*i] == '\"')
		*state = DQUOTE;
	else if (cmd[*i] == '(')
		*state = LEFT_PAR;
	else if (cmd[*i] == ')')
		*state = RIGHT_PAR;
	else if (is_whitespace(cmd[*i]))
		*state = SPACE;
	else if (cmd[*i] == '*')
		*state = WILD;
	else if (cmd[*i] == '$')
		*state = VAR;
	else if (cmd[*i] == '\'')
		*state = SQUOTE;
	else
		*state = STR;
}

void	lexer(char *cmd, t_token *list_tail, int *i)
{
	int	state;
	int	prev_state;

	state = S_CMD;
	while (cmd[*i])
	{
		prev_state = state;
		if (cmd[*i] == '>')
			state = GREAT;
		else if (cmd[*i] == '<')
			state = LESS;
		else if (cmd[*i] == '|')
			state = PIPE;
		else if (cmd[*i] == '&')
			state = AND;
		else
			lexer2(cmd, &state, i);
		if (prev_state != state)
		{
			handle_state(state, cmd, i, list_tail);
			state = S_CMD;
		}
		(*i)++;
	}
}

void	free_family(t_family *head)
{
	t_family	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		// free(tmp->value);
		free(tmp);
	}
}

void	free_list(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

t_family	*parsing(char *cmd, t_token *env)
{
	t_family	*family_head;
	t_token		*tail;
	t_token		*head;
	int			i;

	if (!cmd)
		return (NULL);
	i = 0;
	tail = create_list();
	head = tail->prev;
	if (!tail)
		return (NULL);
	if (!brackets(cmd) || quotes(cmd))
		return (free_list(head), NULL);
	lexer(cmd, tail, &i);
	joiner(head, env);
	if (syntactic_tester(head) == 1)
		return (free_list(head), NULL);
	family_head = create_family_ll(head);
	organizer(family_head);
	// fake_executionner(family_head, env);
	//print_tokens(head);
	extract_paths(family_head, env);
	extract_files(family_head);
	// print_tokens(head);
	// print_family(family_head);
	// free_list(head);
	// free_family(family_head);
	return (family_head);
}

/*
ls >in1>in2>in3>in4 | < in cat -e | cat < in -e || echo "$HOME" $HOME '$HOME'
	&& echo ****.c *'.c' *".c" >> out
	The lexer will :
		identify each part of the command
		parse each token turn it into a token node
(echo hi1 && (echo hi2 || echo hi3)) || (echo hi4 && echo hi5)
*/
