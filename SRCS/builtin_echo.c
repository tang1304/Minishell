/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:08:28 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/04 10:08:49 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_echo(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1][0] == '-' && cmd[1][1] == 'n' && !cmd[1][2])
	{
		i++;
		while (cmd[++i])
			printf("%s", cmd[i]);
	}
	else
	{
		while (cmd[++i])
			printf("%s", cmd[i]);
		write(1, "\n", 1);
	}
}
