############################
#                          #
#        VARIABLES         #
#                          #
############################

NAME		=	minishell

CC			=	cc

RM			=	rm -rf

FLAGS		=	-Wall -Wextra -Werror

HEADER		=	minishell.h

LIBFT		=	libft.a



# DIRECTORIES
D_HEADER	=	incs/

D_SRCS		=	SRCS/

D_OBJS		=	objs/

D_LIBFT		=	libft/


# FILES MINISHELL
LST_SRCS	=	main.c \
				data.c \
				loop.c \
				parser.c \
				lexer.c \
				lexer_utils.c \
				expand.c \
				expander_quotes.c \
				expander_var.c \
				check_error_input.c \
				check_error_utils.c \
				add_infile_outfile.c \
				add_infile_outfile_utils.c \
				remove_nodes.c \
				heredoc.c \
				utils.c

LST_OBJS	=	$(LST_SRCS:.c=.o)

SRCS		=	$(addprefix $(D_SRCS), $(LST_SRCS))

INCS		=	$(addprefix $(D_HEADER), $(HEADER))

OBJS		=	$(addprefix $(D_OBJS), $(LST_OBJS))

LIBFTLIB	=	$(addprefix $(D_LIBFT), $(LIBFT))

# COLORS
_NOC	:=	\033[0m

_RED	:=	\033[1;31m

_GREEN	:=	\033[1;32m

# RULES
all		:	lib $(NAME)

lib :
		$(MAKE) -C $(D_LIBFT)

$(NAME)	:	$(OBJS)
			$(CC) $(OBJS) -lreadline $(LIBFTLIB) -o $(NAME)
			@echo "${_GREEN}### ${NAME} created ###${_NOC}\n"

$(D_OBJS)%.o	:	$(D_SRCS)%.c $(INCS) Makefile $(LIBFTLIB)
					mkdir -p $(D_OBJS)
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
