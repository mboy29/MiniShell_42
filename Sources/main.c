/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:14:35 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/12 14:00:46 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_vars *v, char **e)
{
	g_sig.exit_code = 0;
	g_sig.pid = 0;
	g_sig.interrupt_hd = 0;
	v->in_cpy = dup(STDIN_FILENO);
	v->out_cpy = dup(STDOUT_FILENO);
	buitlin_init(v, e);
}

int	line_status(char *line)
{
	int		i;
	char	quote;
	int		last_ch_is_pipe;

	if (!*line)
		return (1);
	i = -1;
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
			quote = line[i] * (quote == 0) + quote * (line[i] != quote);
		if (line[i] == '|')
			last_ch_is_pipe = 1;
		else if (line[i] != ' ')
			last_ch_is_pipe = 0;
	}
	if (quote != 0 || last_ch_is_pipe == 1)
	{
		print_error(0, 4);
		return (258);
	}
	return (0);
}

int	launch2(t_vars *v)
{
	int	ret;

	ret = tokenize(v);
	free_tabstr(v->word_tab);
	dup2(v->in_cpy, STDIN_FILENO);
	if (g_sig.interrupt_hd == 1 || ret)
	{
		free_tkns(v->tkn_tab);
		if (g_sig.interrupt_hd == 1)
			return (1);
		if (ret)
			return (ret);
	}
	parser(v);
	free_tkns(v->tkn_tab);
	ret = exec(v);
	free_cmd(v->cmd, v->nb_cmd);
	free_tabstr(v->e);
	return (ret);
}

int	launch(t_vars *v, char *line)
{
	int		ret;
	char	*tmp;

	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	tmp = line;
	line = ft_strtrim(line, " ");
	free(tmp);
	ret = line_status(line);
	if (ret)
		return (ret * (ret != 1) + g_sig.exit_code * (ret == 1));
	add_history(line);
	ret = lexer(v, line);
	free(line);
	if (ret)
	{
		free_tabstr(v->word_tab);
		return (ret);
	}
	return (launch2(v));
}

int	main(int ac, char **av, char **e)
{
	t_vars	v;
	char	*line;

	(void)av;
	if (ac != 1)
	{
		print_error("Usage : ./minishell\n", 3);
		return (1);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	init_vars(&v, e);
	while (1)
	{
		echo_control_seq(0);
		dup2(v.in_cpy, STDIN_FILENO);
		dup2(v.out_cpy, STDOUT_FILENO);
		g_sig.status = 0;
		line = readline("minishell> ");
		g_sig.status = 1;
		g_sig.exit_code = launch(&v, line);
		clear();
	}
	return (g_sig.exit_code);
}
