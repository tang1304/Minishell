/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:28:26 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/02 15:12:03 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	command_init(t_data *data, t_command *cmd)
{
	close(data->pipe[0]);
	if (!cmd->cmd[0])
		return ;
	if (cmd->fdin != 0 && !cmd->heredoc_file)
	{
		if (cmd->inf_err > 0)
			return ;
		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
			return (perror("Error with infile dup2"));
	}
	if (cmd->fdout > 0)
	{
		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
			return (perror("Error with outfile dup2"));
	}
	else if (cmd->fdout == 0 && cmd->pipe_a)
	{
		if (dup2(data->pipe[1], STDOUT_FILENO) == -1)
			return (perror("Error with stdout dup2"));
	}
	close(data->pipe[1]);
}

static void	forking(t_data *data, t_command *cmd, int i)
{
	if (i == 0)
	{
		signal_exec_set();
		command_init(data, cmd);
		if (cmd->inf_err || cmd->out_err)
			exit_error(data);
		if (check_builtins(cmd->cmd) == SUCCESS)
		{
			builtins(data, cmd->cmd);
			exec_error_handle(data);
			g_status = 0;
			exit(g_status);
		}
		else
			exec(data, cmd->cmd);
	}
	else
	{
		if (cmd->pipe_a == 1)
			close(data->pipe[1]);
		if (dup2(data->pipe[0], STDIN_FILENO) == -1)
			return (perror("Error with parent dup2"));
		close(data->pipe[0]);
	}
}

static void	prepare_forking(t_data *data, t_command *cmd)
{
	silence_signals();
	heredoc_check(data, cmd);
	if (pipe(data->pipe) == -1)
	{
		perror("Pipe error");
		exit_error(data);
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("Fork error");
		exit_error(data);
	}
	forking(data, cmd, cmd->pid);
	close(data->pipe[1]);
}

static void	no_forking(t_data *data, t_command *cmd)
{
	builtins(data, cmd->cmd);
	if (data->stdin_save > 0 && data->stdout_save > 0)
	{
		if (close(data->stdin_save) == -1 || close(data->stdout_save) == -1)
			return (perror("Error with closing STDIN/STDOUT saves"));
	}
	if (cmd->heredoc_file)
	{
		close(data->hd->fd[cmd->heredoc_num][0]);
		close(data->hd->fd[cmd->heredoc_num][1]);
	}
	return ;
}

void	exec_cmd_lst(t_data *data)
{
	int			status;
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (lstlencmd(data->cmd) == 1 && check_builtins(tmp->cmd) == SUCCESS \
			&& (!tmp->fdout))
		{
			no_forking(data, tmp);
			return ;
		}
		else
			prepare_forking(data, tmp);
		tmp = tmp->next;
	}
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
