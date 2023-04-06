/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:44 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/04 11:08:32 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	file_check_access(t_data *data, char *file, int i)
{
	if (i == 0) // infile
	{
		data->fdin = open(file, O_RDONLY);
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, R_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
	else if (i == 1)
	{
		data->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, W_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
}

void	add_infile(t_data *data, char *file)
{
	t_lexer	*tmp;

	tmp = data->lexer;(void)file;
	while (tmp != NULL)
	{
		if (tmp->word == NULL && ft_strncmp(tmp->token, "|", 1) \
		!= 0 && ft_strlen(tmp->token) <= 2)//len 1 ou 2 pour >> et <<
		{
			tmp = tmp->next;
			tmp = tmp->next;
		}
		else if (tmp->word == NULL && \
		ft_strncmp(tmp->token, "|", 1) == 0 && \
		ft_strlen(tmp->token) == 1)
			tmp = tmp->next;
		if (tmp->word != NULL)
		{
			//tmp->word = file;
			return ;
		}
	}
}

void	add_outfile(t_data *data, char *file) //ls |grep i>o<i ok
{// ls | wc >o marche
	t_lexer	*tkn;(void)file;
	t_lexer	*tmp;

	tmp = data->lexer;
	tkn = data->lexer;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (1)
	{
		if (tmp != data->lexer)
			tkn = tmp->prev;
		if (tmp->word != NULL && tkn->word != NULL)
		{
			//tkn->word.outfile = file;
			return ;
		}
		else if ((tmp->word != NULL &&
		ft_strncmp(tkn->token, "|", 1) == 0) || (tmp == data->lexer))
		{
			//tmp->word = file;
			return ;
		}
		tmp = tkn;
	}
}

void	files_redirection(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "<", 1) == \
		0 && ft_strlen(tmp->token) == 1)
		{
			file_check_access(data, tmp->next->word, 0);
			add_infile(data, tmp->next->word);
		}
		if (tmp->token != NULL && ft_strncmp(tmp->token, ">", 1) == \
		0 && ft_strlen(tmp->token) == 1)
		{
			file_check_access(data, tmp->next->word, 1);
			add_outfile(data, tmp->next->word);
		}
		tmp = tmp->next;
	}


	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->word != NULL)
			ft_printf("cmd: %s\n", tmp->word);
		else
			ft_printf("cmd: %s\n", tmp->token);
		tmp = tmp->next;
	}
}
