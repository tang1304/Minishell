/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:20:18 by rrebois           #+#    #+#             */
/*   Updated: 2023/03/30 11:05:25 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/incs/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_word
{
	char	*name;
	char	**cmd;
	int		fd_in;
	int		ft_out;
}				t_word;

typedef struct s_token
{
	char	*name;
	int		here_doc;
}				t_token;

typedef struct s_lexer
{
	struct s_word	word;
	struct s_token	token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*prev;// a voir
}				t_lexer;

typedef struct s_data
{
	char	*str; // command typed by user
	char	*prompt; // has to be free at the end
	char	*prompt_pwd;
	char	**envp;
	char	**tokens_tab;
	int		tokens; // number of tokens inside line
	int		cmds; // number of cmds
	int		here_doc; // if here_doc or not
	char	*pwd;
	char	*oldpwd;
	struct s_lexer	*lexer;
}				t_data;

enum errors
{
	SUCCESS = 0,
	QUOTE_FAILURE = 2
};

void	data_initialize(t_data *data, char **envp);
void	update_pwd(t_data *data, char *s);
void	prompt_loop(t_data *data);
int		error_quotes(char *line);

/*	lexer.c	*/
int		lexer_init(t_data *data);

/*	lexer_utils.c	*/
int		ft_isspace(char c);
void	*add_node(t_lexer *lexer, char *str, int token);

#endif
