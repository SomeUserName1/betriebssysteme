# Lösungen zum 5\. Übungsblatt

# Bamberger, Jannik und Klopfer, Fabian

## Gesamt: 16/20

## Aufgabe 1: Scheduling: Allgemein 9/9

1. **Wodurch unterscheiden sich Schedulingalgorithmen, die Preemtion nutzen, von ihrern Gegenstücken, die dies nicht tun? Was sind die Vorteile?**  
Preemptive Schedulingalgorithmen ermöglichen es den aktuellen Prozess durch einen Interrupt zu unterbrechen und wieder in die Readyqueue einzureihen, wenn der Prozess z.B. die maximale Rechenzeit überschritten hat (,also wenn ein Clock-Interrupt auftritt), wenn ein I/O-Interrput auftritt, oder ähnliches (je nach Implementierung).  
Preemptive Schedulingalgorithmen verhindern, dass ein langer/ressourcenintensiver Prozess zu viele Ressourcen Monopolisiert, hat dafür einen größeren Overhead, der je nach Implementierung aber effizient gehalten werden kann.  
Nach A.Tanenbaum:
"In contrast, a preemptive scheduling algorithm picks a process and lets it run for a maximum of some fixed time. If it is still running at the end of the time interval, it is suspended and the scheduler picks another process to run (if one is available). Doing preemptive scheduling requires having a clock interrupt occur at the end of the time interval to give control of the CPU back to the scheduler. If no clock is available, nonpreemptive scheduling is the only option."
Nach Stallings (7th and International Edition, S. 424) Ist preempive beschrieben mit:
"Preemptive:The currently running process may be interrupted and moved to the Ready state by the OS. The decision to preempt may be performed when a new process arrives; when an interrupt occurs that places a blocked process in the Ready state; or periodically, based on a clock interrupt."

2. **Welchen Sachverhalt bezeichnet Startvation?**  
Wenn es zu Starvation kommt, erhält ein Prozess nicht mehr ausreichend Ressourcen um bearbeitet werden zu können. Die Ausführung verzögert sich theoretisch je nach Szenario bis ins unendliche.  

3. **Erläutern Sie kurz folgende Schedulingalgorithmen. Nehmen Sie auch Bezug auf Wartezeiten und mögliche Starvation**
    - *First come first serve:*  
	    - wählt das Element aus der Readyqueue, das am längsten wartet.
	    - nicht preemptive;
        - bevorzugt lange und CPU-lastige Prozesse.
    	- benachteiligt kurze und I/O-lastige Prozesse.
        - Starvation nicht möglich (angenommen alle Prozesse Terminieren in diskreter Zeit), da jeder eingegebene Prozess nach der Ausführung endlich vieler anderer Prozesse ausgeführt wird, egal wie weitere Eingaben in die Readyqueue sind.
    	- kann schlechte Reaktionszeit erzeugen, wenn z.B. ein sehr langer Prozess vor sehr vielen, sehr kurzen steht.
    - *Shortest Job first:*  
    	- wählt das Element aus der Readyqueue, das die kürzeste gemessene, eingegebene oder geschätzte Laufzeit.
    	- preemptive **SJF ist nicht preemptive. Die preemptive Version heißt SRT**
    	- bevorzugt kurze Prozesse
    	- benachteiligt lange Prozesse
    	- Starvation möglich, wenn durchgehend kürzere Prozesse zur Readyqueue hinzugefügt werden.
    	- gute Reaktionszeit für kurze Prozesse.
    - *Round Robin (ohne Zeitquantum)*  
    	- iteriert über alle Prozesse in der Readyqueue ohne nach einem best. Zeitquantum zu interrupten. Ein Prozess läuft also solange bis dieser fertig ist. Resultiert in gleichem Verhalten wie FCFS.
    	- nicht preemptive.
    	- Wartezeiten wie bei FCFS.
    	- Starvation nicht möglich, da alle Prozesse durch iteriert werden.
    	- Reaktionszeit wie bei FCFS
    - *Round Robin (mit Zeitquantum)*  
        - iteriert über alle Prozesse in der Readyqueue und weißt bei jedem Schritt einem Prozess die selbe Rechenzeit (Zeitquantum) zu.
    	- Alle Prozesse werden gleich behandelt
    	- Starvation nicht möglich, da alle Prozesse durch iteriert werden.
    	- gute Reaktionszeit für kurze Prozesse.  
    - *Shortest remaining time:*
        - wählt das Element aus der Readyqueue, das die kürzeste verbleibende Laufzeit hat, also nach dem Kriterium (gesamt Laufzeit - bisher genutzte Rechenzeit).
    	- bevorzugt kurze Prozesse.
    	- benachteiligt längere Prozesse.
    	- Starvation möglich wie bei SJF.
    	- gute Reaktionszeit.
    - [*lottery Scheduling*](http://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-lottery.pdf) oder A.Tanenbaum Buch
    	 - weißt jedem Element der Readyqueue eine Anzahl an losen zu und zieht jedes mal wenn ein Element gewählt werden soll ein los und wählt den gelosten Prozess aus. Somit lässt sich die Wahrscheinlichkeit, dass ein best. Prozess an der Reihe ist nicht-deterministisch aber stochastisch bestimmen durch die Anzahl der Lose pro Prozess
    	 - Proportional-Share Verfahren => bevorzugt keinen Prozess/User ausser dies ist gewollt.
    	 - keine Starvation möglich (jeder Prozess hat ein Los => jeder Prozess kann gezogen werden; ist aber Möglich, dass es sehr unwahrscheinlich wird, dass ein Prozess nicht bearbeitet wird)
    	 - Wann werden Tickets wie zugewiesen? Inflation? Übertragungen? Viel von Implementation abhängig, aber schlechte Reaktionsszeit, wenn I/O-bound Prozesse nicht gut gehandlet


## Aufgabe 2: Scheduling: Vergleich 2.5/6
 **Gegeben seien 6 Prozesse mit folgenden Daten:**
1. Prozess A erscheint zum Zeitpunkt 0 und benötigt 4 Zeiteinheiten in der CPU, um fertig zu werden.
2. Prozess B erscheint zum Zeitpunkt 1 und benötigt 8 Zeiteinheiten in der CPU, um fertigzu werden.
3. Prozess C erscheint zum Zeitpunkt 4 und benötigt 4 Zeiteinheiten in der CPU, um fertig zu werden.
4. Prozess D erscheint zum Zeitpunkt 7 und benötigt 5 Zeiteinheiten in der CPU, um fertig zu werden.
5. Prozess E erscheint zum Zeitpunkt 9 und benötigt 2 Zeiteinheiten in der CPU, um fertig zu werden.
6. Prozess F erscheint zum Zeitpunkt 10 und benötigt 2 Zeiteinheiten in der CPU, um fertig zu werden.  


**1. Berechnen Sie für folgende Schedulingalgorithmen die gesamte Systemzeit und das Verhältnis von Rechenzeit zu Systemzeit, sowie den Mittelwert beider Werte über alle Prozesse.**
1. FCFS
2. Round Robin (Zeitquantum = eine Zeiteinheit)
3. Round Robin (Zeitquantum = drei Zeiteinheiten)
4. SJF
5. SRT  

|  Process 		|  A 	|  B 	|  C 	|   D	|  E 	| F  	|
|---			|---	|---	|---	|---	|---	|---	|
| Arrival time	| 0  	|  1 	|  4 	|  7 	|  9 	| 10	|
| Service time	|  4 	|  8 	|  4 	|  5 	| 2  	|  2 	|

|	FCFS		|  A 	|  B 	|  C 	|   D	|  E 	| F  	| Mean 	|
|--- 			|---	|---	|---	|---	|---	|---	|---	|
| Finish Time 	|  4	|  12	| 16	|  21 	|  23 	|  25 	|		|
| TAT  			|  4	|  11	| 12	|  14 	|  14	|  15 	| 11,7 	|
| norm. TAT		|  1	| 1,37	| 3		| 2,8 	|  7 	| 7,5 	| 3,8 	|

|   RR mit Zq=1 |  A 	|  B 	|  C 	|   D	|  E 	| F  	| Mean 	|
|--- 			|---	|---	|---	|---	|---	|---	|---	|
| Finish Time	|   6	|  25	|  19	| 24	| 16	| 17	|		|
| TAT  			|   6	|  24	| 15	| 17	|  7	|  7	| 13,7	|
| norm. TAT		| 3		|   3	| 3,75	| 3,4	| 3,5	| 3,5	| 3,36	|

**C kann nicht zum ZP 4 laufen. ZWar geht ihr davon aus, dass Ankunft = Ankunft in der Readyqueue und dass ein Prozess dann auch direkt laufen kann, was legitim wäre, aber zum ZP 3 lief noch B, A war in die Queue, somit muss mindestens A noch abgearbeitet werden, bevor C kommen kann**
**Es gibt zwar auch die Möglichkeit bei RR neu ankommende Jobs vorne in die Queue zu packen, was dann zu einer Ausführung von C führen könnte, aber dann müsste D bei ZP 7, und nicht erst bei 8, laufen**

|  RR mit Zq=3	|  A 	|  B 	|  C 	|   D	|  E 	| F  	| Mean 	|
|--- 			|---	|---	|---	|---	|---	|---	|---	|
| Finish Time	| 17   	| 25  	|  21  	| 23  	|  14 	|  16 	|		|
| TAT  			| 17   	|  24 	|  17  	| 16  	|  5  	|  6  	| 14,17	|
| norm. TAT		| 4,25 	|  3  	| 4,25 	| 3,2 	| 2.5 	|   3 	|  3,36	|

**Selbes Problem wie bei RR mit Quantum 1. Ihr habt hier zwei Ablaufreihenfolgen drin, die so unmöglich beide vorliegen können:**
**E und F kommen nacheinander und werden auch in dieser Reihenfolge ausgeführt. Ergo packt ihr neue Prozesse hinten in die Queue.**
**Das heißt aber auch, dass A VOR C D E und F wieder in die Queue war (Kommt zu ZP 3 wieder rein) und somit zu ZP 6 ausgeführt werden muss**

|SJF			|  A 	|  B 	|  C 	|   D	|  E 	| F  	| Mean 	|
|--- 			|---	|---	|---	|---	|---	|---	|---	|
| Finish Time	|   4	|   25	|  8 	|  13 	|  15 	| 17  	|		|
| TAT  			|   4	|   24	|  4 	|   6 	|   6	|  7  	| 8,5  	|
| norm. TAT		|   1	|   3 	|  1 	| 1,2 	|   3	| 3.5 	| 2,12 	|

|   SRF 		|  A 	|  B 	|  C 	|   D	|  E 	| F  	| Mean 	|
|---			 |---	|---	|---	|---	|---	|---	|---	|
| Finish Time	|  4  	|  25	|  8 	|  17	|  12 	| 14  	|		|
| TAT  			|  4  	|  24	|  4 	|  10	|   3 	|  4 	| 8,17	|
| norm. TAT		|  1  	|   3	|  1 	|  2	| 1.5 	|  2 	| 1,75	|
**Wenn A bei ZP 0 ankommt und auch sofort laufen darf und selbiges für C gilt, dann muss bei SRT E direkt bei ZP 9 laufen. Danach kommt F und dann D mit 4 Resteinheiten**



![Graphic](https://i.imgur.com/GiFbot4.png)  
[Link to Graphic](https://www.draw.io/?chrome=0&lightbox=1&layers=1&url=http%3A%2F%2Fi.imgur.com%2FGiFbot4.png&edit=https%3A%2F%2Fwww.draw.io%2F%3Furl%3Dhttp%253A%252F%252Fi.imgur.com%252FGiFbot4.png)  

**2. Ein perfektes Schedulingverfahren würde die gesamte Systemzeit eines Prozesses, über alle Prozesse gesehen, möglichst nahe an die wirklich benötigte CPU-Zeit bringen. Warum ist dies in realen System nicht möglich?**
 Solange die Readyqueue nicht leer ist, muss jeder Prozess zunächst warten bis er ausgewählt wird. Ist der Prozess nun sehr kurz (z.B. 1), ist das Verhältnis von Systemzeit durch CPU-Zeit schon sehr hoch, wenn der Prozess nur kurz warten muss (z.B. 2 Schritte). Ausserdem stellen I/0-bound Prozesse ein Problem dar, da diese sich je nach Schedulingalgorithmus bei der wieder Einreihung anders verhält als CPU-bound Prozesse. Hinzu kommen Interrupts, die je nach Ereignis wiederum I/O-bound Prozesse auslösen und so für weitere Wartezeiten sorgen. **Das sind aber alles keine Hindernisse. I/O-Blocks zählen nicht zur Wartezeit, weil der Prozess währenddessen auch nicht ready ist und auf CPU-Zeit wartet. Real ist es allerdings nicht umsetzbar, weil man für eine Minimierung der Wartezeiten Wissen über künftige Erreignisse (Auch Userinteraktionen), sowie die Laufzeit der PRozesse braucht, die man aber nur abschätzen, nie genau wissen, kann**


## Aufgabe 3: Scheduling: Minix
1. **Erklären Sie die Funktionsweise und den Aufbau des Minix-Schedulers und vergleichen Sie ihn auf Vor- und Nachteile mit einem Round Robin, sowie einem FCFS Scheduler. Nehmen Sie u.A. Bezug auf die Funktion "balance_queues "minix/servers/sched/schedule.c", die Handhabung von Prozessen beim Einsortieren in die Readyqueue, deren Aufbau, sowie der Auswahl des nächsten Prozesses, der laufen soll.**  
 Der Minix-Scheduler ist Unterteilt in 16 Queues, die nach Priorität geordnet sind. Hierbei ist 0 die höchst mögliche Priorität und 15 ist die niedrigste (IDLE daemon). In Q0 sind nur Kernel, Clock Task und System Task. In Q1 ist der tty Treiber,... . Die Priorität richtet sich also nach der Wichtigkeit für das System (oder ugs. je wichtiger/hardwarenäher/kritischer der Prozess desto früher wird er geschedulet).  
 Innerhalb der Queues wird dann Round Robin genutzt. Wenn ein Prozess sein Quantum also aufgebraucht hat, wird dieser hinten in der Queue eingefügt. Prozesse, die vor Aufbrauch ihres Zeitquantums in den blocking-Zustand übergegangen sind, werden vorne in der entsprechenden Queue eingefügt um das Zeitquantum restlich zu verbrauchen.  
 Die Queues werden bei 0 beginnend geschedulet, d.h. zunächst werden alle Elemente der Q0 geschedulet bis diese leer ist, dann alle Elemente der Q1 usw. . Bei den am höchsten priorisierten Queues wird ein sehr großes Zeitquantum gewählt, damit Kernel, Treiber und die wichtigsten Komponenten des Betriebsystem/Server ausführen bis sie blocken. Nur in Spezialfällen werden diese preempted. Ansonsten wird ein Standartquantum von 200 verwendet (schedule.c, Z. 44).  
 Wenn ein Prozess sein Quantum komplett aufgebraucht hat, und er läuft das zweite mal hinter einander druch, so wird wird der Porzess "bestraft". Seine Priorität wird vermindert, indem er in die nächst höhere Prioriätsqueue verlegt (Anzeichen für sehr lange oder endlose Schleife). Wenn das Quantum komplett genutzt wurde und davor ein anderer Prozess ausgeführt wurde, so wird der Wert der Strafe auf 1 gesetzt.  
 Alle 5 Sekunden werden alle Prozesse die bestraft sind wieder eine Queuestufe nach unten versetzt (ihre Priorität wird erhöht).
 Die Nachteile des Minix-Schedulers sind, dass er deutlich komplexer ist als die naiven Ansätze Round Robin und FCFS. Dadurch verbraucht das Scheduling selbst mehr Zeit im System. Ausserdem sind deutlich größere Datenstrukturen und mehr Queues nötig, die Speicher verbrauchen.
 Die Vorteile des Minix-Schedulers sind deutlich verbesserte Response Zeiten, da durch Priority Scheduling immer zunächst die system- und damit performance-kritischen Prozesse zuerst geschedulet werden. I/O wird nicht benachteiligt durch dieses Verfahren, da I/O-bound Prozessen die gleiche Rechenzeit pro Zeitquantum zukommt wie den CPU-bound Prozessen (im Vergleich zu normalem Round Robin, bei dem ein durch einen Interrupt in den ready-Zustand Versetzten Prozess immer hinten in die Queue eingereiht wird, unabh. von vorherigem Zeitq.).

2. **Ist Starvation in diesem System möglich? Begründen Sie.**
 Ja in diesem System ist Starvation möglich. Angenommen es werden kontinuierlich kurze, neue Prozesse in die Queues 0 bis 5 eingefügt (Dauer <1ZQ). Dann werden nie Prozesse der Schedules 6 bis 15 geschedulet, denn es existiert durchgehend ein Prozess in den Queues 0 bis 5, der als nächstes geschedulet werden muss aufgrund seiner höheren Priorität. Theoretisch kann man dem mit nice entgegansteuern, dies wird aber (, wenn ich den Code richtig verstanden habe,) nur durch den Prozess Manager genutzt (nicht Teil des Schedulers, Erweiterung des Schedulers? Ich werde hoffentlich im Tut. nochmal fragen).
**Auch wenn der Kommentar bei Balance_queues es anders ausdrückt: Hochgestuft werden alle Prozesse. SIe müssen nur "in_use" sein, sprich der Slot muss einem echten Prozess und keinem Zombie o.ä. gehören. So kann auch ein Userprozess in Kernelprioritäten kommen. Keine Starvation möglich**
