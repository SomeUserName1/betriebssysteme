ALL = server client
COMMON = server.h client.h

all: $(ALL)

clean:
	rm -f $(ALL) *~

server: server.c $(COMMON)
	gcc -o server server.c -Wall -O

client: client.c $(COMMON)
	gcc -o client client.c -Wall -O
