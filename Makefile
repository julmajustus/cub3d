# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skwon2 <skwon2@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 16:11:30 by jmakkone          #+#    #+#              #
#    Updated: 2024/11/27 05:18:12 by jmakkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = cub3D
LIBFT_DIR       = ./libft
MLX42_DIR 		= ./MLX42
SRC_DIR         = src
INC_DIR         = inc

SRC             = $(SRC_DIR)/main.c \
				  $(SRC_DIR)/check_timeout.c \
				  $(SRC_DIR)/init.c \
				  $(SRC_DIR)/init_buffers.c \
				  $(SRC_DIR)/malloc_check.c \
				  $(SRC_DIR)/draw_scene.c \
				  $(SRC_DIR)/draw_kill_count.c \
				  $(SRC_DIR)/check_game_status.c \
				  $(SRC_DIR)/minimap/parse_minimap.c\
				  $(SRC_DIR)/minimap/draw_ply.c\
				  $(SRC_DIR)/minimap/draw_ray.c\
				  $(SRC_DIR)/minimap/draw_sprites.c\
                  $(SRC_DIR)/raycaster/cast_rays.c \
                  $(SRC_DIR)/raycaster/trace_ray.c \
                  $(SRC_DIR)/render_view/get_wall_texture.c \
                  $(SRC_DIR)/render_view/init_pixel_color_buffers.c \
                  $(SRC_DIR)/render_view/render_floor_and_ceiling.c \
                  $(SRC_DIR)/render_view/render_view.c \
                  $(SRC_DIR)/rotate_view.c \
                  $(SRC_DIR)/controls_keyboard.c \
                  $(SRC_DIR)/check_collision.c \
                  $(SRC_DIR)/exit_mlx.c \
				  $(SRC_DIR)/free_textures.c \
				  $(SRC_DIR)/parsing_description/file_exist.c \
				  $(SRC_DIR)/parsing_description/map_configuration.c \
				  $(SRC_DIR)/parsing_description/read_description.c \
				  $(SRC_DIR)/parsing_description/find_player.c \
				  $(SRC_DIR)/parsing_description/parsing_colors.c \
				  $(SRC_DIR)/parsing_description/check_wall.c \
				  $(SRC_DIR)/handle_doors.c \
				  $(SRC_DIR)/reset_door_state.c \
				  $(SRC_DIR)/sprites/init_sprites.c \
				  $(SRC_DIR)/sprites/render_sprites.c \
				  $(SRC_DIR)/sprites/draw_sprite.c \
				  $(SRC_DIR)/sprites/check_sprite_hit.c \
				  $(SRC_DIR)/sprites/render_shotgun.c

OBJ_DIR         = obj
OBJ             = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_DIR_BONUS   = obj_bonus
OBJ_BONUS		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR_BONUS)/%.o)
LIBFT           = $(LIBFT_DIR)/libft.a
MLX42_LIB       = $(MLX42_DIR)/build/libmlx42.a
GLFW_LIB_PATH   = /opt/homebrew/opt/glfw/lib
GLFW_INCLUDE_PATH = /opt/homebrew/opt/glfw/include
BONUS_FLAGS		=

RM              = rm -f
CC              = clang
CFLAGS          = -Wunreachable-code -Wall -Wextra -Werror \
				  -I$(INC_DIR) \
				  -I$(LIBFT_DIR) \
				  -I$(MLX42_DIR)/include \
				  -I$(GLFW_INCLUDE_PATH) -O3 \
				  #-g -ggdb3 -fsanitize=address


all : .delete .mandatory

.delete : 
	@touch .delete
	@rm -f .timestamps .delete_bo

fc: BONUS_FLAGS += -DFC_TEXTURES=1
fc: bonus

bonus: BONUS_FLAGS += -DBONUS=1
bonus : .delete_bo .timestamps

.delete_bo : 
	@touch .delete_bo
	@rm -f .delete .mandatory

.timestamps : $(LIBFT) $(MLX42_LIB) $(OBJ_BONUS)
	@touch .timestamps
	@$(CC) $(CFLAGS) $(BONUS_FLAGS) $(OBJ_BONUS) $(LIBFT) $(MLX42_LIB) -L$(GLFW_LIB_PATH) -lm -lglfw -o $(NAME);
	@echo "\n$(Yellow)-----CUB3D BONUS HAS BEEN CREATED-----$(Ending)\n"

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

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/*.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(BONUS_FLAGS) -c $< -o $@

# Targets
.mandatory : $(LIBFT) $(MLX42_LIB) $(OBJ)
	@touch .mandatory
	@$(CC) $(CFLAGS) $(BONUS_FLAGS) $(OBJ) $(LIBFT) $(MLX42_LIB) -L$(GLFW_LIB_PATH) -lm -lglfw -o $(NAME);
	@echo "\n$(Yellow)-----CUB3D HAS BEEN CREATED-----$(Ending)\n"

# Clean targets
check_bonus:
	@if [ -f .timestamps ]; then \
		rm -f .timestamps .delete_bo; \
	fi

check_mandatory:	
	@if [ -f .mandatory ]; then \
		rm -f .mandatory .delete; \
	fi

clean : check_bonus check_mandatory
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(RM) -r $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
#@rm -rf $(MLX42_DIR)/build

re: fclean all

re_bo : fclean bonus

.PHONY: all clean fclean re bonus fc re_bo check_bonus check_mandatory

Red = \033[0;31m
Green = \033[0;32m
Yellow = \033[0;33m
Blue = \033[0;34m
Magenta = \033[0;35m
Cyan = \033[0;36m
White = \033[0;37m
Ending = \033[0m
