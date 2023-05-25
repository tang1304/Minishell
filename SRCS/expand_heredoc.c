/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:16:39 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/24 08:16:39 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*expand_line(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			quote = 1;
		i++;
	}
	printf("quote %d\n", quote);
	// if (quote == 1)
		// str = str_quotes_removal(data->hd->LIMITER[i]);
	return (str);
}
