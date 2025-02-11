/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:32:39 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/05 19:59:24 by ael-maaz         ###   ########.fr       */
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
	t_family	*family_head;
	// atexit(ll);
	(void)ac;
	(void)av;
	if (!env[0])
		env_ll = basic_env(NULL, NULL, NULL);
	else
		env_ll = env_process(env, 0);
	while (1)
	{
		signals_init(0);
		cmd = readline("minishell$> ");
		if (!cmd)
		{
			system("leaks -quiet minishell");
			exit(0);
		}
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
			system("leaks -quiet minishell");
			continue ;
		}
		free(cmd);
		execution(family_head, env_ll);
		printf("exit status: %d\n",g_last_exit_status);
		free_list(family_head->next->start, 1);
		free_all_family(family_head);
		//system("leaks -quiet minishell");
	}
	free_list(env_ll, 0);
	system("leaks -quiet minishell");
}
