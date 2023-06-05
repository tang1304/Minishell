/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:53:32 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/05 16:01:40 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	exit_error(t_data *data, char *str)
{
	if (str)
		perror(str);
	free_all(data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	close_all(data);//changed fro; close_files to close all
	exit(EXIT_FAILURE);
}

void	ascii_check(t_data *data, char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < 0 || str[i] > 126)
			exit_error(data, "minishell: non ASCII char");
	}
}
