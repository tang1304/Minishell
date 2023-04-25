/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:43:06 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/25 09:45:59 by tgellon          ###   ########lyon.fr   */
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
