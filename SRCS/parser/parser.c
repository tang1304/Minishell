/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:52:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/05 13:58:00 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static t_command	*add_cmd_node(t_command *command, t_command *new)
{
	t_command	*tmp;

	if (command == NULL)
		command = new;
	else
	{
		tmp = command;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (command);
}

static t_command	*fillup(t_data *data, size_t i, size_t x, t_command *new)
{
	size_t		j;
	t_lexer		*tmp;

	j = 0;
	tmp = data->lexer;
	while (tmp->index != i)
		tmp = tmp->next;
	while (i < x)
	{
		new->cmd[j] = ft_strdup(tmp->word);
		if (!new->cmd[j])
			exit_error(data, "minishell: malloc error: ");
		fillup_cmd_node(new, tmp);
		j++;
		i++;
		tmp = tmp->next;
	}
	new->cmd[j] = 0;
	return (new);
}

t_command	*cmd_node(t_data *data, size_t i, size_t x, t_command *cmd)
{
	t_command	*new;

	if (i == x)
		return (NULL);
	new = (t_command *)malloc(sizeof(*new));
	if (new == NULL)
		exit_error(data, "minishell: malloc error: ");
	ft_bzero(new, sizeof(t_command));
	new->cmd = (char **)malloc(sizeof(char *) * (x - i + 1));
	if (new->cmd == NULL)
		exit_error(data, "minishell: malloc error: ");
	new->heredoc_num = -1;
	new = fillup(data, i, x, new);
	cmd = add_cmd_node(cmd, new);
	return (cmd);
}

static void	update_data_structs(t_data *data)
{
	if (data->cmd != NULL)
	{
		free_data(data, &free_lexer_strct);
		add_cmd_index(data);
	}
	close_heredoc_pipes(data);
}

void	create_cmd_lst(t_data *data)
{
	t_lexer		*tmp;
	t_command	*command;

	command = NULL;
	tmp = data->lexer;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		if ((tmp->token == NULL && tmp->word == NULL && lstlen(tmp) == 1))
			return ;
		if (tmp->token == NULL)
		{
			tmp = data->lexer;
			command = cmd_lst_end_node(data, command, tmp);
		}
		else
		{
			tmp = data->lexer;
			command = cmd_lst(data, command, tmp);
		}
		data->cmd = command;
	}
	update_data_structs(data);
}
