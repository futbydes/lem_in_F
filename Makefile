# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vludan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 15:00:01 by vludan            #+#    #+#              #
#    Updated: 2018/10/17 18:25:34 by vludan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = lem_main.c lem_alg.c get_next_line.c
OBJ = $(SRC:.c=.o)
INCLUDES = lem.h
NAME = lem-in
CFLAGS = -Wall -Werror -Wextra
CC = gcc 
DIR = libft
DIR_PF = libft/ft_printf

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(DIR)
	make -C $(DIR_PF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L. $(DIR)/libft.a $(DIR_PF)/libftprintf.a

clean:
	make clean -C $(DIR)
	make clean -C $(DIR_PF)
	rm -f $(OBJ)

fclean:
	make fclean -C $(DIR)
	make fclean -C $(DIR_PF)
	rm -f $(NAME) $(OBJ)

re: fclean all
