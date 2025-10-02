CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS =		ft_strlen.c		ft_strdup.c		\
			ft_strcmp.c		ft_split.c		\
			ft_substr.c 	ft_atoi.c		\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
