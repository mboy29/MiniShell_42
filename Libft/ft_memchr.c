/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:09:59 by alabalet          #+#    #+#             */
/*   Updated: 2021/08/22 22:09:39 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../Includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	int					cpt;

	str = s;
	cpt = -1;
	c = (unsigned char)c;
	while (n - ++cpt)
	{
		if (*(str + cpt) == c)
			return ((void *)(str + cpt));
	}
	return (0);
}
