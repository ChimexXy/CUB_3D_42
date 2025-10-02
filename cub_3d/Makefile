CC = cc

# CFLAGS = -Wall -Wextra -Werror

NAME = cub3d

LIB = ./libft/libft.a

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/build/libmlx42.a

SRC = 	cub3d.c								\
		./parsing/parsing.c					\
		./parsing/set_file.c				\
		./parsing/valid_map.c				\
		./parsing/cub3d_map.c				\
		./parsing/getc_map.c				\
		./parsing/handle_format.c			\
		./parsing/handle_void.c				\
		./parsing/cub3d_config.c			\
		./parsing/print_config.c			\
		./parsing/floor_color.c				\
		./parsing/ceiling_color.c			\
		./parsing/no_texture.c 				\
		./parsing/so_texture.c 				\
		./parsing/we_texture.c 				\
		./parsing/ea_texture.c 				\
		./parsing/utils/utils00.c			\
		./parsing/utils/utils01.c			\
		./parsing/utils/utils02.c			\
		./parsing/utils/utils03.c 			\
		./parsing/utils/utils04.c 			\
		./raycasting/move.c					\
		./raycasting/raycasting.c			\

HDR = 	cub3d.h	./raycasting/raycasting.h	\

OBJ = $(SRC:.c=.o)

S_GNL = ./parsing/get_next_line/gnl.c		\
		./parsing/get_next_line/gnl_utils.c	\

OBJ_GNL = $(S_GNL:.c=.o)

HDR_GNL = ./parsing/get_next_line/gnl.h

SRC_LIB = ./libft/ft_strlen.c 	\
		  ./libft/ft_strdup.c 	\
		  ./libft/ft_strcmp.c	\
		  ./libft/ft_split.c	\
		  ./libft/ft_substr.c	\
		  ./libft/ft_atoi.c		\

OBJ_LIB = $(SRC:.c=.o)

HDR_LIB = ./libft/libft.h

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_GNL) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_GNL) $(LIB)  $(MLX_LIB) -L $(MLX_DIR) -Iinclude -ldl -lglfw -pthread -lm -o $@

./parsing/get_next_line/%.o: ./parsing/get_next_line/%.c $HDR_GNL
	$(CC) $(CFALGS) -c $< -o $@

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(SRC_LIB) $(HDR_LIB)
	$(MAKE) -C ./libft

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_GNL)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all