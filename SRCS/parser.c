/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:52:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/03/30 16:06:26 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static size_t	ft_lstlen(t_lexer tmp)
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

void	implement_redirections_cmds(t_data *data)
{
	t_lexer	*buffer;
	t_lexer	*tmp;
	int		token;

	buffer = data->lexer;
	tmp = data->lexer;
	len = ft_lstlen(tmp);
	while (tmp != NULL)
	{
		token = 0;
		if (tmp->word.name == NULL) // => token node
			token = 1;

		if (ft_strncmp(data->lexer.token, '>', 1) == 1 && \
		ft_strlen(data->lexer.token) == 1)
		{
			data->lexer.word
		}
		tmp = tmp->next;
	}
}
