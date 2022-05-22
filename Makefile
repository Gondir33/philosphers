# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbendu <sbendu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 11:16:24 by sbendu            #+#    #+#              #
#    Updated: 2022/05/21 18:15:50 by sbendu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -pthread

INCLD = ./

SRC = ./main.c\
		./lunch.c\
		./parsing.c\
		./phil_set.c\
		./utils.c\

OBJ = $(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ) 
	$(CC) $^ -o $@ $(CFLAGS) -o $(NAME)

%.o: %.c  philo.h $(SRC)
	$(CC) $(CFLAGS) -I $(INCLD) -c $< -o $(<:.c=.o)

clean:
	rm -rf $(OBJ) 

fclean: clean
	rm -rf $(NAME)

re: fclean  all

.PHONY : all clean fclean re