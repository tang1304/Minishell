/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:19:14 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/25 14:31:32 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	close_heredoc_pipes(t_data *data) //ls<<a<<b<<c|wc<<d<<e segfaults
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
	close(data->stdin_save);
	close(data->stdout_save);
}
