/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:44 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/12 17:29:47 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h" // Get filename and check file permissions.

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

void	add_infile(t_data *data, char *file)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (check_if_cmd(tmp->word) == SUCCESS)
		{
			if (tmp->infile != NULL && ft_strlen(file) == \
			ft_strlen(data->LIMITER) && data->here_doc == 1 && \
			ft_strncmp(data->LIMITER, file, ft_strlen(file)) == 0)
			{
				free(tmp->infile);
				data->here_doc = 0;
			}
			else
				free(tmp->infile);
			if (file != NULL)
				tmp->infile = file;
			else
				tmp->infile = data->LIMITER;
if (tmp->infile != NULL)
	ft_printf("%s: tmp->infile: %s\n", tmp->word, tmp->infile);
			return ;
		}
		tmp = tmp->next;
	}
}

// void	add_outfile(t_data *data, char *file) //ls |grep i>o<i ok
// {// ls | wc >o marche
// 	t_lexer	*tkn;(void)file;
// 	t_lexer	*tmp;

// 	tmp = data->lexer;
// 	tkn = data->lexer;
// 	while (tmp->next != NULL)
// 		tmp = tmp->next;
// 	while (1)
// 	{
// 		if (tmp != data->lexer)
// 			tkn = tmp->prev;
// 		if (tmp->word != NULL && tkn->word != NULL)
// 		{
// 			//tkn->word.outfile = file;
// 			return ;
// 		}
// 		else if ((tmp->word != NULL &&
// 		ft_strncmp(tkn->token, "|", 1) == 0) || (tmp == data->lexer))
// 		{
// 			//tmp->word = file;
// 			return ;
// 		}
// 		tmp = tkn;
// 	}
// }

void	files_redirection(t_data *data, int index, size_t i)
{
	t_lexer	*tmp;
	char	*filename;

	tmp = data->lexer;
	while (tmp->index != index)
		tmp = tmp->next;
	if (tmp->word[i] == '>' && tmp->word[i + 1] == '>') //outfile append
	{
		filename = get_filename(tmp->word, i);
ft_printf("filename: %s\n", filename);

		file_check_access(data, filename, 0);
		//add_outfile(data, tmp->next->word);
	}
	else if (tmp->word[i] == '>' && tmp->word[i + 1] != '>') //outfile
	{
	filename = get_filename(tmp->word, i);
ft_printf("filename: %s\n", filename);

		file_check_access(data, filename, 1);
		// add_outfile(data, tmp->next->word);
	}
	else if (tmp->word[i] == '<' && tmp->word[i + 1] != '<') // INFILE
	{
		filename = get_filename(tmp->word, i);
ft_printf("filename: %s\n", filename);

		file_check_access(data, filename, 2);
		add_infile(data, filename);
	}
	else if (tmp->word[i] == '<' && tmp->word[i + 1] == '<') //here_doc
	{
		data->LIMITER = get_filename(tmp->word, i);
		data->here_doc = 1;
		add_infile(data, NULL);
	}
	ft_printf("tmp->word: %s\n", tmp->word);
		tmp->word = remove_file(tmp->word, i);//pe a la fin pour le faire dans chaque??
ft_printf("tmp->word: %s\n", tmp->word);
}

void	check_redirection(t_data *data)
{
	size_t	i;
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		i = 0;
ft_printf("word redir: %s\n", tmp->word);
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
			i++;
		}
		tmp = tmp->next;
	}//<inf ls >out >>    got an additional outfile
}
