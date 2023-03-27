/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:52:44 by rrebois           #+#    #+#             */
/*   Updated: 2023/03/27 13:14:31 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Gonna check the cmd line arguments typed in by the user
// Needs to be improved in case 1 d_q between 2 s_q, the " must be considered as a word not as a d_quote
int	error_quotes(char *line)
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
		return(QUOTE_FAILURE);// a voir
	return (SUCCESS);
}
