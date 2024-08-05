/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:20:18 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/04 12:31:47 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_darr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	arr[i] = NULL;
	free(arr);
	arr = NULL;
}

void	free_files(t_family *node)
{
	int	i;

	i = 0;
	if (node->files)
	{
		while (node->files[i].path != NULL)
		{
			if (node->files[i].type == HEREDOC)
				unlink(node->files[i].path);
			free(node->files[i].lim);
			free(node->files[i].path);
			if (node->files[i].fd > 0)
				close(node->files[i].fd);
			i++;
		}
		free(node->files);
	}
}
