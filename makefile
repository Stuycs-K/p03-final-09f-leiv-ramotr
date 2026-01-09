.PHONY: compile clean

compile: networking.o server.o client.o game.o
	@gcc -o server server.o networking.o
	@gcc -o client client.o networking.o game.o

networking.o: networking.c networking.h
	@gcc -c networking.c

server.o: server.c networking.h
	@gcc -c server.c

client.o: client.c networking.h
	@gcc -c client.c

game.o: game.c networking.h
	@gcc -c game.c

clean:
	@rm *.o client server
