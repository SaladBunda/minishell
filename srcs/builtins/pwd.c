/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:50:18 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/05 12:42:51 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

void	pwd_builtin(void)
{
	char	pwd[1024];

	getcwd(pwd, 1024);
	printf("%s\n", pwd);
	g_last_exit_status = 0;
}

char	*pwd_extract(void)
{
	char	pwd[1024];
	char	*cwd;

	getcwd(pwd, 1024);
	cwd = ft_strdup(pwd);
	if (!cwd)
		return (NULL);
	return (cwd);
}
