/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:19:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/02 11:25:51 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	heredoc_check(t_data *data, t_command *cmd)
{
	if (cmd->heredoc_file)
	{
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
	close_files(data);
}
