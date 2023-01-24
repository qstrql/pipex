# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 16:15:35 by mjouot            #+#    #+#              #
#    Updated: 2023/01/24 14:45:25 by mjouot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#=================================VARS=========================================#
NAME = pipex
NAME_BONUS = pipex_bonus

SRCS = mandatory/pipex.c \
	   mandatory/paths.c \
	   mandatory/utils.c

SRCS_BONUS = bonus/pipex_bonus.c \
			 bonus/utils_bonus.c \
			 bonus/paths_bonus.c
CC = clang
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
FLAGS = -Wall -Wextra -Werror -I ./libft/INCLUDES/ -ggdb3
#====================================COLORS====================================#
NOC            = \033[0m
BOLD        = \033[1m
UNDERLINE    = \033[4m
BLACK        = \033[1;30m
RED            = \033[1;31m
GREEN        = \033[1;32m
YELLOW        = \033[1;33m
BLUE        = \033[1;34m
VIOLET        = \033[1;35m
CYAN        = \033[1;36m
WHITE        = \033[1;37m

NORMAL        = \e[25
BLINK        = \e[5m
#================================PROGRESS BAR UTILS============================#
PERCENT = 0
NB_COMPIL = 0
TOTAL_COMPIL = $(words $(OBJS))
PROGRESS_BAR_DETAIL = 5
#=====================================RULES====================================#
all: $(NAME)

$(NAME): $(OBJS)
		@rm .progressbar
		make -C libft
		$(CC) $(FLAGS) $^ -o $(NAME) libft/libft.a

%.o: %.c
	$(if $(filter $(NB_COMPIL),0), @echo "$(BLUE)Compiling pipex$(NOC)")
	$(if $(filter $(NB_COMPIL),0), @echo "$(YELLOW)$(NB_COMPIL) 0%$(NOC)")
	$(if $(filter $(NB_COMPIL),0), @make create_progressbar) 
	$(eval NB_COMPIL=$(shell echo $$(($(NB_COMPIL)+1))))
	$(eval PERCENT=$(shell echo $$(($(NB_COMPIL) * 100 / $(TOTAL_COMPIL)))))
	@echo -ne '\e[1A\e[K'
	@./.progressbar $(PERCENT)
	$(if $(filter $(PERCENT),100), @echo "$(GREEN)$(PERCENT)%$(NOC)", @echo "$(YELLOW)$(PERCENT)%$(NOC)")
	$(CC) $(FLAGS) -c $< -o $@

create_progressbar:
	@echo '#!/bin/bash\n' > .progressbar
	@echo 'for i in {0..100..$(PROGRESS_BAR_DETAIL)}' >> .progressbar
	@echo 'do' >> .progressbar
	@echo '    if [ $$i -gt $$1 ]' >> .progressbar
	@echo '    then' >> .progressbar
	@echo '        echo -ne "$(RED)█$(NOC)"' >> .progressbar
	@echo '    else' >> .progressbar
	@echo '        echo -ne "$(GREEN)█$(NOC)"' >> .progressbar
	@echo '    fi' >> .progressbar
	@echo 'done' >> .progressbar
	@echo 'echo -n " "' >> .progressbar
	@chmod 777 .progressbar

bonus: $(OBJS_BONUS)
		@rm .progressbar
		make -C libft
		$(CC) $(FLAGS) $(OBJS_BONUS) -o $(NAME_BONUS) libft/libft.a

clean:
	make clean -C libft
	rm -f $(OBJS_BONUS)
	rm -f $(OBJS)

fclean: clean
	rm -f libft/libft.a
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

.SILENT: 
.PHONY: all clean fclean re create_progressbar
#=============================================================================#
