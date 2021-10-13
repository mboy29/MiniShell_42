/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:08:33 by alabalet          #+#    #+#             */
/*   Updated: 2021/08/22 22:11:17 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../Includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;

	ret = malloc(ft_strlen(s1) + 1);
	if (!ret)
		return (0);
	ft_memcpy(ret, s1, ft_strlen(s1));
	ret[ft_strlen(s1)] = '\0';
	return (ret);
}
