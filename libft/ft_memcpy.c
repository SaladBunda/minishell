/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:48:53 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:29:01 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}
/*int main(void)
{
	char s1[] = "String Paste Here     ";
	char s2[] = "String Paste Here     ";
	char src[] = "String Gone";
	printf("%s\n", ft_memcpy(s1, src, 11));
	printf("%s\n", memcpy(s2, src, 11));
	return (0);
}*/