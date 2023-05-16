/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:14:33 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/16 15:46:16 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	signal_handler_sigquit()
{
	sigset_t	set;
	if (sigemptyset(&set) == -1)
		return ;
	if (sigaddset(&set, SIGQUIT) == -1)
		return ;
}

void	signal_handler_sigint()
{
	exit (5);
}

void	signal_m(int signal)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	if (signal == SIGQUIT)
	{
		sa.sa_handler = &signal_handler_sigquit;
		sigaction(signal, &sa, NULL);
	}
	// if (signal == SIGINT)
	// 	return ;
}

void	signal_heredoc(t_data *data)
{(void)data;
	struct sigaction	sa;
	int					signal;

	signal = 3;
	ft_bzero(&sa, sizeof(sa));
	if (SIGQUIT == signal)
	{
		sa.sa_handler = &signal_handler_sigquit;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (SIGINT == signal)
	{
		sa.sa_handler = &signal_handler_sigint;
		sigaction(SIGINT, &sa, NULL);
	}
}
