# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 16:06:41 by eamghar           #+#    #+#              #
#    Updated: 2023/01/18 18:21:50 by eamghar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = pipex.h

NAME = pipex

NAME_B = pipex_bonus

SRC =	mandatory/ft_external_functions.c \
		mandatory/ft_spilt.c \
		mandatory/parcing.c \

SRC_B = 

CC = cc

CFLAGS = -Wall -Werror -Wextra 

all : $(NAME)

bonus : $(NAME_B)

$(NAME) : $(SRC) $(HEADER)
	$(CC) $(SRC) -o $(NAME)

$(NAME_B) : $(SRC_B) $(HEADER)
	$(CC) $(SRC_B) -o $(NAME_B)

clean : 
		rm -rf $(NAME)
		rm -rf $(NAME_B)

fclean : clean

re : fclean all