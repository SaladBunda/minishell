/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:34:52 by nhayoun           #+#    #+#             */
/*   Updated: 2023/12/13 14:45:56 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
int	main(void)
{
	char	str[] = "UpPeR CaSe Me";
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_toupper(str[i]))
			str[i] = ft_toupper(str[i]);
		i++;
	}
	printf("%s\n", str);
	return (0);
}
*/