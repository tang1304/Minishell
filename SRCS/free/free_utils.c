/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:25:20 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/09 13:33:07 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	free_substr_strct(t_substr *s)
{
	// if (s->s)
	// 	free(s->s);
	// if (s->before)
	// 	free(s->before);
	if (s->middle)
		free(s->middle);
	if (s->after)
		free(s->after);
	if (s->sub_b)
		free(s->sub_b);
	if (s->sub_m)
		free(s->sub_m);
	if (s->sub_a)
		free(s->sub_a);
	ft_bzero(s, sizeof(t_substr));
}

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
