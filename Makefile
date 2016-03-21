# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 11:59:46 by cfelbacq          #+#    #+#              #
#    Updated: 2016/03/21 16:54:54 by cfelbacq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SOURCE = SRC/main.c \
		 SRC/option.c \
		 SRC/print.c \
		 SRC/fill.c \
		 SRC/fill2.c \
		 SRC/fill_data2.c \
		 SRC/ar.c \
		 SRC/free.c \
		 SRC/init.c \
		 SRC/ins.c \
		 SRC/check.c \
		 SRC/print2.c \
		 SRC/total.c \
		 SRC/dir.c

OBJ = main.o \
	  option.o \
	  print.o \
	  fill.o \
	  fill2.o \
	  fill_data2.o \
	  ar.o \
	  free.o \
	  init.o \
	  ins.o \
	  check.o \
	  print2.o \
	  total.o \
	  dir.o

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
