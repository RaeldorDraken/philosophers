# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/02 14:48:15 by eros-gir          #+#    #+#              #
#    Updated: 2023/09/03 17:59:07 by eros-gir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = ./src/philo_main.c ./src/philo_utils.c ./src/philo_print.c \
	  ./src/philo_process.c ./src/philo_init.c

HDR = ./incl/philolib.h Makefile

OBJ = $(SRC:.c=.o)

GC = gcc
FLAGS = -g -Wall -Wextra -Werror

%.o: %.c $(HDR)
	$(GC) $(FLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ) $(HDR)
	$(GC) $(FLAGS) -o $(NAME) $(OBJ) -lpthread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
