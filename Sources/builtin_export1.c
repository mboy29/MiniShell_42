/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:27:39 by mboy              #+#    #+#             */
/*   Updated: 2021/09/27 18:28:09 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Fonction qui va anayler si l'argument passer en paramètre
//est valide ou non déterminer si la variable existe dèjà
//dans notre env ou pas
int	find_export(t_vars *v, char *param)
{
	int		idx;
	char	**find;

	idx = -1;
	if (param[0] == '=')
		return (1);
	find = split_export(param);
	if (!find || builtin_check(find[0]) == 1)
	{
		if (find)
			free_tabstr(find);
		return (1);
	}
	while (v->tab_env[++idx])
	{
		if (ft_strcmp(v->tab_env[idx][0], find[0]) == 0)
		{
			free_tabstr(find);
			if (join_export(NULL, param, 1) == 1)
				return (4);
			return (3);
		}
	}
	free_tabstr(find);
	return (0);
}

//Fonction qui va venir ajouter une nouvelle variable si
//celle-ci n'existe pas dans l'en tout en incrémentant de
//+1 la taille globale de notre env et de notre export
//(v->tab_len)
int	add_export(t_vars *v, char *param)
{
	int		idx;
	char	***new_env;

	v->tab_len += 1;
	new_env = malloc(sizeof(char **) * (v->tab_len + 1));
	if (!new_env)
		return (1);
	idx = -1;
	while (++idx < v->tab_len - 1)
	{
		new_env[idx] = malloc(2 * sizeof(char *));
		new_env[idx][0] = ft_strdup(v->tab_env[idx][0]);
		if (v->tab_env[idx][1])
			new_env[idx][1] = ft_strdup(v->tab_env[idx][1]);
		else
			new_env[idx][1] = NULL;
	}
	new_env[idx] = split_export(param);
	if (!new_env[idx])
		return (1);
	new_env[idx + 1] = NULL;
	free_matrix(v->tab_env);
	v->tab_env = new_env;
	return (0);
}

//Fonction qui va venir mettre à jour le composant d'une 
//variable de l'env si celle-ci existe déjà
int	update_export(t_vars *v, char *param)
{
	int		idx;
	char	**update;
	char	***new_env;

	update = split_export(param);
	new_env = malloc(sizeof(char **) * (v->tab_len + 1));
	if (!update || !new_env)
		return (1);
	idx = -1;
	while (v->tab_env[++idx])
	{
		if (ft_strcmp(v->tab_env[idx][0], update[0]) == 0)
			new_env[idx] = copy_env(v->tab_env[idx][0], update[1]);
		else
			new_env[idx] = copy_env(v->tab_env[idx][0], v->tab_env[idx][1]);
	}
	new_env[idx] = NULL;
	free_matrix(v->tab_env);
	v->tab_env = new_env;
	free_tabstr(update);
	return (0);
}

//Fonction qui va venir joindre deux chaine de caracteres 
//dans le cas du +=
int	join_export(t_vars *v, char *param, int select)
{
	int		idx;
	char	*tmp;
	char	**join;

	idx = -1;
	if (select == 1)
	{
		while (param[++idx])
			if (param[idx] == '+' && param[idx + 1] == '=')
				return (1);
		return (0);
	}
	join = split_export(param);
	while (v->tab_env[++idx])
	{
		if (ft_strcmp(v->tab_env[idx][0], join[0]) == 0)
		{
			tmp = ft_strjoin(v->tab_env[idx][1], join[1]);
			free(v->tab_env[idx][1]);
			v->tab_env[idx][1] = ft_strdup(tmp);
			free(tmp);
		}
	}
	free_tabstr(join);
	return (0);
}

//Fonction pricipale du vin env//
int	builtin_export(t_vars *v, char **param)
{
	int		idx;
	int		ret;

	idx = -1;
	ret = 0;
	if (!param[0] || !param)
		return (sort_export(v));
	while (param[++idx])
	{
		ret = find_export(v, param[idx]);
		if (ret == 1)
			return (error_export(param[idx]));
		else if ((ret == 3 && update_export(v, param[idx]) == 1)
			|| (ret == 0 && add_export(v, param[idx]) == 1)
			|| (ret == 4 && join_export(v, param[idx], 0) == 1))
			return (1);
	}
	return (0);
}
