NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include -I./libft -I./minilibx-linux
RM = rm -f

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -lXext -lX11 -lm

SRCS = src/main.c \
	src/utils/error.c \
	src/utils/spaces.c \
	src/parsing/parser_data.c \
	src/parsing/parse_file.c \
	src/parsing/parse_line.c \
	src/parsing/parse_config.c \
	src/parsing/parse_color.c \
	src/parsing/map_store.c \
	src/parsing/map_utils.c \
	src/parsing/validate_map.c \
	src/graphics/visual.c \
	src/graphics/image.c \
	src/graphics/hooks.c \
	src/graphics/player.c \
	src/graphics/textures.c \
	src/graphics/movement.c \
	src/graphics/raycast.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
