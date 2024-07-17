/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:30:16 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:28:58 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	byte_comparison(unsigned char c1, unsigned char c2)
{
	return (c1 - c2);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				cmp;
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	size_t			i;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		cmp = byte_comparison(*s1_ptr++, *s2_ptr++);
		if (cmp)
			return (cmp);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	s1[] = "tesa";
	char	s2[] = "tesb";

	printf("%d\n", ft_memcmp(s1, s2, 3));
	printf("%d\n", memcmp(s1, s2, 3));
	return (0);
}
*/
