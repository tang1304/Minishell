/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 07:28:41 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/26 10:39:44 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)av;
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (ac != 1)
	{
		ft_putstr_fd("Error: Bad arguments\nRun ./minishell\n", 2);
		exit(0);
	}
	data_initialize(&data, envp);
	return (0);
}
