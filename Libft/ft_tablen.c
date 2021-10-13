/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 05:04:26 by mboy              #+#    #+#             */
/*   Updated: 2021/09/25 17:59:39 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_tablen(void **tab)
{
	int		idx;

	idx = 0;
	if (!tab)
		return (0);
	while (tab[idx])
		idx++;
	return (idx);
}
