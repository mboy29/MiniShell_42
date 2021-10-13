/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 10:42:28 by alabalet          #+#    #+#             */
/*   Updated: 2021/08/22 21:57:37 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../Includes/libft.h"

static void	ft_strrcpy(char *dst, char *src, int len_src)
{
	int	cpt;

	cpt = 0;
	while (len_src - cpt)
	{
		dst[cpt] = src[len_src - cpt - 1];
		cpt++;
	}
	dst[cpt] = '\0';
}

char	*ft_itoa(int n)
{
	int		sign;
	char	tmp[40];
	char	*ret;
	int		cpt;

	if (n == 0)
	{
		ret = malloc(2);
		ft_strlcpy(ret, "0", 2);
		return (ret);
	}
	sign = -(n < 0) + (n >= 0);
	cpt = 0;
	while (n)
	{
		tmp[cpt++] = '0' + sign * (n % 10);
		n /= 10;
	}
	ret = malloc(cpt + 1 + (sign == -1));
	if (!ret)
		return (0);
	ret[0] = '-';
	ft_strrcpy(ret + (sign == -1), tmp, cpt);
	return (ret);
}
