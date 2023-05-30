/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:53:32 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/29 14:08:03 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	exit_error(t_data *data)
{
	perror("Malloc error");
	free_all(data);
	if (data->stdin_save > 0 && data->stdout_save > 0)
	{
		if (close(data->stdin_save) == -1 || close(data->stdout_save) == -1)
			return (perror("Error with closing STDIN/STDOUT saves"));
	}
	close(data->pipe[0]);
	close(data->pipe[1]);
	exit(EXIT_SUCCESS);
}
