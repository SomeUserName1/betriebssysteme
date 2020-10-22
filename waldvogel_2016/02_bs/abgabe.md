## Übungsblatt 2

Jannik Bamberger, Fabian Klopfer

## Gesamt: 17/20

#### Aufgabe 1: Allgemein 6/7


###### 1.
 Durch Memory-mapped I/O können I/O-Operationen wie normale Hauptspeicherzugriffe behandelt werden. Hierfür gibt es 
 einen, zwischen CPU und I/O-Gerät geteilten Speicherbereich, auf den die Register und Speicher der I/O-Geräte 
 abgebildet wird. Dadurch ist ein Zugriff auf IO-Geräte über den Datenbus möglich und es sind keine speziellen Befehle
 für IO-Operationen nötig.

###### 2.
 DMA heißt direct memory access und ist ein Modul, dass den Austausch von I/O-Daten zwischen dem Hauptspeicher und und dem jeweiligen (oder nur einem) I/O-Modul regelt. Hierfür muss der Prozessor lediglich eine entsprechende Anfrage an das DMA-Modul senden und kann sich danach um andere Aufgaben kümmern.  
Während das DMA-Modul die entsprechenden Daten überträgt, um dann durch einen Interrupt über die Fertigstellung des Transfers benachrichtigt zu werden **Vorteile klar benennen 1/2**


###### 3.
- Authentifizierung
- Zugangskontrolle
- Intrusion Detection/ Eindringlingserkennung
- Firewall
- Je nach Use Case Deep Packet inspection

#### Aufgabe 2: Control Stack 1/3

Nein. Der Stack-Pointer ist die Adresse des obersten Elements im Stack. Der Stack enthält alle Informationen über den Zustand der laufenden Programme u.a. Rücksprungadressen anderer Routinen die die aktuelle Aufgerufen haben. Der Programmzähler enthält die Adresse des nächsten auszuführenden Befehls und wird immer um 1 inkrementiert um den korrekten nächsten Befehl zu fetchen. Würde man also den Programmcounter mit dem Stack-Pointer ersetzen würde die Maschiene nicht mehr Funktionieren, eben weil Prozesszustandsinformationen auf dem Stack liegen und nicht die Adresse des nächsten Befehls. Ebenso wird der Stack nicht für jeden ausgeführten Befehl verändert, und entsprechen würde es Befehle geben, bei denen das Programm stehen bleibt, weil der Stack nicht verändert wird. **Vorsicht: Die Aufgabe besagt explizit, dass hier ein Stack für Prozeduraufrufe und Returnadressen verwendet wird. In einem solchen Fall würde es tatsächlich funktionieren. Aber nur ohne Funktionsargumente**

#### Aufgabe 3 2/2

- USB 2.0 (Hi-Speed)
  Bei USB 2.0 Hi-Speed sind theoretisch 480Mbit/s möglich. Damit ist maximal die Verwendung von 12x möglich und somit
  432 Mbit/s. **Ich nehme mal an, dass sich diese Antwort darauf bezieht, dass es keine x13 Laufwerke gibt? Bei sowas aufpassen. Dann lieber schreiben: Theoretisch ~13-fach, gibt es aber nicht**

- USB 3.0 (SuperSpeed)
  Der SuperSpeed standard ist schnell genug um alle möglichen Laufwerkgeschwindigkeiten vollständig auszulasten. Daher
  hängt die Geschwindigkeit von dem Laufwerk ab. Maximal sind 576 Mbit/s (16x) möglich. **Aktuell, ja**

| Laufwerksgeschwindigkeit | Datenrate in Mbit/s |
| :------------- | :------------- |
| 1x |	36 |
| 2× |	72 |
| 4× |	144 |
| 6× |	216 |
|8× |	288 |
|12× |	432 |
|16×	| 576 |
Table 3-1. Comparing SuperSpeed to USB 2.0

| Characteristic	| SuperSpeed USB |	USB 2.0 |
| :--------------- | :------------- | :-------|
| Data Rate |	SuperSpeed (5.0 Gbps) |	low-speed (1.5 Mbps), full-speed (12 Mbps), and high-speed (480 Mbps)|
| Data Interface |	Dual-simplex, four-wire differential signaling separate from USB 2.0 signaling Simultaneous bi-directional data flows	| Half-duplex two-wire differential signaling Unidirectional data flow with negotiated directional bus transitions |
| Cable signal count |	Six: Four for SuperSpeed data path Two for non-SuperSpeed data path |	Two: Two for low-speed/full-speed/high- speed data path |
|Bus transaction protocol |	Host directed, asynchronous traffic flow Packet traffic is explicitly routed | Host directed, polled traffic flow Packet traffic is broadcast to all devices. |
Quelle: USB 3.0 doc 3.1.4 USB 3.0 Architecture Summary
[Download Seite der Doc](http://www.usb.org/developers/docs/documents_archive/)

#### Aufgabe 4: DMA 4/4
Wenn das DMA-Modul bitweise schreiben würde, würden 19200 Befehle weniger für den Prozessor zur Verfügung stehen.
Angenommen das DMA-Modul schreibt byte-weise, dann werden ``100 - (5000000 - (19200/8))/ 50000 = 100 - 4997600/50000 = 0,048%`` der Befehle 
benötigt. Falls das DMA-Modul den kompletten Datenbus benutzt dann sind entsprechend noch weniger Befehle nötig.

#### Aufgabe 5: Selbststudium 4/4

###### 1.
Beim Hyper-Threading führt ein Hyper-Threading-Kern Threads, falls in der Pipeline Lücken entstehen, z.B. bei einem Cache-Miss. Bei einem Cache-Miss muss der/die Haupt-Kern/e neue Daten aus dem Hauptspeicher laden. Diese Zeit wird beim Hyper-Threading genutzt indem ein anderer Thread in der Ladezeit bearbeitet wird. Auf der Hardwareebene betrachtet hat der Hyper-Threading-Kern keine ALU eigene Register, eigene paging tables und das Steuerwerk der CPU ist komplexer.mit mindestens 2 Programmcounter Stac
**Der Korrektheit halber: Der zweite "Kern" kommt regelmäßig dran, nicht nur, wenn der andere Thread die Recheneinheit nicht braucht und warten muss**

##### 2.
> So enthielt der ST zwar für damalige Verhältnisse üppige 512 KByte RAM, aber kein eigenes Video-RAM. Doch die Atari-Ingenieure hatten sich Mühe gegeben, den Nachteil auszugleichen: CPU und Video-Controller reizten beim abwechselnden Zugriff auf den Speicher die Möglichkeiten der RAM-Bausteine voll aus.

[Quelle](https://www.heise.de/ct/artikel/Sensationell-PC-Schreck-Der-Atari-ST-wird-30-Jahre-alt-2689006.html)

Beim Hyper-Threading greifen der/die Core(s) zu, bis ein Cache-Miss passiert. Dann übernimmtder Hyper-Threading-Kern. Bei der Atari ST hat der Grafikchip "Shifter" den Hauptspeicher des CPUs mitgenutzt, da kein V-RAM verbaut wurde.
**Genauer (Es geht ja um die Parallelen): Es gibt in beiden Fällen eine Ressource, die nicht voll ausgenutzt werden kann. (Recheneinheiten der CPU wegen Memorydelay beim Intel und der RAM beim Atari, weil die CPU nicht alle Zyklen nutzen kann). Somit gehen beide den Weg, die nicht voll ausreizbare Leistung der Ressource doppelt zu belegen. (Intel setzt zwei Threads in einen Kern, Atari lässt shifter und CPU einfach abwechselnd an den RAM, was keinen Stört, da die CPU in den SHiftertakten, sowieso nicht zugreifen könnte** 
