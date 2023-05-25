/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:19:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/25 13:14:19 by rrebois          ###   ########lyon.fr   */
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

void	both_dup2(t_data *data, int in, int out)
{
	(void)data;

	if (dup2(in, STDIN_FILENO) == -1)
	{
		// frees;
		exit(EXIT_SUCCESS);
	}
	if (dup2(out, STDOUT_FILENO) == -1)
	{
		// frees;
		exit(EXIT_SUCCESS);
	}
}
