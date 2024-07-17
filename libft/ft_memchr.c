/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:07:38 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:27:35 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*byte;

	i = 0;
	byte = (unsigned char *)s;
	while (i < n)
	{
		if (*byte == (unsigned char)c)
			return ((void *)byte);
		i++;
		byte++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	str[] = "Hello \0world";

	printf("%p\n", ft_memchr(str, 0, 6));
	printf("%p\n", memchr(str, 0, 6));
}
*/