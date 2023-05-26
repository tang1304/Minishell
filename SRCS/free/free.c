/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:33:48 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/26 14:36:18 by rrebois          ###   ########lyon.fr   */
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
	// free_content_cmd_node(data->cmd);
	// data->cmd = NULL;
}

void	free_data_strct(t_data *data)
{
	if (data->str)
		free(data->str);
	if (data->prompt)
		free(data->prompt);
	if (data->path)
		free(data->path);
	if (data->envp)
		ft_free_pp(data->envp);
	if (data->paths)
		ft_free_pp(data->paths);
}

void	free_hd_strct(t_data *data)
{
	data->hd->heredoc = 0;
	if (data->hd->LIMITER != NULL)
		ft_free_pp(data->hd->LIMITER);
	if (data->hd->fd != NULL) //pose problème, sans ça ça roule
	{
		while (data->hd->heredoc < data->hd->hd_count)
		{
			free(data->hd->fd[data->hd->heredoc]);
			data->hd->heredoc++;
		}
		free(data->hd->fd);
		free(data->hd->xpd);
	}
	data->hd->fd = NULL;
	data->hd->hd_count = 0;
	data->hd->heredoc = 0;
}

void	free_all(t_data *data)
{
	free_data(data, &free_cmd_strct);
	free_data(data, &free_lexer_strct);
	free_data(data, &free_hd_strct);
	free_data(data, &free_env_strct);
	free_data_strct(data);
}

void	free_data(t_data *data, void(*f)())
{
	(*f)(data);
}
