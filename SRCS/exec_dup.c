/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:19:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/15 11:35:50 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	heredoc_check(t_command *cmd)
{
	if (cmd->heredoc_file)
	{
		printf("\nheredoc\n");
		if (!cmd->cmd[0] || !cmd->cmd)
			return (0);
		if (dup2(cmd->fd[0], STDIN_FILENO) == -1)
			return (perror("Error in heredoc dup2"), 0);
		if (cmd->fdout > 0)
		{
			if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
				return (perror("Error with outfile dup2"), 0);
		}
		if (close(cmd->fd[0]) == -1)
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
