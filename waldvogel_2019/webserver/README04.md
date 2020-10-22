# Projekt Webserver - Woche 4

**Abgabe: 10.12.19 04:00**
Die Abgabe ist der letzte Commit vor der Abgabe der master branch.

## Überblick
Diese Woche entfernen wir die Limitierungen des Webservers indem wir dynamischen
Speicher nutzen, anstatt der bisherigen konstanten Puffer. Das bedeutet es können
belieb lange Anfragen empfangen und Antworten jeglicher Länge gesendet werden.

Im folgenden finden Sie eine Übersicht über die Entwicklung des Webservers:

1. Webserver liefert statische Antworten und einfache Headerverarbeitung :heavy_check_mark:
2. Angefragte Dateien werden ausgeliefert und Ordnerstrukturen ausgegeben :heavy_check_mark:
3. **Speicherbegrenzungen werden aufgehoben**
4. Mehrere Anfragen können parallel bearbeitet werden und Antworten werden zwischengespeichert
5. Webserver soll im Hintergrund laufen und möglichst wenige Berechtigungen haben
6. Um bei Google ein gutes Ranking zu bekommen muss der Webserver via TLS erreichbar sein

## Aufgaben

### Linked List
Um Daten, wie die Anfrage- und Antworteheader, dynamisch zu speichern bietet sich
eine verlinkte Liste an. Hierzu haben wir schon ein Gerüst und entsprechende Tests
bereitgestellt. Implementieren Sie diese in `stringlist.c` nach den Anforderungen 
von `stringlist.h`. Es sollen alle Tests in `test_stringlist.c` bestanden werden, 
ohne Fehler oder Warnungen von `valgrind`. (Ignorieren Sie eventuelle Ausgaben 
durch getaddrinfo.)

Um die Unittests in `test_stringlist.c` zu kompilieren, nutzen Sie `make unittest` 
und rufen `./test` auf. Da wir zwei verschiedene Programme durch die gleiche Makefile 
erstellen, passen Sie die Makefile ggf. an, falls Sie `.c` Dateien hinzufügen.

### Anfragen einlesen und verarbeiten
Anfragen sollen dynamisch eingelesen werden und eine beliebige Anzahl von Headern
in beliebiger Länge verarbeitet werden. Hierzu können Sie beispielsweise ihre
oben erstellte Linked List verwenden.

### Antworten erstellen
Anstatt Antworten zu bauen indem wir line-by-line in einen großen allozierten
Speicher schreiben, können wir die oben erstellte Linked List verwenden um die
Antwort dynamisch wachsen zu lassen.

## Hinweise

### Valgrind
Valgrind hilft memory leaks und andere Speicherfehler zu finden. Die Anwendung ist
simpel und gut dokumentiert im [Valgrind Quick Start Guide](http://valgrind.org/docs/manual/quick-start.html),
wobei die Interpretation der Resultate Übung erfordert. Bei Fragen melden Sie sich
bitte bis zum nächsten Übungstermin.

### Beautify
Um ihren Code schön zu formatieren können Sie das Tool [Uncrustify](http://uncrustify.sourceforge.net/)
verwenden. Dies erhöht die Lesbarkeit und hilft Ihnen Fehler einfacher zu erkennen.
Nachdem Sie das Program mit `sudo apt install uncrustify` installiert haben, können
Sie ihren Code mit `make beautify` verschönern.

