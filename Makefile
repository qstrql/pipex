# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 16:15:35 by mjouot            #+#    #+#              #
#    Updated: 2022/12/05 17:35:24 by mjouot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = mandatory/pipex.c \
	   mandatory/paths.c \
	   mandatory/utils.c

SRCS_BONUS = bonus/pipex_bonus.c \
			 bonus/utils_bonus.c \
			 bonus/paths_bonus.c

SRCS_BONUS =

CC = clang
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
FLAGS = -Wall -Wextra -Werror -I ./libft/INCLUDES/ -ggdb3

$(NAME): $(OBJS)
		make extra -C libft
		$(CC) $(FLAGS) $^ -o $(NAME) libft/libft.a

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

bonus: $(OBJS_BONUS)
		make extra -C libft
		$(CC) $(FLAGS) $(OBJS_BONUS) -o $(NAME) libft/libft.a

clean:
	make clean -C libft
	rm -f $(OBJS_BONUS)
	rm -f $(OBJS)

fclean: clean
	rm -f libft/libft.a
	rm -f $(NAME)

re: fclean all

.SILENT: 
.PHONY: all clean fclean re
