/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:20:18 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/27 15:39:30 by tgellon          ###   ########lyon.fr   */
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
#include <sys/wait.h>

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

// typedef struct s_command
// {
// 	char				**cmd;//malloc a free
// 	int					index;
// 	char				*infile;
// 	char				*outfile;
// 	struct s_command	*next;
// 	struct s_command	*prev;
// }				t_command;ls        | "grep >out" <Makefile| wc -l >outer

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
}				t_env;

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
	int					heredoc; // if here_doc or not
	char				*LIMITER;
	char				*pwd;
	char				*oldpwd;
	int					fdin;//infile
	int					fdout;//outfile
	size_t				child;
	int					fd[2];//pipe for here_doc
	int					*pipe;//pipes for other cmds
	pid_t				*pids;//pids of child processes
	struct s_env		*env;
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
char	**get_envp(t_data *data, char **envp);

/*	loop.c	*/
void	prompt_loop(t_data *data);

/*	check_error_input.c	*/
int		error_check(char *line);
int		error_pipes(char *line, size_t i);
int		error_last_token(char *line);
int		error_great(char *line, size_t i);
int		error_less(char *line, size_t i);

/*	check_error_utils.c	*/
int		is_word(char *s, int i, char c);
int		error_quotes(char *line, size_t i);
int		check_token(char *s, size_t i);
// int		count_quote(char *s, size_t *i, char c);

/*	parser.c	*/
// void	implement_redirections_cmds(t_data *data);

/*	add_infile_outfile.c	*/
void	remove_nodes_redirection(t_data *data, size_t index);
void	token_check(t_data *data);
void	check_redirection(t_data *data, char *token, char *filename);
void	file_check_access(t_data *data, char *file, int i);

/*	add_infile_outfile_utils.c	*/
void	add_infile(t_data *data, char *file, int i);
void	add_outfile(t_data *data, char *file);
size_t	lstlen(t_lexer *lexer);

/*	remove_nodes.c	*/
void	remove_front_nodes(t_data *data);
void	remove_back_nodes(t_data *data);
void	remove_middle_nodes(t_data *data, size_t index);

/*	lexer.c	*/
int		lexer_init(t_data *data);
int		is_pipe(char *str, int i);

/*	lexer_utils.c	*/
void	add_index(t_data *data);
int		ft_isspace(char c);
int		quote_handling(char *str, int i, char quote);
int		add_node(t_lexer **lexer, char *str, int token);

/*	cmd_struct.c	*/
void	create_cmd_struct(t_data *data);

// /*	lexer_quote_handle	*/
// int		quote_handling(char *str, int i, char quote);
// int		is_quote(char c);
// int		quote_worder(t_data *data, char *str, int i);

/*	expand.c	*/
void	expand(t_data *data);

/*	expander_var.c	*/
char	*get_var(t_data *data, char *s);
char	*join_all(char *s, char *b, char *e, char *a);

/*	expander_quotes.c	*/
char	*str_quotes_removal(char *str);
int		quotes_removal(t_lexer *lexer);

/*	builtins.c	*/

/*	builtin_export.c	*/
void	ft_export(t_data *data, char **cmd);
int		ft_print_export(t_env **env);

/*	builtin_export_utils.c	*/
void	ft_list_sort(t_env **env, int size);
int		ft_list_size(t_env *env);

/*	envp_utils.c	*/
char	*get_shlvl(char *str);

/*	heredoc.c	*/
void	check_heredoc(t_data *data);
void	init_heredoc(t_data *data);

/*	utils.c	*/
char	*ft_strjoin_free(char *s1, char *s2);

#endif
