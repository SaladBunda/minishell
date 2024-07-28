/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:13:39 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/28 10:46:06 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

void	sigint_handler_nl(int sig)
{
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	sigint_handler(int sig)
{
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	sigquit_reset(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

// void	heredoc_sig(void)
//{
//	struct sigaction	sa_int;

//	sa_int.sa_handler = here_sig;
//	sigemptyset(&sa_int.sa_mask);
//	sa_int.sa_flags = 0;
//	if (sigaction(SIGINT, &sa_int, NULL) == -1)
//		perror("Error setitng SIGINT handler");
//}

void	signals_init(void)
{
	signal(SIGINT, sigint_handler_nl);
	signal(SIGQUIT, SIG_IGN);
}