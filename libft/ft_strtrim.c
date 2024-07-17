/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 09:39:49 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:30:20 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_check(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*generate_string(int start_index, int end_index, const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * ((end_index - start_index) + 2));
	if (!ptr)
		return (NULL);
	while (i < (end_index - start_index + 1))
	{
		ptr[i] = s1[i + start_index];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start_index;
	int	end_index;

	if (!s1 || !set)
		return (NULL);
	start_index = 0;
	if (!ft_strlen(set))
		return (ft_strdup(s1));
	end_index = ft_strlen(s1) - 1;
	if (end_index == -1)
		return (ft_strdup(""));
	while (char_check(s1[start_index], set))
	{
		if (start_index == end_index)
			return (ft_strdup(""));
		start_index++;
	}
	while (char_check(s1[end_index], set))
		end_index--;
	return (generate_string(start_index, end_index, s1));
}
/*
int	main(void)
{
	char	s1[] = "hhhhhhhhh";
	char	set[] = "h";

	printf("%s" ,ft_strtrim(s1, set));
}
*/
