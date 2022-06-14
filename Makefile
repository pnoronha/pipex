# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 18:15:19 by pnoronha          #+#    #+#              #
#    Updated: 2022/06/14 21:07:34 by pnoronha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INC		=	-Iincludes -Ilibft/includes
LINK	=	-Llibft -lft

SRC_DIR	=	./sources
OBJ_DIR	=	./objects

SRC		=	$(SRC_DIR)/main.c			\
			$(SRC_DIR)/pipex.c			\
			$(SRC_DIR)/parse.c			\
			$(SRC_DIR)/exit.c			\
			$(SRC_DIR)/files_parse.c

OBJ		:=	$(patsubst %.c, %.o, $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC)))

all:		libft $(OBJ_DIR) $(NAME)

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) $(^) $(LINK) -o $(@)
	@echo "\n\033[7;1;3;32m >> Pipex Compiled << \033[m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $(^) -o $(@)

$(OBJ_DIR):
	@mkdir -p objects

norm:
	@norminette $(SRC_DIR) includes/

test: re
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes \
	--num-callers=20 --track-fds=yes ./$(NAME) here_doc ai "grep fd" "wc -l" out

libft:
	@make -C libft

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean:		clean
	@make fclean -C libft
	@rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re norm test libft $(OBJ_DIR)
