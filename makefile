all: http_server http_client 

http_server: http_server.c
	gcc -o http_server http_server.c

http_client: http_client.c
	gcc -o http_client http_client.c
