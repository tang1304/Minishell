/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:20:18 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/14 13:30:49 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>

# define UNSET_ERR	"minishell: unset: `%s': not a valid identifier\n"
# define SQUOTE_ERR "minishell: syntax error near unexpected token `\''\n"
# define DQUOTE_ERR "minishell: syntax error near unexpected token `\"'\n"
# define HEREDOC_LIMIT "minishell: maximum here-document count exceeded\n"
# define HD_START_D "minishell: warning: here-document at line %ld "
# define HD_END_D "delimited by end-of-file (wanted `%s')\n"

typedef struct s_lexer
{
	char			*word;
	char			*token;
	char			*infile;
	int				inf_err;
	char			*outfile;
	int				out_err;
	int				fdin;
	int				fdout;
	int				hd_file;
	int				hd_number;
	size_t			index;
	int				word_quote_pairs;
	int				s_q;
	int				d_q;
	int				pipe_b;
	int				pipe_a;
	int				rm;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

typedef struct s_substr
{
	char	*s;
	char	*before;
	char	*middle;
	char	*after;
	char	*sub_b;
	char	*sub_m;
	char	*sub_a;
}				t_substr;

typedef struct s_command
{
	char				**cmd;
	size_t				index;
	char				*infile;
	int					inf_err;
	char				*outfile;
	int					out_err;
	int					heredoc_file;
	int					heredoc_num;
	int					fd[2];
	int					fdin;
	int					fdout;
	int					pipe_b;
	int					pipe_a;
	pid_t				pid;
	int					child;
	struct s_command	*next;
	struct s_command	*prev;
}				t_command;

typedef struct s_heredoc
{
	int					hd_count;
	int					heredoc;
	char				**limiter;
	int					*xpd;
	int					**fd;
}				t_heredoc;

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

typedef struct s_data
{
	char				*str;
	char				*strtrim;
	char				*prompt;
	char				*prompt_pwd;
	char				**envp;
	char				*path;
	char				**paths;
	char				*pwd;
	char				*oldpwd;
	size_t				svd_index;
	int					fdin;
	int					fdout;
	int					maxfdin;
	int					maxfdout;
	int					pipe[2];
	pid_t				*pids;
	int					stdin_save;
	int					stdout_save;
	size_t				max_index;
	size_t				ctrl_d_val;
	char				*buf;
	int					stop;
	struct s_env		*env;
	struct s_heredoc	*hd;
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
	NOT_WORD = 8,
	FILE_ERROR = 9,
	CHILD_SUCCESS = 10,
	NOT_BUILTIN = 11,
	NO_INPUT = 12,
	HD_ERROR_NUMBER = 13,
	HD_CTRL_D = 14,
	HD_CTRL_C = 15,
	ERR_NODE = 16
};

extern int	g_status;

/*	data.c	*/
void		data_initialize(t_data *data, char **envp);
char		*update_pwd(t_data *data);
char		**get_envp(t_data *data, char **envp);

/*	loop.c	*/
void		prompt_loop_init(t_data *data);

/*	check_error_input.c	*/
int			error_check(t_data *data, char *line);
int			error_pipes(char *line, size_t i);
int			error_last_token(char *line);
int			error_great(char *line, size_t i);
int			error_less(char *line, size_t i);

/*	check_error_utils.c	*/
int			is_word(char *s, int i, char c);
int			error_quotes(char *line, size_t i);
int			check_token(char *s, size_t i);

/*	errors.c	*/
void		exit_error(t_data *data, char *str);
void		expand_error(t_data *data, t_substr *s, char *str);
void		expand_error_hd(t_data *data, t_substr *s, char *buffer, char *str);
void		ascii_check(t_data *data, char *str);

/*	parser.c	*/
void		create_cmd_lst(t_data *data);
t_command	*cmd_node(t_data *data, size_t i, size_t x, t_command *cmd);

/*	parser_utils.c	*/
t_command	*cmd_lst_end_node(t_data *data, t_command *command, t_lexer *tmp);
t_command	*cmd_lst(t_data *data, t_command *command, t_lexer *tmp);
void		add_cmd_index(t_data *data);
void		fillup_cmd_node(t_data *data, t_command *new, t_lexer *tmp);

/*	add_infile_outfile.c	*/
void		remove_nodes_redirection(t_data *data, size_t index);
int			token_check(t_data *data);
int			file_check_access(t_data *data, char *file, int i);
int			check_redirection(t_data *data, char *token, char *file, \
								size_t index);

/*	add_infile_outfile_utils.c	*/
t_lexer		*find_start(t_lexer *tmp);
void		ft_error_file(char *file, int i);
void		add_infile(t_data *data, char *file, size_t index, int valid);
void		add_outfile(t_data *data, char *file, size_t index, int valid);
void		add_file_node(t_data *data, t_lexer *lexer, char *file, int i);

/*	add_pipes_lexer	*/
void		add_pipes_redir(t_data *data);

/*	remove_lexer_nodes.c	*/
void		free_content_lexer_node(t_lexer *tmp);
void		free_lst(t_data *data, t_lexer *tmp);
void		remove_front_nodes(t_data *data, size_t len);
void		remove_back_nodes(t_data *data);
void		remove_middle_nodes(t_data *data, size_t index);

/*	lexer.c	*/
int			lexer_init(t_data *data);

/*	lexer_update.c	*/
void		update_lexer(t_data *data);
void		remove_single_node(t_data *data, size_t index);

/*	lexer_utils.c	*/
void		add_index(t_data *data);
int			ft_isspace(char c);
int			quote_handling(char *str, int i, char quote);
int			add_node(t_lexer **lexer, char *str, int token);

/*	lexer_utils2.c	*/
int			config_node(char *str, t_lexer *node, int i);

/*	expand.c	*/
void		expand(t_data *data);

/*	expand_string.c	*/
void		string_xpd_hd(t_data *data, t_substr *s, size_t *i, char *buffer);

/*	expander_var.c	*/
void		question_mark(t_data *data, t_substr *s, size_t *i, size_t index);
char		*get_var(t_data *data, char *s, int *err);
void		number_xpd(t_data *data, t_substr *s, size_t *i, size_t index);

/*	expand_join_all.c	*/
char		*join_all_mid(t_data *data, char *str, t_substr *s);
char		*join_all_sub(t_data *data, char *str, t_substr *s);

/*	expander_quotes.c	*/
void		set_sub_strs(t_data *data, t_substr *s, size_t j, int *err);
char		*str_quotes_removal(t_data *data, char *str);

/*	expander_quotes_utils.c	*/
char		*str_without_single_quotes(t_data *data, char *str, int i, int j);
char		*remove_str_middle_quote(t_data *data, char *str, char c);
char		*expand_str(t_data *data, t_substr *s, int *err);

/*	expander_quotes_main.c	*/
void		expand_quotes(t_data *data, t_substr *str, size_t *i, char c);

/*	expand_heredoc.c	*/
char		*expand_line(t_data *data, char *str, char *buffer);
void		prepare_expand_hd(t_data *data);
void		expand_dollar_hd(t_data *data, t_substr *s, size_t *i, \
							char *buffer);
void		remove_limiter_quotes(t_data *data);

/*	expand_heredoc_utils.c	*/
void		question_mark_hd(t_data *data, t_substr *s, size_t *i, \
							char *buffer);
void		number_xpd_hd(t_data *data, t_substr *s, size_t *i, char *buffer);

/*	expand_utils.c	*/
void		modify_lxr_nds(t_data *data, t_substr *s, size_t index);

/*	expand_utils2.c	*/
t_lexer		*update_tmp_index(t_data *data, size_t *i);
int			check_space_expand(t_data *data, t_substr *s, size_t index);
void		substrs_prep(t_data *data, t_substr *s, size_t *i);
void		remove_nodes(t_data *data);

/*	builtins.c	*/
int			builtins(t_data *data, t_command *cmd_struct, char **cmd);
int			check_builtins(char **cmd);
int			check_builtins_lexer(char *cmd);

/*	builtin_cd.c	*/
int			ft_cd(t_data *data, char **cmd);
char		*search_env(t_data *data, char *env);
int			replace_env(t_data *data, char *env, char *old_env);

/*	builtin_echo.c	*/
int			ft_echo(char **cmd, t_command *cmd_struct);

/*	builtin_echo.c	*/
void		ft_exit(t_data *data, char **cmd);

/*	builtin_export.c	*/
void		ft_list_sort(t_env **env, int size);
int			ft_export(t_data *data, char **cmd);
char		**export_var(t_data *data, char *cmd);
int			print_export(t_env **env);

/*	builtin_export_utils.c	*/
int			ft_list_size(t_env *env);
int			envp_replacement(t_data *data, char **var, char *cmd);
int			existing_var(t_data *data, char *cmd, int i);
char		**export_var_only(t_data *data, char *cmd);

/*	builtin_export_utils2.c	*/
void		iterate_pp_envp(t_data *data, char *cmd, int i, int export);

/*	builtin_unset.c	*/
int			ft_unset(t_data *data, char **cmd);

/*	envp_handle.c	*/
char		*get_shlvl(t_data *data, char *str);
char		*search_env(t_data *data, char *env);
int			replace_env(t_data *data, char *env, char *old_env);
int			add_env_node(t_env **env, char *str);

/*	heredoc.c	*/
void		init_heredoc_data(t_data *data);
void		heredoc_pipe(t_data *data);
void		create_pipes_hd(t_data *data);
int			heredoc_ctrl_check(t_data *data, char *line, char *buffer);

/*	heredoc_redir.c	*/
int			heredoc_redir(t_data *data);
void		add_heredoc(t_data *data, char *file, size_t index);
void		heredoc_count(t_data *data);

/*	utils.c	*/
char		*ft_change_str(t_data *data, char *s1, char *s2);
size_t		lstlen(t_lexer *lexer);
size_t		lstlencmd(t_command *cmd);
void		complete_inf_data(t_data *data, t_lexer *tmp, char *file, \
								int valid);

/*	utils2.c	*/
void		complete_out_data(t_data *data, t_lexer *tmp, char *file, \
								int valid);
size_t		ft_strlen_pp(char **s);
char		*ft_substr_check(char *s, size_t i, size_t len, int *err);

/*	utils3.c	*/
char		*ft_strjoin_free_s2(t_data *data, char *s1, char *s2);
char		*ft_strjoin_expand(t_data *data, char *s1, char *s2);
char		*ft_strjoin_free(t_data *data, char *s1, char *s2);

/*	free.c	*/
void		free_lexer_strct(t_data *data);
void		free_env_strct(t_data *data);
void		free_cmd_strct(t_data *data);
void		free_data_strct(t_data *data);
void		free_hd_strct(t_data *data);

/*	free_2.c	*/
void		free_content_cmd_node(t_command *tmp);
void		free_content_env_node(t_env *tmp);
void		free_data(t_data *data, void (*f)(t_data *data));
void		free_all(t_data *data);
void		free_loop(t_data *data);

/*	free_3.c	*/
void		free_substr_strct(t_substr *s);
void		free_substr_strct_hd(t_substr *s);

/*	free_utils.c	*/
void		ft_free_pp(char **ptr);
void		ft_free_paths(t_data *data);
void		ft_free_limiter(t_heredoc *hd);
void		free_hd_limit(t_data *data);

/*	exec_data_creation.c	*/
void		exec_cmd_lst(t_data *data);

/*	exec.c	*/
void		exec(t_data *data, char **cmd);

/*	exec_utils.c	*/
int			heredoc_check(t_data *data, t_command *cmd);
void		exec_error_handle(t_data *data);
void		join_path_and_cmd(t_data *data, char *cmd, int i);
void		restore_stds(t_data *data);
void		extract_paths(t_data *data);
void		exec_cmd_lst_wait(t_data *data);

/*	exec_utils2.c	*/
void		exec_cmd_lst_wait(t_data *data);
void		loop_on_path(t_data *data, char **cmd_args, char *cmd, int i);

/*	signals.c	*/
void		signal_set(void);
void		signal_hd_set(void);
void		signal_exec_set(void);
void		silence_signals(void);

/*	signals_handler.c	*/
void		handler_sigint(int signal);
void		handler_hd_sigint(int signal);
void		handler_exec(int signal);

/*	close.c	*/
void		close_heredoc_pipes(t_data *data);
void		close_all(t_data *data);
void		close_files(t_data *data);

#endif
