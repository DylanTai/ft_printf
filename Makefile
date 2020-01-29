# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtai <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/16 11:09:52 by dtai              #+#    #+#              #
#    Updated: 2020/01/27 22:43:58 by dtai             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
INCS = includes/
SRCS = \
srcs/ft_printf.c \
srcs/read_arg.c \
srcs/add_w_p.c \
srcs/ft_putchar.c \
srcs/ft_putpoi.c \
srcs/ft_putstr.c \
srcs/ft_putnbr.c \
srcs/ft_putoct.c \
srcs/ft_putuint.c \
srcs/ft_puthex.c \
srcs/ft_putflo.c \
srcs/ft_putbin.c \
srcs/ft_putiso.c \
srcs/ft_putiso_set.c
OBJ = \
ft_printf.o \
read_arg.o \
add_w_p.o \
ft_putchar.o \
ft_putpoi.o \
ft_putstr.o \
ft_putnbr.o \
ft_putoct.o \
ft_putuint.o \
ft_puthex.o \
ft_putflo.o \
ft_putbin.o \
ft_putiso.o \
ft_putiso_set.o

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

$(OBJ):
	@gcc $(FLAGS) -c $(SRCS) -I $(INCS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
