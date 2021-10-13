/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 04:45:33 by mboy              #+#    #+#             */
/*   Updated: 2021/09/24 23:11:24 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_n(char *str)
{
	int	i;

	i = 1;
	if (ft_strncmp(str, "-n", 2))
		return (0);
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

//Fonction pricipale du builtin echo
int	builtin_echo(char **param)
{
	int		idx;
	int		op_n;

	idx = 0;
	op_n = 1;
	if (param[idx] && is_all_n(param[idx]))
	{
		op_n = 0;
		idx++;
	}
	while (param[idx] && is_all_n(param[idx]))
		idx++;
	idx--;
	while (param[++idx])
	{
		ft_putstr_fd(param[idx], STDOUT_FILENO);
		if (param[idx + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (op_n == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
