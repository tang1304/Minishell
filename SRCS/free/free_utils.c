/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:25:20 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/09 13:35:40 by tgellon          ###   ########lyon.fr   */
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
		if (ptr[x] != NULL)
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

void	free_hd_limit(t_data *data)
{
	ft_putstr_fd(HEREDOC_LIMIT, STDOUT_FILENO);
	free_data(data, &free_lexer_strct);
	free_data(data, &free_env_strct);
	free_data_strct(data);
	if (data->stdin_save > 0)
		close(data->stdin_save);
	if (data->stdout_save > 0)
		close(data->stdout_save);
	exit(EXIT_FAILURE);
}
