/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:13:39 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/22 12:13:15 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	sigval;

// void	sigterm_handler(void)
//{
//}

//void	sigint_handler(void)
//{
//	pid_t	ps;

//	ps = fork();
//	if (!ps)
//	{
//		write(1, "\nminishell$> ", 13);
//		exit(1);
//	}
//	else
//		wait(&sigval);
//}

//void	sig_int(t_files *files)
//{

//}

//void	signal_handler(void)
//{
//	signal(SIGINT, (void *)sigint_handler);
//}