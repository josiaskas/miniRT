# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/14 18:37:04 by jkasongo          #+#    #+#              #
#    Updated: 2022/08/28 12:19:07 by jkasongo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES_DIR = ./includes
OBJS_DIR = ./objs
#libft
LIBFT_DIR = ./libft
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
UTILS_SRCS = vector.c vector_suite.c point.c
UTILS_SRCS_PREFIXED = $(addprefix $(UTILS_DIR), $(UTILS_SRCS))

#sources
SRCS_DIR = srcs/
SRCS = main.c errors.c app.c raytrace.c parse.c $(UTILS_SRCS_PREFIXED)
SRCS_PREFIXED = $(addprefix $(SRCS_DIR), $(SRCS))

#includes
INCLUDES_FILES = minirt.h vector.h point.h raytrace.h
INCLUDES = $(INCLUDES_FILES:%=$(INCLUDES_DIR)/%)

#objsm
OBJS := $(SRCS_PREFIXED:%.c=$(OBJS_DIR)/%.o)

all : $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS) $(MLX_LIB_FILES)
	@echo "$(GREEN)finish building objects$(RESET_COLOR)"
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) -lm -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $@
	@echo "$(GREEN)$(NAME) est construit$(RESET_COLOR)"
$(OBJS_DIR):
	@echo "$(GREEN)building object dir $(RESET_COLOR)"
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : %.c $(INCLUDES)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

$(MLX_LIB_FILES):
	@$(MAKE) -C $(MLX_DIR)
	@cd $(MLX_DIR) && mv $@ ..

clean :
	@rm -rf $(OBJS_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(GREEN)cleaning objs$(RESET_COLOR)"

fclean : clean
	@$(MAKE) clean -C $(MLX_DIR)
	@rm -rf $(MLX_LIB_FILES)
	@rm -f ./$(NAME)
	@echo "$(RED)clean$(RESET_COLOR)"

re : fclean all

help	:
	@echo "all $(NAME) clean fclean re"

.PHONY	: all clean fclean re help