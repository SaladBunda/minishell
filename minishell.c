/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:32:39 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/15 10:30:20 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//ALERT: NEWS: IF THE VARIABLE IS NOT FOUND IT IS SUPPOSED TO GET DELETED FROM THE LINKED LIST AND NOT REPLACED WITH EMPTY STRING!!!!!!!!!!!!!

#include "./include/minishell.h"

void		print_env(t_token *env_head)
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

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	t_token	*env_ll;
	t_token	*tail;
	t_family *family_head;

	(void)ac;
	(void)av;
	env_ll = env_process(env, 0);
	tail = list_tail(env_ll);
	while ((cmd = readline("minishell$> ")) != NULL)
	{
		add_history(cmd);

		family_head = parsing(cmd, env_ll);
		if(!family_head)
		{
			free(cmd);
			continue;
		}
		free(cmd);
		execution(family_head, env_ll);
		//system("leaks -quiet minishell");
	}
	free_list(env_ll);
}
