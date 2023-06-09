/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:50:54 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/08 15:42:22 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	quote_handling(char *str, int i, char quote)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != quote)
		j++;
	return (j);
}

static t_lexer	*new_lexer_node(t_data *data, char *str, int token)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node)
		exit_error(data, "minishell: malloc error : ");
	ft_bzero(node, sizeof(t_lexer));
	if (token == 0)
		config_node(data, str, node, 0);
	else
		config_node(data, str, node, 1);
	return (node);
}

int	add_node(t_data *data, t_lexer **lexer, char *str, int token)
{
	t_lexer	*new;
	t_lexer	*tmp;

	new = new_lexer_node(data, str, token);
	if (!*lexer)
	{
		*lexer = new;
		return (1);
	}
	tmp = *lexer;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (1);
}

void	add_index(t_data *data)
{
	size_t	i;
	int		change;
	t_lexer	*tmp;

	i = 0;
	tmp = data->lexer;
	while (tmp != NULL)
	{
		change = 0;
		if (tmp->index == data->svd_index)
			change = 1;
		tmp->index = i;
		if (change == 1)
			data->svd_index = tmp->index;
		i++;
		tmp = tmp->next;
	}
	data->max_index = i;
	if (i > INT_MAX)
		ft_putstr_fd("minishell: Command too long.\n", 0);
}
