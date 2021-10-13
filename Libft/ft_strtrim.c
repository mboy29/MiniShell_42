/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:51:39 by alabalet          #+#    #+#             */
/*   Updated: 2021/08/22 22:12:37 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../Includes/libft.h"

int	in(char c, char const *set)
{
	int	cpt;

	cpt = 0;
	while (set[cpt])
	{
		if (set[cpt++] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		cpt;
	int		len;

	cpt = 0;
	len = ft_strlen(s1);
	while (in(s1[cpt], set))
		cpt++;
	while (in(s1[len - 1], set))
		len--;
	if (cpt > len)
	{
		ret = malloc(1);
		if (!ret)
			return (0);
		ret[0] = '\0';
		return (ret);
	}
	ret = ft_substr(s1, cpt, len - cpt);
	return (ret);
}
