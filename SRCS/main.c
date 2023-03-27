/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 07:28:41 by rrebois           #+#    #+#             */
/*   Updated: 2023/03/27 09:55:18 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int ac, char **av, char **envp)//https://github.com/maiadegraaf/minishell
{(void)av;(void)envp;
	if (ac != 1)
	{
		ft_putstr_fd("Error: Bad arguments\nRun ./minishell\n", 2);
		exit(0);
	}

	// Create a loop to have the display prompt until exit
	prompt_loop();
	return (0);
}
