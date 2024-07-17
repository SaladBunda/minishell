/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:09:27 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:30:00 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (dstsize != 0)
	{
		while (i < (dstsize - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}
/*int	main(void)
{
	char	src[] = "Copy This string";
	char	dst1[10];
	char	dst2[10];
	printf("%zu\n",ft_strlcpy(dst1, src, sizeof(dst1)));
	printf("%s\n", dst1);
	printf("%zu\n",strlcpy(dst2, src, sizeof(dst2)));
	printf("%s\n", dst2);
}*/
