/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:44 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/17 19:05:56 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	file_check_access(t_data *data, char *file, int i)
{
	if (i == 0) // infile >
	{
		data->fdin = open(file, O_RDONLY);
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, R_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
	else if (i == 1) // outfile >
	{
		data->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, W_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
	else if (i == 2) // outfile append >>
	{
		data->fdout = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, W_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
}

void	check_redirection(t_data *data, char *token, char *filename)
{
	filename = str_quotes_removal(filename);
printf("\nfilename name: %s\n\n", filename);
	if (ft_strncmp(token, ">", 1) == 0 && ft_strlen(token) == 1) // outfile
	{printf("outfile\n");
		file_check_access(data, filename, 1);
		add_outfile(data, filename);
	}
	else if (ft_strncmp(token, ">>", 2) == 0 && ft_strlen(token) == 2) // out app
	{printf("outfile append\n");
		file_check_access(data, filename, 2);
		add_outfile(data, filename);
	}
	else if (ft_strncmp(token, "<", 1) == 0 && ft_strlen(token) == 1) // inf
	{printf("infile\n");
		file_check_access(data, filename, 0);
		add_infile(data, filename);
	}
	else
	{
		printf("Here_doc redirection\n");
		data->LIMITER = filename;
		data->here_doc = 1;
		//if (data->lexer->infile != NULL alors free et NULL dans function add infile avec hd)
	}
}

void	remove_nodes_redirection(t_lexer *lexer, size_t index)
{
	int		count;
	t_lexer	*tmp;
	t_lexer	*buffer;

	count = 2;
	tmp = lexer;
	while (tmp->next->index != index)
		tmp = tmp->next;
	buffer = tmp;
	while (count > 0)
	{
		tmp = buffer->next;
		if (tmp->next != NULL)
		{
			buffer->next = tmp->next;//aussi gerer tmp->prev
			tmp->next->prev = buffer;
		}
		else
			buffer->next = NULL;
		if (tmp->word != NULL)
		{printf("freeing word: %s\n", tmp->word);
			free(tmp->word);
		}

		if (tmp->token != NULL)
		{
			printf("freeing token: %s\n", tmp->token);free(tmp->token);
		}

		free(tmp);
		tmp = buffer;
		count --;
	}
}

void	token_check(t_data *data)//add si infile and outfile rights/ seg fault
{
	t_lexer	*tmp;


	//test
	size_t len;
	len = 0;
	tmp = data->lexer;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	printf("len: %ld\n", len);
	//endtest

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) != \
		0)
		{
			check_redirection(data, tmp->token, tmp->next->word);
			remove_nodes_redirection(data->lexer, tmp->index);
		}
		tmp = tmp->next;
	}



	// test
	len = 0;
	tmp = data->lexer;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	printf("len: %ld\n", len);


	t_data	*tmp2;
	tmp2 = data;
	while (tmp2->lexer != NULL)
	{
		ft_printf("\n\n");
if (tmp2->lexer->word != NULL)
	ft_printf("word node: %s\n", tmp2->lexer->word);
else
	ft_printf("token node: %s\n", tmp2->lexer->token);
ft_printf("infile: %s\n", tmp2->lexer->infile);
ft_printf("outfile: %s\n", tmp2->lexer->outfile);
ft_printf("h_doc: %d\n", tmp2->here_doc);
		tmp2->lexer = tmp2->lexer->next;
	}
	// end test
}
