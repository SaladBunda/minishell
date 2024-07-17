/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:32:27 by nhayoun           #+#    #+#             */
/*   Updated: 2024/07/05 09:47:10 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*int	main(void)
{
	char str[] = "1337 School";
	char str1[1];
	printf("custom=>%zu  Lib's=>%zu\n", ft_strlen(str1), strlen(str));
	return (0);
}*/