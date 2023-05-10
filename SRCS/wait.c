/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:00:10 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/10 13:02:10 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	wait_child(t_data *data)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < lstlencmd(data->cmd))
	{
		waitpid(data->pids[i], &status, 0);
		i++;
	}
}
