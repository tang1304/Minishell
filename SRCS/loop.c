/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:47:34 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/31 13:01:57 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	generate_prompt(t_data *data)
{
	char	*prompt;

	prompt = update_pwd(data);
	data->str = ft_strtrim_free(ft_strdup(readline(prompt)), " ");
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
