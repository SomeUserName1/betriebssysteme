# 0. Übungsblatt

**Abgabe** 31. Oktober, während des Tutoriums

:warning: Für alle Abgaben gelten die Abgabevoraussetzungen aus dem [Repo Readme].

## Aufgabe 1: Ankommen & Einrichten
Generieren Sie einen SSH-Key und schicken Sie den öffentliche (z.B. id_rsa.pub) an die Tutoren.
Unter Windows können Sie hierzu PuTTY, und unter Linux und Mac `ssh-keygen` verwenden.
Sie erhalten dann Zugang zu ihrem Ubuntu Server, mit dem Sie sich mit `ssh` oder PuTTY jeweils verbinden können.
Nun können Sie entweder direkt Dateien über einen kommandozeilenbasierten Editor wie `nano` oder `vim` bearbeiten, oder diese zuerst lokal bearbeiten und dann mithilfe von `scp` auf den Server kopieren.
Probieren Sie das Hello World aus der Vorlesung zu schreiben, kompilieren und auszuführen.
Hierfür müssen Sie mit `sudo apt install` noch Pakete wie `gcc` installieren.
Um weitere SSH-Zugänge hinzuzufügen fügen Sie die öffentlichen Schlüssel zu `~/.ssh/authorized_keys` hinzu.

## Aufgabe 2: Manpages
Manpages sind Hilfe- und Dokumentationsseiten unter UNIX und verwandten Betriebssystemen,
z.B. Linux.

Lesen Sie die Manpage vom Kommando man, indem Sie das Kommando `man man` ausführen. Geben
Sie dabei Antworten auf folgende Fragen:

1. Wie kann man eine Manpage verlassen?
2. Wie kann man in einer Manpage nach Text suchen?
3. Aus welchen Abschnitten kann eine Manpage bestehen?
4. Was wird normalerweise im Abschnitt *SYNOPSIS* angegeben?
5. Wie sucht man nach Manpages, in den ein bestimmtes Schlüsselwort vorkommt?

## Aufgabe 3: Fork Repository
Forken Sie das [Repository lectures/systeme-3-2019][systeme-3-2019] über das Webinterface
von Gitlab, clonen Sie Ihren Fork via SSH (entweder auf Ihrem Server oder lokalen Rechner[^1]) und
fügen Sie das original-Repository als Upstream Remote hinzu. Welche Kommandos sind hierfür
notwendig und wie können Sie Upstream-Änderungen in Ihren Fork einspielen?
Checken Sie eine Textdatei (`members`) mit den Benutzernamen der Gruppenmitglieder ein und pushen Sie es in Ihren Fork.
Geben Sie in der Weboberfläche von Gitlab Klaus Herberth und Christian Loehle maximale Berechtigungen (master) und
stellen Sie die Sichtbarkeit ihres Forks auf privat.

**Hinweis:** Um pushen zu können, müssen Sie SSH nutzen. Dies bedeutet, dass Sie ihren Fork
mit der SSH-URL geklont haben (beginnt mit git@git.uni-konstanz.de), Sie im Besitz eines
privaten SSH-Schlüssels sind und den öffentlichen Teil in Gitlab hinterlegt haben. Eine Anleitung,
inklusive Key-Generierung unter Linux, finden Sie zum Beispiel in den [Gitlab Docs].

## Aufgabe 4: Common Commands
Benutzen Sie die entsprechenden Manpages und beschreiben
Sie kurz was die folgenden Kommandos machen:

* `cat`, `pwd`, `ls`, `cd`, `mv`, `rm`, `mkdir` `find`

Die Kommandos `pwd` und `cd` sind in der Shell eingebaut, die Beschreibung ist in der Manpage von `bash` zu finden.

**Bonus:** Warum sind diese in der Shell eingebaut?

## Aufgabe 5: Hello YOUR_NAME
Schreiben und kompilieren Sie ein C-Programm (in Ihrer virtuellen Maschine), dass Sie nach Ihrem Namen fragt und Sie dann persönlich begrüßt. Fügen Sie bitte den Quelltext in einer Datei namens `hello.c` Ihrer Abgabe hinzu. Nutzen Sie bitte die entsprechenden Flags für `gcc` die in der Vorlesung vorgestellt wurden und beachten Sie die Regeln zu Punktabzug bzw. Bonuspunkten.

`gcc -std=c99 -g -Wall -Wextra -Wpedantic -Wbad-function-cast -Wconversion -Wwrite-strings -Wstrict-prototypes hello.c`

[Repo Readme]: ../README.md
[systeme-3-2019]: https://git.uni-konstanz.de/disy/lectures/systeme-3-2019
[^1]: Wir empfehlen das Forken auf ein Linuxsystem.
