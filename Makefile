NAME		= a.out cub3d

FT_PATH		= ./libft
MLX_PATH	= ./mlx
MLX_LIB		= libmlx.a
FT_LIB		= libft.a
INC_PATH	= ./inc
SRC_PATH	= ./src
OBJ_PATH	= ./obj

LINK_MLX	=-L$(MLX_PATH) -lmlx
LINK_FT	=  -L$(FT_PATH) -lft

MLX_MAC_THINGS =-framework OpenGL -framework AppKit

SRCS	=$(SRC_PATH)/main.c \
$(SRC_PATH)/init_mlx.c \
$(SRC_PATH)/destroy_mlx.c \
$(SRC_PATH)/init_player.c

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
OBJECTS = $(patsubst %.c,%.o, $(SRCS))

all: $(NAME)
	printf "Compiling complete, run ./a.out or ./cub3d"

$(NAME): $(OBJECTS) $(MLX_LIB) $(FT_LIB)
	$(CC) -I$(INC_PATH) -I$(MLX_PATH) -I$(FT_PATH) $(LINK_MLX) $(LINK_FT) $(MLX_MAC_THINGS) -o $@ $(OBJECTS)


# %.o: $(SRC_PATH)/%.c
	# @printf "Source to Objects\n"
	# $(CC) $(CFLAGS) -c -o $@ $^

$(MLX_LIB):
	make -C $(MLX_PATH)

$(FT_LIB):
	make -C $(FT_PATH)

clean:
	make clean -sC $(MLX_PATH)
	make clean -sC $(FT_PATH)
	rm -f $(OBJECTS)
	# rm -f $(MLX_LIB)

fclean: clean
	rm -f $(FT_PATH)/$(FT_LIB)
	rm -f $(NAME)

re: fclean all

fclear: fclean
clear: fclean

.PHONY:	all clean fclean re fclear
