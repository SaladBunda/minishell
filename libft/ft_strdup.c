/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:46:13 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:29:50 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*buffer;
	size_t	len;

	len = ft_strlen(s1);
	buffer = (char *)malloc((len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (len == 0)
	{
		ft_bzero(buffer, 1);
		return (buffer);
	}
	ft_memmove(buffer, s1, len + 1);
	return (buffer);
}
/*
int	main(void)
{
	char	str[] = "1337 coding school";

	printf("%s\n", ft_strdup(str));
	return (0);
}
*/