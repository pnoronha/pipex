# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 18:15:19 by pnoronha          #+#    #+#              #
#    Updated: 2022/05/05 16:46:31 by pnoronha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
INC			=	-Iincludes -Ilibft/includes
LINK		=	-Llibft -lft
RM			=	rm -f

SRC			=	main.c	\
				parse.c

OBJ			:=	$(SRC:%.c=%.o)

all:		libft $(NAME)

$(NAME):	$(OBJ)
		@$(CC) $(CFLAGS) $^ $(LINK) -o $@

%.o: %.c
		@$(CC) $(CFLAGS) $(INC) -c $^ -o $@

norm:
		@norminette -R CheckForbiddenSourceHeader $(SRC)
		@norminette -R CheckDefine includes/*

test:
		valgrind --tool=memcheck --leak-check=yes --show-reachable=yes \
		--num-callers=20 --track-fds=yes ./$(NAME)

libft:
		@make -C libft

clean:
		@make clean -C libft
		@$(RM) $(OBJ)

fclean:		clean
		@make fclean -C libft
		@$(RM) $(NAME)

re:			fclean all

.PHONY : 	all clean fclean re norm test libft
