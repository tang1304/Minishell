/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:25:20 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/02 15:26:05 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_free_pp(char **ptr)
{
	size_t	x;

	x = 0;
	if (ptr == NULL)
		return ;
	while (ptr[x] != 0)
	{
		free(ptr[x]);
		ptr[x] = NULL;
		x++;
	}
	free(ptr);
	ptr = NULL;
}

void	ft_free_paths(t_data *data)
{
	size_t	x;

	x = 0;
	if (data->paths == NULL)
		return ;
	while (data->paths[x] != 0)
	{
		free(data->paths[x]);
		data->paths[x] = NULL;
		x++;
	}
	free(data->paths);
	data->paths = NULL;
}

void	ft_free_limiter(t_heredoc *hd)
{
	size_t	x;

	x = 0;
	if (hd->limiter == NULL)
		return ;
	while (hd->limiter[x] != 0)
	{
		free(hd->limiter[x]);
		hd->limiter[x] = NULL;
		x++;
	}
	free(hd->limiter);
	hd->limiter = NULL;
}
