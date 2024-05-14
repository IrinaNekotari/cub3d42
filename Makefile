# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjuette <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 10:26:29 by mjuette           #+#    #+#              #
#    Updated: 2024/03/20 10:42:18 by mjuette          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT_PATH	= ./libft/

LIBFT_FILE	= libft.a

LIBFT_LIB	= $(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

MLX42 = MLX42

MLX = MLX42/libmlx42.a

SRC = src/raycasting.c \
	src/parse_memory.c src/get_position.c src/errors.c src/color.c src/checks.c src/parser.c src/utils.c \
	src/size_utils.c src/list.c src/file_open.c src/map.c src/imgset.c src/imgset_utils.c src/main.c src/render.c src/render_util.c\
	src/movement.c src/input.c src/mlx_memory.c src/event.c src/init.c src/displays.c src/UI.c src/minimap.c \
	src/raycasting2.c src/maths.c src/animations.c src/ticks.c src/load_images.c src/end.c src/pixel.c src/game.c src/sprites.c src/raycasting_sprites.c
	
INC	= ./include/
OBJ = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror

FLAGLIB = -lglfw -ldl -lm

all: lib $(NAME)

lib:
	@echo "\033[0;33m\Compilation de la libft ...\n"
	@make -C $(LIBFT_PATH)
	@echo "\033[1;32mLibft compilee.\n"


$(NAME): $(OBJ)
	cc $(OBJ) $(FLAG) $(LIBFT_LIB) $(MLX) $(FLAGLIB) -o $(NAME) -g3

.c.o:
	cc -c $(FLAG) $< -o ${<:.c=.o} -g3

clean:
	@echo "\033[0;31mSuppression de la libft ...\n"
	@make clean -sC $(LIBFT_PATH)
	@echo "\033[1;Termine\n"
	rm -f $(OBJ)

$(MLX):
	git clone https://github.com/kodokaii/MLX42.git
	cmake $(MLX42) -B $(MLX42)
	make -C MLX

cleanMLX42:
	rm -rf $(MLX42)
fclean: clean
	@make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
