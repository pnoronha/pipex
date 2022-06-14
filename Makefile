# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 18:15:19 by pnoronha          #+#    #+#              #
#    Updated: 2022/06/14 22:36:43 by pnoronha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INC		=	-Iincludes -Ilibft/includes
LINK	=	-Llibft -lft

SRC_DIR	=	./sources
B_SRC_D	=	./bonus_sources
OBJ_DIR	=	./objects
B_OBJ_D	=	./bonus_objects

SRC		=	$(SRC_DIR)/main.c			\
			$(SRC_DIR)/pipex.c			\
			$(SRC_DIR)/parse.c			\
			$(SRC_DIR)/exit.c			\
			$(SRC_DIR)/files_parse.c

B_SRC	=	$(SRC_DIR)/main.c			\
			$(SRC_DIR)/pipex.c			\
			$(SRC_DIR)/parse.c			\
			$(SRC_DIR)/exit.c			\
			$(SRC_DIR)/files_parse.c

OBJ		:= $(patsubst %.c, %.o, $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC)))
B_OBJ	:= $(patsubst %.c, %.o, $(subst $(SRC_DIR), $(B_OBJ_D), $(B_SRC)))

all:		libft $(OBJ_DIR) $(B_OBJ_D) $(NAME)

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) $(^) $(LINK) -o $(@)
	@echo "\n\033[7;1;3;32m >> Pipex Compiled << \033[m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $(^) -o $(@)

bonus:	$(B_OBJ) | libft
	@$(CC) $(CFLAGS) $(^) $(LINK) -o pipex
	@echo "\n\033[7;1;3;32m >> Pipex Bonus Compiled << \033[m"

$(B_OBJ_D)/%.o:	$(B_SRC_D)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $(^) -o $(@)

$(OBJ_DIR):
	@mkdir -p objects

$(B_OBJ_D):
	@mkdir -p bonus_objects

norm:
	@norminette *sources/ includes/

test: re
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes \
	--num-callers=20 --track-fds=yes ./$(NAME) sources/main.c "grep a" "wc" out

libft:
	@make -C libft

clean:
	@rm -f $(OBJ) $(B_OBJ)
	@rm -rf $(OBJ_DIR) $(B_OBJ_D)

fclean:		clean
	@make fclean -C libft
	@rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re norm test libft $(OBJ_DIR)
