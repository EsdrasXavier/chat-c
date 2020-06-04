all: client server

client:	client.c 
	gcc -o client client.c -I.

server: server.c
	gcc -o server server.c server_log.c -I.

clean:
	rm -rf *.o *~ client