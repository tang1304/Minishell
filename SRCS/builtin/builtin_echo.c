/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:43:06 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/12 11:45:16 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	echo_n_check(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1][0] == '-')
	{
		while (cmd[1][++i])
		{
			if (cmd[1][i] != 'n')
				break ;
		}
	}
	if (cmd[1][i] == '\0')
	{
		i = 1;
		while (cmd[++i])
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1])
				printf(" ");
		}
		return (1);
	}
	return (0);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	n_check;

	i = 0;
	n_check = 0;
	if (cmd[1] == NULL)
		write(1, "\n", 1);
	else if (cmd[1][0] == '-' && cmd[1][1] == 'n')
		n_check = echo_n_check(cmd);
	if (n_check == 0 && cmd[1])
	{
		i = 0;
		while (cmd[++i])
		{
			printf("%s", cmd[i]);
			g_status = 0;
			if (cmd[i + 1])
				printf(" ");
		}
		printf("\n");
	}
	return (1);
}
