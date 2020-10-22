ALL = fork-join rendezvous barrier reader-writer reader-writer-nostarve mutex-nostarve

all: $(ALL)

clean:
	rm -f $(ALL) *~

fork-join: fork-join.c
	gcc -o fork-join fork-join.c -Wall -pthread -O

rendezvous: rendezvous.c
	gcc -o rendezvous rendezvous.c -Wall -pthread -O

barrier:
	gcc -o barrier barrier.c -Wall -pthread -O

reader-writer:
	gcc -o reader-writer reader-writer.c -Wall -pthread -O

reader-writer-nostarve:
	gcc -o reader-writer-nostarve reader-writer-nostarve.c -Wall -pthread -O

mutex-nostarve:
	gcc -o mutex-nostarve mutex-nostarve.c -Wall -pthread -O
