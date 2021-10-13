/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:08:23 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/11 17:12:44 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_pipes(t_vars *v, int cpt)
{
	if (cpt >= 1)
	{
		dup2(v->cmd[cpt - 1].pipefd[0], STDIN_FILENO);
		close(v->cmd[cpt - 1].pipefd[0]);
		close(v->cmd[cpt - 1].pipefd[1]);
	}
	if (cpt < v->nb_cmd - 1)
	{
		dup2(v->cmd[cpt].pipefd[1], STDOUT_FILENO);
		close(v->cmd[cpt].pipefd[0]);
		close(v->cmd[cpt].pipefd[1]);
	}
}

void	close_pipes(t_vars *v, int cpt)
{
	if (cpt >= 1)
	{
		close(v->cmd[cpt - 1].pipefd[0]);
		close(v->cmd[cpt - 1].pipefd[1]);
	}
}

void	exec_binary(t_cmd cmd, char **e)
{
	int		cpt;

	cpt = -1;
	if (cmd.av[0][0] == '.' || cmd.av[0][0] == '/')
	{
		execve(cmd.av[0], cmd.av, e);
		print_error(cmd.av[0], 2);
		exit(127);
	}
	while (cmd.path[++cpt])
	{
		execve(cmd.path[cpt], cmd.av, e);
	}
	print_error(cmd.av[0], 0);
	exit(127);
}

int	exec_pipeline(t_vars *v)
{
	int	cpt;
	int	ret;

	cpt = -1;
	while (++cpt < v->nb_cmd)
	{
		if (cpt < v->nb_cmd - 1)
			pipe(v->cmd[cpt].pipefd);
		v->cmd[cpt].pid = fork();
		if (v->cmd[cpt].pid == -1)
			exit(128);
		if (!v->cmd[cpt].pid)
		{
			dup_pipes(v, cpt);
			ret = redir(v->cmd[cpt].redir_tab);
			if (ret)
				exit(ret);
			atomic_exec(v, cpt);
		}
		close_pipes(v, cpt);
	}
	return (get_exit_code(v));
}

int	exec(t_vars *v)
{
	int	ret;

	if (v->nb_cmd == 1)
	{
		if (v->cmd[0].av[0] && is_builtin(v->cmd[0].av[0]))
		{
			ret = redir(v->cmd[0].redir_tab);
			if (ret)
				return (ret);
			return (builtin(v, 0));
		}
	}
	return (exec_pipeline(v));
}
