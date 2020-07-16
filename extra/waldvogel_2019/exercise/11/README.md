# 11. Übungsblatt

**Abgabe** Optional bis zum 29. Januar, 4:00 Uhr.

## Aufgabe 1: Networking
1. Nennen und erklären Sie drei unterschiedliche Anwendungsarchitekturen um Daten zu übertragen.
2. Nehmen Sie an Sie möchten bei sich zu Hause einen Webserver betreiben. Welche Schwierigkeiten könnten hier auf Sie warten und wie könnten Sie diese lösen?
3. Erklären Sie den Unterschied von TCP und UDP.
4. Wird UDP noch verwendet? Wenn ja, warum?
5. Warum läuft HTTP über TCP und nicht UDP?
5. TLS wird verwendet um TCP Verbindungen abzusichern. Welche Möglichkeiten gibt es eine UDP Verbindung abzusichern? (Eigenstudium)
6. Erklären Sie Multiplexing bzw. Demultiplexing im Umfeld von Netzwerkkommunikation.

## Aufgabe 2: Wireshark
Mit Wireshark kann man Netzwerkpakete aufzeichnen, filtern und analysieren. Um die Funktionsweise von UDP besser zu verstehen, schauen Sie sich bitte folgende [UDP Übung][1] an.

## Aufgabe 3: Linux Boot Process
1. Was hat Münchausen mit dem Linux Boot Process zu tun?
2. Was ist der real-address mode bei einer CPU? Warum wird er benötigt?
3. Wieso sind beim Booten Interrupts deaktiviert?
4. Woher bekommt die CPU ihre erste Instruktion?
5. Welche Aufgaben hat das BIOS?
6. Warum wurde das BIOS durch UEFI ersetzt?
7. Wieso ist der Stage 1.5 bootloader nötig?
8. Was ist der große Vorteil von GRUB im Gegensatz zu LILO?
9. Was passiert jeweils wenn Sie sich ihre Partitionstabelle am Anfang der Festplatte überschreiben wenn Sie MBR bzw. GPT nutzen?
10. Welchen Kernel nutzt ihre VM? Geben Sie das verwendete Kommando an.
11. Wieso wird eine initrd benötigt?

[1]: http://www-net.cs.umass.edu/wireshark-labs/Wireshark_UDP_v7.0.pdf
