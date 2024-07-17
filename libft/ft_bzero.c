/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:21:32 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:27:54 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (n == 0)
		return ;
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}
/*int	main(void)
{
	char s1[] = "Long String String";
	char s2[] = "Long String String";
	ft_bzero((s1 + 12), 4);
	printf("Custom ==> %s\n", s1);
	bzero((s2 + 12), 4);
	printf("Original ==> %s\n", s2);
}*/