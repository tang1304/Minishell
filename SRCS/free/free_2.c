/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:33:48 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/09 09:03:38 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	free_content_cmd_node(t_command *tmp)
{
	if (tmp->cmd != NULL)
		ft_free_pp(tmp->cmd);
	if (tmp->infile != NULL)
		free(tmp->infile);
	if (tmp->outfile != NULL)
		free(tmp->outfile);
	tmp->infile = NULL;
	tmp->outfile = NULL;
	tmp->prev = NULL;
	tmp->next = NULL;
	free(tmp);
	tmp = NULL;
}

void	free_content_env_node(t_env *tmp)
{
	if (tmp->var_name != NULL)
		free(tmp->var_name);
	if (tmp->var_value != NULL)
		free(tmp->var_value);
	tmp->prev = NULL;
	tmp->next = NULL;
	free(tmp);
	tmp = NULL;
}

void	free_loop(t_data *data)
{
	free_data(data, &free_cmd_strct);
	if (!data->paths || data->paths[0] != NULL)
		ft_free_paths(data);
	free_data(data, &free_hd_strct);
	if (data->str)
	{
		free(data->str);
		data->str = NULL;
	}
}

void	free_all(t_data *data)
{
	close_files(data);
	free_data(data, &free_cmd_strct);
	free_data(data, &free_lexer_strct);
	free_data(data, &free_hd_strct);
	free_data(data, &free_env_strct);
	free_data_strct(data);
	if (data->fdin > 0)
	{
		close(data->fdin);
		data->fdin = 0;
	}
	if (data->fdout > 0)
	{
		close(data->fdout);
		data->fdout = 0;
	}
}

void	free_data(t_data *data, void (*f)(t_data *data))
{
	(*f)(data);
}
