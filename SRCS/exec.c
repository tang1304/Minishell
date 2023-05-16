/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:47:12 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/16 14:15:12 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	join_path_and_cmd(t_data *data, char *cmd, int i)
{
	data->path = ft_strjoin(data->paths[i], cmd);
	if (data->path == NULL)
	{
		// free_split(data->paths);
		perror("malloc error");
	}
}

static void	check_if_absolute_path(t_data *data, char **cmd)
{
	int	fd;

	if ((cmd[0][0] == '.' && cmd[0][1] == '/' && !ft_isalnum(cmd[0][2])) \
	|| (cmd[0][0] == '/' && (!ft_isalnum(cmd[0][1]) || cmd[0][1] == '/')))
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": Is a directory\n", 18);
		// free_split(cmd);
		// pre_check_cmd_error(data);
		exit(SUCCESS);
	}
	fd = open(cmd[0], O_RDONLY);
	if (fd == -1 || access(cmd[0], X_OK))
	{
		perror(cmd[0]);
		// free_split(cmd);
		// pre_check_cmd_error(data);
		exit(SUCCESS);
	}
	if (execve(cmd[0], cmd, data->envp) == -1)
	{
		close(fd);
		// execve_error(data, cmd);
		exit(SUCCESS);
	}
}

static void	pre_check_on_cmd(t_data *data, char **cmd)
{
	(void)data;

	if (cmd[0][0] == '.' && !cmd[0][1])
	{
		write(2, ".: filename argument required\n", 30);
		write(2, ".: usage: . filename [arguments]\n", 33);
		// pre_check_cmd_error(data);
		exit(SUCCESS);
	}
}

static void	loop_on_path(t_data *data, char **cmd_args)
{
	int		i;
	char	*cmd;

	i = -1;
	cmd = ft_strjoin("/", cmd_args[0]);
	if (cmd == NULL)
	{
	// 	free(data->children);
	// 	free_split(data->paths);
	// 	free_split(cmd_args);
		perror("Malloc error");
	}
	if (data->paths == NULL)
		return ;
	while (data->paths[++i])
	{
		join_path_and_cmd(data, cmd, i);
		if (access(data->path, X_OK) == 0)
		{
			if (execve(data->path, cmd_args, data->envp) == -1)
				// execve_error(data, cmd_args);
				exit(SUCCESS);
		}
		free(data->path);
	}
	// free_all(data, cmd_args, cmd, i);
}

void	exec(t_data *data, char **cmd)
{
	pre_check_on_cmd(data, cmd);
	if (cmd[0] == NULL)
	{
		// free(data->children);
		// free_split(cmd);
		// free_split(data->paths);
		// close_fds(data);
		// get_cmd_error(argv);
		exit(SUCCESS);
	}
	if (ft_strchr(cmd[0], '/') != NULL)
		check_if_absolute_path(data, cmd);
	loop_on_path(data, cmd);
	// close_fds(data);
	// get_cmd_error(argv);
	exit(SUCCESS);
}
