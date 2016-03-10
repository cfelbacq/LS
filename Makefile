# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 11:59:46 by cfelbacq          #+#    #+#              #
#    Updated: 2016/03/10 12:04:33 by cfelbacq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SOURCE = main.c \
		 option.c \
		 print.c \
		 fill.c

OBJ = main.o \
	  option.o \
	  print.o \
	  fill.o

LIB = libft/libft.a

all : $(NAME)

$(NAME) :
	make re -C libft
	gcc -c -Wall -Werror -Wextra $(SOURCE)
	gcc -o $(NAME) $(OBJ) $(LIB)

clean :
	rm -rf $(OBJ)
	make clean -C libft

fclean : clean
	rm -rf $(NAME)
	make fclean -C libft

re : fclean all

.PHONY : all clean fclean re
