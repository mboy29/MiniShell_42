/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:29:21 by mboy              #+#    #+#             */
/*   Updated: 2021/09/27 09:22:49 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Fonction qui va afficher l'element de tab_env
//suivant l'affichage de export dans bash
void	print_export(char **print)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(print[0], STDOUT_FILENO);
	if (print[1])
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(print[1], STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

//Fonction va chercher la chaine de caractere de
//dans tab_env qui suit directement min (order ASCII)
char	**min_export(t_vars *v, char **min)
{
	int		idx;
	char	**cur;

	idx = 0;
	while (ft_strcmp(min[0], v->tab_env[idx][0]) >= 0)
		idx++;
	cur = v->tab_env[idx];
	while (v->tab_env[++idx])
	{
		if (ft_strcmp(min[0], v->tab_env[idx][0]) < 0
			&& ft_strcmp(cur[0], v->tab_env[idx][0]) > 0)
			cur = v->tab_env[idx];
	}
	print_export(cur);
	return (cur);
}

//ft_split personalisé
char	**split_export(char *param)
{
	int		idx;
	char	**tmp;
	char	**split;

	idx = -1;
	tmp = NULL;
	if (join_export(NULL, param, 1) == 1)
		tmp = ft_split(param, '+');
	else
		tmp = ft_split(param, '=');
	split = malloc(sizeof(char *) * 3);
	split[0] = ft_strdup(tmp[0]);
	if (tmp[1] == 0)
		split[1] = 0;
	else
	{
		split[1] = ft_strdup(ft_strchr(param, '=') + 1);
		split[2] = 0;
	}
	free_tabstr(tmp);
	return (split);
}

//Fonction qui va trier tab_env par ordre ASCII
int	sort_export(t_vars *v)
{
	int		idx[2];
	char	**min;

	idx[0] = 0;
	min = v->tab_env[idx[0]];
	while (v->tab_env[++idx[0]])
	{
		if (ft_strcmp(min[0], v->tab_env[idx[0]][0]) > 0)
			min = v->tab_env[idx[0]];
	}
	print_export(min);
	idx[1] = -1;
	while (++idx[1] < v->tab_len - 1)
		min = min_export(v, min);
	return (0);
}

//Gestion d'erreur
int	error_export(char *param)
{
	if (param[0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(param[0], 2);
		ft_putchar_fd(param[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	else
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(param, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (1);
}
