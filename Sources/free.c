/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:52:16 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/10 19:08:37 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tkns(t_token *tkn_list)
{
	int	cpt;

	cpt = -1;
	while (tkn_list[++cpt].type)
		if (tkn_list[cpt].str)
			free(tkn_list[cpt].str);
	free(tkn_list);
}

void	free_tabstr(char **tab)
{
	int	cpt;

	cpt = -1;
	while (tab[++cpt])
		free(tab[cpt]);
	free(tab);
}

void	free_cmd(t_cmd	*cmd_list, int n)
{
	int	cpt;

	cpt = -1;
	while (++cpt < n)
	{
		free_tkns(cmd_list[cpt].redir_tab);
		free_tabstr(cmd_list[cpt].av);
		free_tabstr(cmd_list[cpt].path);
	}
	free(cmd_list);
}

void	free_matrix(char ***matrix)
{
	int	cpt;

	cpt = -1;
	while (matrix[++cpt])
	{
		free(matrix[cpt][0]);
		if (matrix[cpt][1])
			free(matrix[cpt][1]);
		free(matrix[cpt]);
	}
	free(matrix);
}

void	free_vars(t_vars *v)
{
	free_cmd(v->cmd, v->nb_cmd);
	free(v->pwd);
	free(v->home);
	free_matrix(v->tab_env);
}
