NAME = minishell
CC = cc
CFLAGS = -c -Wall -Wextra# -Werror
READLINE = -lreadline -L readline-dghonyan/lib/
PREFIX = "${shell find /Users/${USER} -name readline-dghonyan 2>/dev/null}"
# READLINE = -lreadline
LIBFT = -lft -L libft
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

%.c:
	$(CC) $(CFLAGS) $(SRCS)

all: lib $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(READLINE) $(LIBFT) -o $(NAME) -g

lib:
	cd libft && make 

clean:
	rm -f ./*.o libft/*.o

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all

readline:
	rm -rf readline-dghonyan/*
	cd readline-master && make clean && ./configure --prefix=$(PREFIX)/ && make && make install

.PHONY: all clean fclean re lib readline
