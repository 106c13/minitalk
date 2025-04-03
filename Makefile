CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_SERVER = ft_server/server.c
SRC_CLIENT = ft_client/client.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

NAME_SERVER = server
NAME_CLIENT = client

all: $(NAME_SERVER) $(NAME_CLIENT)


$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(OBJ_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(OBJ_CLIENT) -o $(NAME_CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_CLIENT)
	@rm -rf $(OBJ_SERVER)

fclean: clean
	@rm -f $(NAME_SERVER)
	@rm -f $(NAME_CLIENT)

re: fclean all


.PHONY:	all clean fclean re
