/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:11:24 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/02 08:54:58 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	handler_sigint(int	signal)
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

void	handler_exec_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		g_status = 128 + signal;//?
		exit (0);// exit (0); //penser a free tout dans le child + close pipes
	}
}
