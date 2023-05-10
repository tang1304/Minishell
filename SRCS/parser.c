/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:52:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/05 15:42:08 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// void	check_hidden_nodes(t_data *data)
// {
// 	t_lexer *tmp;

// 	tmp = data->lexer;
// 	while ()
// }

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
// Ajouter fonction pour checker si pipe apres et mettre valeur de pipe a 1.
	j = 0;
	tmp = data->lexer;
	while (tmp->index != i)
		tmp = tmp->next;
	while (i++ < x)
	{
		new->cmd[j] = ft_strdup(tmp->word);
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
		if (new->out_err == 0)
			new->out_err = tmp->out_err;
		j++;
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
	new->heredoc_num = -1;
	new->inf_err = 0;
	new->out_err = 0;
	new->pipe_b = 0;
	new->pipe_a = 0;
	new = fillup(data, i, x, new);
	cmd = add_cmd_node(cmd, new);
	return (cmd);
}

void	create_cmd_lst(t_data *data)//si ls |>out faut creer un autre node vide a la fin
{
	size_t		buffer;
	t_lexer		*tmp;
	t_command	*command;

	command = NULL;
	buffer = 0;
	tmp = data->lexer;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->token == NULL && tmp->word == NULL && lstlen(tmp) == 1)
		return ;// au cas ou on a <TODO par ex
	if (tmp->token == NULL)
	{
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
	}
	else
	{
		tmp = data->lexer;
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
	}
	data->cmd = command; //free tmp
	check_heredoc(data);

	//a la fin on peut free le lexer


	// TEST ls <TODO -l|wc >outfile -l <<eof
	// ls <TODO -l|wc >outfile -l <eof
	// ls <TODO -l <<eof|wc >outfile -l <<eof1 <<eof2 infile todo added instead of null

// 	int p;
// 	t_command *t;
// 	t = command;
// // printf("len cmdlst: %ld\n", lstlencmd(t));p = 0;
// 	while (t != NULL)
// 	{//printf("node %d:\n", p);p = 0;
// 		p = 0;
// 		while (t->cmd[p] != NULL)
// 		{
// 			printf("cmd[%d] = %s\n", p, t->cmd[p]);
// 			p++;
// 		}
// // 	printf("infile = %s\n", t->infile);
// // 	printf("inf_err= %d\n", t->inf_err);
// // 	printf("outfile = %s\n", t->outfile);
// // 	printf("out_err = %d\n", t->out_err);
// // 	printf("heredoc? = %d\n", t->heredoc_file);
// // 	printf("heredoc numba = %d\n", t->heredoc_num);
// 	t=t->next;
// 	}
// 	// END TEST
}
