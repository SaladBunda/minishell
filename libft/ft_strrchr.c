/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:46:25 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:30:17 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i--;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
/*int	main(void)
{
	char	str[] = "hello world";

	printf("%p\n", ft_strrchr(str, 'z'));
	printf("%p\n", strrchr(str, 'z'));
	return (0);
}*/