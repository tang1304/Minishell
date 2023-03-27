# Variables
NAME	=	libft.a

CC	=	cc

RM	=	rm -rf

FLAGS	=	-Wall -Wextra -Werror

HEADER	=	libft.h


# directories
D_HEADER	=	incs/

D_SRCS		=	SRCS/

D_OBJS		=	objs/


# files
LST_SRCS	=	ft_isalnum.c ft_memcmp.c ft_strdup.c ft_strnstr.c ft_isalpha.c ft_memcpy.c \
				ft_strrchr.c ft_isascii.c ft_memmove.c ft_strlcat.c ft_atoi.c ft_isdigit.c \
				ft_memset.c  ft_strlcpy.c ft_bzero.c ft_isprint.c ft_strlen.c  ft_tolower.c \
				ft_calloc.c  ft_memchr.c  ft_strchr.c  ft_strncmp.c ft_toupper.c ft_substr.c \
				ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
				ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
				ft_lstiter.c ft_lstmap.c \
				get_next_line.c get_next_line_utils.c \
				ft_convert_address.c ft_convert_nbr.c ft_printf.c ft_putchar.c \
				ft_putnbr_unsigned.c ft_putnbr.c ft_putstr.c

SRCS		=	$(addprefix $(D_SRCS), $(LST_SRCS))

INCS		=	$(addprefix $(D_HEADER), $(HEADER))

OBJS		=	$(subst $(D_SRCS), $(D_OBJS), $(SRCS:.c=.o))


#rules
all		:	$(NAME)

$(NAME)	:	$(OBJS) $(INCS) Makefile
			ar -rcs $(NAME) $(OBJS) $(INCS)

$(D_OBJS)%.o	:	$(D_SRCS)%.c $(INCS) Makefile | $(D_OBJS)
					$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

$(D_OBJS)		:
					mkdir -p $(D_OBJS)

clean	:
			$(RM) $(OBJS)
			$(RM) $(D_OBJS)

fclean	:
			$(MAKE) clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
