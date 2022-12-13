# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/14 18:37:04 by jkasongo          #+#    #+#              #
#    Updated: 2022/12/13 11:50:25 by jkasongo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = clang
CFLAGS = -Wall -Wextra -Werror -Ofast -fno-strict-aliasing
INCLUDES_DIR = ./includes
OBJS_DIR = ./objs
OBJS_BONUS_DIR = ./objs_bonus
#libft
LIBFT_DIR = ./libft
LIBFT_LIB = ./libft/libft.a
#mlx
MLX_DIR =./minilibx
MLX_FLAGS = -L./ -lmlx -framework OpenGl -framework AppKit
MLX_LIB_FILES = libmlx.dylib

#styles for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET_COLOR = \033[0m

#utils sources
UTILS_DIR = utils/
UTILS_SRCS = vector.c vector_suite.c vector_op.c color.c ray.c camera.c scene.c \
			 transformations.c matrix.c matrix_op.c quaternion.c
UTILS_SRCS_PREFIXED = $(addprefix $(UTILS_DIR), $(UTILS_SRCS))

#parsing sources
PARSER_DIR = parsing/
PARSER_SRCS = parser.c file.c parser_utils.c parser_suite.c parser_suite_bonus.c object_creation.c edit.c
PARSER_SRCS_PREFIXED = $(addprefix $(PARSER_DIR), $(PARSER_SRCS))

#raytracing sources
RAYTRACING_DIR = raytracing/
RAYTRACING_SRCS = intersect.c light.c sphere.c plan.c cylinder.c triangle.c transformable_sphere.c
RAYTRACING_SRCS_PREFIXED = $(addprefix $(RAYTRACING_DIR), $(RAYTRACING_SRCS))

#config sources
CONFIG_DIR = config/
CONFIG_SRCS = key_hooks.c mouse_hooks.c screen.c select_mode.c camera.c
CONFIG_SRCS_PREFIXED = $(addprefix $(CONFIG_DIR), $(CONFIG_SRCS))

#multithreading sources
THREADING_DIR = multithreading/
THREADING_SRCS = loop.c
THREADING_SRCS_PREFIXED = $(addprefix $(THREADING_DIR), $(THREADING_SRCS))

#sources
SRCS_DIR = srcs/
SRCS = main.c errors.c app.c raytrace.c $(UTILS_SRCS_PREFIXED) $(PARSER_SRCS_PREFIXED) $(RAYTRACING_SRCS_PREFIXED) $(CONFIG_SRCS_PREFIXED)
SRCS_PREFIXED = $(addprefix $(SRCS_DIR), $(SRCS))

#bonus sources
BONUS_SRCS = main.c errors.c app.c raytrace_bonus.c $(UTILS_SRCS_PREFIXED) $(PARSER_SRCS_PREFIXED) $(RAYTRACING_SRCS_PREFIXED) $(CONFIG_SRCS_PREFIXED) $(THREADING_SRCS_PREFIXED)
BONUS_SRCS_PREFIXED = $(addprefix $(SRCS_DIR), $(BONUS_SRCS))

#includes
INCLUDES_FILES = minirt.h vector.h color.h raytrace.h parser.h window.h ray.h transformation.h
INCLUDES = $(INCLUDES_FILES:%=$(INCLUDES_DIR)/%)
#includes bonus
INCLUDES_FILES_BONUS = $(INCLUDES_FILES) multithread.h
INCLUDES_BONUS = $(INCLUDES_FILES:%=$(INCLUDES_DIR)/%)

#objsm
OBJS := $(SRCS_PREFIXED:%.c=$(OBJS_DIR)/%.o)
#objsm bonus
OBJS_BONUS := $(BONUS_SRCS_PREFIXED:%.c=$(OBJS_BONUS_DIR)/%.o)

all : $(NAME)

bonus: $(NAME)_bonus

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT_LIB) $(MLX_LIB_FILES)
	@echo "$(GREEN)finish building objects$(RESET_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) -lm -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $@
	@echo "$(GREEN)$(NAME) est construit$(RESET_COLOR)"

$(NAME)_bonus: $(OBJS_BONUS_DIR) $(OBJS_BONUS) $(LIBFT_LIB) $(MLX_LIB_FILES)
	@echo "$(GREEN)finish building objects$(RESET_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -lm -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)_bonus
	@echo "$(GREEN)$(NAME) bonus version est construit$(RESET_COLOR)"

#normal build
$(OBJS_DIR):
	@echo "$(GREEN)building object dir $(RESET_COLOR)"
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : %.c $(INCLUDES)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

#bonus build
$(OBJS_BONUS_DIR):
	@echo "$(GREEN)building bonus object dir $(RESET_COLOR)"
	@mkdir -p $(OBJS_BONUS_DIR)

$(OBJS_BONUS_DIR)/%.o : %.c $(INCLUDES_BONUS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -DIS_BONUS=1 -c $< -o $@

$(MLX_LIB_FILES):
	@echo "trying to build mlx"
	@$(MAKE) -C $(MLX_DIR)
	@cd $(MLX_DIR) && mv $@ ..

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)
clean :
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_BONUS_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(GREEN)cleaning objs$(RESET_COLOR)"

fclean : clean
	@rm -f ./$(NAME)
	@rm -f ./$(NAME)_bonus
	@echo "$(RED)clean$(RESET_COLOR)"

re : fclean all

test : clean all

help	:
	@echo "all $(NAME) clean fclean re"

.PHONY	: all clean fclean re help
