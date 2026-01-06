.PHONY: compile clean

compile: networking.o server.o client.o
	@gcc -o server server.o networking.o
	@gcc -o client client.o networking.o

networking.o: networking.c networking.h
	@gcc -c networking.c

server.o: server.c networking.h
	@gcc -c server.c

client.o: client.c networking.h
	@gcc -c client.c

clean:
	@rm *.o client server
