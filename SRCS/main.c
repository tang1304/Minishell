/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 07:28:41 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/03 09:57:23 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//https://github.com/maiadegraaf/minishell
int	main(int ac, char **av, char **envp)
{
	(void)av;
	t_data	data;

	if (ac != 1)
	{
		ft_putstr_fd("Error: Bad arguments\nRun ./minishell\n", 2);
		exit(0);
	}
	// Create a loop to have the display prompt until exit
	data_initialize(&data, envp);
	return (0);
}
