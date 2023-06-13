/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:11:24 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/13 12:00:22 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	handler_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_status = 128 + signal;
}

void	handler_hd_sigint(int signal)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_done = 1;
	g_status = signal + 128;
}

void	handler_exec(int signal)
{
	if (signal == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		printf("Quit (core dumped)\n");
	}
	g_status = 128 + signal;
}

// void	handler_exec_sigquit(int signal)
// {printf("ici\n");
// 	write(1, "\n", 1);
// 	rl_replace_line("Quit (Core dumped)", 0);
// 	g_status = 128 + signal;
// }
