/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:58:08 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/12 14:38:56 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	is_word(char *s, int i, char c)
{
	while (s[i] == c)
		i++;
	while (s[i] == ' ')
		i++;
	if (ft_isprint(s[i]) == 1 && s[i] != '>' && s[i] != '<')
		return (SUCCESS);
	return (NOT_WORD);
}

int	check_token(char *s, size_t i)
{
	if (s[i] == '>')
		if (error_great(s, i) != SUCCESS)
			return (FAILURE);
	if (s[i] == '<')
		if (error_less(s, i) != SUCCESS)
			return (FAILURE);
	return (SUCCESS);
}

int	error_quotes(char *line, size_t i)
{
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			i++;
			while (i < ft_strlen(line) && line[i] != '\'')
				i++;
			if (line[i] == '\0')
				return (ft_dprintf(2, "minishell: syntax error near unexpected \
				token `\''\n"), QUOTE_FAILURE);
			return (SUCCESS);
		}
		if (line[i] == '"')
		{
			i++;
			while (i < ft_strlen(line) && line[i] != '"')
				i++;
			if (line[i] == '\0')
				return (ft_dprintf(2, "minishell: syntax error near unexpected \
				token `\"'\n"), QUOTE_FAILURE);
			return (SUCCESS);
		}
	}
	return (SUCCESS);
}
