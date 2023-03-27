/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:20:18 by rrebois           #+#    #+#             */
/*   Updated: 2023/03/27 13:14:42 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/incs/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_data
{
	char	*str;
	int		tokens; // number of tokens inside line
	int		pipes;
	int		redir;
	int		here_doc;
	int		cmd;

}				t_data;

enum errors
{
	SUCCESS = 0,
	QUOTE_FAILURE = 2,
};

void	prompt_loop();
int		error_quotes(char *line);

#endif
