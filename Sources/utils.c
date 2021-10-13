/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:40:21 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/11 17:13:24 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "cd", 3) || !ft_strncmp(str, "export", 7))
		return (1);
	if (!ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "exit", 5))
		return (1);
	if (!ft_strncmp(str, "env", 4) || !ft_strncmp(str, "echo", 5))
		return (1);
	if (!ft_strncmp(str, "pwd", 4))
		return (1);
	return (0);
}

int	get_type(char *str)
{
	if (!str)
		return (END);
	if (!ft_strncmp(str, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(str, "<", 2))
		return (LEFT);
	else if (!ft_strncmp(str, ">", 2))
		return (RIGHT);
	else if (!ft_strncmp(str, "<<", 3))
		return (LLEFT);
	else if (!ft_strncmp(str, ">>", 3))
		return (RRIGHT);
	else
		return (TXT);
}

char	*get_tabenv(t_vars *v, char *key)
{
	int		i;
	char	*value;

	i = -1;
	while (v->tab_env[++i])
	{
		if (!ft_strcmp(v->tab_env[i][0], key))
		{
			if (v->tab_env[i][1])
				value = ft_strdup(v->tab_env[i][1]);
			else
			{
				value = malloc(1);
				value[0] = 0;
			}
			return (value);
		}
	}
	value = malloc(1);
	value[0] = 0;
	return (value);
}

void	clear(void)
{
	int		cpt;
	char	*tmp;
	char	*tmp2;

	cpt = 0;
	tmp = ft_itoa(cpt);
	tmp2 = ft_strjoin(".tmp", tmp);
	while (!access(tmp2, F_OK))
	{
		unlink(tmp2);
		free(tmp);
		free(tmp2);
		cpt++;
		tmp = ft_itoa(cpt);
		tmp2 = ft_strjoin(".tmp", tmp);
	}
	free(tmp);
	free(tmp2);
	g_sig.interrupt_hd = 0;
}
