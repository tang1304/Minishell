/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:14:33 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/02 09:01:10 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	signal_set(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	signal_hd_set(t_data *data)
{(void)data;
	struct sigaction	sa;

	g_status = 0;
	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = &handler_hd_sigint;
	sigaction(SIGINT, &sa, NULL);
	if (g_status == 130)
	{
		printf("You pressed Ctrl + C\n");
		exit(0);
	}

		// free_all(data);
}

void	signal_exec_set(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	// sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_exec_sigint;
	sigaction(SIGINT, &sa, NULL);
}

void	silence_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
