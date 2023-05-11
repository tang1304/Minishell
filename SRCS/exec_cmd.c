/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:11:50 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/11 08:47:49 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// int	get_cmd(t_data *data, int *fd, int i)
// {
// 	data->split = ft_split(data->av[i + 2], ' ');
// 	if (data->split[0] == NULL)
// 		error_cmd(data, i + 2);
// 	check_invalid_cmds(data);
// 	if (data->paths == NULL)
// 	{
// 		if (access(data->split[0], F_OK | X_OK) == 0)
// 		{
// 			child_process_path(i, data, data->split[0], fd);
// 			return (0);
// 		}
// 		else
// 			error_cmd(data, 0);
// 	}
// 	else
// 	{
// 		if (access(data->split[0], F_OK | X_OK) == 0)
// 		{
// 			child_process_path(i, data, data->split[0], fd);
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

// void	check_cmd_path(char *cmd, char *path, t_data *data)
// {(void)data;
// 	size_t	j;

// 	j = 0;
// 	while (cmd[j] != '\0')
// 	{
// 		if (cmd[j] == '/' && cmd[j + 1] == '/' && j + 1 < ft_strlen(cmd))
// 		{
// 			free(cmd);
// 			free(path);
// 			// error_cmd(data, 1);
// 		}
// 		j++;
// 	}
// }

// void	valid_cmd(size_t i, t_data *data)
// {
// 	int		j;
// 	char	*cmd;
// 	char	*path;

// 	j = 0;
// 	// if (get_cmd(data, fd, i) == 0)
// 	// 	return ;
// 	//check builtin if builtin
// 		// func then exit
// 	// else
// 	while (data->paths[j] != 0)
// 	{
// 		path = ft_strjoin(data->paths[j], "/");
// 		cmd = ft_strjoin(path, data->cmd[0]);
// 		// check_cmd_path(cmd, path, data); Pas sur si besoin de ca
// 		if (access(cmd, F_OK | X_OK) == 0)
// 		{
// 			free(path);
// 			// child_process(i, data, cmd, fd);
// 			return ;
// 		}
// 		free(path);
// 		free(cmd);
// 		j++;
// 	}
// 	// error_cmd(data, 0);
// }
