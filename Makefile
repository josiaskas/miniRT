# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/14 18:37:04 by jkasongo          #+#    #+#              #
#    Updated: 2022/08/14 16:34:07 by jkasongo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES_DIR = ./includes
LIBFT_DIR = ./libft
MLX_DIR =./minilibx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGl -framework AppKit
OBJS_DIR = ./objs
DEBUGS_DIR = $(NAME).dSYM/


#styles for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET_COLOR = \033[0m

#utils sources
UTILS_DIR = utils/
UTILS_SRCS = vector.c point.c
UTILS_SRCS_PREFIXED = $(addprefix $(UTILS_DIR), $(UTILS_SRCS))

#sources
SRCS = main.c $(UTILS_SRCS_PREFIXED)

#includes
INCLUDES_FILES = minirt.h point.h
INCLUDES = $(INCLUDES_FILES:%=$(INCLUDES_DIR)/%)

#objsm
OBJS := $(SRCS:%.c=$(OBJS_DIR)/%.o)

all : $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@echo "$(GREEN)finish building objects$(RESET_COLOR)"
	@$(MAKE) re -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $@
	@echo "$(GREEN)$(NAME) est construit$(RESET_COLOR)"
$(OBJS_DIR):
	@echo "$(GREEN)building object dir $(RESET_COLOR)"
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : %.c $(INCLUDES)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

clean :
	@rm -rf $(OBJS_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(GREEN)cleaning objs$(RESET_COLOR)"

fclean : clean
	@rm -f ./$(NAME)
	@echo "$(RED)clean$(RESET_COLOR)"

re : fclean all

help	:
	@echo "all $(NAME) clean fclean re"

.PHONY	: all clean fclean re help