/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:32:39 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/24 13:05:43 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int		g_last_exit_status = 0;

void	print_env(t_token *env_head)
{
	t_token	*token;

	token = env_head->next;
	while (token->type != E_CMD)
	{
		if (ft_strchr(token->value, '='))
			printf("%s\n", token->value);
		token = token->next;
	}
}
int	check_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_whitespace(str[i]) == 1)
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*cmd;
	t_token		*env_ll;
	t_token		*tail;
	t_family	*family_head;

	(void)ac;
	(void)av;
	env_ll = env_process(env, 0);
	tail = list_tail(env_ll);
	while ((cmd = readline("minishell$> ")) != NULL)
	{
		if (check_empty(cmd) == 1)
		{
			free(cmd);
			continue ;
		}
		add_history(cmd);
		family_head = parsing(cmd, env_ll);
		if (!family_head)
		{
			free(cmd);
			continue ;
		}
		free(cmd);
		//sig_int();
		execution(family_head, env_ll);
		// free_list(family_head->start);
		system("leaks -quiet minishell");
		// system("leaks -quiet minishell");
	}
	free_list(env_ll);
}
