/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:33:48 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/16 10:10:51 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	free_lexer_strct(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (data->lexer != NULL)
	{
		data->lexer = data->lexer->next;
		free_content_lexer_node(tmp);
		tmp = data->lexer;
	}
	// free_content_lexer_node(data->lexer);
	// data->lexer = NULL;
}

void	free_cmd_strct(t_data *data)
{
	t_command	*tmp;

	tmp = data->cmd;
	while (data->cmd != NULL)
	{
		data->cmd = data->cmd->next;
		free_content_cmd_node(tmp);
		tmp = data->cmd;
	}
	// free_content_cmd_node(data->cmd);
	// data->cmd = NULL;
}

void	free_hd_struct(t_data *data)
{
	size_t	i;

	i = 0;
	ft_free_pp(data->hd->LIMITER);
	while (i++ < data->hd->hd_count)
		free(data->hd->fd[i]);
	free(data->hd->fd);
	data->hd->fd = NULL;
	data->hd->hd_count = 0;
	data->hd->heredoc = 0;
}

void	free_data(t_data *data, void(*f)())
{
	(*f)(data);
}
