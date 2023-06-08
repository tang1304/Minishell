/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:19:12 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/07 14:55:38 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	check_numeric(t_data *data, char **str)
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
			free_all(data);
			close_files(data);
			exit(2);
		}
		i++;
	}
	return ;
}

static void	exit_numeric(char **str)
{
	int			err;
	long long	code;

	if (str[1] && (ft_atoi_ll(str[1], &err) < 255 && err == 0))
		g_status = ft_atoi_ll(str[1], &err);
	else
	{
		code = ft_atoi_ll(str[1], &err);
		if (err == 1)
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", \
						str[1]);
			g_status = 2;
		}
		else
			g_status = code;
	}
}

void	ft_exit(t_data *data, char **str)
{
	printf("exit\n");
	if (!str[1])
	{
		free_all(data);
		close_files(data);
		exit(g_status);
	}
	check_numeric(data, str);
	if (str[2])
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		exit_error(data, NULL);
	}
	exit_numeric(str);
	free_all(data);
	close_files(data);
	exit(g_status);
}
