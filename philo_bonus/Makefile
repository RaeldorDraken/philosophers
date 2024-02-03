# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/02 14:48:15 by eros-gir          #+#    #+#              #
#    Updated: 2023/01/02 11:26:30 by eros-gir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRC = ./src/philo_main_bonus.c ./src/philo_utils_bonus.c ./src/philo_print_bonus.c \
	  ./src/philo_process_bonus.c ./src/philo_init_bonus.c

HDR = ./incl/philolib_bonus.h

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
