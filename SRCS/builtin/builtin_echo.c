/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:43:06 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/12 13:32:25 by tgellon          ###   ########lyon.fr   */
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

int	ft_echo(char **cmd, t_command *cmd_struct)
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
			if (cmd_struct->inf_err == 0 && cmd_struct->out_err == 0)
				g_status = 0;
			if (cmd[i + 1])
				printf(" ");
		}
		printf("\n");
	}
	return (1);
}
