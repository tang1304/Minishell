/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:14:33 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/17 10:46:02 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"



void	signal_set(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.flags = SA_RESTART;
	sa.sa_handler = &handler_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}
