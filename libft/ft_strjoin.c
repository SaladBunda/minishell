/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 08:56:59 by nhayoun           #+#    #+#             */
/*   Updated: 2024/02/27 17:00:24 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * ((s1_len + s2_len) + 1));
	if (!ptr)
		return (NULL);
	while (i < s1_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	while (i < (s1_len + s2_len))
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}
/*int	main(void)
{
	printf("%s", ft_strjoin("1337", " Coding school"));
	return (0);
}*/