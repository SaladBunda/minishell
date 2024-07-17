/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fcmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:28:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/14 11:26:45 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		else if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}
