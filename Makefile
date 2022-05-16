NAME = minitalk

SERVER = server

CLIENT = client

LIST =	server.c	client.c

LIST_B =	server.c	client.c

OBJ = $(patsubst %.c,%.o,$(LIST))

OBJ_B = $(patsubst %.c,%.o,$(LIST_B))

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SERVER) $(CLIENT)

$(SERVER) : server.o
	gcc $(FLAGS) server.o -o $@

$(CLIENT) : client.o
	gcc $(FLAGS) client.c -o $@

bonus :
	@make OBJ="$(OBJ_B)" all

clean :
	@rm -f $(OBJ) $(OBJ_B)

fclean : clean
	@rm -f $(SERVER) $(CLIENT)

re : fclean all

.PHONY : all clean fclean re bonus
