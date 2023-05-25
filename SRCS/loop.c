/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:47:34 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/25 14:15:05 by rrebois          ###   ########lyon.fr   */
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
		update_pwd(data);
		prompt = ft_strjoin(data->prompt, data->prompt_pwd);
		prompt = ft_strjoin_gnl(prompt, "$ ");
		data->str = ft_strdup(readline(prompt));
		free(prompt);
		// signal_set();
		if (ft_strlen(data->str) > 0)
			add_history(data->str);
		if (error_check(data->str) == SUCCESS)
		{
			lexer_init(data); //OK ls<<a<<b<<c|wc<<d<<e|cat<<f et <<a<<b<<c<<d<<e<<f ok
			if (heredoc_redir(data) == SUCCESS)
			{
				expand(data);
				token_check(data);
				create_cmd_lst(data);
	printf("cmd len =%ld\n", lstlencmd(data->cmd));
				if (lstlencmd(data->cmd) > 0)
				{
					extract_paths(data);
					exec_cmd_lst(data);
					free_data(data, &free_lexer_strct);
				}
				free_data(data, &free_hd_strct);
			}
		}

// printf("cmd len =%ld\n", lstlencmd(data->cmd));//<Makefile<<a sgf somewhere
			// if (lstlencmd(data->cmd) > 0)
			// {
			// 	extract_paths(data);
			// 	// exec_cmd_lst(data);
			// 	free_data(data, &free_cmd_strct);
			// }
	//if (check_error(line) == SUCCESS)
		// if (error_quotes(line) != 0)
		// 	ft_putstr_fd("Error: Invalid syntax\n", 2);// Send the line into the lexer to check for errors and create the array of cmd/pipes/etc..
		// ft_printf("%s\n", line);//juste a test line. Gotta be removed at the end
		free(data->str);
	}
}
