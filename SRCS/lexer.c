/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:45:15 by tgellon           #+#    #+#             */
/*   Updated: 2023/03/30 11:05:29 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	spaces_skip(char *str, int i)
{
	int	j;

	j = 0;
	while (ft_isspace(str[i + j]))
		j++;
	return (j);
}

static int	is_token(char *str, int i)
{
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		return ((int)str[i]);
	return (0);
}

static int	tokenizer(t_data *data, char *str, int i)
{
	char	*token;

	if ((str[i] == '>' && str[i + 1] == '>') \
		|| (str[i] == '<' && str[i + 1] == '<'))
	{
		token = ft_substr(str, i, 2);
		if (!add_node(data->lexer, token, 1))
			return (-1);
		free(token);
		return (2);
	}
	else
	{
		token = ft_substr(str, i, 1);
		if (!add_node(data->lexer, token, 1))
			return (-1);
		free(token);
		return (1);
	}
}

static int	worder(t_data *data, char *str, int i)
{
	char	*new;
	int		j;

	j = 0;
	while (str[i + j] != '\0' && !ft_isspace(str[i+j]) && !is_token(str, i))
		j++;
	new = ft_substr(str, i, j);
	if (!add_node(data->lexer, str, 0))
		return (-1);
	free(new);
	return (j);
}

int	lexer_init(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->str[i])
	{
		j = 0;
		i = i + spaces_skip(data->str, i);
		if (is_token(data->str, i))
			j = tokenizer(data, data->str, i);
		else
			j = worder(data, data->str, i);
		if (j == -1)
			return (0);
		i = i + j;
	}
	return (1);
}
