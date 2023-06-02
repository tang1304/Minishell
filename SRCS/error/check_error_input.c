/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:53:10 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/02 11:22:08 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	error_pipes(char *line, size_t i)
{
	int	j;

	if (i == ft_strlen(line) || i == 0)
		return (FAILURE);
	j = (int)i + 1;
	while (line[j] != '\0')
	{
		while ((line[j] == ' ' || line[j] == '\t') && line[j] != '\0')
			j++;
		if (line[j] == '|' || j == (int)ft_strlen(line))
			return (FAILURE);
		else
			break ;
	}
	j = (int)i - 1;
	while (j > -1)
	{
		while ((line[j] == ' ' || line[j] == '\t') && j >= 0)
			j--;
		if (ft_isprint(line[j]) == 1 && line[j] != '>' && line[j] != '<' \
		&& j >= 0)
			return (SUCCESS);
		break ;
	}
	return (FAILURE);
}

int	error_last_token(char *line)
{
	size_t	len;

	len = ft_strlen(line) - 1;
	while ((int)len > -1)
	{
		while ((line[len] == ' ' || line[len] == '\t') && (int)len > -1)
			len--;
		if (line[len] == '|' || line[len] == '>' || line[len] == '<')
			return (ft_dprintf(2, \
			"minishell: syntax error near unexpected token `%c'\n", line[len]), \
			TOKEN_FAILURE);
		return (SUCCESS);
	}
	return (SUCCESS);
}

int	error_great(char *line, size_t i)
{
	int	great;

	while (line[i] != '\0')
	{
		great = 0;
		if (line[i] == '\'' || line[i] == '"')
			i += quote_handling(line, (int)i, line[i]);
		if (line[i] == '>')
			if (is_word(line, i, line[i]) != SUCCESS)
				great = 5;
		while (line[i] == '>' && i < ft_strlen(line))
		{
			great++;
			i++;
		}
		if (great > 2)
			return (ft_dprintf(2, \
				"minishell: syntax error near unexpected token `>'\n"), FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	error_less(char *line, size_t i)
{
	int	less;

	while (line[i] != '\0')
	{
		less = 0;
		if (line[i] == '\'' || line[i] == '"')
			i += quote_handling(line, (int)i, line[i]);
		if (line[i] == '<')
			if (is_word(line, i, line[i]) != SUCCESS)
				less = 5;
		while (line[i] == '<' && i < ft_strlen(line))
		{
			less++;
			i++;
		}
		if ((less > 2) || (line[i] == '>' && less > 0))
			return (ft_dprintf(2, \
				"minishell: syntax error near unexpected token `<'\n"), FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	error_check(char *line)
{
	size_t	i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (NO_INPUT);
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (error_quotes(line, i) != SUCCESS)
				return (FAILURE);
			i += quote_handling(line, (int)i, line[i]);
		}
		if (line[i] != '\0' && line[i] == '|')
			if (error_pipes(line, i) != SUCCESS)
				return (ft_dprintf(2, \
				"minishell: syntax error near unexpected token `|'\n"), FAILURE);
		if (line[i] == '>' || line[i] == '<')
			if (check_token(line, i) != SUCCESS)
				return (FAILURE);
		i++;
	}
	if (error_last_token(line) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
