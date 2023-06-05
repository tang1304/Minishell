/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:53:32 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/05 10:28:22 by tgellon          ###   ########lyon.fr   */
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
	close_files(data);
	exit(EXIT_FAILURE);
}
