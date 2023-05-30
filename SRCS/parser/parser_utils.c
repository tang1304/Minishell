/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:14:42 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/30 15:11:16 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_command	*cmd_lst_end_node(t_data *data, t_command *command, t_lexer *tmp)
{
	size_t		buffer;

	buffer = 0;
	while (tmp->next != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) == 0)
		{
			command = cmd_node(data, buffer, tmp->index, command);
			buffer = tmp->index + 1;
		}
		tmp = tmp->next;
	}
	command = cmd_node(data, buffer, tmp->index + 1, command);
	return (command);
}

t_command	*cmd_lst(t_data *data, t_command *command, t_lexer *tmp)
{
	size_t		buffer;

	buffer = 0;
	while (tmp->next != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) == 0)
		{
			if (tmp->index == lstlen(data->lexer) - 1)
				break ;
			command = cmd_node(data, buffer, tmp->index, command);
			buffer = tmp->index + 1;
		}
		tmp = tmp->next;
	}
	command = cmd_node(data, buffer, tmp->index, command);
	return (command);
}

void	add_cmd_index(t_data *data)
{
	size_t		i;
	t_command	*tmp;

	i = 0;
	tmp = data->cmd;
	while (tmp != NULL)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
}

void	fillup_cmd_node(t_command *new, t_lexer *tmp)
{
	if (tmp->infile != NULL)
		new->infile = ft_strdup(tmp->infile);
	if (tmp->outfile != NULL)
		new->outfile = ft_strdup(tmp->outfile);
	if (tmp->hd_file != 0)
		new->heredoc_file = tmp->hd_file;
	if (tmp->hd_number != -1)
		new->heredoc_num = tmp->hd_number;
	if (new->inf_err == 0)
		new->inf_err = tmp->inf_err;
	if (new->pipe_b == 0)
		new->pipe_b = tmp->pipe_b;
	if (new->pipe_a == 0)
		new->pipe_a = tmp->pipe_a;
	if (new->fdin == 0)
		new->fdin = tmp->fdin;
	if (new->fdout == 0)
		new->fdout = tmp->fdout;
}
