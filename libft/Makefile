NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -c
ARCHIVE = ar -crs
SRCS = $(wildcard *.c)
  
OBJS = $(SRCS:.c=.o)

%.c:
	$(CC) $(CFLAGS) $(SRCS)

all: $(NAME)

$(NAME): $(OBJS)
	$(ARCHIVE) $(NAME) $(OBJS) 

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re