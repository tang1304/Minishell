/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:52:44 by rrebois           #+#    #+#             */
/*   Updated: 2023/03/27 10:39:59 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Gonna check the cmd line arguments typed in by the user
void	error_quotes(char *line)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			s_quote++;
		if (line[i] == '"')
			d_quote++;
		i++;
	}
	if ((s_quote % 2 != 0) || (d_quote % 2 != 0))
		exit(QUOTE_FAILURE);// a voir
}
