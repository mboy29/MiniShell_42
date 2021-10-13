/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 00:05:44 by alabalet          #+#    #+#             */
/*   Updated: 2021/10/11 02:43:04 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int code)
{
	(void)code;
	printf("\r");
	write(1, "\n", 1);
	if (g_sig.status == 1)
		g_sig.exit_code = 130;
	if (!g_sig.status)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig.exit_code = 1;
	}
	if (g_sig.status == 2)
	{
		close(0);
		g_sig.status = 1;
		g_sig.interrupt_hd = 1;
		g_sig.exit_code = 1;
	}
}

void	sigquit_handler(int code)
{
	(void)code;
	if (!g_sig.status || g_sig.status == 2)
	{
		printf("%c[2K", 27);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_sig.status == 1)
	{
		g_sig.exit_code = 131;
		printf("Quit: 3\n");
	}
}

void	echo_control_seq(int c)
{
	struct termios	conf;

	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == 1)
		conf.c_lflag |= ECHOCTL;
	else if (c == 0)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCSETA, &conf);
}
