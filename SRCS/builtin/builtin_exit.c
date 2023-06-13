/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:19:12 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/13 15:21:07 by tgellon          ###   ########lyon.fr   */
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

	err = 0;
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

static int	check_num_multiple_args(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '-' || str[0] == '+')
			i++;
		if (!ft_isdigit(str[i]))
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", \
						str[1]);
			free_all(data);
			close_files(data);
			exit(2);
		}
		i++;
	}
	ft_dprintf(2, "minishell: exit: too many arguments\n");
	g_status = 1;
	return (0);
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
		if (!check_num_multiple_args(data, str[1]))
			return ;
	}
	exit_numeric(str);
	free_all(data);
	close_files(data);
	exit(g_status);
}
