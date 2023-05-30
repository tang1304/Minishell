/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:19:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/29 13:26:51 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	heredoc_check(t_data *data, t_command *cmd)
{
	if (cmd->heredoc_file)
	{
		// if (!cmd->cmd[0] || !cmd->cmd)
		// 	return (0);
		printf("\nheredoc\n");
printf("test = %d\n", cmd->heredoc_num);
		if (dup2(data->hd->fd[cmd->heredoc_num][0], STDIN_FILENO) == -1)
			return (perror("Error in heredoc dup2"), 0);
		if (close(data->hd->fd[cmd->heredoc_num][0]) == -1)
			return (perror("Error in heredoc close"), 0);
		if (close(data->hd->fd[cmd->heredoc_num][1]) == -1)
			return (perror("Error in heredoc close"), 0);
		return (1);
	}
	return (0);
}

void	exec_error_handle(t_data *data)
{
	free_all(data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	close(data->stdin_save);
	close(data->stdout_save);
	close(data->fdin);
	close(data->fdout);
}
