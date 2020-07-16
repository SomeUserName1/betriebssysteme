# Lösungen zum 13\. Übungsblatt

```
/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 12
 */
 ```

## Aufgabe 2: Korrektur
Die Aufgabenstellung war vermutlich die gleiche wie Aufgabe 3 Auf Assignment 4. Es sollte also ein Histogram der Wortlängen angefertigt werden:

*Es sei ein Text auf der Standardeingabe gegeben. Schreiben Sie ein Programm namens word-histo.c,
welches ein Histogramm der Längen der eingegebenen Wörter berechnet. Für alle Wörter der Länge
< 16 soll die Häufigkeit ihres Auftretens absolut, in Prozent und “grafisch” ausgegeben werden,
ebenso wie die Anzahl der längeren Wörter und die Gesamtzahl.*


# 0 Punkte, da _** keine Namen darauf stehen**_.   
Und die Abgabe nicht kompiliert, nicht kommentiert ist und selbst wenn die offensichtlichen Fehler behoben werden, d.h. das fehlende Semikolon und die zwei Stellen an denen über die Arraygrenzen hinweg geschrieben/gelesen wird bekommt man eine Ausgabe. Bei dieser stimmt aber nur der Prozentwert und die gesamte Wortanzahl. Mit der Ausgabe kann ein Benutzer nichts anfangen, da jegliche beschreibung fehlt und die Werte direkt hintereinander geschrieben sind, so dass sie nicht eindeutig getrennt werden können. Das Histogramm fehlt komplett, da ein float zwischen 0 und 1 zu einem int gecastet wird, also immer außer bei 1 nichts ausgegeben wird.

## Aufgabe 3: Fragen über Fragen
|Seite	|Antwort	|
|---	|---		|
|49		|36 Bytes	|
|94		|Damit konstante Strings kopiert werden können, z.B. String literale oder Pointer auf solche				|
|130	|f ist ein Pointer auf eine Funktion ohne Parameter, die einen Pointer auf ein Array mit 2 ints zurückgibt.	|
|154	|``kr_free`` wird mit der Startadresse des Speicherblocks aufgerufen. Vor jedem Block steht aber der Header (in diesem Fall an ``p``). ``p+1`` ist dann genau die Adresse, die ``kr_free`` benötigt.		|
