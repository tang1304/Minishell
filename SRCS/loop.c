/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:47:34 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/02 10:31:44 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	generate_prompt(t_data *data)
{
	char	*prompt;

	prompt = update_pwd(data);
	data->str = readline(prompt);
	if (data->str == NULL)
	{
		write(1, "\n", 1);
		free_all(data);
		free(prompt);
		exit (0);
	}
	data->str = ft_strtrim_free(data->str, " ");
	data->str = ft_strtrim_free(data->str, "\t");
	free(prompt);
	data->stdin_save = dup(STDIN_FILENO);
	data->stdout_save = dup(STDOUT_FILENO);
}

void	prompt_loop(t_data *data)
{
	signal_set();
	while (1)
	{
		generate_prompt(data);
		if (ft_strlen(data->str) > 0)
			add_history(data->str);
		if (error_check(data->str) == SUCCESS)
		{
			lexer_init(data);
			if (heredoc_redir(data) == SUCCESS && data->max_index <= INT_MAX)
			{
				expand(data);
				update_lexer(data);
				token_check(data);
				create_cmd_lst(data);
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
