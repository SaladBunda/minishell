/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:12:46 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:29:08 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (NULL);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len)
		{
			len--;
			*(unsigned char *)(len + dst) = *(unsigned char *)(len + src);
		}
	}
	return (dst);
}

/*int main() {
	char source1[50] = "fork";
	char source2[50] = "fork";

	memcpy(source1 + 2, source1, sizeof(source1));
	printf("memmove: %s\n", source1 + 2);
	ft_memcpy(source2 + 2, source2, sizeof(source2));
	printf("ft_memmove: %s\n", source2 + 2);
	return (0);
}*/
