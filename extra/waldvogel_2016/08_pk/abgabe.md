# Lösungen zum 8\. Übungsblatt

# Bamberger, Jannik und Klopfer, Fabian

## Aufgabe 6: Advanced Makefile
```
/**
 * @author Jannik Bamberger
 * @author Fabian Klopfer
 * @credits 9
 * Erklärung $< falsch (-1)
 */
```

- 1 Definiert CFLAGS mit den Compiler-Flags die für alle impliziten Regeln verwendet werden
- 4 SRC wird mit allen .c Dateien aus dem Verzeichnis initialisiert. wildcard sorgt dafür, dass ``*.c`` zu den Dateinamen erweitert wird.
- 5 OBJ enthält die Namen der Object-Files zu den .c Dateien aus SRC. patsubst ersetzt alle Dateierweiterungen ``.c`` mit ``.o``.
- 7 .PHONY bedeutet, dass die genannten Targets kein Dateien erzeugen.
- 9 default Target all benötigt calc
- 10 clean löscht alle Object-Files
- 12 distclean setzt voraus, dass alle Object-Files gelöscht wurden und löscht dann das calc Executable
- 15 calc wird erstellt, indem gcc mit -o calc und den Objektdateien aufgerufen wird. ``$@`` ist der Targetname. Es wird vorausgesetzt, dass alle Object-Files aktuell sind.
- 18 Musterregel zum erstellen aller Objektdateien. Zu jeder Objektdatei wird die entsprechende .c Datei benötigt. $< wird zu allen Prerequisits erweitert, also zu mindestens der .c Datei und ggf. weiteren.
- 21-23 Deklariert Dependencies für manche Objektdateien.
