/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:25:20 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/30 13:33:16 by tgellon          ###   ########lyon.fr   */
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
