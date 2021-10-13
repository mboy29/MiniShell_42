/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:28:30 by mboy              #+#    #+#             */
/*   Updated: 2021/09/23 14:33:17 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Fonction primaire du builint pwd
int	builtin_pwd(t_vars *v, char **param)
{
	if (param[0] && param[0][0] == '-')
	{
		ft_putstr_fd("minishell: pwd: -", 2);
		ft_putchar_fd(param[0][1], 2);
		ft_putstr_fd(" invalid option\npwd: usage: pwd\n", 2);
		return (1);
	}
	ft_putstr_fd(v->pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', 2);
	return (0);
}
