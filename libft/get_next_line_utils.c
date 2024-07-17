/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:38:31 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/13 19:09:51 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_gnl(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*buf;

	i = 0;
	len = ft_strlen(s1);
	buf = (char *)malloc((len + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (i < len)
	{
		buf[i] = s1[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*joined_str;
	int		lengths[2];

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	joined_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined_str)
		return (NULL);
	lengths[0] = 0;
	while (s1 && s1[lengths[0]])
	{
		joined_str[lengths[0]] = s1[lengths[0]];
		lengths[0]++;
	}
	lengths[1] = 0;
	while (s2 && s2[lengths[1]])
	{
		joined_str[lengths[0] + lengths[1]] = s2[lengths[1]];
		lengths[1]++;
	}
	joined_str[lengths[0] + lengths[1]] = 0;
	return (joined_str);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*ft_substr_gnl(char *s, size_t start, size_t len)
{
	size_t	string_length;
	char	*buf;
	size_t	i;

	string_length = ft_strlen(s);
	i = 0;
	if (start >= string_length)
		return (NULL);
	if (len > string_length - start)
		len = string_length - start;
	buf = (char *)malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	while (i < len)
		buf[i++] = s[start++];
	buf[i] = '\0';
	return (buf);
}
