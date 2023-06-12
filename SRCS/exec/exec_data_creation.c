/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:28:26 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/12 13:41:51 by tgellon          ###   ########lyon.fr   */
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
			exit_error(data, NULL);
		if (check_builtins(cmd->cmd) == SUCCESS)
		{
			builtins(data, cmd, cmd->cmd);
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
		exit_error(data, "minishell: pipe error: ");
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit_error(data, "minishell: fork error: ");
	forking(data, cmd, cmd->pid);
	close(data->pipe[1]);
}

static void	no_forking(t_data *data, t_command *cmd)
{
	if (cmd->inf_err || cmd->out_err)
		return ;
	builtins(data, cmd, cmd->cmd);
	if (data->stdin_save > 0 && data->stdout_save > 0)
	{
		if (close(data->stdin_save) == -1 || close(data->stdout_save) == -1)
			return (perror("Error with closing STDIN/STDOUT saves"));
		data->stdin_save = 0;
		data->stdout_save = 0;
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
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (lstlencmd(data->cmd) == 1 && check_builtins(tmp->cmd) == SUCCESS)
		{
			if ((tmp->fdout && ft_strncmp(tmp->cmd[0], "exit", 4) == 0) \
			|| (tmp->fdout && ft_strncmp(tmp->cmd[0], "cd", 2) == 0) \
			|| !tmp->fdout)
			{
				no_forking(data, tmp);
				return ;
			}
			else
				prepare_forking(data, tmp);
		}
		else
			prepare_forking(data, tmp);
		tmp = tmp->next;
	}
	exec_cmd_lst_wait(data);
}
