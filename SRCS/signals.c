/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:14:33 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/26 13:39:38 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*	Commande exec OK -> 0
	Cmd not found -> 127
	Cmd found but not executable -> 126
	Ctrl-c -> 130
	Invalid option/arg dans builtin, ou pas d'acces a un dossier -> 2
	No
	ctrl-c dans heredoc
	ctrl-c dans exec
	ctrl-d dans exec
	ctrl-d dans heredoc
	ctrl-/ dans heredoc
	
*/

void	signal_set(void)
{return ;
	// struct sigaction	sa;

	// ft_bzero(&sa, sizeof(sa));
	// sa.flags = SA_RESTART;
	// sa.sa_handler = &handler_sigquit;
	// sigaction(SIGQUIT, &sa, NULL);
}
