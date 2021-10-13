/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:25:26 by alabalet          #+#    #+#             */
/*   Updated: 2021/01/20 09:42:00 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "../Includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	int					cpt;

	str1 = s1;
	str2 = s2;
	cpt = -1;
	while (n - ++cpt)
		if (*(str1 + cpt) != *(str2 + cpt))
			return (*(str1 + cpt) - *(str2 + cpt));
	return (0);
}
