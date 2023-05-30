/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:25:20 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/30 15:28:56 by tgellon          ###   ########lyon.fr   */
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
	if (hd->LIMITER == NULL)
		return ;
	while (hd->LIMITER[x] != 0)
	{
		free(hd->LIMITER[x]);
		hd->LIMITER[x] = NULL;
		x++;
	}
	free(hd->LIMITER);
	hd->LIMITER = NULL;
}
