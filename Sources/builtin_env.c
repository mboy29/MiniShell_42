/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 04:45:41 by mboy              #+#    #+#             */
/*   Updated: 2021/09/27 17:49:24 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Fonction stockant une copie de l'env dans v->tab_env
//et qui va attribuer à la variable v->pwd notre emplacement
//actuel (substitu d'une fonction builtin_pwd)

char	**copy_env(char *key, char *val)
{
	char	**ret;

	ret = malloc(2 * sizeof(char *));
	ret[0] = ft_strdup(key);
	if (val)
		ret[1] = ft_strdup(val);
	else
		ret[1] = 0;
	return (ret);
}

void	get_env(t_vars *v, char **env)
{
	int		idx;

	idx = -1;
	v->tab_len = ft_tablen((void **)env);
	v->tab_env = malloc(sizeof(char **) * (v->tab_len + 1));
	while (++idx != v->tab_len)
	{
		v->tab_env[idx] = ft_split(env[idx], '=');
		if (ft_strcmp(v->tab_env[idx][0], "OLDPWD") == 0)
		{
			free(v->tab_env[idx][1]);
			v->tab_env[idx][1] = 0;
		}
	}
	v->tab_env[idx] = NULL;
}

int	print_env(t_vars *v)
{
	int		idx;

	idx = -1;
	while (v->tab_env[++idx])
	{
		if (v->tab_env[idx][1])
		{
			ft_putstr_fd(v->tab_env[idx][0], STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(v->tab_env[idx][1], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
	return (0);
}

//Fonction pricipale du builtin env
int	builtin_env(t_vars *v, char **param)
{
	if (!param[0])
	{
		print_env(v);
		return (0);
	}
	else if (param[0] || param[0][0] == '-')
	{
		ft_putstr_fd("minishell: env: --", 2);
		ft_putchar_fd(param[0][1], 2);
		ft_putstr_fd(": invalid option\nenv: usage: env\n", 2);
		return (1);
	}
	return (0);
}
