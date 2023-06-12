/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:19:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/09 16:15:37 by tgellon          ###   ########lyon.fr   */
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

void	join_path_and_cmd(t_data *data, char *cmd, int i)
{
	data->path = ft_strjoin(data->paths[i], cmd);
	if (data->path == NULL)
		exit_error(data, "minishell: malloc error: ");
}

void	restore_stds(t_data *data)
{
	if (dup2(data->stdin_save, STDIN_FILENO) == -1 \
	|| dup2(data->stdout_save, STDOUT_FILENO) == -1)
		return (perror("Error with restoring STDIN/STDOUT dup2"));
	if (close(data->stdin_save) == -1 || close(data->stdout_save) == -1)
		return (perror("Error with closing STDIN/STDOUT saves"));
}

void	extract_paths(t_data *data)
{
	char	*s;
	t_env	*tmp;

	tmp = data->env;
	s = NULL;
	while (tmp)
	{
		s = search_env(data, "PATH");
		if (s != NULL)
			break ;
		tmp = tmp->next;
	}
	if (s != NULL)
	{
		data->paths = ft_split(s, ':');
		if (!data->paths)
		{
			printf("ici\n");
			exec_error_handle(data);
		}
	}
}
