/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:36:57 by alabalet          #+#    #+#             */
/*   Updated: 2021/08/22 22:11:36 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../Includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	cpt;
	unsigned int	cpt2;
	unsigned int	len_dest;

	if (!size)
		return (ft_strlen(src));
	cpt = 0;
	cpt2 = 0;
	while (dest[cpt])
		cpt++;
	len_dest = cpt;
	while (src[cpt2])
	{
		if (cpt == size - 1)
			dest[cpt] = '\0';
		if (cpt < size - 1)
			dest[cpt] = src[cpt2];
		cpt++;
		cpt2++;
	}
	dest[cpt] = '\0';
	if (size <= len_dest)
		return ((size_t)(cpt2 + size));
	else
		return ((size_t)(cpt2 + len_dest));
}
