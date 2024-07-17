/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:10:14 by nhayoun           #+#    #+#             */
/*   Updated: 2024/04/04 01:38:02 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* OVRFLOW CASE NBR HAS REACHED THE LIMIT OF LONG LONG,RETURNS A-1*/
/* UNDERFLOW CASE NBR HAS REACHED THE LIMIT OF LONG LONG,RETURNS A 0*/

static int	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

static int	is_overflow(unsigned long long result, int sign)
{
	if (sign == 1 && result > 9223372036854775807)
		return (-1);
	else if (sign == -1 && result > 9223372036854775807)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	while (is_whitespace(str[i]))
		i++;
	result = 0;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = (result * 10) + (str[i] - '0');
		if (is_overflow(result, sign) != 1)
			return (is_overflow(result, sign));
		i++;
	}
	return (result * sign);
}
/*int	main(int ac, char **av)
{
	if (ac == 1)
		return (0);
	printf("%d\n", ft_atoi(av[1]));
	printf("%d\n", atoi(av[1]));
}*/