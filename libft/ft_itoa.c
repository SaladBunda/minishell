/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:00:15 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:28:53 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_digits(int n)
{
	int	digits;

	digits = 0;
	if (n < 0)
	{
		digits++;
		n *= -1;
	}
	while (n >= 10)
	{
		n /= 10;
		digits++;
	}
	return (++digits);
}

static void	fill_buf(int n, char *ptr, int index)
{
	if (n < 10)
	{
		ptr[index] = (n % 10) + '0';
		return ;
	}
	else
	{
		ptr[index] = (n % 10) + '0';
		fill_buf((n / 10), ptr, --index);
	}
}

char	*ft_itoa(int n)
{
	int		digits_number;
	char	*ptr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digits_number = number_digits(n);
	ptr = (char *)malloc(sizeof(char) * (digits_number + 1));
	if (!ptr)
		return (NULL);
	ptr[digits_number] = '\0';
	if (n < 0)
	{
		ptr[0] = '-';
		n *= -1;
	}
	fill_buf(n, ptr, --digits_number);
	return (ptr);
}
/*
int	main(void)
{
	printf("%s", ft_itoa(-2147483648));
	return (0);
}*/
