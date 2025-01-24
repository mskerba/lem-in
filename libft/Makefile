# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 08:39:44 by mskerba           #+#    #+#              #
#    Updated: 2021/11/24 16:52:23 by mskerba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c ft_strtok.c ft_isalpha.c ft_memchr.c  ft_memset.c  ft_strlcat.c ft_strnstr.c ft_bzero.c   ft_isascii.c ft_memcmp.c  ft_strchr.c  ft_strlcpy.c ft_strrchr.c ft_calloc.c  ft_isdigit.c ft_memcpy.c  ft_strdup.c  ft_strlen.c  ft_substr.c ft_isalnum.c ft_isprint.c ft_memmove.c ft_strncmp.c ft_strcmp.c ft_tolower.c ft_toupper.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c 

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

bonus:

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all