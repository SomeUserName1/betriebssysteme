# Webserver TLS

**Abgabe:** 4. Februar, 40:00 Uhr

## Überblick
Diese Woche erstellen wir ein TLS Zertifikat und implementieren TLS mithilfe der
[libtls] Bibliothek.

### libtls
libtls ist ein Teil des LibreSSL Projekts. Laden Sie sich den letzten libressl
Release (2.9.0) von der [Downloadseite][download] herunter und entpacken Sie
diese. Eine Anleitung zum Bauen von libressl finden Sie in `README.md`, die
wichtigsten Schritte sind: `./configure`, `make check`, `make install`. Der
letzte Befehl installiert die Bibliothek auf dem System. Um die Schreibrechte
dafür zu erlangen benutzen Sie `sudo`.

Um auch ohne Neustart die Bibliotheken des Systems neu zu laden benutzen Sie
`sudo /sbin/ldconfig -v`.

Sie können jetzt libtls nutzen indem Sie gcc den flag `-ltls` als letzten
Parameter mitgeben. Der dazugehörige header ist `<tls.h>`.

[libtls]: https://www.libressl.org
[download]: https://ftp.openbsd.org/pub/OpenBSD/LibreSSL/

### LetsEncrypt
Um unser Zertifikat zu generieren und signieren zu lassen, nutzen wir den gratis
Dienst [LetsEncrypt]. Um sicherzustellen, dass die angefragte Domain wirklich
Ihnen gehört, nutzt LetsEncrypt `certbot`. Es werden einige Challenges an den
HTTP Dienst der Domain geschickt, um diese nicht selbst umsetzen zu müssen
nutzen wir die standalone Version von certbot, die selbst einen Webserver dafür
mitbringt. Rufen Sie certbot auf und geben Sie als Domain die ihrer Cloud
Instanz an.

```
sudo certbot certonly
```

Sie sollten in der Ausgabe die Pfade Ihrer Zertifikate sehen.

[LetsEncrypt]: https://letsencrypt.org

### HTTPS
Um Ihren Webserver auch auf dem Server zu benutzen, müssen Sie den `getaddrinfo`
Aufruf verändern, da dieser bisher nur Verbindungen über localhost zulässt. Es
reicht hier als interface `NULL` zu übergeben. Außerdem sollten Sie die `Host`
HTTP-Header-Überprüfung anpassen.

HTTPS sollte auf Port 443 gebunden sein. Um in Linux auf Ports unter 1024 binden
zu können brauchen Sie root-Rechte (z.B. `sudo ./server`). Ihr Webserver muss
nicht mehr HTTP (Port 80) ausliefern.

Sie können sich mit der Dokumentation von libretls vertraut machen. Ein Snippet
finden Sie unter `httpssnippet.c` Die Manpages zu den libtls Funktionen sollten
jetzt auf Ihrem System verfügbar sein. Implementieren Sie nun TLS mit den
generierten Zertifikaten.

Alle Aufrufe sollten nach Fehlern im Rückgabewert überprüft werden. Funktionen
die einen Context übergeben bekommen, setzen dort genauere Fehlerhinweise, die
Sie mit `tls_error(ctx)` abrufen können.

Um sogennante [sslstrip] Attacken zu verhindern implementieren Sie in ihrem
Server [HTTP Strict Transport Security][HSTS]. Dies funktioniert mit einem HTTP
Header Field.

[sslstrip]: https://avicoder.me/2016/02/22/SSLstrip-for-newbies/
[HSTS]: https://www.owasp.org/index.php/HTTP_Strict_Transport_Security_Cheat_Sheet

### Tests
Zum Bestehen der Übung muss ihr Server bei [ssllabs] mindestens mit der Note C
und bei [securityheaders] mit mindestens der Note D bestehen. Da beide Services
bei zu vielen Anfragen weitere Tests sperren, sollten Sie zuerst wie gewohnt mit
`curl -v` testen.

[ssllabs]: https://www.ssllabs.com/ssltest/index.html
[securityheaders]: https://securityheaders.com
