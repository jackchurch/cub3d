NAME	= libft.a
CC		= clang
CFLAGS	= -Wall -Wextra -Werror

SRC		:=	\
	ft_putchar_fd.c	ft_atoi.c		ft_memset.c		ft_strncmp.c	ft_strjoin.c	\
	ft_strrchr.c	ft_split.c		ft_isupper.c	ft_memchr.c		ft_substr.c		\
	ft_strmapi.c  	ft_isdigit.c	ft_isascii.c	ft_putnbr_fd.c	ft_itoa.c		\
	ft_bzero.c		ft_strlcat.c	ft_striteri.c	ft_strnstr.c	ft_isprint.c	\
	ft_putstr_fd.c	ft_strcpy.c		ft_strchr.c		ft_memcmp.c		ft_strlcpy.c	\
	ft_tolower.c	ft_toupper.c	ft_memcpy.c		ft_isalpha.c	ft_isalnum.c	\
	ft_putendl_fd.c	ft_calloc.c		ft_strdup.c		ft_memmove.c	ft_strlen.c		\
	ft_islower.c	ft_strtrim.c	ft_lstadd_back.c	ft_lstadd_front.c	\
	ft_lstclear.c	ft_lstdelone.c	ft_lstiter.c	ft_lstlast.c	ft_lstmap.c		\
	ft_lstnew.c		ft_lstsize.c	get_next_line.c

OBS		:= $(patsubst %.c, %.o, $(SRC))

all: $(NAME)
$(NAME): $(OBS)
	ar -rcs $(NAME) $(OBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
