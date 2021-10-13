/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 04:52:02 by mboy              #+#    #+#             */
/*   Updated: 2021/10/10 18:37:26 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Init Builtin Structure
void	buitlin_init(t_vars *v, char **env)
{
	int			idx;

	idx = -1;
	get_env(v, env);
	while (++idx != v->tab_len)
	{
		if (ft_strcmp(v->tab_env[idx][0], "PWD") == 0)
			v->pwd = ft_strdup(v->tab_env[idx][1]);
		if (ft_strcmp(v->tab_env[idx][0], "HOME") == 0)
			v->home = ft_strdup(v->tab_env[idx][1]);
	}
	return ;
}

//Fonction vérifiant si le builtin passé en 
//argument existe

int	builtin_check(char *check)
{
	int	idx;

	idx = 0;
	if (check[0] != '_' && ft_isalpha(check[0]) == 0)
		return (1);
	while (check[++idx])
	{
		if (check[idx] != '_' && ft_isalnum(check[idx]) == 0)
			return (1);
	}
	return (0);
}

int	builtin_select(t_vars *v, t_cmd cmd)
{
	if (ft_strcmp(cmd.av[0], "env") == 0)
		return (builtin_env(v, cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "echo") == 0)
		return (builtin_echo(cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "pwd") == 0)
		return (builtin_pwd(v, cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "cd") == 0)
		return (builtin_cd(v, cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "export") == 0)
		return (builtin_export(v, cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "unset") == 0)
		return (builtin_unset(v, cmd.av + 1));
	else if (ft_strcmp(cmd.av[0], "exit") == 0)
		return (builtin_exit(v, cmd.av + 1));
	return (84);
}

//Fonction principial redirigeant faire la
//fonction builtin précisée en paramètre
int	builtin(t_vars *v, int cpt)
{
	return (builtin_select(v, v->cmd[cpt]));
}
