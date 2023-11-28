NAME		= a.out cub3d

FT_PATH		= ./libft
MLX_PATH	= ./mlx
MLX_LIB		= libmlx.a
FT_LIB		= libft.a
INC_PATH	= ./inc
SRC_PATH	= ./src
OBJ_PATH	= ./obj

INC_DIRS	= $(INC_PATH) $(MLX_PATH) $(FT_PATH)
INC_LIBS	= -L$(MLX_PATH) -lmlx -L$(FT_PATH) -lft
MLX_MAC_THINGS = -framework OpenGL -framework AppKit

SRCS	= src/main.c \
src/player.c
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g -MP -MD
OBJECTS = $(patsubst %.c,%.o, $(SRCS))
DEPFILES = $(patsubst %.c,%.d,$(SRCS))


all: $(NAME)

$(NAME): $(OBJECTS) $(MLX_LIB) $(FT_LIB)
	$(CC) -fsanitize=address -g $(OBJECTS) $(INC_LIBS) $(MLX_MAC_THINGS) -o $@

%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(MLX_LIB):
	make -C $(MLX_PATH)

$(FT_LIB):
	make -C $(FT_PATH)

clean:
	make clean -sC $(MLX_PATH)
	make clean -sC $(FT_PATH)
	rm -f $(OBJECTS) $(DEPFILES)
	# rm -f $(MLX_LIB)

fclean: clean
	rm -f $(FT_PATH)/$(FT_LIB)
	rm -f $(NAME)

re: fclean all

fclear: fclean
clear: fclean

-include $(DEPFILES)

.PHONY:	all clean fclean re fclear
