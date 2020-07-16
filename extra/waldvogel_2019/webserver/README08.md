# Projekt Webserver
**Abgabe: 21.1.2020 04:00**
Die Abgabe ist der letzte Commit vor der Abgabe der master branch.

## Überblick
Diese Woche integrieren wir den Webserver in das System und sichern ihn ab.

# System
## Benutzer und Dateien
Der Webserver soll statt `/tmp/www/`, welches bei jedem Neustart gelöscht wird nun
`/var/www/` benutzen. Zusätzlich soll der Webserver im Betrieb als Nutzer `www-data`
und gleichnamiger Gruppe arbeiten.
Legen Sie diese Benutzer und Dateistruktur an mit entsprechenden Berechtigungen.

## Systemd
Erstellen Sie einen Systemd-service für den Webserver, so dass dieser bei Neustart
als Daemon gestartet wird.
Dafür erstellen Sie eine entsprechende sogenannte Unit-Datei unter
`/etc/systemd/system`.
Als Anleitung können Sie das Administrationshandbuch von [Redhat](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/system_administrators_guide/sect-managing_services_with_systemd-unit_files) zur Hilfe nehmen.
Für eine Erklärung der Optionen gibt es die manpage `systemd.unit`.
Beim Debugging hilft Ihnen der Befehl `systemctl status servicename`.
Braucht ihr Webserver eine Routine für `systemctl stop servicename`, warum bzw.
warum nicht?
Für die jeweilige Option erläutern Sie bitte in einem Kommentar (mit #), warum
Sie dies für die richtige Lösung halten.
Wo liegt der Webserver und welche Berechtigungen hat er? (`ls -l` Ausgabe)
Geben Sie die Unit-Datei mit ab.
(Punkte: 2 Test = 50%)

# Sicherheit
## Privilegien
Das Binden auf Ports unter 1024 braucht Root-Privilegien, danach können diese
allerdings gedroppt werden.
Der Webserver soll also, falls er als root gestartet wird, die Privilegien zu
`www-data` ändern.
Nutzen Sie hierfür `getuid`, `setgid` und `setuid`.
**Hinweis: **Achten Sie auf die Reihenfolge der Befehle!

## Absichern
Damit der Webserver auch wirklich stabil läuft, muss er mit fehlerhaften Anfragen
umgehen können. Wie und ob er diese beantwortet ist nebensächlich, entscheidend
ist, dass er nicht abstürzt und Ressourcen wieder freigibt, auch wenn Anfragen
nicht vollständig beantwortet wurden.
Ihr Webserver soll, wenn 5 Sekunden nach öffnen der Verbindung die Anfrage noch
nicht fertig übermittelt wurde, den Thread beenden (ob mit Antwort oder ohne).
Hierfür können Sie mithilfe von `setsockopt` einen Timeout von `recv` angeben:
`SO_RECVTIMEO`. Dieser sorgt dafür, dass recv spätestens nach dem Timeout aufhört
zu blocken.

**Hinweis: **Der Test überprüft nur ob die Threads beendet werden, es ist aber
auch erforderlich, dass keine memory leaks enstehen.

# Tests
**Hinweis: **Die Tests müssen als root ausgeführt werden.
Ihren Server können Sie mit `telnet`, `curl` oder einem gewöhnlichen Webbrowser
testen. Zur Bewertung relevante Tests finden Sie in `test06.sh`
welches Sie auch mit `make test` aufrufen können.

Abgaben die nur darauf abzielen die Tests zu bestehen, können wir natürlich
nicht gelten lassen. Eure Abgabe sollte mindestens genau so viele alte Tests
bestehen wie eure vergangene Abgabe.
