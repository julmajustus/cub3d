# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 16:11:30 by jmakkone          #+#    #+#              #
#    Updated: 2024/11/04 11:00:00 by skwon2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = cub3D
LIBFT_DIR       = ./libft
MLX42_DIR 		= ./MLX42
SRC_DIR         = src
INC_DIR         = inc

SRC             = $(SRC_DIR)/main.c \
                  $(SRC_DIR)/init.c \
                  $(SRC_DIR)/parse_minimap.c \
                  $(SRC_DIR)/raycaster.c \
                  $(SRC_DIR)/rotate_view.c \
                  $(SRC_DIR)/controls_keyboard.c \
                  $(SRC_DIR)/exit_mlx.c \
                  $(SRC_DIR)/parsing_description/file_exist.c \
                  $(SRC_DIR)/parsing_description/map_configuration.c \
                  $(SRC_DIR)/parsing_description/read_description.c \
                  $(SRC_DIR)/parsing_description/find_player.c \
                  $(SRC_DIR)/parsing_description/parsing_colors.c \
                  $(SRC_DIR)/parsing_description/check_wall.c

OBJ_DIR         = obj
OBJ             = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT           = $(LIBFT_DIR)/libft.a
MLX42_LIB       = $(MLX42_DIR)/build/libmlx42.a
GLFW_LIB_PATH   = /opt/homebrew/opt/glfw/lib
GLFW_INCLUDE_PATH = /opt/homebrew/opt/glfw/include

RM              = rm -f
CC              = clang
CFLAGS          = -Wunreachable-code -Wall -Wextra -Werror \
                  -I$(INC_DIR) \
                  -I$(LIBFT_DIR) \
                  -I$(MLX42_DIR)/include \
                  -I$(GLFW_INCLUDE_PATH) -Ofast\
                  -g -ggdb3 -fsanitize=address

all: $(LIBFT) $(MLX42_LIB) $(NAME)


$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX42_LIB):
	@if [ ! -d $(MLX42_DIR) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git \
		$(MLX42_DIR); \
	fi
	@if [ ! -d "$(MLX42_DIR)/build" ]; then \
		mkdir -p $(MLX42_DIR)/build; \
	fi
	@cd $(MLX42_DIR)/build && \
		if [ ! -f CMakeCache.txt ]; then \
			cmake .. -D CMAKE_OSX_ARCHITECTURES=arm64; \
		fi && \
		cmake --build .

# Object file compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/*.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Targets
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42_LIB) -L$(GLFW_LIB_PATH) -lglfw -o $(NAME);
	@echo "\n$(Yellow)-----CUB3D HAS BEEN CREATED-----$(Ending)\n"

# Clean targets
clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(MLX42_DIR)/build

re: fclean all

.PHONY: all clean fclean re

Red = \033[0;31m
Green = \033[0;32m
Yellow = \033[0;33m
Blue = \033[0;34m
Magenta = \033[0;35m
Cyan = \033[0;36m
White = \033[0;37m
Ending = \033[0m
