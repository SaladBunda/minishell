/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:13:39 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/03 18:32:14 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_last_exit_status;

void	edit_global(int status)
{
	g_last_exit_status = status;
}

void	_edit(int *var, int value)
{
	*var = value;
}

int	nof_pipes(t_family *head)
{
	int			i;
	t_family	*ittr;

	i = 0;
	ittr = head->next;
	while (ittr->type != E_CMD)
	{
		if (ittr->type == CMD_ROW)
			i++;
		ittr = ittr->next;
	}
	return (i);
}

void	close_fds(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}

void	save_pipe(int *prev_fd, int *fds)
{
	close(*prev_fd);
	*prev_fd = fds[0];
	close(fds[1]);
}
