/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:47:12 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/02 14:23:50 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	access_checks(t_data *data, char **cmd)
{
	DIR	*check;

	check = opendir(cmd[0]);
	if (check != NULL)
	{
		ft_dprintf(2, "minishell: %s : Is a directory\n", cmd[0]);
		exec_error_handle(data);
		closedir(check);
		g_status = 126;
		exit(g_status);
	}
	if (access(cmd[0], F_OK) != 0)
	{
		perror(cmd[0]);
		exec_error_handle(data);
		g_status = 127;
		exit(g_status);
	}
	if (access(cmd[0], X_OK) != 0)
	{
		perror(cmd[0]);
		exec_error_handle(data);
		g_status = 126;
		exit(g_status);
	}
}

static void	check_if_absolute_path(t_data *data, char **cmd)
{
	if ((cmd[0][0] == '.' && cmd[0][1] == '/' && !ft_isalnum(cmd[0][2])) \
	|| (cmd[0][0] == '/' && (!ft_isalnum(cmd[0][1]) || cmd[0][1] == '/')))
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": Is a directory\n", 17);
		exec_error_handle(data);
		g_status = 126;
		exit(g_status);
	}
	access_checks(data, cmd);
	if (execve(cmd[0], cmd, data->envp) == -1)
	{
		perror(cmd[0]);
		exec_error_handle(data);
		g_status = 127;
		exit(g_status);
	}
}

static void	pre_check_on_cmd(t_data *data, char **cmd)
{
	(void)data;
	if (cmd[0][0] == '.' && !cmd[0][1])
	{
		write(2, "minishell: .: filename argument required\n", 41);
		write(2, ".: usage: . filename [arguments]\n", 33);
		if (close(data->stdin_save) == -1 || close(data->stdout_save) == -1)
			return (perror("Error with closing STDIN/STDOUT saves"));
		exec_error_handle(data);
		g_status = 2;
		exit(g_status);
	}
}

static void	loop_on_path(t_data *data, char **cmd_args)
{
	int		i;
	char	*cmd;

	if (!data->paths || !data->paths[0])
		return ;
	i = -1;
	cmd = ft_strjoin("/", cmd_args[0]);
	if (cmd == NULL)
		exit_error(data);
	while (data->paths[++i])
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
	free(cmd);
}

void	exec(t_data *data, char **cmd)
{
	pre_check_on_cmd(data, cmd);
	if (cmd[0] == NULL)
	{
		exec_error_handle(data);
		g_status = 127;
		exit(g_status);
	}
	if (ft_strchr(cmd[0], '/') != NULL)
		check_if_absolute_path(data, cmd);
	loop_on_path(data, cmd);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
	exec_error_handle(data);
	g_status = 127;
	exit(g_status);
}
