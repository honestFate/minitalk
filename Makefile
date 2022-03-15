CC = gcc
INC = .
INCLUDES = minitalk.h
CFLAGS = -Wall -Wextra -Werror

CLIENT_NAME = client
SERVER_NAME = server

SRCS_CLIENT = client.c utils.c
SRCS_SERVER = server.c utils.c

OBJS_CLIENT = $(SRCS_CLIENT:%.c=%.o)
OBJS_SERVER = $(SRCS_SERVER:%.c=%.o)

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(OBJS_CLIENT)
	$(CC) -o $(CLIENT_NAME) $(OBJS_CLIENT) $(CFLAGS) -I$(INC)

$(SERVER_NAME): $(OBJS_SERVER)
	$(CC) -o $(SERVER_NAME) $(OBJS_SERVER) $(CFLAGS) -I$(INC)

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	$(RM) $(CLIENT_NAME) $(SERVER_NAME)

re: clean all