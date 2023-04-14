/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:44 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/14 10:25:57 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h" // Get filename and check file permissions.

char	*filename_quote_removal(char *file)
{
	char	*filename;

	filename = str_quote_removal(file);
	free(file);
	return (filename);
}

void	file_check_access(t_data *data, char *file, int i)
{
	if (i == 2) // infile <
	{
		data->fdin = open(file, O_RDONLY);
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, R_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
	else if (i == 1) //outfile >
	{
		data->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, W_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
	else if (i == 0) //outfile append >>
	{
		data->fdout = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, W_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
}

static void	init_here_doc(t_data *data, char *filename)
{
	data->LIMITER = filename;
	data->here_doc = 1;
	add_infile(data, NULL);
}

void	files_redirection(t_data *data, int index, size_t i)
{
	t_lexer	*tmp;
	char	*filename;

	tmp = data->lexer;
	while (tmp->index != index)
		tmp = tmp->next;
	filename = get_filename(tmp->word, i);
	if (tmp->word[i] == '>' && tmp->word[i + 1] == '>') //outfile append
	{
ft_printf("out app: %s\n", filename);
		file_check_access(data, filename, 0);
		add_outfile(data, filename);
	}
	else if (tmp->word[i] == '>' && tmp->word[i + 1] != '>') //outfile
	{
	// filename = get_filename(tmp->word, i);
ft_printf("out: %s\n", filename);
		file_check_access(data, filename, 1);
		add_outfile(data, filename);
	}
	else if (tmp->word[i] == '<' && tmp->word[i + 1] != '<') // INFILE
	{
		// filename = get_filename(tmp->word, i);
ft_printf("inf: %s\n", filename);
		file_check_access(data, filename, 2);
		add_infile(data, filename);
	}
	else
		init_here_doc(data, filename);
	ft_printf("tmp->word before: %s\n", tmp->word);
		tmp->word = remove_file(tmp->word, i);//pe a la fin pour le faire dans chaque??
ft_printf("tmp->word after: %s\n", tmp->word);
}

void	check_redirection(t_data *data)
{
	size_t	i;
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		i = 0;
// ft_printf("word redir: %s\n", tmp->word);
		while (tmp->word[i] != '\0')
		{
			if (tmp->word[i] == '\'' || tmp->word[i] == '"')
				i += quote_handling(tmp->word, i, tmp->word[i]);
			if (i < ft_strlen(tmp->word) && (tmp->word[i] == '>' || \
			tmp->word[i] == '<'))
			{
				if (i == 0)
					files_redirection(data, tmp->index, i);
				else if (i > 0 && (tmp->word[i - 1] != '>' && \
				tmp->word[i - 1] != '<'))
					files_redirection(data, tmp->index, i);
			}
			else
				i++;
		}
		tmp = tmp->next;
	}





	// test
	t_data	*tmp2;
	tmp2 = data;
	while (tmp2->lexer != NULL)
	{
		ft_printf("\n\n");
ft_printf("word node: %s\n", tmp2->lexer->word);
ft_printf("infile node: %s\n", tmp2->lexer->infile);
ft_printf("outfile node: %s\n", tmp2->lexer->outfile);
ft_printf("h_doc: %d\n", tmp2->here_doc);
		tmp2->lexer = tmp2->lexer->next;
	}
	// end test
}
