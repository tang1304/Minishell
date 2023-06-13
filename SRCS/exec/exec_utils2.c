/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:20:04 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/13 10:34:07 by tgellon          ###   ########lyon.fr   */
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

void	loop_on_path(t_data *data, char **cmd_args, char *cmd, int i)
{
	join_path_and_cmd(data, cmd, i);
	if (access(data->path, X_OK) == 0)
	{
		if (execve(data->path, cmd_args, data->envp) == -1)
		{
			exec_error_handle(data);
			free(cmd);
			exit(g_status);
		}
	}
	free(data->path);
	data->path = NULL;
}
