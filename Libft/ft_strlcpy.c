/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:34:08 by alabalet          #+#    #+#             */
/*   Updated: 2021/01/23 16:15:27 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../Includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		cpt;
	int		src_is_terminated;

	if (!dst)
	{
		return ((size_t)ft_strlen(src));
	}
	if (!dstsize)
	{
		return ((size_t)ft_strlen(src));
	}
	cpt = 0;
	src_is_terminated = 0;
	while (cpt < (int)dstsize - 1 && src[cpt])
	{
		dst[cpt] = src[cpt];
		cpt++;
	}
	dst[cpt] = '\0';
	return ((size_t)ft_strlen(src));
}
