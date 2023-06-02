/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:14:33 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/02 11:45:05 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	signal_set(void)
{
	struct sigaction	sa;

	// ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	signal_hd_set(void)
{
	struct sigaction	sa;

	// ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = &handler_hd_sigint;
	sigaction(SIGINT, &sa, NULL);
}

void	signal_exec_set(void)
{
	struct sigaction	sa;
  
	// ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_exec_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = &handler_exec_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
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
