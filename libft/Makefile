# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjouot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 16:46:46 by mjouot            #+#    #+#              #
#    Updated: 2022/11/14 22:42:13 by mjouot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
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
	  SRCS/libft/ft_lstmap.c

SRCS_EXTRA = \
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
		SRCS/extra/ft_strcmp.c

CC = clang
OBJS = $(SRCS:.c=.o)
OBJS_EXTRA = $(SRCS_EXTRA:.c=.o)
FLAGS = -Wall -Wextra -Werror -I ./INCLUDES

ifdef VAR_EXTRA
	SRCS += $(SRCS_EXTRA)
endif

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

extra: $(OBJS)
	@make VAR_EXTRA=true

clean:
	rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_EXTRA)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

