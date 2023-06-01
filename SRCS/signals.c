/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:14:33 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/01 09:33:25 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	signal_set(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	// sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_sigint;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	signal_hd_set(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	// sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_hd_sigint;
	sigaction(SIGINT, &sa, NULL);
}
