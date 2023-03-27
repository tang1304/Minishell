/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:47:34 by rrebois           #+#    #+#             */
/*   Updated: 2023/03/27 10:13:11 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Function displaying and collecting what user types in and saves it into line
void	prompt_loop()
{
	char	*line;

	while (1)
	{
		line = readline("$ ");
		error_quotes(line); // Send the line into the lexer to check for errors and create the array of cmd/pipes/etc..
		ft_printf("%s\n", line);//juste a test line. Gotta be removed at the end
		free(line);
	}
}
