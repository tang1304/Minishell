/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:52:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/28 13:26:31 by rrebois          ###   ########lyon.fr   */
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
	}printf("OKIE DOKIE\n");
	return (command);
}

static t_command	*cmd_node(t_data *data, size_t i, size_t x, t_command *cmd)
{
	size_t		j;
	t_lexer		*tmp;
	t_command	new;
printf("buffer = %ld index = %ld\n", i, x);
	j = 0;
	tmp = data->lexer;
	while (tmp->index != i)
		tmp = tmp->next;
	new.cmd = (char **)malloc(sizeof(char *) * (x - i + 1));
	if (new.cmd == NULL)
		return (NULL);
	while (i < x)
	{
		new.cmd[j] = ft_strdup(tmp->word);
		if (tmp->infile != NULL)
			new.infile = ft_strdup(tmp->infile);
		if (tmp->outfile != NULL)
			new.outfile = ft_strdup(tmp->outfile);
		new.heredoc_file = data->hd->hd_as_inf;
		new.next = NULL;
		new.prev = NULL;
		j++;
		i++;
		tmp = tmp->next;
	}
	new.cmd[j] = 0;
	cmd = add_cmd_node(cmd, &new);
	return (cmd);
}

void	create_cmd_lst(t_data *data)
{
	size_t		buffer;
	t_lexer		*tmp;
	t_command	*command;

	command = NULL;
	buffer = 0;
	tmp = data->lexer;
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
	//a la fin on peut free le lexer

printf("Finished creating cmd nodes\n");

	// TEST ls >out -l| wc

	// int p;
	t_command *t;
	t = command;
printf("cmd[%d] = %s\n", 0, t->cmd[0]);
	// while (t != NULL)
	// {printf("node\n");
	// 	// p = 0;
	// 	// while (t->cmd[p] != NULL)
	// 	// {
	// 		// printf("cmd[%d] = %s\n", 0, t->cmd[0]);
	// 	// 	p++;
	// 	// }
	// // printf("infile = %s\n", t->infile);
	// t=t->next;
	// }
	// END TEST
}
