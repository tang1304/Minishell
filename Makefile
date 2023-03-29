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


# FILES SO_LONG
LST_SRCS	=	main.c \
				data.c \
				builting.c \
				loop.c \
				check_error_input.c

LST_OBJS	=	$(LST_SRCS:.c=.o)

SRCS		=	$(addprefix $(D_SRCS), $(LST_SRCS))

INCS		=	$(addprefix $(D_HEADER), $(HEADER))

OBJS		=	$(addprefix $(D_OBJS), $(LST_OBJS))

LIBFTLIB	=	$(addprefix $(D_LIBFT), $(LIBFT))


# RULES
all		:	lib $(NAME)

lib :
		$(MAKE) -C $(D_LIBFT)

$(NAME)	:	$(OBJS)
			$(CC) $(OBJS) -lreadline $(LIBFTLIB) -o $(NAME)

$(D_OBJS)%.o	:	$(D_SRCS)%.c $(INCS) Makefile $(LIBFTLIB)
					mkdir -p $(D_OBJS)
					$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

clean	:
			$(RM) $(OBJS)
			$(RM) $(D_OBJS)
			$(MAKE) clean -C $(D_LIBFT)

fclean	:
			$(MAKE) clean
			$(RM) $(NAME)
			$(MAKE) fclean -C $(D_LIBFT)

re		:	fclean all

.PHONY	:	all clean fclean re lib
