/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 10:20:35 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/08 19:07:30 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delimiter(char c, char d)
{
	return (d == c);
}

static int	word_count(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (is_delimiter(str[i], c) && str[i])
		i++;
	while (str[i])
	{
		while (!is_delimiter(str[i], c) && str[i])
			i++;
		count++;
		while (is_delimiter(str[i], c) && str[i])
			i++;
	}
	return (count);
}

static char	**wipe_arr(char **ptr, int n)
{
	while (n > 0)
	{
		n--;
		free(ptr[n]);
	}
	free(ptr);
	return (NULL);
}

char	**split_string(char const *s, char c)
{
	int		j;
	int		i;
	int		n;
	char	**ptrs;

	n = 0;
	i = 0;
	ptrs = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!ptrs)
		return (NULL);
	while (s[i] && n < word_count(s, c))
	{
		j = 0;
		while (is_delimiter(s[i], c) && s[i])
			i++;
		while (!is_delimiter(s[i + j], c) && s[i + j])
			j++;
		ptrs[n] = ft_substr(s, i, j);
		if (!ptrs[n])
			return (wipe_arr(ptrs, n));
		i += j;
		n++;
	}
	ptrs[n] = NULL;
	return (ptrs);
}

char	**ft_split(char const *s, char c)
{
	if (!s || !(*s))
		return (NULL);
	return (split_string(s, c));
}