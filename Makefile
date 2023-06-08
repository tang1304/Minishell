############################
#                          #
#        VARIABLES         #
#                          #
############################

NAME		=	minishell

CC			=	cc -g3 #-fsanitize=address

RM			=	rm -rf

FLAGS		=	-Wall -Wextra -Werror

HEADER		=	minishell.h

LIBFT		=	libft.a



# DIRECTORIES
D_HEADER	=	incs/

D_SRCS		=	SRCS/
D_SRCS_P	=	SRCS/parser/
D_SRCS_E	=	SRCS/expand/
D_SRCS_B	=	SRCS/builtin/
D_SRCS_H	=	SRCS/hd/
D_SRCS_X	=	SRCS/exec/
D_SRCS_F	=	SRCS/files/
D_SRCS_L	=	SRCS/lexer/
D_SRCS_FR	=	SRCS/free/
D_SRCS_ERR	=	SRCS/error/
D_SRCS_S	=	SRCS/signals/
D_SRCS_U	=	SRCS/utils/

D_OBJS		=	objs/
D_OBJS_P	=	objs/parser/
D_OBJS_E	=	objs/expand/
D_OBJS_B	=	objs/builtins/
D_OBJS_H	=	objs/hd/
D_OBJS_X	=	objs/exec/
D_OBJS_F	=	objs/files/
D_OBJS_L	=	objs/lexer/
D_OBJS_FR	=	objs/free/
D_OBJS_ERR	=	objs/error/
D_OBJS_S	=	objs/signals/
D_OBJS_U	=	objs/utils/

D_LIBFT		=	libft/


# FILES MINISHELL
LST_SRCS		=	main.c \
					data.c \
					loop.c \
					envp_handle.c \
					envp_utils.c \
					close.c

LST_SRCS_U		=	utils.c \
					utils2.c

LST_SRCS_S		=	signals.c \
					signals_handler.c

LST_SRCS_L		=	lexer.c \
					lexer_utils.c \
					lexer_utils2.c \
					lexer_update.c \
					remove_lexer_nodes.c

LST_SRCS_FR		=	free.c \
					free_2.c \
					free_utils.c

LST_SRCS_ERR	=	check_error_input.c \
					check_error_utils.c \
					errors.c

LST_SRCS_P		=	parser.c \
					parser_utils.c

LST_SRCS_E		=	expand.c \
					expander_quotes.c \
					expander_quotes_utils.c \
					expander_var.c \
					expand_utils.c \
					expand_join_all.c \
					expand_heredoc.c \
					expand_heredoc_utils.c

LST_SRCS_B		=	builtins.c \
					builtin_cd.c \
					builtin_echo.c \
					builtin_exit.c \
					builtin_unset.c \
					builtin_export.c \
					builtin_export_utils.c \
					builtin_export_utils2.c

LST_SRCS_H		=	heredoc.c \
					heredoc_redir.c

LST_SRCS_X		=	exec_data_creation.c \
					exec.c \
					exec_utils.c \
					exec_utils2.c

LST_SRCS_F		=	add_infile_outfile.c \
					add_infile_outfile_utils.c \
					add_pipes_lexer.c

LST_OBJS		=	$(LST_SRCS:.c=.o)
LST_OBJS_P		=	$(LST_SRCS_P:.c=.o)
LST_OBJS_E		=	$(LST_SRCS_E:.c=.o)
LST_OBJS_B		=	$(LST_SRCS_B:.c=.o)
LST_OBJS_H		=	$(LST_SRCS_H:.c=.o)
LST_OBJS_X		=	$(LST_SRCS_X:.c=.o)
LST_OBJS_F		=	$(LST_SRCS_F:.c=.o)
LST_OBJS_L		=	$(LST_SRCS_L:.c=.o)
LST_OBJS_FR		=	$(LST_SRCS_FR:.c=.o)
LST_OBJS_ERR	=	$(LST_SRCS_ERR:.c=.o)
LST_OBJS_S		=	$(LST_SRCS_S:.c=.o)
LST_OBJS_U		=	$(LST_SRCS_U:.c=.o)

SRCS		=	$(addprefix $(D_SRCS), $(LST_SRCS))
SRCS_P		=	$(addprefix $(D_SRCS_P), $(LST_SRCS_P))
SRCS_E		=	$(addprefix $(D_SRCS_E), $(LST_SRCS_E))
SRCS_B		=	$(addprefix $(D_SRCS_B), $(LST_SRCS_B))
SRCS_H		=	$(addprefix $(D_SRCS_H), $(LST_SRCS_H))
SRCS_X		=	$(addprefix $(D_SRCS_X), $(LST_SRCS_X))
SRCS_F		=	$(addprefix $(D_SRCS_F), $(LST_SRCS_F))
SRCS_L		=	$(addprefix $(D_SRCS_L), $(LST_SRCS_L))
SRCS_FR		=	$(addprefix $(D_SRCS_FR), $(LST_SRCS_FR))
SRCS_ERR	=	$(addprefix $(D_SRCS_ERR), $(LST_SRCS_ERR))
SRCS_S		=	$(addprefix $(D_SRCS_S), $(LST_SRCS_S))
SRCS_U		=	$(addprefix $(D_SRCS_U), $(LST_SRCS_U))

INCS		=	$(addprefix $(D_HEADER), $(HEADER))

OBJS		=	$(addprefix $(D_OBJS), $(LST_OBJS))
OBJS_P		=	$(addprefix $(D_OBJS_P), $(LST_OBJS_P))
OBJS_E		=	$(addprefix $(D_OBJS_E), $(LST_OBJS_E))
OBJS_B		=	$(addprefix $(D_OBJS_B), $(LST_OBJS_B))
OBJS_H		=	$(addprefix $(D_OBJS_H), $(LST_OBJS_H))
OBJS_X		=	$(addprefix $(D_OBJS_X), $(LST_OBJS_X))
OBJS_F		=	$(addprefix $(D_OBJS_F), $(LST_OBJS_F))
OBJS_L		=	$(addprefix $(D_OBJS_L), $(LST_OBJS_L))
OBJS_FR		=	$(addprefix $(D_OBJS_FR), $(LST_OBJS_FR))
OBJS_ERR	=	$(addprefix $(D_OBJS_ERR), $(LST_OBJS_ERR))
OBJS_S		=	$(addprefix $(D_OBJS_S), $(LST_OBJS_S))
OBJS_U		=	$(addprefix $(D_OBJS_U), $(LST_OBJS_U))

LIBFTLIB	=	$(addprefix $(D_LIBFT), $(LIBFT))

# COLORS
_NOC	:=	\033[0m

_RED	:=	\033[1;31m

_GREEN	:=	\033[1;32m

# RULES
all		:	lib $(NAME)

lib :
		$(MAKE) -C $(D_LIBFT)

$(NAME)	:	$(OBJS) $(OBJS_P) $(OBJS_E) $(OBJS_B) $(OBJS_H) $(OBJS_X) $(OBJS_F) $(OBJS_L) $(OBJS_FR) $(OBJS_ERR) $(OBJS_S) $(OBJS_U)
			$(CC) $(OBJS) $(OBJS_P) $(OBJS_S) $(OBJS_E) $(OBJS_B) $(OBJS_H) $(OBJS_X) $(OBJS_F) $(OBJS_L) $(OBJS_FR) $(OBJS_ERR) $(OBJS_U) -lreadline $(LIBFTLIB) -o $(NAME)
			@echo "${_GREEN}### ${NAME} created ###${_NOC}\n"

$(D_OBJS)%.o		:	$(D_SRCS)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS_P)%.o		:	$(D_SRCS_P)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS_P)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS_E)%.o		:	$(D_SRCS_E)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS_E)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS_B)%.o		:	$(D_SRCS_B)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS_B)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS_H)%.o		:	$(D_SRCS_H)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS_H)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS_X)%.o		:	$(D_SRCS_X)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS_X)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS_F)%.o		:	$(D_SRCS_F)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS_F)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS_L)%.o		:	$(D_SRCS_L)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS_L)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS_FR)%.o		:	$(D_SRCS_FR)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS_FR)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS_ERR)%.o	:	$(D_SRCS_ERR)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS_ERR)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS_S)%.o		:	$(D_SRCS_S)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS_S)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS_U)%.o		:	$(D_SRCS_U)%.c $(INCS) Makefile $(LIBFTLIB)
						mkdir -p $(D_OBJS_U)
						$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

clean	:
			$(RM) $(OBJS)
			$(RM) $(D_OBJS)
			$(MAKE) clean -C $(D_LIBFT)
			@echo "${_RED}### Removed ${NAME} object files ###${_NOC}"

fclean	:
			$(MAKE) clean
			$(RM) $(NAME)
			$(MAKE) fclean -C $(D_LIBFT)
			@echo "${_RED}### Removed ${NAME} ###${_NOC}"


re		:	fclean all

.PHONY	:	all clean fclean re lib
