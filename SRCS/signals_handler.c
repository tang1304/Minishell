/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:11:24 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/26 13:06:50 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	handler_sigint(int	signal)
{
	if (signal != SIGINT)
		return ;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler_hd_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	if (signal == SIGINT)
		exit (0); //penser a free tout dans le child
}
