/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 11:38:55 by alabalet          #+#    #+#             */
/*   Updated: 2021/08/22 22:10:15 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../Includes/libft.h"

static void	ft_putstrr_fd(char *src, int fd, int len_src)
{
	int	cpt;

	cpt = 0;
	while (len_src - cpt)
	{
		write(fd, &src[len_src - cpt - 1], 1);
		cpt++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		sign;
	char	tmp[40];
	int		cpt;

	if (n == 0)
		write(fd, "0", 1);
	sign = -(n < 0) + (n >= 0);
	cpt = 0;
	while (n)
	{
		tmp[cpt++] = '0' + sign * (n % 10);
		n /= 10;
	}
	if (sign == -1)
		write(fd, "-", 1);
	ft_putstrr_fd(tmp, fd, cpt);
}
