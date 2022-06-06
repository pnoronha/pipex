# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 18:15:19 by pnoronha          #+#    #+#              #
#    Updated: 2022/06/06 22:23:06 by pnoronha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
INC			=	-Iincludes -Ilibft/includes
LINK		=	-Llibft -lft
RM			=	rm -f

SRC			=	main.c	\
				parse.c	\
				pipex.c

OBJ			:=	$(SRC:%.c=%.o)

all:		libft $(NAME) clean

$(NAME):	$(OBJ)
		@$(CC) $(CFLAGS) $(^) $(LINK) -o $(@)
		@echo "\n\033[7;1;3;32m >> Pipex Compiled <<\033[m"

%.o: %.c
		@$(CC) $(CFLAGS) $(INC) -c $(^) -o $(@)

norm:
		@norminette -R CheckForbiddenSourceHeader $(SRC)
		@norminette -R CheckDefine includes/*

test: re
		valgrind --tool=memcheck --leak-check=yes --show-reachable=yes \
		--num-callers=20 --track-fds=yes ./$(NAME) parse.c "/grep 2" "wc" out
libft:
		@make -C libft

clean:
		@$(RM) $(OBJ)

fclean:		clean
		@make fclean -C libft
		@$(RM) $(NAME)

re:			fclean all

cl:			all clean

.PHONY:	all clean fclean re norm test libft
