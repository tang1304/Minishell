/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:47:34 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/05 16:11:22 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Function displaying and collecting what user types in and saves it into line
// Needs to implement the $USER@minishell:$PWD pwd befre $
void	prompt_loop(t_data *data)
{
	char	*prompt;

	while (1)
	{
		prompt = ft_strjoin(data->prompt, data->prompt_pwd);
		prompt = ft_strjoin(prompt, "$ ");
		data->str = ft_strdup(readline(prompt));
		if (ft_strlen(data->str) > 0)
			add_history(data->str);
		if (error_check(data->str) == SUCCESS)
		{
			lexer_init(data);
			expand(data);
			token_check(data);
			create_cmd_lst(data);// create cmd lst and send to hd
			builtins(data, data->cmd->cmd);
			print_export(&data->env);
			//penser a free(data)
		}
	//if (check_error(line) == SUCCESS)
		// if (error_quotes(line) != 0)
		// 	ft_putstr_fd("Error: Invalid syntax\n", 2);// Send the line into the lexer to check for errors and create the array of cmd/pipes/etc..
		// ft_printf("%s\n", line);//juste a test line. Gotta be removed at the end
		free(data->str);
	}
}
