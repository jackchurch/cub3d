NAME		= cub3D

OS			= $(shell uname)
FT_PATH		= ./libft
FT_LIB		= $(FT_PATH)/libft.a
INC_PATH	= ./inc
SRC_PATH	= ./src
OBJ_PATH	= ./obj

SRCS	= $(SRC_PATH)/main.c \
$(SRC_PATH)/ft_mlx.c \
$(SRC_PATH)/error.c \
$(SRC_PATH)/movement.c \
$(SRC_PATH)/maths.c \
$(SRC_PATH)/map.c \
$(SRC_PATH)/draw.c \
$(SRC_PATH)/render.c \
$(SRC_PATH)/ray.c \
$(SRC_PATH)/ray_intersect.c \
$(SRC_PATH)/ray_facing.c \
$(SRC_PATH)/cub_file_utils.c \
$(SRC_PATH)/cub_file_utils_2.c \
$(SRC_PATH)/init_cub_file.c \
$(SRC_PATH)/init_textures.c \
$(SRC_PATH)/update.c \
$(SRC_PATH)/parsing.c \
$(SRC_PATH)/mouse_movement.c \
$(SRC_PATH)/eff_norminette.c \
$(SRC_PATH)/set_ceiling_floor.c

CC		= cc
DFLAGS  = #-fsanitize=address -g
CFLAGS	= -Wall -Wextra -Werror -I$(INC_PATH) $(DFLAGS) -MP -MD -Ofast -flto
OBJECTS = $(patsubst %.c,%.o, $(SRCS))
DEPFILES = $(patsubst %.c,%.d,$(SRCS))

ifeq ($(OS),Darwin)
	MLX_PATH = ./mlx_mac
	MLX_FLAGS = -framework OpenGL -framework AppKit
else ifeq ($(OS),Linux)
	MLX_PATH = ./mlx_linux
	MLX_FLAGS = -lXext -lX11 -lm
endif

MLX_LIB		= $(MLX_PATH)/libmlx.a

INC_LIBS	= -L$(MLX_PATH) -lmlx -L$(FT_PATH) -lft
CFLAGS		+= -I $(MLX_PATH)

all: $(NAME)

$(NAME): $(OBJECTS) $(MLX_LIB) $(FT_LIB)
	$(CC) $(DFLAGS) $(CFLAGS) $(OBJECTS) $(INC_LIBS) $(MLX_FLAGS) -o $@

%.o:$(SRC_PATH)/.c
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
