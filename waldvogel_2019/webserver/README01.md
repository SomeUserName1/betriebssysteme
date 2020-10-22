# Projekt Webserver
In den nächsten Übungen werden wir einen Webserver schreiben der
möglichst konform mit den Spezifikationen von RFC 7230-7237 sein soll.

**Abgabe:**
Die Abgabe ist der letzte Commit vor der Abgabe der main branch.
(Sollten Sie bereits vorarbeiten wollen, oder den Webserver anders erweitern,
arbeiten Sie bitte in einer seperaten branch und mergen diese ggf. nach dem
Abgabetermin. Abgabetermin ist der **12. November um 4.00 Uhr**.

## Überblick
In dieser Übung geht es um das Grundgerüst inklusive Fehlerbehandlung und einer
einfachen Ausgabe.
Die übergebenen Parameter sollen ausgelesen und zur Verarbeitung präpariert werden.

## Teil 1 Einfache Anfragen
In `server.c` ist ein Skelett für einen Webserver. Bis jetzt nimmt das Programm eine
Portnummer als Kommandozeilenparameter, benutzt 8080 als Default und erstellt
einen Listening Socket auf diesem. Danach akzeptiert es nacheinander Clients in
einer Endlosschleife. Diese sollen mit folgenden Funktionen bedient werden:

1. Bei einem `GET /` oder `GET /index.html` soll der Server diesen positiv
   mit einem `Hello World!` beantworten. Wer möchte darf diese Nachricht auch
   schon mit HTML verschönern.
2. Für `GET /index.php` soll er signalisieren, dass diese Datei dauerhaft auf `/index.html`
   umgezogen ist.
3. GET Anfragen für andere Dateien soll der Server mit einem `Not Found` beantworten.
4. Davon abweichende Anfragen soll der Server entsprechend der Spezifikation beantworten.
   Vorallem unbekannte Methoden und korrupte Anfragen.
5. Der Server soll nur auf Anfragen für den Host `localhost` reagieren bzw.
   andere entsprechend mit einem Fehler ablehnen.
6. Der Server soll die aktuelle Uhrzeit der Antwort sowie Informationen über die
   Server Software (eure :wink:) im Header seiner Antwort mitschicken.
**Hinweis: Informieren Sie sich über `time()` und `localtime()`**

**Nutzen Sie Funktionen wie `strstr`, `strcmp`, `strtok`, `sscanf` und `sprintf`.**

Sie können annehmen, dass die Anfrage und die Antwort nicht größer als 4095
Zeichen lang sind.
Ändern Sie bitte alles an `server.c` (und benutzen Sie nach Wunsch weitere
C-Dateien) nach Ihrem Belieben. Benennen Sie auch gern die Datei um wenn Sie
möchten. Passen Sie in beiden Fällen das Makefile entsprechend an. Wichtig ist
lediglich die Funktion des Webservers, bei der Struktur des Codes sind Sie frei.
Ihre gcc Flags müssen Sie noch um folgenden Zusatz erweitern:
`-D_POSIX_C_SOURCE=200112L`.

## Teil 2 Header
Ihr Server soll auch die Header Felder auslesen. Sie können annehmen, dass
nicht mehr als 30 Felder gegeben sind. Ein Header-Feld besteht aus einem
Schlüssel und einem Wert. Unsere Annahme: Ein Header Schlüssel ist dabei nicht
länger als 31 Zeichen, ein Wert nicht länger als 255 Zeichen.
Lesen Sie die Header Felder als `char[]` ein.

1. Bei einem `GET /keys` soll der Server alle Header-Schlüssel ausgeben.
   Jeweils auf einer eigenen Zeile.
1. Bei einem `GET /values` soll der Server alle Header-Werte ausgeben.
   Jeweils auf einer eigenen Zeile.
2. Bei einer Anfrage der Form  `GET /header/fieldkey` soll der Server positiv
   mit dem Header-Wert von `fieldkey` antworten, falls dieser in der Request
   gegeben war und Not Found, falls dieser nicht gegeben war.

**Wie ist laut RFC Groß- und Kleinschreibung der Header-Schlüssel zu beachten?**


### Tests
Ihren Server können Sie mit `telnet`, `curl` oder einem gewöhnlichen Webbrowser testen. Zur
Bewertung relevante Tests finden Sie in `test01.sh` welches Sie auch mit `make test`
aufrufen können. Beachten Sie, dass dieser Test die Uhrzeit nicht automatisch testet.

### Hinweise
**Nummer 1**
Beachten Sie, dass Linux Ports unter 1024 für Prozesse mit root Rechten vorbehält, nutzen
Sie also höhere Ports.

**Nummer 2**
Einen HTTP Server zu schreiben ist ein beliebtes Hobby-Projekt, deshalb findet sich auch
einiges an Ressourcen dazu, im Zweifel stimmt aber nur die offizielle RFC (7230-7237) der
[IETF](https://tools.ietf.org/html/rfc7230)

**Nummer 3**
Für detaillierte Informationen zur Netzwerkprogrammierung wird für C oft auf
[Beej's Guide](https://beej.us/guide/bgnet/) verwiesen. Für dieses Projekt ist dies aber
eher für Interessierte relevant. In der Literatur zur Linux und Unix Programmierung
sollten Sie ebenfalls fündig werden.
