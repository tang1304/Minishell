/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:20:04 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/08 15:20:23 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	exec_cmd_lst_wait(t_data *data)
{
	t_command	*tmp;
	int			status;

	tmp = data->cmd;
	while (tmp)
	{
		waitpid(tmp->pid, &status, 0);
		tmp = tmp->next;
	}
	signal_set();
	g_status = WEXITSTATUS(status);
	restore_stds(data);
}
