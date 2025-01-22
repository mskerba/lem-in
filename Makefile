CC		=	gcc
SRCS	=	src/lem_in.c src/room_ant_utils.c src/parse.c  libft/ft_atoi.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c 
OBJS	= $(SRCS:.c=.o)
FLAGS	= -Wall -Wextra -Werror
NAME	= lem-in

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all