/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:53:10 by rrebois           #+#    #+#             */
/*   Updated: 2023/03/29 14:39:18 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Gonna check the cmd line arguments typed in by the user
// Needs to be improved in case 1 d_q between 2 s_q, the " must be considered as a word not as a d_quote

static int	count_quote(char *s, size_t *i, char c)
{
	int		count;
	size_t	len;

	count = 0;
	len = ft_strlen(s);
	while (s[*i] != '\0')
	{
		if (s[*i] == c && *i < len)
		{
			count++;
			*i = *i + 1;
		}
		while (s[*i] != c && *i < len)
			*i = *i + 1;
		if (s[*i] == c && *i < len)
		{
			count++;
			return (count);
		}
	}
	return (count);
}

int	error_quotes(char *line)
{
	size_t	i;
	int		s_quote;
	int		d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && i < ft_strlen(line))
			s_quote += count_quote(line, &i, '\'');
		if (line[i] == '"' && i < ft_strlen(line))
			d_quote += count_quote(line, &i, '"');
		i++;
	}
	if ((s_quote % 2 != 0) || (d_quote % 2 != 0))
		return(QUOTE_FAILURE);
	return (SUCCESS);
}

int	check_error(char *line)
{
	if (error_quotes(line) != SUCCESS)
	{
		ft_putstr_fd("Wrong input\n", 2);
		return (FAILURE); // Not sure if we have to return 1 or another value like 3?
	}
	return (SUCCESS);
}
