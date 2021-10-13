/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 04:45:26 by mboy              #+#    #+#             */
/*   Updated: 2021/09/27 12:06:24 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rm_last(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] != '/')
		i--;
	if (i > 0)
		str[i] = 0;
	else
		str[i + 1] = 0;
}

void	ft_add_suffix(char **str, char *suffix)
{
	int		i;
	int		i_suf;
	char	*new_str;

	i = -1;
	i_suf = -1;
	new_str = malloc(ft_strlen(*str) + ft_strlen(suffix) + 2);
	while ((*str)[++i])
		new_str[i] = (*str)[i];
	if ((*str)[i - 1] != '/')
		new_str[i++] = '/';
	while (suffix[++i_suf])
		new_str[i++] = suffix[i_suf];
	new_str[i] = 0;
	free(*str);
	*str = new_str;
}

char	*ft_absolute_path(t_vars *v, char *p)
{
	char	*ret;
	char	**path;
	int		i;

	if (!p)
		return (ft_strdup(v->home));
	if (p[0] == '/')
		ret = ft_strdup("/");
	else
		ret = ft_strdup(v->pwd);
	path = ft_split(p, '/');
	i = -1;
	while (path[++i])
	{
		if (ft_strncmp(path[i], ".", 2))
		{
			if (!ft_strncmp(path[i], "..", 3))
				ft_rm_last(ret);
			else
				ft_add_suffix(&ret, path[i]);
		}
	}
	free_tabstr(path);
	return (ret);
}

void	ft_update_env(t_vars *v, char *new_pwd)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", v->pwd);
	update_export(v, tmp);
	free(tmp);
	tmp = ft_strjoin("PWD=", new_pwd);
	update_export(v, tmp);
	free(tmp);
	free(v->pwd);
	v->pwd = ft_strdup(new_pwd);
}

int	builtin_cd(t_vars *v, char **p)
{
	char	*new_pwd;

	new_pwd = ft_absolute_path(v, p[0]);
	if (chdir(new_pwd) < 0)
	{
		free(new_pwd);
		ft_putstr_fd("minishel: cd: ", 2);
		ft_putstr_fd(p[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	ft_update_env(v, new_pwd);
	free(new_pwd);
	return (0);
}
