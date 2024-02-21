# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 12:00:51 by pviegas           #+#    #+#              #
#    Updated: 2024/02/21 10:23:02 by pviegas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color variables
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m
RESET 	= \033[0m

# Executable name
NAME 			= cub3D
NAME_BONUS		= cub3D_bonus

# Compiler options
CC 				= cc
FLAGS			= -Wall -Werror -Wextra -g3  #-fsanitize=address
MLXFLAGS		= -L ./minilibx -lm -lmlx -Ilmlx -lXext -lX11

# Paths
SRC_DIR			= ./src/
OBJ_DIR			= ./obj/

LIBFT 			= ./libft/libft.a
LIBFT_DIR 		= ./libft
MINILIBX_PATH	= ./minilibx

# Source and object files
SRCS = $(wildcard $(SRC_DIR)*.c)
OBJS = $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

${NAME}: $(OBJS)
	@$(MAKE) --no-print-directory -C $(MINILIBX_PATH)
	@echo "\n$(GREEN) [Success] Minilibix compiled.$(RESET)\n\n"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo "\n$(GREEN) [Success] Libft compiled.$(RESET)\n\n"
	$(CC) $(FLAGS) $(SRCS) $(MLXFLAGS) $(LIBFT) -o $(NAME)
	@echo "\n$(GREEN) [Success] ./$(NAME) created.$(RESET)\n\n"

bonus: $(NAME_BONUS)

${NAME_BONUS}: $(OBJS)
	@$(MAKE) --no-print-directory -C $(MINILIBX_PATH)
	@echo "\n$(GREEN) [Success] Minilibix compiled.$(RESET)\n\n"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo "\n$(GREEN) [Success] Libft compiled.$(RESET)\n\n"
	$(CC) $(FLAGS) $(SRCS) $(MLXFLAGS) $(LIBFT) -o $(NAME_BONUS)
	@echo "\n$(GREEN) [Success] ./$(NAME_BONUS) created.$(RESET)\n\n"

clean:
	@rm -rf $(OBJS)
	@echo "$(RED) [Deleting] .o files ... (deleted)$(RESET)"
	@cd $(LIBFT_DIR) && $(MAKE) --no-print-directory clean

fclean: clean
	@rm -rf $(NAME_BONUS)
	@rm -rf $(NAME) $(OBJS)
	@echo "$(RED) [Deleting] .a files ... (deleted)$(RESET)"
	@cd $(LIBFT_DIR) && $(MAKE) --no-print-directory fclean

v:
	clear && make re && valgrind --track-fds=yes --show-reachable=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3D maps/map_01.cub

p1:
	clear && make re && ./cub3D maps/map_01.cub

p2:
	clear && make re && ./cub3D maps/map_02.cub

norm:
	@clear
	@norminette $(SRC_DIR) $(LIBFT_DIR) ./include/ | grep -v "OK" || true
	
re: fclean all

.PHONY: all clean fclean re bonus fclean_bonus
