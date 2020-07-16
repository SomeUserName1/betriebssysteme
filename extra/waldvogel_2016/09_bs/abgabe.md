# Lösungen zum 9\. Übungsblatt

# Bamberger, Jannik und Klopfer, Fabian

## Gesamt: 20/20

## Aufgabe 1: Allgemeine Fragen 3/3
1. **Erläutern Sie die Idee, die Virtual Memory zu Grunde liegt.**  
 Bei Virtual Memory kann Programmen vom Betriebssystem wesentlich mehr Speicher zugewiesen werden, als eigentlich physikalisch vorhanden ist. Der Speicherplatz der nicht im echten Haupspeicher steht befindet sich auf dem Sekundärspeicher. Das Betriebssystem kümmert sich dann darum, dass die benötigten Speicherbereiche des Sekundärspeichers im physikalischen Hauptspeicher stehen, wenn sie benötigt werden, damit so viele Prozesse wie möglich gleichzeitig im Arbeitsspeicher sein können (um Prozessor und I/O Geräte maximal auszulasten). Hierbei werden Referenzen logisch Adressiert und erst zur Laufzeit in physische Adressen umgewandelt. So kann man einen Prozess nicht vollständig, nicht zusammenhängend und an wechselnden Adressen gespeichert und trotzdem ausgeführt werden.  

2. **Was versteht man unter Page Sharing?**  
 Beim Page Sharing steht eine Page in der Pagetabelle mehrerer Prozesse, so dass sie gemeinsam darauf zugreifen können. Sie teilen also einen Speicherbereich, über den sie kommunizieren können. Die Addressen die die jeweiligen Programme sehen müssen nicht gleich sein.  

3. **Prepaging ist ein Beispiel für eine Lazy Loading Methode. Erklären Sie das Grundprinzip und wann hierdurch eine Effizienzsteigerung erreicht werden kann.**  
 Lazy Loading bezeichnet ein Software-Entwurfsmuster, bei dem ein Speicherobjekt zunächst nur repräsentiert wird, bis der konkrete Inhalt benutzt wird, dann wird das eigentliche Speicherobjekt geholt. Zu Effizienzsteigerungen kommt es wenn z.B. eine Variable mit einem SQL-Befehl belegt wird und dieser erst aufgelöst wird, wenn der Wert der Variable gelesen werden soll. Ein Besipiel wäre demand paging.
 Prepaging ist ein Beispiel für eager loading, bei dem mehr Speicherobjekte als zwingend benötigt geladen werden, um im weiteren Verlauf der Ausführung Speicherobjekte vorgeladen zu haben, die später bennötigt werden und sich so die Ladezeit zu sparen. Dies ist effizient, wenn viele der vorgeladenen Objekte im späteren Verlauf verwendet werden.
 Beim Prepaging wird wenn ein Programm gestartet wird gleich eine größere Menge an Pages geladen, als eigentlich sofort benötigt werden. Damit wird zum einen versucht, die Anzahl an Pagefaults beim starten eine Programmes in Grenzen zu halten (jeder Pagefault ist ein unnötiger Overhead der das System verlangsamt), da es sehr wahrscheinlich ist, dass das Programm Daten aus mehreren Pages braucht. Andererseits wird dadurch auch ausgenutzt, dass der Sekundärspeicher häufig schneller sequenziell lesen kann, als random, und damit am Anfang nur ein langsamer Zugriff auf den Sekundärspeicher nötig ist, anstatt sehr vielen.

## Aufgabe 2: Zuteilung und Auslagerung 4/4
1. **Wie groß konnte der ausgelagerte Prozess maximal gewesen sein?**  
Der Prozess war 1M groß und stand direkt links von X, sonst wäre X nicht an dieser Stelle (in der Mitte von einem freien Block) platziert worden

2. **Wie groß war der freie Block, der durch X aufgespalten wurde?**  
 Der Block war `2M + 5M = 7M` groß.

3. **Sei Y der einzufügende 3M Block. Einfügen von 3M:**
  - first fit: 4M Block wird in Y + 1M frei geteilt
  - next fit: 5M Block wird in Y + 2M frei geteilt
  - best fit: 3M Block ganz hinten
  - worst fit: 8M Block wird in Y + 5M frei geteilt

## Aufgabe 3: Page Replacement Policies 10/10
**a-e)**

|Einfügen:		|FIFO	|LRU	|Clock-Algorithmus	|Optimal	|
|---			|---	|---	|---				|---		|
|7,0,1			|7,0,1	|7,0,1	|7,0,1				|7,0,1		|
|2				|2,0,1	|2,0,1	|2,0,1				|2,0,1		|
|0				|2,0,1	|2,0,1	|2,0,1				|2,0,1		|
|3				|2,3,1	|2,0,3	|2,0,3				|2,0,3		|
|0				|2,3,0	|2,0,3	|2,0,3				|2,0,3		|
|4				|4,3,0	|4,0,3	|4,0,3				|2,4,3		|
|2				|4,2,0	|4,0,2	|4,2,3				|2,4,3		|
|3				|4,2,3	|4,3,2	|4,2,3				|2,4,3		|
|0				|0,2,3	|0,3,2	|4,2,0				|2,0,3		|
|3				|0,2,3	|0,3,2	|3,2,0				|2,0,3		|
|2				|0,2,3	|0,3,2	|3,2,0				|2,0,3		|
|**Pagefaults**	|7		|6		|6					|4			|

f) **Welche der Strategien sind in einem realen System umsetzbar?**  
Es sind FIFO und der Clock-Algorithmus umsetzbar. Bei der Optimalen Austauschstrategie muss vorher genau bekannt sein, wann welche Page benötigt wird. Dies ist nicht möglich, da die Zukunft nicht vorhergesagt werden kann. Der LRU-Algorithmus kann zwar in der Theorie verwendet werden, aber bei dem einsatz in einem realen System entsteht ein zu großer Overhead durch den Algorithmus. Es müsste ja bei jedem Speicherzugriff ein Zeitstempel für den letzten Zugriff geschrieben oder eine Liste neu sortiert werden. Bei FIFO kann die Pagetabelle wie ein Ring verwendet werden, und damit ist FIFO nutzbar. Bei dem Clock-Algorithmus entsteht auch nur bei einem Pagefault zusätzlicher Overhead.

## Aufgabe 4: Selbststudium 3/3
- **Wie viele Bits hat eine logische Adresse?**  
 29 (Pageadresse + Pagegröße)
- **Wie viele Bytes hat ein Frame?**  
 2^11 (So viele wie eine Page)
- **Wie viele Bits der physikalischen Adresse spezifizieren einen Frame?**  
 21 (32 - 11 bzw. Physikalische Adressen / Seitengröße)
- **Wie viele Einträge hat die Seitentabelle (Page Table)?**  
 2^18 (So viele wie es Pages gibt maximal)
- **Wie viele Bits sind in jedem Eintrag der Seitentabelle (Page Table)? Jeder Eintrag beinhalte ein valid/invalid Bit.**  
 22 (21 Frame Adresse und 1 valid/invalid Bit)
