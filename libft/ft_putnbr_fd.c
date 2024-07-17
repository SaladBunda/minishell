/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:54:40 by nhayoun           #+#    #+#             */
/*   Updated: 2024/03/30 07:29:38 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	put_nbr(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		put_nbr(n, fd);
	}
	else if (n < 10)
		ft_putchar_fd((n + '0'), fd);
	else
	{
		put_nbr((n / 10), fd);
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
		put_nbr(n, fd);
}

/*int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int num = ft_atoi(av[1]);
	ft_putnbr_fd(num, 1);
	return (0);
}*/
