/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:38:02 by alabalet          #+#    #+#             */
/*   Updated: 2021/08/22 22:12:18 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include "../Includes/libft.h"

static int	eq_str(char *s1, const char *s2)
{
	int	cpt;

	cpt = 0;
	while (s2[cpt])
	{
		if (s1[cpt] != s2[cpt])
			return (0);
		cpt++;
	}
	return (1);
}

char	*ft_strnstr(char *str, const char *to_find, size_t len)
{
	int	cpt;

	cpt = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[cpt] && cpt + ft_strlen(to_find) <= (int)len)
	{
		if (str[cpt] == to_find[0])
		{
			if (eq_str(str + cpt, to_find))
				return (str + cpt);
		}
		cpt++;
	}
	return (0);
}
