/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:19:14 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/18 12:58:21 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	close_heredoc_pipes(t_data *data) //ls<<a<<b<<c|wc<<d<<e segfaults
{
	// t_command	*tmp;
	int			i;

	i = 0;
	// tmp = data->cmd;
	// while (tmp != NULL)
	// {
		// if (tmp->heredoc_num > -1)
		// {
			while (i < data->hd->hd_count)
			{
				close(data->hd->fd[i][0]);
				close(data->hd->fd[i][1]);
				i++;
			}
	// 		i++;
	// 	}
	// 	tmp = tmp->next;
	// }
}
