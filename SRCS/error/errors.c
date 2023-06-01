/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:53:32 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/01 08:38:07 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	exit_error(t_data *data)
{
	free_all(data);
	if (data->stdin_save > 0 && data->stdout_save > 0)
	{
		close(data->stdin_save);
		close(data->stdout_save);
	}
	close(data->pipe[0]);
	close(data->pipe[1]);
	exit(EXIT_FAILURE);
}
