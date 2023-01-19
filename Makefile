# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 16:06:41 by eamghar           #+#    #+#              #
#    Updated: 2023/01/19 15:52:44 by eamghar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = pipex.h

NAME = pipex

NAME_B = pipex_bonus

SRC =	mandatory/ft_external_functions.c \
		mandatory/ft_spilt.c \
		mandatory/parcing.c \

SRC_B = bonus/ft_external_functions.c \
		bonus/ft_external_functions2.c \
		bonus/ft_spilt.c \
		bonus/parcing.c \

CC = cc

CFLAGS = -Wall -Werror -Wextra 

all : $(NAME)

bonus : $(NAME_B)

$(NAME) : $(SRC) $(HEADER)
	$(CC) $(SRC) $(CFLAGS) -o $(NAME)

$(NAME_B) : $(SRC_B) $(HEADER)
	$(CC) $(SRC_B) $(CFLAGS)-o $(NAME_B)

clean : 
		rm -rf $(NAME)
		rm -rf $(NAME_B)

fclean : clean

re : fclean all