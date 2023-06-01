/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:52:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/01 10:55:09 by rrebois          ###   ########lyon.fr   */
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
		return (NULL);
	ft_bzero(new, sizeof(t_command));
	new->cmd = (char **)malloc(sizeof(char *) * (x - i + 1));
	if (new->cmd == NULL)
		return (NULL);
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






	// TEST ls <TODO -l|wc >outfile -l <<eof
	// ls <TODO -l|wc >outfile -l <eof
	// ls <TODO -l <<eof|wc >outfile -l <<eof1 <<eof2 infile todo added instead of null

// 	int p;
// 	t_command *t;
// 	t = command;
// 	printf("\n\n\n");
// printf("len cmdlst = %ld\n", lstlencmd(t));p = 0;
// 	while (t != NULL)
// 	{printf("node %d:\n", p);p = 0;

// 		while (t->cmd[p] != NULL)
// 		{
// 			printf("cmd[%d] = %s\n", p, t->cmd[p]);
// 			p++;
// 		}
// 	printf("infile = %s\n", t->infile);
// 	printf("inf_err= %d\n", t->inf_err);
// 	printf("outfile = %s\n", t->outfile);
// 	printf("out_err = %d\n", t->out_err);
// 	printf("heredoc? = %d\n", t->heredoc_file);
// 	printf("heredoc numba = %d\n", t->heredoc_num);
// 	printf("pipe before = %d\n", t->pipe_b);
// 	printf("pipe after = %d\n", t->pipe_a);
// 	printf("fdin = %d\n", t->fdin);
// 	printf("fdout = %d\n", t->fdout);
// 	printf("\n");
// 	t=t->next;
// 	}
// 	printf("data fdin = %d\n", data->fdin);
// 	printf("data fdout = %d\n", data->fdout);
// // 	// END TEST
}
