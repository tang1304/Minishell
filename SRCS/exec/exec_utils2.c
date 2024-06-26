/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:20:04 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/13 12:04:11 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	exec_cmd_lst_wait(t_data *data)
{
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		waitpid(tmp->pid, &g_status, 0);
		tmp = tmp->next;
	}
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	else if (WIFSIGNALED(g_status))
		g_status = 128 + WTERMSIG(g_status);
	signal_set();
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
