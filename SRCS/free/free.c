/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:33:48 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/05 09:12:15 by rrebois          ###   ########lyon.fr   */
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
}

void	free_env_strct(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (data->env != NULL)
	{
		data->env = data->env->next;
		free_content_env_node(tmp);
		tmp = data->env;
	}
}

void	free_data_strct(t_data *data)
{
	if (data->str != NULL)
	{
		free(data->str);
		data->str = NULL;
	}
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
	if (data->envp)
		ft_free_pp(data->envp);
	if (data->paths)
		ft_free_paths(data);
}

void	free_hd_strct(t_data *data)
{
	data->hd->heredoc = 0;
	if (data->hd->limiter)
		ft_free_limiter(data->hd);
	if (data->hd->fd != NULL)
	{
		while (data->hd->heredoc < data->hd->hd_count)
		{
			free(data->hd->fd[data->hd->heredoc]);
			data->hd->heredoc++;
		}
		free(data->hd->fd);
	}
	if (data->hd->xpd != NULL)
	{
		free(data->hd->xpd);
		data->hd->xpd = NULL;
	}
	data->hd->fd = NULL;
	data->hd->hd_count = 0;
	data->hd->heredoc = 0;
}
