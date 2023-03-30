/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:52:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/03/30 17:03:35 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static size_t	ft_lstlen(t_lexer *tmp)
{
	t_lexer	*lst;
	size_t	len;

	lst = tmp;
	while (lst != NULL)
	{
		len++;
		lst = lst->nextl;
	}
	return (len);
}

void	add_infile(t_data *data, char *file)
{
	t_lexer	*tmp;
	int		token;

	token = 0;
	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->word.name == NULL)
			token = 1;
		if (token == 1 && ft_lstlen(tmp) > 2)
		{
			tmp = tmp->next;
			tmp = tmp->next;
		}
	}
}

void	infile_redirection(t_data *data)
{
	t_lexer	*tmp;
	int		token;
	size_t	i;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		token = 0;
		if (ft_strncmp(tmp->token, '<', 1) == 1 && \
		ft_strlen(tmp->token.name) == 1)
		{
			token = 1;// a voir si utile??
			tmp = tmp->next;
			add_infile(t_data *data, tmp->word.name);
		}
		else if (ft_strncmp(tmp->token, '|', 1) == 1 && \
		ft_strlen(tmp->token.name) == 1)
		{

		}
		tmp = tmp->next;
	}
}
