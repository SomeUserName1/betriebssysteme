# Projekt Webserver


**Abgabe:**
Die Abgabe ist der letzte Commit vor der Abgabe der main branch.
(Sollten Sie bereits vorarbeiten wollen, oder den Webserver anders erweitern,
arbeiten Sie bitte in einer seperaten branch und mergen diese ggf. nach dem
Abgabetermin.

**Abgabetermin:** 26. November 2019 um 4 Uhr

## Überblick
Diese Woche erweitern wir den Webserver um den Umgang mit dem Dateisystem.


## Dateiverzeichnis
Ihr Webserver soll das Verzeichnis `/tmp/www` als Wurzelverzeichnis nutzen und
vom Browser aus zugänglich machen. Es gilt also `GET /foo/bar` greift auf
`/tmp/www/foo/bar` zu.

1. Wird ein GET auf ein Verzeichnis unter `/tmp/www/` angefordert, soll wenn
   eine `index.html` Datei vorhanden ist, diese ausgegeben werden. Wird keine
   entsprechende Datei gefunden, soll eine Seite mit HTML-Links ausgeben werden,
   die jede Datei bzw. Ordner in diesem Verzeichnis enthält und das Öffnen bzw.
   Navigieren durch das Verzeichnis erlaubt.
2. Wird ein GET auf eine Datei unter `/tmp/www/` oder einem Unterverzeichnis, soll
   diese zurückgegeben werden.
3. Gibt es keine dementsprechende Datei soll der Webserver dies mitteilen.
5. Ihr Server soll auch mit relativen Pfaden umgehen können.
6. Keine Datei außerhalb von `/tmp/www/` soll ausgegeben werden können.
   (Das dies nicht ganz trivial ist, sieht man daran, dass es eine oft vorkommende
   Sicherheitslücke ist, sie nennt sich Directory oder Path Traversal).
7. Der Webserver soll zumindest die Header Felder über den Content-Typen
   (`text/html`, `image/jpeg` bzw. `application/octet-stream`), das letzte
   Änderungsdatum und die Content-Länge zurückgeben. (Zusätzlich zu den
   bisherigen Date und Server Feldern)
8. Schickt man gängigen Browsern ein Änderungsdatum mit, werden sie bei der
   nächsten Anfrage für die selbe Datei dieses als `If-Modified-Since` header
   field hinzufügen, um zu verhindern, dass diese doppelt übertragen wird. Die
   Datei wird somit im Browser gecached. Überprüfen Sie demententsprechend beim
   Empfang dieses Änderungsdatum das tatsächliche Änderungsdatum und wenn es
   keine Neuerungen gibt, sollte dies dem Browser mitgeteilt werden, ohne dass
   die Datei neu übertragen wird.

### Tests
Ihren Server können Sie mit `telnet`, `curl` oder einem gewöhnlichen Webbrowser
testen. Zur Bewertung relevante Tests finden Sie in `test2.sh`
welches Sie auch mit `make test` aufrufen können. Beachten Sie, dass dieser Test
die Links im Directory Listing nicht überprüft.
