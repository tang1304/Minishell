/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:52:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/03 16:41:22 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// static size_t	ft_lstlen(t_lexer *tmp)
// {
// 	t_lexer	*lst;
// 	size_t	len;

// 	lst = tmp;
// 	while (lst != NULL)
// 	{
// 		len++;
// 		lst = lst->next;
// 	}
// 	return (len);
// }

void	add_infile(t_data *data, char *file)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->word.name == NULL && ft_strncmp(tmp->token.name, "|", 1) \
		!= 0 && ft_strlen(tmp->token.name) == 1)//len 1 ou 2 pour >> et <<
		{
			tmp = tmp->next;
			tmp = tmp->next;
		}
		else if (tmp->word.name == NULL && \
		ft_strncmp(tmp->token.name, "|", 1) == 0 && \
		ft_strlen(tmp->token.name) == 1)
			tmp = tmp->next;
		if (tmp->word.name != NULL)
		{
			tmp->word.infile = file;
			return ;
		}
	}
}

void	add_outfile(t_data *data, char *file)
{// ls | wc >o marche pas
	t_lexer	*tkn;
	t_lexer	*tmp;

	tmp = data->lexer;
	tkn = data->lexer;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (1)
	{
		if (tkn == tmp)
		{
			tmp->word.outfile = file;
			return ;
		}
		while (tkn->next != tmp)
			tkn = tkn->next;
		if (tmp->word.name != NULL && tkn->token.name == NULL &&
		ft_strncmp(tmp->word.name, "-", 1) != 0)
		{
			tmp->word.outfile = file;
			return ;
		}
		tmp = tkn;
		tkn = data->lexer;
	}
}

void	files_redirection(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->token.name != NULL && ft_strncmp(tmp->token.name, "<", 1) == \
		0 && ft_strlen(tmp->token.name) == 1)
			add_infile(data, tmp->next->word.name);
		if (tmp->token.name != NULL && ft_strncmp(tmp->token.name, ">", 1) == \
		0 && ft_strlen(tmp->token.name) == 1)
			add_outfile(data, tmp->next->word.name);
		// if (tmp->token.name != NULL && ft_strncmp(tmp->token.name, ">", 1) ==
		// 0 && ft_strlen(tmp->token.name) == 1)
		// if (tmp->word.name != NULL)
		// 	ft_printf("infile: %s\n", tmp->word.infile);
	// 	// ft_printf("word: %s\n", tmp->word.name);
	// 	// ft_printf("infile: %s\n", tmp->word.infile);
	// 	// // else if (ft_strncmp(tmp->token, '|', 1) == 1 &&
	// 	// // ft_strlen(tmp->token.name) == 1)
	// 	// // {

	// 	// // }
		tmp = tmp->next;
	}




	tmp = data->lexer;
	while (tmp != NULL)
	{

		// if (tmp->token.name != NULL && ft_strncmp(tmp->token.name, ">", 1) ==
		// 0 && ft_strlen(tmp->token.name) == 1)
		if (tmp->word.name != NULL)
		{
			ft_printf("name: %s infile: %s\n", tmp->word.name, tmp->word.infile);
			ft_printf("name: %s outfile: %s\n", tmp->word.name, tmp->word.outfile);
		}
	// 	// ft_printf("word: %s\n", tmp->word.name);
	// 	// ft_printf("infile: %s\n", tmp->word.infile);
	// 	// // else if (ft_strncmp(tmp->token, '|', 1) == 1 &&
	// 	// // ft_strlen(tmp->token.name) == 1)
	// 	// // {

	// 	// // }
		tmp = tmp->next;
	}
}

void	implement_redirections_cmds(t_data *data)
{
	files_redirection(data);
}
