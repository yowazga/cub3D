# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 21:42:20 by zmoumen           #+#    #+#              #
#    Updated: 2023/08/15 18:43:48 by zmoumen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#~~~~~~~~~~~~~~[COMPILER]~~~~~~~~~~~~~~
CC = cc
CFLAGS =  -I./mlx42/include/MLX42 -I./libft -Wall -Wextra -Werror

NAME = cub3D
NAME_BONUS = cub3D_bonus
all: $(NAME)

SHELL = /bin/bash
.PHONY = all
#~~~~~~~~~~~~~~

#~~~~~~~~~~~~~~[MAND_SOURCE FILES]~~~~~~~~~~~~~~
MAND_SRC_MP_LDR = map_loader.c map_utils.c parse_matrix.c textures_utils/load_textures.c textures_utils/parse_textures.c

MAND_RAYCASTER_ENGINE_SRC = draw_3d_map.c recast_algo.c utils_recst_algo.c utils.c utils_main.c
MAND_SRC = mandatory/main.c $(addprefix mandatory/map_loader/, $(MAND_SRC_MP_LDR)) $(addprefix mandatory/raycaster_engine/, $(MAND_RAYCASTER_ENGINE_SRC))
#~~~~~~~~~~~~~~


#~~~~~~~~~~~~~~[BONUS SOURCE FILES]~~~~~~~~~~~~~~
BNS_SRC_MP_LDR = map_loader_bonus.c map_utils_bonus.c parse_matrix_bonus.c textures_utils/load_textures_bonus.c textures_utils/parse_textures_bonus.c

BNS_RAYCASTER_ENGINE_SRC = draw_3d_map_bonus.c draw_minimap_bonus.c recast_algo_bonus.c utils_recst_algo_bonus.c utils_bonus.c utils_main_bonus.c utils_main2_bonus.c
BNS_SRC = bonus/main_bonus.c $(addprefix bonus/map_loader/, $(BNS_SRC_MP_LDR)) $(addprefix bonus/raycaster_engine/, $(BNS_RAYCASTER_ENGINE_SRC))
#~~~~~~~~~~~~~~


#~~~~~~~~~~~~~~[MLX AND ITS DEPS]~~~~~~~~~~~~~~
MLX = mlx42/build/libmlx42.a
MLX_CMAKE = mlx42/CMakeLists.txt
GLFW = $(shell brew --prefix glfw )/lib/libglfw.dylib

$(GLFW):
	@echo "📛  Missing glfw library"
	@echo "🛂  Install it with brew\n\n"
	@exit 1

$(MLX_CMAKE):
	@if [ -d mlx42 ]; then echo "🟠  MLX42 already cloned\n🛂  Call make re_mlx if folder is corrupted\n\n"; exit 1; fi
	@echo "📡  cloning mlx42"
	@git clone https://github.com/codam-coding-college/MLX42.git mlx42 --quiet


clone_mlx: $(MLX_CMAKE)

 $(MLX): $(GLFW)
	@if [ ! -d mlx42 ]; then echo "📛  MLX42 not cloned"; echo "🛂  Call make clone_mlx first"; exit 1; fi
	@echo "🏭🏗 Building MLX42"
	@cmake -Bmlx42/build -Hmlx42 > /dev/null
	@make -C mlx42/build
	@echo "✅  MLX42 Built"

build_mlx: $(GLFW) $(MLX)

mlx: $(GLFW) $(MLX_CMAKE) $(MLX)

rm_mlx:
	@echo "🚮  Removing MLX42"
	@rm -rf mlx42

re_mlx: rm_mlx mlx

.PHONY += clone_mlx build_mlx mlx rm_mlx re_mlx
#~~~~~~~~~~~~~~

#~~~~~~~~~~~~~~[LIBFT]~~~~~~~~~~~~~~
LIBFT = libft/libft.a

$(LIBFT):
	@echo "🏭🏗 Building libft"
	@make -C libft > /dev/null

libft: $(LIBFT)

libft_clean:
	@echo "🚮  Cleaning libft"
	@make fclean -C libft > /dev/null

libft_re: libft_clean libft

.PHONY += libft libft_clean libft_re
#~~~~~~~~~~~~~~

#~~~~~~~~~~~~~~[CUB3D]~~~~~~~~~~~~~~
$(NAME): $(MLX_CMAKE) $(MLX) $(GLFW) $(LIBFT) $(MAND_SRC) mandatory/cub3d.h
	@echo "🏭🏗 Building executable"
	@$(CC) $(CFLAGS) $(MAND_SRC)  -I./mandatory $(MLX) $(LIBFT) $(GLFW) -o $@
	@echo "✅🎮 Ready to Play"

#~~~~~~~~~~~~~~

$(NAME_BONUS): $(MLX_CMAKE) $(MLX) $(GLFW) $(LIBFT) $(BNS_SRC) bonus/cub3d_bonus.h
	@echo "🏭🏗 Building executable"
	@$(CC) $(CFLAGS) $(BNS_SRC)  -I./bonus $(MLX) $(LIBFT) $(GLFW) -o $@
	@echo "✅🎮 Ready to Play"

bonus: $(NAME_BONUS)
#~~~~~~~~~~~~~~[CLEANING]~~~~~~~~~~~~~~
clean:
	@echo "🚮  Removing executables and libft .o"
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@make -C libft clean > /dev/null

fclean: clean rm_mlx libft_clean
	@make -C libft fclean > /dev/null
	@echo "✅  All cleared"
	

re_source_only: clean all

re: fclean all

.PHONY += clean fclean re
#~~~~~~~~~~~~~~
