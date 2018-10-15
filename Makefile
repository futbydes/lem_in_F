# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vludan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 15:00:01 by vludan            #+#    #+#              #
#    Updated: 2018/10/15 15:07:40 by vludan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = lem_main.c lem_alg.c get_next_line.c
OBJ = $(SRC:.c=.o)
INCLUDES = lem.h
NAME = lem-in
CFLAGS = -g -Wall -Werror -Wextra
CC = gcc 
DIR = libft

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L. $(DIR)/libft.a

clean:
	make clean -C $(DIR)
	rm -f $(OBJ)

fclean:
	make fclean -C $(DIR)
	rm -f $(NAME) $(OBJ)

re: fclean all
