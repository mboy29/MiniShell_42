/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:57:19 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/10 19:00:47 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_loop(char **tab, t_token tkn, int cpt)
{
	if (tkn.type == PIPE)
	{
		if (get_type(tab[cpt + 1]) == PIPE)
		{
			print_error(tab[cpt + 1], 5);
			return (258);
		}
	}
	else if (1 <= tkn.type && tkn.type <= 4)
	{
		if (get_type(tab[cpt + 1]) != TXT)
		{
			print_error(tab[cpt + 1], 5);
			return (258);
		}
	}
	return (0);
}

/*
Verifie que :
	Pas 2 pipes a la suite
	Pas de redirection sans texte derriere
	Le premier mot n'est pas un pipe
*/
int	check_syntax(char **tab)
{
	int		ret;
	int		cpt;
	t_token	tkn;

	ret = 0;
	cpt = -1;
	if (get_type(tab[0]) == PIPE)
	{
		print_error(tab[0], 5);
		return (258);
	}
	while (tab[++cpt])
	{
		tkn.type = get_type(tab[cpt]);
		ret = check_syntax_loop(tab, tkn, cpt);
		if (ret != 0)
			return (ret);
	}
	return (0);
}
