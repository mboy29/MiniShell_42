/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:53:24 by alabalet          #+#    #+#             */
/*   Updated: 2021/08/22 21:56:30 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_atoi(const char *str)
{
	int	cpt;
	int	sign;
	int	nb;

	cpt = 0;
	sign = 1;
	nb = 0;
	while (str[cpt] == ' ' || (9 <= str[cpt] && str[cpt] <= 13))
		cpt++;
	if (str[cpt] == '-' || str[cpt] == '+')
	{
		if (str[cpt] == '-')
			sign *= -1;
		cpt++;
	}
	while ('0' <= str[cpt] && str[cpt] <= '9')
		nb = nb * 10 + str[cpt++] - '0';
	return (sign * nb);
}
