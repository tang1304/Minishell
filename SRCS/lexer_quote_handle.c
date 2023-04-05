/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:13:12 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/04 16:25:47 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	quote_handling(char *str, int i, char quote)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != quote)
		j++;
	return (j);
}

int	is_quote(char c)
{
	if (c == '\'' || (c == '"'))
		return (1);
	return (0);
}

int	quote_worder(t_data *data, char *str, int i)
{
	char	*new;
	int		j;

	j = 0;
	while (str[i + j] && !ft_isspace(str[i + j]) && !is_pipe(str, i + j))
	{
		if (str[i + j] == '\'')
			j = j + quote_handling(str, i + j, '\'');
		if (str[i + j] == '"')
			j = j + quote_handling(str, i + j, '"');
		j++;
	}
	new = ft_substr(str, i, j);
	if (!add_node(&data->lexer, new, 0))
		return (-1);
	free(new);
	return (j);
}
