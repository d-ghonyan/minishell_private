NAME = minishell
CC = cc
CFLAGS = -c -Wall -Wextra -g -ggdb3 -D LINUX # -Werror
# READLINE = -lreadline -L readline-dghonyan/lib/
READLINE = -lreadline
PREFIX = "${shell find ${HOME} -name readline-dghonyan 2>/dev/null}"
LIBFT = -lft -L libft
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

%.c:
	$(CC) $(CFLAGS) $(SRCS)

all: lib $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(READLINE) $(LIBFT) -o $(NAME)

lib:
	cd libft && make 

clean:
	rm -f ./*.o libft/*.o

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all

readline:
# rm -rf readline-dghonyan/*
	cd readline-master && ./configure --prefix=$(PREFIX)/ && make clean && make && make install

.PHONY: all clean fclean re lib readline
