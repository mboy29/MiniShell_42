/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:10:38 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/11 17:11:30 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	fill_cmd(t_vars *v, int ic, int i)
{
	int	cpt;
	int	i2;
	int	i_av;

	v->cmd[ic].redir_tab = malloc((v->nb_tkn + 1) * sizeof(t_token));
	v->cmd[ic].av = malloc((v->nb_tkn + 1) * sizeof(char *));
	cpt = 0;
	i2 = 0;
	i_av = 0;
	while (v->tkn_tab[i + cpt].type && v->tkn_tab[i + cpt].type != PIPE)
	{
		if (v->tkn_tab[i + cpt].type != TXT)
		{
			v->cmd[ic].redir_tab[i2].type = v->tkn_tab[i + cpt].type;
			v->cmd[ic].redir_tab[i2++].str = ft_strdup(v->tkn_tab[i + cpt].str);
		}
		else
			v->cmd[ic].av[i_av++] = ft_strdup(v->tkn_tab[i + cpt].str);
		cpt++;
	}
	v->cmd[ic].redir_tab[i2].type = END;
	v->cmd[ic].av[i_av] = 0;
	return (v->cmd[ic]);
}

char	**add_elem(char **av, char *str)
{
	char	**res;
	int		i;

	res = malloc((ft_tablen((void **)av) + 2) * sizeof(char *));
	i = -1;
	while (av[++i])
	{
		res[i] = ft_strdup(av[i]);
		free(av[i]);
	}
	if (str)
		res[i++] = ft_strdup(str);
	res[i] = 0;
	free(av);
	return (res);
}
