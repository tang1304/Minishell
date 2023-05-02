/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:52:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/02 08:50:26 by rrebois          ###   ########lyon.fr   */
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
		if (tmp->infile != NULL)
			new->infile = ft_strdup(tmp->infile);
		if (tmp->outfile != NULL)
			new->outfile = ft_strdup(tmp->outfile);
		new->heredoc_file = data->hd->hd_as_inf;
		j++;
		i++;
		tmp = tmp->next;
	}
	new->cmd[j] = 0;
	return (new);
}

static t_command	*cmd_node(t_data *data, size_t i, size_t x, t_command *cmd)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->cmd = (char **)malloc(sizeof(char *) * (x - i + 1));
	if (new->cmd == NULL)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->heredoc_file = 0;
	new = fillup(data, i, x, new);
	cmd = add_cmd_node(cmd, new);
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


	// TEST ls <TODO -l|wc >outfile -l <<eof segfaults
	// ls <TODO -l|wc >outfile -l <eof

	int p;
	t_command *t;
	t = command;
printf("len cmdlst: %ld\n", lstlencmd(t));p = 0;
	while (t != NULL)
	{printf("node %d:\n", p);p = 0;

		while (t->cmd[p] != NULL)
		{
			printf("cmd[%d] = %s\n", p, t->cmd[p]);
			p++;
		}
	printf("infile = %s\n", t->infile);
	printf("outfile = %s\n", t->outfile);
	printf("heredoc? = %d\n", t->heredoc_file);
	t=t->next;
	}
	// END TEST
}
