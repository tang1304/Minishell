/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:53:10 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/17 15:26:46 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	error_pipes(char *line, int i)
{
	int	j;

	if ((size_t)i == ft_strlen(line) || i == 0)
		return (FAILURE);
	j = i + 1;

	while (line[j] != '\0')
	{
		while ((line[j] == ' ' || line[j] == '\t') && line[j] != '\0')
			j++;
		if (line[j] == '|' || (size_t)j == ft_strlen(line))
			return (FAILURE);
		else
			break ;
	}
	j = i - 1;
	while (j >= 0)
	{
		while ((line[j] == ' ' || line[j] == '\t') && j >= 0)
			j--;
		if (line[j] == '|' || j <= 0)
			return (FAILURE);
		else
			break ;
	}
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

int	error_great(char *line)// regler le cas ou ls > | o erreur au lieu de rien
{
	size_t	i;
	int		great;

	i = 0;
	while (line[i] != '\0')
	{
		great = 0;
		if (line[i] == '\'' || line[i] == '"')
			i += quote_handling(line, i, line[i]);
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
		if (line[i] == '\'' || line[i] == '"')
			i += quote_handling(line, i, line[i]);
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
	int	error;

	error = error_quotes(line);
	if (error == QUOTE_FAILURE)
		return (FAILURE); // Not sure if we have to return 1 or another value like 3?
	else if (error == PIPE_FAILURE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (FAILURE);
	}
	if (error_great(line) != SUCCESS || error_less(line) != SUCCESS)
		return (FAILURE);
	if (error_last_token(line) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
