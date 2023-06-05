/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:19:14 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/05 10:45:59 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
// Close unused heredoc pipes in parent
void	close_heredoc_pipes(t_data *data)
{
	t_command	*tmp;
	int			i;

	if (lstlencmd(data->cmd) == 0)
	{
		close_all(data);
		return ;
	}
	i = 0;
	tmp = data->cmd;
	while (tmp != NULL)
	{
		if (i < tmp->heredoc_num)
		{
			while (i < tmp->heredoc_num)
			{
				close(data->hd->fd[i][0]);
				close(data->hd->fd[i][1]);
				i++;
			}
		}
		tmp = tmp->next;
	}
}

// Close remaining opened pipes in parent
static void	close_left_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->hd->hd_count)
	{
		close(data->hd->fd[i][0]);
		close(data->hd->fd[i][1]);
		i++;
	}
}

void	close_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->hd->hd_count)
	{
		close(data->hd->fd[i][0]);
		close(data->hd->fd[i][1]);
		i++;
	}
	if (data->stdin_save > 0)
	{
		close(data->stdin_save);
		data->stdin_save = 0;
	}
	if (data->stdout_save > 0)
	{
		close(data->stdout_save);
		data->stdout_save = 0;
	}
	close_files(data);
}

// Close infiles and outfiles opened
void	close_files(t_data *data)
{
	int	i;

	i = 0;
	if (data->maxfdin > data->maxfdout)
		i = data->maxfdin;
	else
		i = data->maxfdout;
	while (i > 2)
	{
		close(i);
		i--;
	}
	if (data->stdin_save > 0)
		close(data->stdin_save);
	if (data->stdout_save > 0)
		close(data->stdout_save);
	close_left_pipes(data);
}
