/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:19:12 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/01 10:24:24 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	check_numeric(char **str)
{
	int	i;

	i = 0;
	while (str[1][i])
	{
		if (str[1][0] == '-' || str[1][0] == '+')
			i++;
		if (!ft_isdigit(str[1][i]))
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", \
						str[1]);
			exit(2);
		}
		i++;
	}
	return ;
}

void	ft_exit(t_data *data, char **str)
{
	printf("exit\n");
	if (!str[1])
	{
		free_all(data);
		if (data->stdin_save > 0 && data->stdout_save > 0)
		{
			if (close(data->stdin_save) == -1 || close(data->stdout_save) == -1)
				return (perror("Error with closing STDIN/STDOUT saves"));
		}
		exit(g_status);
	}
	if (str[2])
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		exit_error(data);
	}
	check_numeric(str);
	if (str[1] && ft_atoi(str[1]) < 255)
		g_status = ft_atoi(str[1]);
	// else if (str[1] && ft_atoi)
	free_all(data);
	if (data->stdin_save > 0 && data->stdout_save > 0)
	{
		if (close(data->stdin_save) == -1 || close(data->stdout_save) == -1)
			return (perror("Error with closing STDIN/STDOUT saves"));
	}
	exit(g_status);
}
