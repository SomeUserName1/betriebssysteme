# Answers

1.  ###### First, write a simple server that can accept and serve TCP connecions. You’ll have to poke around the Internet a bit if you don’t already know how to do this. Build this to serve exactly one request at a time; have each request be very simple, e.g., to get the current time of day.

    -  Siehe: `1/server.c`, `1/server.h`, `1/client.c` sowie `1/client.h`.

2.  ###### Now, add the `select()` interface. Build a main program that can accept multiple connections, and an event loop that checks which file descriptors have data on them, and then read and process those requests. Make sure to carefully test that you are using `select()` correctly.

    -  Siehe: `2/server.c`, `2/server.h`, `2/client.c` sowie `2/client.h`.

3.  ###### Next, let’s make the requests a little more interesting, to mimic a simple web or file server. Each request should be to read the contents of a file (named in the request), and the server should respond by reading the file into a buffer, and then returning the contents to the client. Use the standard `open()`, `read()`, `close()` system calls to implement this feature. Be a little careful here: if you leave this running for a long time, someone may figure out how to use it to read all the files on your computer!

    -  Siehe: `3/server.c`, `3/server.h`, `3/client.c` sowie `3/client.h`.

4.  ###### Now, instead of using standard I/O system calls, use the asynchronous I/O interfaces as described in the chapter.

    -  Siehe: `4/server.c`, `4/server.h`, `4/client.c` sowie `4/client.h`.

    ###### How hard was it to incorporate asynchronous interfaces into your program?

    -  Es war erstaunlich einfach, die asynchronen System-Calls in das Programm
       einzubauen.

5.  ###### For fun, add some signal handling to your code. One common use of signals is to poke a server to reload some kind of configuration file, or take some other kind of administrative action. Perhaps one natural way to play around with this is to add a user-level file cache to your server, which stores recently accessed files. Implement a signal handler that clears the cache when the signal is sent to the server process.

    -  Siehe: `5/server.c`, `5/server.h`, `5/client.c`,`5/client.h` sowie
       `5/file_cache.h`.

6.  ###### Finally, we have the hard part: how can you tell if the effort to build an asynchronous, event-based approach are worth it?

    -  Das Programm verschwendet keine Zeit mehr mit warten (z.B. auf
       Ressourcen) und kann daher in der Zwischenzeit andere Aufgaben
       erledigen. Hierdurch wird die Performance eines Programm beschleunigt.
       Gerade in graphischen Benutzeroberflächen ist dies von Vorteil, da
       anderenfalls die GUI solange hängt, bis ein blockierender Funktionsaufruf
       abgeschlossen wurde.

    -  Im Gegensatz zu einer Thread basierten Variante, kann durch den
       Event-basierten Ansatz komplett auf Synchronisierungsmechanismen
       (z.B. Locks) verzichtet werden, wodurch sich die Komplexität eines
       Programms verringert. Hierdurch werden auch die Probleme der nebenläufigen
       Programmierung (wie z.B. Deadlocks) vermieden.

    -  **Fazit:** Immer wenn parallel zum Warten auf Ressourcen,
       andere Tätigkeiten ausgeführt werden können, lohnt sich der Verzicht auf
       blockierende Funktionsaufrufe, welche durch nicht blockierende
       (asynchrone) Funktionsaufrufe ersetzt werden.

    ###### Can you create an experiment to show the benefits?

    -  Code siehe `6/server.h`.

       Immer wenn `aio_read()` oder `aio_write()` aufgerufen wird, werden
       solange Primzahlen berechnet, bis `aio_read()` bzw. `aio_write()`
       abgeschlossen sind. Dadurch werden während der Wartezeit keine CPU-Zyklen
       verschwendet, sondern mit der Berechnung von Primzahlen verbracht.

    ###### How much implementation complexity did your approach add?

    -  Das Programm wurde nicht sehr viel komplexer, da lediglich eine Funktion
       zur Berechnung von Primzahlen benötigt wurde, sowie eine Funktion um dem
       Client die Primzahlen zu senden.
