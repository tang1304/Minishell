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

int	count_quote(char *s, size_t *i, char c)
{
	int		count;
	size_t	len;

	count = 1;
	len = ft_strlen(s);
	while (*i < len && *i + 1 < len)
	{
		*i = *i + 1;
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
		else if (line[i] == '"' && i < ft_strlen(line))
			d_quote += count_quote(line, &i, '"');
		// else if (line[i] == '|' && s_quote % 2 == 0 && d_quote % 2 == 0)
		// 	if (error_pipes(line, i) != SUCCESS)
		// 		return (PIPE_FAILURE);
		i++;
	}
	if (s_quote % 2 != 0)
		ft_putstr_fd("minishell: syntax error near unexpected token `\''\n", 2);
	if (d_quote % 2 != 0)
		ft_putstr_fd("minishell: syntax error near unexpected token `\"'\n", 2);
	if ((s_quote % 2 != 0) || (d_quote % 2 != 0))
		return (QUOTE_FAILURE);
	return (SUCCESS);
}
