/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 04:45:50 by mboy              #+#    #+#             */
/*   Updated: 2021/09/23 17:17:53 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Fonction qui va venir supprimer la variable de notre env
//précisée en argument
int	delete_unset(t_vars *v, char *param)
{
	int		idx[2];
	char	***new_env;

	idx[0] = -1;
	idx[1] = 0;
	new_env = malloc(sizeof(char **) * (--v->tab_len + 1));
	if (!new_env)
		return (1);
	while (v->tab_env[++idx[0]])
	{
		if (ft_strcmp(param, v->tab_env[idx[0]][0]) != 0)
			new_env[idx[1]++] = copy_env(v->tab_env[idx[0]][0],
					v->tab_env[idx[0]][1]);
	}
	new_env[idx[1]] = NULL;
	free_matrix(v->tab_env);
	v->tab_env = new_env;
	return (0);
}

int	error_unset_bis(char *param)
{
	int	idx;

	idx = -1;
	while (param[++idx])
	{
		if (param[idx] == '!')
			return (1);
	}
	return (0);
}

int	error_unset(char *param)
{
	if (error_unset_bis(param) == 1)
	{
		ft_putstr_fd("minishel: unset: ", 2);
		ft_putstr_fd(ft_strchr(param, '!'), 2);
		ft_putstr_fd(": event not found\n", 2);
		return (1);
	}
	if (param[0] == '-')
	{
		ft_putstr_fd("minishel: unset: ", 2);
		ft_putchar_fd(param[0], 2);
		ft_putchar_fd(param[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
	else
	{
		ft_putstr_fd("minishel: unset: '", 2);
		ft_putstr_fd(param, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (1);
}

//Fonction principale du builtin unset
int	builtin_unset(t_vars *v, char **param)
{
	int		idx;

	idx = -1;
	while (param[++idx])
	{
		if (builtin_check(param[idx]) == 1)
			return (error_unset(param[idx]));
		else if (find_export(v, param[idx]) == 3)
		{
			if (delete_unset(v, param[idx]) == 1)
				return (1);
			else if (ft_strcmp(param[idx], "PATH") == 0)
				return (99);
		}
	}
	return (0);
}
