/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:33:48 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/16 10:52:41 by tgellon          ###   ########lyon.fr   */
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

void	free_all(t_data *data)
{
	free_data(data, &free_cmd_strct);
	free_data(data, &free_lexer_strct);
	free_data(data, &free_env_strct);
	free_data_strct(data);
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
