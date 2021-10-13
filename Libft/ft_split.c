/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 09:03:30 by alabalet          #+#    #+#             */
/*   Updated: 2021/09/28 14:11:19 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../Includes/libft.h"

static int	ft_wc(char *str, char c)
{
	int	cpt;
	int	wc;

	wc = 0;
	cpt = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return (!(str[0] == '\0'));
	while (str[cpt] == c)
		cpt++;
	while (str[cpt])
	{
		while (!(str[cpt] == c) && str[cpt])
			cpt++;
		wc++;
		while (str[cpt] == c)
			cpt++;
	}
	return (wc);
}

static char	*ft_parse_word(char *str, char sep, int *cpt)
{
	int		len;
	char	*ret;

	len = 0;
	while (str[*cpt + len] && !(str[*cpt + len] == sep))
		len++;
	ret = malloc(len + 1);
	if (!ret)
		return (0);
	len = 0;
	while (str[*cpt + len] && !(str[*cpt + len] == sep))
	{
		ret[len] = str[*cpt + len];
		len++;
	}
	ret[len] = '\0';
	*cpt += len;
	return (ret);
}

char	**ft_split(char *str, char c)
{
	int		cpt_tab;
	int		cpt_str;
	int		wc;
	char	**ret;

	wc = ft_wc(str, c);
	ret = malloc(sizeof(char *) * (wc + 1));
	if (!ret)
		return (0);
	cpt_str = 0;
	cpt_tab = 0;
	while (cpt_tab < wc)
	{
		while (str[cpt_str] == c)
			cpt_str++;
		ret[cpt_tab++] = ft_parse_word(str, c, &cpt_str);
	}
	ret[cpt_tab] = 0;
	return (ret);
}
