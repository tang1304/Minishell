/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:14:42 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/05 12:28:53 by rrebois          ###   ########lyon.fr   */
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
