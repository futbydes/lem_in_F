# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vludan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 15:00:01 by vludan            #+#    #+#              #
#    Updated: 2017/12/20 16:13:05 by vludan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c ft_pfflags.c ft_sizemod.c ft_typemod.c ft_ib_u.c ft_ib_s.c \
	  ft_digitconv.c ft_optfunct.c ft_unicon.c ft_format_str.c ft_atoi.c \
	  ft_memalloc.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strcpy.c \
	  ft_strlen.c ft_strncpy.c
OBJ = $(SRC:.c=.o)
INCLUDES = ft_printf.h
NAME = libftprintf.a
CFLAGS = -Wall -Werror -Wextra
CC = gcc

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re: fclean all
