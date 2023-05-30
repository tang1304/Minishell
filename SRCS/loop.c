/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:47:34 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/30 09:37:06 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// Function displaying and collecting what user types in and saves it into line
// Needs to implement the $USER@minishell:$PWD pwd befre $
void	prompt_loop(t_data *data)
{
	char	*prompt;

	signal_set();
	while (1)
	{
		update_pwd(data);
		prompt = ft_strjoin(data->prompt, data->prompt_pwd);
		prompt = ft_strjoin_gnl(prompt, "$ ");
		data->str = ft_strtrim_free(ft_strdup(readline(prompt)), " ");
		free(prompt);
		if (ft_strlen(data->str) > 0)
			add_history(data->str);
		data->stdin_save = dup(STDIN_FILENO);
		data->stdout_save = dup(STDOUT_FILENO);
		if (error_check(data->str) == SUCCESS)
		{
			lexer_init(data); //OK ls<<a<<b<<c|wc<<d<<e|cat<<f et <<a<<b<<c<<d<<e<<f ok
			if (heredoc_redir(data) == SUCCESS && data->max_index <= INT_MAX)
			{
				expand(data);
				token_check(data);
				create_cmd_lst(data);
	// printf("cmd len =%ld\n", lstlencmd(data->cmd));
				if (lstlencmd(data->cmd) > 0)
				{
					extract_paths(data);
					exec_cmd_lst(data);
				}
			}
		}
		close_files(data);
		free_loop(data);
	}
}
