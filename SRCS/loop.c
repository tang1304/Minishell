/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:47:34 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/17 13:59:32 by rrebois          ###   ########lyon.fr   */
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
		signal_set();
		if (ft_strlen(data->str) > 0)
			add_history(data->str);
		if (error_check(data->str) == SUCCESS)
		{
			lexer_init(data);
			heredoc_redir(data);
			expand(data);
			token_check(data);
			create_cmd_lst(data);




			int	i = 0;
			while (i < data->hd->hd_count)
			{
				printf("limitor = %s\n", data->hd->LIMITER[i]);
				i++;
			}
// printf("cmd len =%ld\n", lstlencmd(data->cmd));
			// if (lstlencmd(data->cmd) > 0)
			// {
			// 	extract_paths(data);
			// 	// exec_cmd_lst(data);
			// 	free_data(data, &free_lexer_strct);
			// }
			// if (data->hd->hd_count > 0)
			free_data(data, &free_hd_struct); //here a segf.
		}

	//if (check_error(line) == SUCCESS)
		// if (error_quotes(line) != 0)
		// 	ft_putstr_fd("Error: Invalid syntax\n", 2);// Send the line into the lexer to check for errors and create the array of cmd/pipes/etc..
		// ft_printf("%s\n", line);//juste a test line. Gotta be removed at the end
		free(data->str);
	}
}
