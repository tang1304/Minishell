/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:11:24 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/06 09:34:35 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	handler_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_status = 128 + signal;
}

void	handler_hd_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_status = signal + 128;
		return (exit(g_status));
		// exit (0); //penser a free tout dans le child + close pipes
	}
}

void	handler_exec_sigint(int signal) //ne rentre pas la
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_status = 128 + signal;//?
		return (exit(g_status));// exit (0); //penser a free tout dans le child + close pipes
	}
}

void	handler_exec_sigquit(int signal)
{
	if (signal == SIGQUIT)
	{
		write(1, "Quit (Core dumped)\n", 19);
		write(1, "\n", 1);
		rl_replace_line("Quit (Core dumped)", 0);
		g_status = 128 + signal;//?
		return (exit(g_status));// exit (0); //penser a free tout dans le child + close pipes
	}
}
