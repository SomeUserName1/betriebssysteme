# Lösungen zum 8\. Übungsblatt

# Bamberger, Jannik und Klopfer, Fabian

## Gesamt: 15/20

## Aufgabe 1: Allgemeine Fragen 5/5

- **pages haben im Normalfall eine Größe, die einer Zweierpotenz entspricht. Welche Vorteile bringt das mit sich? Wieso sind diese Vorteile wichtig?**
 - Durch die Verwendung von 2er Potenzen kann die logische Adresse ohne weitere Arithmetik parallel in pagenummer und Offset umgewandelt werden. Das Vereinfacht nicht nur die Adressierung für Programmierer, Assembler und Linker, sondern auch die hardwareseitige Umwandlung von logischen in physische Adressen. Diese ist sehr wichtig, da sie bei jedem Speicherzugriff verwendet wird.


- **Was ist ein TLB und wofür wird er benötigt?**  
 - translation lookaside buffer (TLB): Ein sehr schneller Cache, der verwendet wird um zuletzt referenzierte page table Einträge zu speichern, damit weniger auf den Hauptspeicher zugegriffen wird um page table Einträge zu laden.


- **Erklären Sie normale, hierarchische und invertierte page tables. Zeigen Sie Vor- und Nachteile auf.**  
 - Normale page tables: Teilt den addressierbaren user memory space in pages auf und schreibt für jede page die Framenummer und weitere Infos (Kontrollbits, Alter, ...) in eine page table pro Prozess. Da jeder Prozess, in einem System mit n byte logischem und physischem Adressraum mit m bytes pagegröße, 2^(n-m) pages adressieren kann, hat die page table daher bis zu 2^(n-m) Einträge pro Prozess. Jeder Eintrag besitzt eine Framenummer der Länge (n-m) Bits und Kontrollbits, insgesamt also ((n-m) + ||Kontrollbits||)/8 Bytes pro Eintrag.
 Die page table insgesamt ist dann 2^(n-m) &middot; &lceil;((n-m + ||Kontrollbits|| )/8)&rceil; Bytes groß. Bei 32 Bit und 2^12 (4KB) pagesize und 4 Kontrollbits sind das bis zu  2^20 &middot; (20+4)/(2^3) = (2^2) &middot; (2^20) = 2^22 MB =  4 MB pro Prozess, bei 64 Bit wären das cirka 2^54 < 2^52 Einträge &middot; ((52+x)/8) Bytes < 2^55 = 2 Petabyte <= Größe <= 4 Petabyte.  
 - Hierarchische page tables: "gepagetes Paging". Um keine riesigen page tables im Hauptspeicher verwalten zu müssen wird eine Baumstruktur erstellt. Die Wurzel speichert hierbei Pointer auf den Beginn der jeweiligen Subpage table. So ist es auch möglich nicht die ganze page table in den Hauptspeicher laden zu müssen, sondern nur den Teil der genutzt wird. Der Rest der page table Struktur muss also nicht physisch gespeichert werden, sondern viritualisiert und kann jeder Zeit in den Arbeitsspeicher geladen werden, falls bennötigt. Vorteil: weniger Speicherkomplexität, kleinere und Teil- page tables. Nachteil: Sekundärspeicher wird voller (egal), mehr Overhead  
 - Invertierte page tables: Anstatt für jede virtuelle page einen Eintrag anzulegen in der page table, wird für jeden pageframe ein Eintrag angelegt. Ein Eintrag beinhaltet die pagenummer zum zugehörigen Frame, die ID des Besitzerprozesses, Kontrollbits und einen Chain-/Next-Pointer, falls mehrere log. Adressen auf den gleichen Frame "abgebildet" werden. Wird eine logische Adresse eingegeben, so wird durch die Hashfunktion ein Pointer auf den Eintrag des entsprechenden Frames zurück gegeben. Damit hängt die größe der invertierten page tables nicht am logisch-adressierbaren Speicher, sondern an der physischen Speichergröße.


## Aufgabe 2: Dynamische Partitionierung 4/6
**Bestimmen Sie die Suchlänge (Anzahl der Speicherblöcke) für drei aufeinander folgende Suchen und Zuweisungen von 200 KiB Blöcken bei den folgenden Speicherzuteilungsalgorithmen der dynamischen Partitionierung. Die Anzahl der freien Blöcke sei N und sie seien abwechselnd 100 und 200 KiB groß, beginnend mit einem 100 KiB Block.**  
- **Best fit**  
Zuweisung 1: Suchlänge = n  
Zuweisung 2: Suchlänge = n-1  
Zuweisung 3: Suchlänge = n-2  
Insgesamt: Sum_i=0^3-1 (n - i)


- **First fit**  
Zuweisung 1: Suchlänge = 2  
Zuweisung 2: Suchlänge = 3  
Zuweisung 3: Suchlänge = 4  
Insgesamt: Sum_i=1^3 (i+1)


- **Next fit**  
Zuweisung 1: Suchlänge = 2  
Zuweisung 2: Suchlänge = 2  
Zuweisung 3: Suchlänge = 2  
Insgesamt: 3 &middot; 2


## Aufgabe 3: Worst Fit 2/3
**Ein Problem des Best-Fit Algorithmus ist, dass der nach dem Allozieren eines Blocks entstehende freie Block so klein ist, dass er meistens nicht verwendbar ist.**
- **Kann der Worst-Fit Algorithmus dieses Problem beheben?**  
In manchen Situationen ja, denn dann wären die entstehenden Lücken teilweise so groß, dass diese wieder verwendet werden können. Ansonsten kann dieses Problem jedoch auch bei worst-fit auftreten, wenn entweder nur ein freier Block groß genug ist für den zu allozierenden oder wenn ein zu allozierender Block theoretisch in einen etwas kleineren freien Bock gepasst hätte, jedoch wegen worst-fit der etwas größere ausgewählt wurde, so dass ein immer noch zu kleiner Block entsteht, aber im Vergleich mehr Speicher durch externe Fragmentierung verschwendet wird.  


- **Welche Nachteile hat der Worst-Fit Algorithmus?**  
Angenommen es gibt n freie Blöcke, von denen 2 größer sind als m aber nur einer größer als o. Seien nun 3 Prozesse A, B, C mit den zu allozierenden Blöcken der Größen a=m, b=o, c=x (0 < x < m < o). Suche passende Blöcke mit worst-fit, beginnend bei A.  
A wird also der freie Block zugewiesen mit Länge Block > o.  
Für B existiert somit kein freier Block mehr, wenn keine weiteren de-/re-allocationen getätigt werden. Dies ist unnötig, da bei anderer Reihenfolge alle drei Prozesse im Arbeitsspeicher ohne re-/deallocationen untergekommen wären.


- **Mit welcher Änderung kann dieser Nachteil verringert werden?**  
Buffern der Elemente, sortieren des Buffers absteigend nach Größe des zu allozierenden Blocks.


## Aufgabe 4: Hierarchical page Table 4/6
**Gehen Sie von einem System aus, welches Virtual-Paging mit 64-bit virtuellen Adressen und Seitengrößen von 2 KiB verwendet. Jeder Eintrag der Seitentabelle (page table) benötige 64 Bits. Erwünscht ist, dass eine Seitentabelle genau in eine Seite passt.**  
2 KiB = 2048 Bytes = 2^11 ; 64 Bit = 8 Byte = 2^3 ; Mit Formel aus 1 Größe der page table: 2^53 Einträge &middot; 2^3 Bytes = 2^56 Bytes

- **Wie viele Bits werden innerhalb einer page zur Adressierung verwendet?**  
Oder auch wie groß ist der Offset? Da es 2^53 pages geben kann bennötigt man 53 Bit zur Addressierung der page, daher gibt es 64-53 = 11 Bit, die den Offset innerhalb einer page angeben.**1/1**


- **Geben Sie die Größe einer der Seitentabellen auf pro Level an.**  
2^11 Bytes pro page / 2^3 Byte pro Eintrag = 2^8 Bytes = 256 Einträge; Größe einer page bleibt 2^11 Bytes = 2 KiB **1/1**


- **Wie viele Levels von Seitentabellen werden benötigt?**  
Wenn möglich bitte von unten nach oben lesen; 7 Ebenen werden bennötigt  
 0 Ebene: 2^5 Einträge &middot; 2^3 Bytes = 2^8 Bytes  = 1 page mit 2^3 Bytes interner Fragmentierung.   
 1 Ebene: 2^13 Einträge &middot; 2^3 Bytes = 2^16 Bytes  = 2^5 pages  
 2 Ebene: 2^21 Einträge &middot; 2^3 Bytes = 2^24 Bytes  = 2^13 pages  
 3 Ebene: 2^29 Einträge &middot; 2^3 Bytes = 2^32 Bytes  = 2^21 pages  
 4 Ebene: 2^37 Einträge &middot; 2^3 Bytes = 2^40 Bytes  = 2^29 pages  
 5 Ebene: 2^45 Einträge &middot; 2^3 Bytes = 2^48 Bytes  = 2^37 pages  
 6 Ebene:  2^64 Adressierbarer Speicher /2^11 pagegröße &middot; 8 Bytes Eintragsgröße = 2^(64-11) &middot; 2^3 = 2^56 Bytes = 2^45 pages
**2/2**

(Variante mit Blatt statt Wurzel Fragmentierung)

0: 2^8 E &middot; 2^3 B/E = 2^11 B = 1 P  
1: 2^16 E &middot; 2^3 B/E = 2^19 B = 2^8 P  
2: 2^24 E &middot; 2^3 B/E = 2^27 B = 2^16 P  
3: 2^32 E &middot; 2^3 B/E = 2^35 B = 2^24 P  
4: 2^40 E &middot; 2^3 B/E = 2^43 B = 2^32 P
5: 2^48 E &middot; 2^3 B/E = 2^51 B = 2^40 P
6: 2^56 E &middot; 2^3 B/E = 2^59 B = 2^48 P

- **Was ist die minimale Anzahl von Seiten, die bei diesem System zum Speichern von Seitentabellen benötigt wird?**
7 page tables werden bennötigt, um von der Wurzel zu einem Kind zu kommen, d.h. es werden genau so viele mindestens gebraucht, wie der Baum tief ist, sodass alle Speicherbereiche abgebildet werden können.**Das heißt nur, dass 7 Pages da sein müssen, damit man eine bestimmte Adresse in jedem Fall umrechnen kann. Aber wie viele sind es denn gesamt? 0/2**

1 + 2^8 + 2^16 + 2^24 + 2^32 + 2^40 + 2^48 
