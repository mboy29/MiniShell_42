/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 01:32:15 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/11 17:11:20 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_string(char *str, int *i)
{
	char	q;
	int		i_tmp;
	char	*tmp;

	tmp = malloc(ft_strlen(str) + 1);
	i_tmp = 0;
	q = 0;
	while (str[*i] && (q != 0 || str[*i] != ' '))
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			if (q && q != str[*i])
				tmp[i_tmp++] = str[*i];
			q = str[*i] * (q == 0) + q * (q != str[*i]);
		}
		else
			tmp[i_tmp++] = str[*i];
		(*i)++;
	}
	tmp[i_tmp] = 0;
	return (tmp);
}

char	**divide(t_cmd cmd, t_vars *v)
{
	char	**res;
	int		i_av;
	int		i_str;
	char	*tmp;

	res = malloc(sizeof(char *));
	res[0] = 0;
	i_av = -1;
	while (cmd.av[++i_av])
	{
		expand(&(cmd.av[i_av]), v);
		i_str = 0;
		while (cmd.av[i_av][i_str])
		{
			tmp = get_next_string(cmd.av[i_av], &i_str);
			res = add_elem(res, tmp);
			free(tmp);
			while (cmd.av[i_av][i_str] == ' ')
				i_str++;
		}
	}
	free_tabstr(cmd.av);
	return (res);
}

void	update_env(t_vars *v)
{
	int		i;
	int		i_e;
	char	*tmp;

	v->e = malloc((v->tab_len + 1) * sizeof(char *));
	i = -1;
	i_e = 0;
	while (++i < v->tab_len)
	{
		if (v->tab_env[i][1])
		{
			tmp = ft_strjoin(v->tab_env[i][0], "=");
			v->e[i_e++] = ft_strjoin(tmp, v->tab_env[i][1]);
			free(tmp);
		}
	}
	v->e[i_e] = 0;
}

char	**get_cmd_path(t_vars *v, char *cmd)
{
	char	**ret;
	int		cpt;
	char	*tmp;

	if (!cmd)
	{
		ret = malloc(sizeof(char *));
		ret[0] = 0;
		return (ret);
	}
	tmp = get_tabenv(v, "PATH");
	ret = ft_split(tmp, ':');
	free(tmp);
	cpt = -1;
	while (ret[++cpt])
	{
		tmp = ft_strjoin(ret[cpt], "/");
		free(ret[cpt]);
		ret[cpt] = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	return (ret);
}

/*
Remplit v em fonction de tkn_tab au format demande par la fonction d'execution
	nb_cmd = nb pipe + 1
	Parcours chaque token et remplit la liste des redirection
	et des av dans la commande associee
	Expand chaque av
	Dans chaque av, soustait les quotes et decoupe en fonction des ' ' unquoted
	A partir de av[0], remplit les paths d'execution potentiels
*/		
void	parser(t_vars *v)
{
	int	i_cmd;
	int	i_tkn;

	v->nb_cmd = 1;
	i_tkn = -1;
	while (v->tkn_tab[++i_tkn].type)
		if (v->tkn_tab[i_tkn].type == PIPE)
			v->nb_cmd++;
	v->nb_tkn = i_tkn;
	v->cmd = malloc(v->nb_cmd * sizeof(t_cmd));
	i_cmd = -1;
	i_tkn = -1;
	while (++i_cmd < v->nb_cmd)
	{
		v->cmd[i_cmd] = fill_cmd(v, i_cmd, ++i_tkn);
		v->cmd[i_cmd].av = divide(v->cmd[i_cmd], v);
		v->cmd[i_cmd].path = get_cmd_path(v, v->cmd[i_cmd].av[0]);
		while (v->tkn_tab[i_tkn].type && v->tkn_tab[i_tkn].type != PIPE)
			i_tkn++;
	}
	update_env(v);
}
