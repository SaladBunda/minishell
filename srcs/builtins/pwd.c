/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:50:18 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/23 11:21:21 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int g_last_exit_status;

void	pwd_builtin(void)
{
	char pwd[1024];

	getcwd(pwd, 1024);
	printf("%s\n", pwd);
	g_last_exit_status = 0;
}