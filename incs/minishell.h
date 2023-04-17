/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:20:18 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/17 17:54:39 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/incs/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_lexer
{
	char			**cmd;//malloc a free
	char			*word;
	char			*token;
	char			*infile;//free if not NULL
	char			*outfile;//free if not NULL
	char			*LIMITER;
	size_t			index;
	int				word_quote_pairs;
	int				s_q;
	int				d_q;
	struct s_lexer	*next;
	struct s_lexer	*prev;// a voir
}				t_lexer;

typedef struct s_data
{
	char				*str; // command typed by user
	char				*prompt; // has to be free at the end
	char				*prompt_pwd;
	char				**envp;
	char				**paths;
	char				**tokens_tab;
	int					tokens; // number of tokens inside line
	int					cmds; // number of cmds
	int					here_doc; // if here_doc or not
	char				*LIMITER;
	char				*pwd;
	char				*oldpwd;
	int					fdin;//infile
	int					fdout;//outfile
	size_t				child;
	int					fd[2];//pipe for here_doc
	int					*pipe;//pipes for other cmds
	pid_t				*pids;//pids of child processes
	struct s_lexer		*lexer;
	struct s_command	*cmd;
}				t_data;

enum e_errors
{
	SUCCESS = 0,
	FAILURE = 2,
	QUOTE_FAILURE = 3,
	PIPE_FAILURE = 5,
	TOKEN_FAILURE = 6,
	NODE_FAILURE = 7,
	NOT_WORD = 8
};
/*	data.c	*/
void	data_initialize(t_data *data, char **envp);
void	update_pwd(t_data *data, char *s);
char	**get_envp(char **envp);

/*	loop.c	*/
void	prompt_loop(t_data *data);

/*	check_error_input.c	*/
int		error_check(char *line);
int		error_pipes(char *line, int i);
int		error_last_token(char *line);
int		error_great(char *line);
int		error_less(char *line);

/*	check_error_utils.c	*/
int		error_quotes(char *line);
int		count_quote(char *s, size_t *i, char c);

/*	parser.c	*/
// void	implement_redirections_cmds(t_data *data);

/*	add_infile_outfile.c	*/
void	remove_nodes_redirection(t_lexer *lexer, size_t index);
void	token_check(t_data *data);
void	check_redirection(t_data *data, char *token, char *filename);
void	file_check_access(t_data *data, char *file, int i);

/*	add_infile_outfile_utils.c	*/
// char	*get_filename(char *s, size_t i);
// char	*remove_file(char *s, size_t i);
// int		check_if_cmd(char *s);
// void	add_infile(t_data *data, char *file, int i);
void	add_infile(t_data *data, char *file);
void	add_outfile(t_data *data, char *file);
// void	add_outfile(t_data *data, char *file, int i);

/*	lexer.c	*/
int		lexer_init(t_data *data);
int		is_pipe(char *str, int i);

/*	lexer_utils.c	*/
int		ft_isspace(char c);
int		quote_handling(char *str, int i, char quote);
int		add_node(t_lexer **lexer, char *str, int token);


/*	cmd_struct.c	*/
void	create_cmd_struct(t_data *data);

/*	lexer_quote_handle	*/
int		quote_handling(char *str, int i, char quote);
int		is_quote(char c);
int		quote_worder(t_data *data, char *str, int i);

/*	expander_var.c	*/
int		expand(t_data *data);

/*	expander_quotes.c	*/
char	*str_quotes_removal(char *str);
int		quotes_removal(t_lexer *lexer);

/*	builtins.c	*/

#endif
