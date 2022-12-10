# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjouot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 16:46:46 by mjouot            #+#    #+#              #
#    Updated: 2022/12/08 13:36:23 by mjouot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#=================================VARS=========================================#
NAME = libft.a

SRCS = \
    SRCS/libft/ft_atoi.c \
    SRCS/libft/ft_bzero.c \
    SRCS/libft/ft_calloc.c \
    SRCS/libft/ft_isalnum.c \
    SRCS/libft/ft_isalpha.c \
    SRCS/libft/ft_isascii.c \
    SRCS/libft/ft_isdigit.c \
    SRCS/libft/ft_isprint.c \
    SRCS/libft/ft_memchr.c \
    SRCS/libft/ft_memcmp.c \
    SRCS/libft/ft_memcpy.c \
    SRCS/libft/ft_memmove.c \
    SRCS/libft/ft_memset.c \
    SRCS/libft/ft_putchar_fd.c \
    SRCS/libft/ft_putendl_fd.c \
    SRCS/libft/ft_putnbr_fd.c \
    SRCS/libft/ft_putstr_fd.c \
    SRCS/libft/ft_strdup.c \
    SRCS/libft/ft_strlcat.c \
    SRCS/libft/ft_strnstr.c \
    SRCS/libft/ft_strlcpy.c \
    SRCS/libft/ft_strchr.c \
    SRCS/libft/ft_strrchr.c \
    SRCS/libft/ft_strlen.c \
    SRCS/libft/ft_strncmp.c \
    SRCS/libft/ft_substr.c \
    SRCS/libft/ft_strjoin.c \
    SRCS/libft/ft_strtrim.c \
    SRCS/libft/ft_strmapi.c \
    SRCS/libft/ft_striteri.c \
    SRCS/libft/ft_itoa.c \
    SRCS/libft/ft_split.c \
    SRCS/libft/ft_tolower.c \
    SRCS/libft/ft_toupper.c \
    SRCS/libft/ft_lstnew.c \
    SRCS/libft/ft_lstadd_front.c \
    SRCS/libft/ft_lstsize.c \
    SRCS/libft/ft_lstlast.c \
    SRCS/libft/ft_lstadd_back.c \
    SRCS/libft/ft_lstdelone.c \
    SRCS/libft/ft_lstclear.c \
    SRCS/libft/ft_lstiter.c \
    SRCS/libft/ft_lstmap.c \
	\
	SRCS/printf/ft_printf.c \
	SRCS/printf/ft_check_str.c \
	SRCS/printf/ft_printnbr.c \
	SRCS/printf/ft_printnbr_base.c \
	SRCS/printf/ft_utilities.c \
	\
	SRCS/extra/ft_super_strjoin.c \
	SRCS/extra/ft_strndup.c \
	SRCS/extra/ft_isprime.c \
	SRCS/extra/ft_printf_strs.c \
	SRCS/extra/ft_abs.c \
	SRCS/extra/ft_putnbr.c \
	SRCS/extra/ft_putstr.c \
	SRCS/extra/ft_putchar.c \
	SRCS/extra/ft_putendl.c \
	SRCS/extra/ft_get_next_line.c \
	SRCS/extra/ft_intlen.c \
	SRCS/extra/ft_ishexdigit.c \
	SRCS/extra/ft_printf_tab.c \
	SRCS/extra/ft_atof.c

CC = cc
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror -I ./INCLUDES

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
		ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(if $(filter $(NB_COMPIL),0), @echo "$(BLUE)Compiling libft$(NOC)")
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

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SILENT:
.PHONY: all clean fclean re create_progressbar
#==============================================================================#
