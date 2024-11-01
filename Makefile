# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 16:11:30 by jmakkone          #+#    #+#              #
#    Updated: 2024/11/01 20:57:58 by jmakkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME            = cub3D
LIBFT_DIR       = ./libft
MLX42_DIR       = ./MLX42
SRC_DIR         = src
INC_DIR         = inc

SRC             = $(SRC_DIR)/main.c \
				  $(SRC_DIR)/init.c \
				  $(SRC_DIR)/read_map.c \
				  $(SRC_DIR)/parse_minimap.c \
				  $(SRC_DIR)/raycaster.c \
				  $(SRC_DIR)/controls_keyboard.c \
				  $(SRC_DIR)/rotate_view.c \
				  $(SRC_DIR)/exit_mlx.c \

OBJ_DIR         = obj
OBJ             = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT           = $(LIBFT_DIR)/libft.a
LIBMLX42        = $(MLX42_DIR)/build/libmlx42.a -Ofast -ldl -lglfw -pthread -lm

RM              = rm -f
CC              = clang
CFLAGS          = -Wunreachable-code -Wall -Wextra -Werror \
				  -I$(INC_DIR) \
				  -I$(LIBFT_DIR) \
				  -I$(MLX42_DIR)/include/$(MLX42_DIR) \
				  -O3 #-g -ggdb3 -fsanitize=address


all:  $(LIBFT) $(LIBMLX42) $(NAME)

# Build library targets
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(LIBMLX42):
	@if [ ! -d $(MLX42_DIR) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git \
		$(MLX42_DIR); \
	fi
	@if [ ! -f $(MLX42_DIR)/build/libmlx42.a ]; then \
		cmake $(MLX42_DIR) -B $(MLX42_DIR)/build && \
		cmake --build $(MLX42_DIR)/build -j$(shell nproc); \
	fi

# Object file compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/*.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Targets

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBMLX42) $(LIBFT) -o $(NAME)



# Clean targets
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(MLX42_DIR)/build

re: fclean all

.PHONY: all clean fclean re bonus
