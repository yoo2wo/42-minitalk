CC = gcc
CFLAGS = -Wextra -Werror -Wall
CLIENT = client
SERVER = server
NAME = minitalk
SRCS_SERVER = server.c ft_putnbr.c
SRCS_CLIENT = client.c ft_atoi.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

all : $(NAME)

$(NAME) : $(CLIENT) $(SERVER)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

$(CLIENT) : $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLIENT)

$(SERVER) : $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJS_SERVER)

clean :
	rm -rf $(OBJS_CLIENT)
	rm -rf $(OBJS_SERVER)

fclean : clean
	rm -rf $(CLIENT)
	rm -rf $(SERVER)

re : fclean all

.PHONY : all clean fclean re
