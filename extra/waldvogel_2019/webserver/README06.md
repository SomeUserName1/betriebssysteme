# Projekt Webserver
**Abgabe: 7.1.2020 04:00**
Die Abgabe ist der letzte Commit vor der Abgabe der master branch.

## Überblick
Diese Woche implementieren wir Multithreading im Webserver und schreiben einen
File Cache.

Im folgenden finden Sie eine Übersicht über die Entwicklung des Webservers:

1. Webserver liefert statische Antworten und einfache Headerverarbeitung :heavy_check_mark:
2. Angefragte Dateien werden ausgeliefert und Ordnerstrukturen ausgegeben :heavy_check_mark:
3. Speicherbegrenzungen werden aufgehoben :heavy_check_mark:
4. **Mehrere Anfragen können parallel bearbeitet werden und Antworten werden zwischengespeichert**
5. Webserver soll im Hintergrund laufen und möglichst wenige Berechtigungen haben
6. Um bei Google ein gutes Ranking zu bekommen muss der Webserver via TLS erreichbar sein

## Cache
Ihr Webserver soll mehrere Anfragen mithilfe von Threads gleichzeitig bearbeiten
können. Es soll außerdem einen File Cache geben, so dass die letzten 10 Dateien
nicht neu vom Filesystem eingelesen werden müssen.

1. Der Server soll für jede Anfrage einen `pthread` ausführen. Ist die Anfrage
   bearbeitet soll der Thread dementsprechend aufgeräumt werden.
2. Der Server soll einen Filecache mit 10 Einträgen haben, den alle Threads
   gemeinsam nutzen.
3. Ist der Filecache voll und es wird eine neue Datei angefordert, soll der
   Eintrag auf den am längsten nicht zugegriffen wurde mit der neuen Datei
   ersetzt werden. (LRU-Cache)
4. Locks sollten nicht gehalten werden wenn I/O mit dem Filesystem wie `read()`
   oder `fread()` geschieht, oder wenn ein Paket gesendet wird (mit `send()` oder
   `write()`).

:warning: Wenn Sie die Datei neu einlesen, bauen Sie einen sleep mit 3 Sekunden
ein, um das Programm zuverlässig zu testen. Also vor jedem `read()` oder `fread()`
muss ein `sleep(3)` stehen. Wenn die Datei aus dem Cache geholt wird soll der
sleep nicht eintreten.

## Thread Limitierung
Eine unbegrenzte Anzahl an Threads lassen sich bei einem ausgelasteten Server
kaum verwalten, deshalb kann es sinnvoll sein die Anzahl Threads zu beschränken.
Mit dem Argument `-tl X` soll die Anzahl Threads auf X begrenzt werden.

## Threadpool
Threads zu erstellen und beenden kostet Zeit, deshalb werden häufig Threadpools
eingesetzt, statt für jede Verbindung einen neuen Thread zu erstellen.
Wird Ihr Server mit `-tp X` aufgerufen soll er bereits beim Start X Threads
erstellen, die dann die Anfragen bearbeiten. Ausser diesen X Threads sollen keine
weiteren Threads mehr erstellt werden.


Sie können davon ausgehen, dass der Server nur mit `-tp THREADZAHL PORT` oder
nur `PORT` aufgerufen wird. Um die Reihenfolge der Argumente brauchen Sie sich
also nicht zu kümmern.

Mögliche Aufrufe:
- `./server -tp 200 8080`
- `./server -tl 100`
- `./server 8080`

Um das Programm mit pthreads zu bauen, nutzen sie `-pthread` oder das bereitgestellte
Makefile.

### Tests
Ihren Server können Sie mit `telnet`, `curl` oder einem gewöhnlichen Webbrowser
testen. Zur Bewertung relevante Tests finden Sie in `test06.sh`
welches Sie auch mit `make test` aufrufen können.

Abgaben die nur darauf abzielen die Tests zu bestehen, können wir natürlich
nicht gelten lassen. Eure Abgabe sollte mindestens genau so viele alte Tests
bestehen wie eure vergangene Abgabe.


### Literatur
* [Advanced Linux Programming](https://richard.esplins.org/static/downloads/linux_book.pdf)
* The Linux Programming Interface: A Linux and UNIX System Programming Handbook
* [Linux-UNIX Programmierung](http://openbook.rheinwerk-verlag.de/linux_unix_programmierung)
* [C von A bis Z](http://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap10-000.htm)
* [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
