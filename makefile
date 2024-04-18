CC = gcc
CFLAGS = -Wall -g
LIBS = -lpthread

all: server client

server: server.c csapp.c
	$(CC) $(CFLAGS) -o server server.c csapp.c $(LIBS)

client: client.c csapp.c
	$(CC) $(CFLAGS) -o client client.c csapp.c $(LIBS)

clean:
	rm -f server client
rs:
	./server 8080
rc: 
	./client localhost 8080
