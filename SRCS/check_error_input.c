/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:53:10 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/05 11:23:04 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	error_pipes(char *line)
{
	int	word;
	int	pipe;

	while (*line)
	{
		word = 0;
		pipe = 0;
		while (*line == ' ' || *line == '\t')
			line++;
		if (ft_isprint(*line) == 1 && (*line != '|') && (*line != ' '))
			word = 1;
		while (ft_isprint(*line) == 1 && (*line != '|'))
			line++;
		if (*line == '|' || !*line)
			pipe = 1;
		if ((*line == '|') && ((word == 0) || (pipe == 0)))
			return (PIPE_FAILURE);
		line++;
	}
	if (line[ft_strlen(line) - 1] == '|')
		return (PIPE_FAILURE);
	return (SUCCESS);
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
		{
			ft_putstr_fd("minishell: syntax error near unexpected token", 2);
			ft_printf(" `%c'\n", line[len]);
			return (TOKEN_FAILURE);
		}
		return (SUCCESS);
	}
	return (SUCCESS);
}

int	error_great(char *line)
{
	size_t	i;
	int		great;

	i = 0;
	while (line[i] != '\0')
	{
		great = 0;
		while (line[i] == '>' && i < ft_strlen(line))
		{
			great++;
			i++;
		}
		if ((great > 2) || (line[i] == '<' && great > 0))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	error_less(char *line)
{
	size_t	i;
	int		less;

	i = 0;
	while (line[i] != '\0')
	{
		less = 0;
		while (line[i] == '<' && i < ft_strlen(line))
		{
			less++;
			i++;
		}
		if ((less > 2) || (line[i] == '>' && less > 0))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	error_check(char *line)
{
	if (error_quotes(line) != SUCCESS)
		return (FAILURE); // Not sure if we have to return 1 or another value like 3?
	if (error_pipes(line) != SUCCESS)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (FAILURE);
	}
	if (error_great(line) != SUCCESS || error_less(line) != SUCCESS)
		return (FAILURE);
	if (error_last_token(line) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
