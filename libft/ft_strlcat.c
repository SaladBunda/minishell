/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 09:02:19 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:29:58 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	total;
	size_t	i;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	total = dst_len + src_len;
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] != '\0' && (dst_len + i < size - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (total);
}

/*
int	main(void)
{
	char	dest1[15] = "Watch this";
	char	dest2[15] = "Watch this";
	char	src[15] = "Watch this";

	printf("%zu\n", ft_strlcat(dest1, src, sizeof(dest1)));
	printf("%s\n", dest1);
	printf("%zu\n", strlcat(dest2, src, sizeof(dest2)));
	printf("%s\n", dest2);
}
*/