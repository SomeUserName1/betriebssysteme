# 13 Übungsblatt
**Bamberger, Jannik; Klopfer, Fabian**

## Aufgabe 1: Allgemeines RAID		(/4)

**a) Einige RAID-Level bieten rein rechnerisch einen besseren Datendurchsatz als einzelne Platten. Welche Umstände, außer unterschiedlichen Dateigrößen und der Blockverteilung auf dem Medium, können diese Leistung im realen System vermindern? (/2)**

- Schreib & Lesegeschwindigkeitsdifferenzen zwischen den Platten
- suboptimales Verhältnis vom Plattenanzahl zu Blockgröße (entscheided darüber, wie oft für die Paritätsdaten gelesen werden muss)
- kaputte ATA Kabel
- kaputte Platten(-controller)/auffällige S.M.A.R.T.-Daten
- verschlissene/veraltete Platten und Neue kombinieren
- Fehlerrate bei großen Platten (unrecoverable read error rate)

**b) Warum sind Lesegeschwindigkeiten von RAID-Systemen abhängig von der Größe der zu lesenden Daten? (/2)**

Abhängig von der Dateigröße können die Operationen besser auf die verschiedenen Festplatten verteilt werden. Zudem erzeugen kleine Dateien im Vergleich zu ihrer Größe einen enormen Overhead, der das System verlangsamt.

## Aufgabe 2: RAID Performance 	(/12)
**Angenommen, Sie haben vier Festplatten mit einer Datenübertragungsrate von bis zu 100 MB/s. Geben Sie für die RAID-Level 0, 1, 5 und 6 folgende Werte an. Begründen Sie jeweils ihre Ergebnisse.:**  

**a) Lesegeschwindigkeit (Dateigröße < Stripegröße) (/2)**  

| RAID-Level | max Lesegeschwindigkeit| Begründung |
|--- |--- |--- |
| 0 | etwa 100 Mb/s | Es wird von nur einer Platte gelesen, also ist auch deren Geschwindigkeit maßgeblich. |
| 1 | etwa 100 Mb/s (theoretisch bis zu 400 Mb/s) | Es kann von einer beliebigen Platte gelesen werden, da die Datei aber kleiner als die Stripegröße ist, wird nur eine Festplatte verwendet. Theoretisch wäre es möglich, kleinere Abschnitte als die Stripegröße zu lesen, dann würde man bis zu vierfacher Geschwindigkeit erreichen. |
| 5 | etwa 100 Mb/s | Wie bei RAID0 wird von einer Platte gelesen |
| 6 | etwa 100 Mb/s | Wie bei RAID0 wird von einer Platte gelesen |

**b) Lesegeschwindigkeit (Sehr große Dateien) (/2)**   

| RAID-Level | max. Lesegeschwindigkeit | Begründung |
|--- |--- |--- |
| 0 | etwa 400 Mb/s | Da die Datei wesentlich größer als die Stripegröße ist wird von allen Platte parallel gelesen. Im Idealfall erreicht man also die vierfache Geschwindigkeit. |
| 1 | etwa 400 Mb/s | Wie bei RAID0 kann von allen Platten gleichzeitig gelesen werden, da jede Platte eine Kopie der anderen ist, und entsprechend alle Daten enthält (nicht in allen RAID-Controllern) |
| 5 | bis zu 300 Mb/s | Es kann von allen Platten gleichzeitig gelesen werden. Die Paritätsdaten werden jeweils übersprungen, kosten aber trotzdem ein 1/4 der Geschwindikeit, da der Lesekopf trotzdem darüber fährt und so nicht von allen 4 sondern nur von 3 gleichzeitig verwertbar gelesen werden kann. |
| 6 | bis zu 200 Mb/s | Es kann von allen Platten gleichzeitig gelesen werden. Die Paritätsdaten werden jeweils übersprungen, 2 Köpfe lesen aber Paritätsdaten, sodass diese nichts verwertbares lesen können. |

**c) Schreibgeschwindigkeit (Dateigr < Stripegröße) (/2)**  

| RAID-Level | max. Schreibgeschwindigkeit | Begründung |
|--- |--- |--- |
| 0 | etwa 100 Mb/s | Es wird nur auf eine Platte geschrieben. |
| 1 | etwa 100 Mb/s | Es wird auf alle Platten parallel das gleiche geschrieben, es ist also die Performance so gut, wie die schlechteste Platte |
| 5 | etwa 50 Mb/s (wenn r/w gleich schnell sind) | Bevor geschrieben wird müssen alle anderen Stripes der Gruppe gelesen werden und die neuen Paritätsdaten berechnet werden. Alle Blöcke können parallel geschrieben werden. Es kommen also zu der Zeit zum Schreiben noch die Zeit zum lesen und das berechnen der Parität(XOR kann vernachlässigt werden) hinzu. |
| 6 | bis zu 50 Mb/s (wenn r/w etwa gleich schnell) | Es muss wie bei RAID5 jeder Stripe der Gruppe gelesen werden und es müssen zwei mal die Paritätsdaten berechnet werden. Einmal kann dabei XOR verwendet werden. Die zweite Funktion ist aber zeitaufwendiger, wodurch unter Umständen der Datendurchsatz schrumpft |


RAID 5 & 6:
Random Ops: Mies, da jeweils pro kleinem Zugriff wieder die Paritätsdaten gelesen berechnet und geschrieben werden müssen
R5: W = N*X/4 (N Platten, X Geschwindikeit)
R6: W = N*X/6

**d) Schreibgeschwindigkeit (Sehr große Dateien) (/2)****  

| RAID-Level | max. Schreibgeschwindigkeit | Begründung |
|--- |--- |--- |
| 0 | etwa 400 Mb/s |  Alle Platten können parallel beschrieben werden. |
| 1 | etwa 100 Mb/s | Es wird auf alle Platten das gleiche geschreiben, man ist also so schnell, wie die langsamste Platte |
| 5 | bis zu 300 Mb/s | Auf alle Platten wird parallel geschrieben. Ein Viertel der Daten ist aber Paritätsinformation. Die Berechnung der Parität ist mit XOR vernachlässigbar und es muss nicht gelesen werden, da immer außer am Schluss/Anfang alle Stripes einer Gruppe beschrieben werden. |
| 6 | bis zu 200 Mb/s | Wie bei RAID5, aber es ist die Hälft Paritätsinformation. Je nach dem wie schnell die zweite Paritätsfunktion ist wird die Datenrate niederer. |

**e) Wie verändern sich diese Werte, wenn eine Festplatte im Verbund ausfällt? (/4)**

| RAID-Level	| Begründung								|
|---			|---										|
| 0				|Nicht mehr Betriebsfähig|
| 1				|Schreibt gleich schnell, aber liest nur noch mit bis zu 300 Mb/s|
| 5				|Schreibt gleich schnell, da nicht Daten neu geschrieben werden die aus Parität berechnet wurden, sondern nur die Parität überschrieben wird; Write bei kleinen Daten, wenn die betreffende Platte ausgefallen ist muss von allen anderen Platten (erst Daten, dann Parität) gelesen werden und die Daten berechnet => 33.3 MB/s; sonst 50MB/s. Bei reads kommt das Wiederherstellen dazu aus der Parität, das sorgt aber "nur" für CPU Auslastung und eine daraus entstehende Latenz|
| 6				|s. R5 |

## Aufgabe 3: Selbststudium: VFS 	(/4)
**a) Was versteht man unter einem Virtuellen Dateisystem (VFS) (/1)**
Ein Virtuelles Filesystem ist eine Abstraktionsschicht zwischen dem konkreten Dateisystem und den Programmen. Es stellt eine Reihe von Operationen zur Verfügung, die von allen gängigen Dateisystemen unterstützt werden. Das virtuelle Dateisystem kann von Userprogrammen so genutzt werden wie ein normales Dateisystem, ohne zu wissen, wie die konkrete Implementierung aussieht. Es können zum Beispiel Netzlaufwerke mit dem gleichen Interface angesprochen werden, wie ein Wechseldatenträger oder eine interne Festplatte. 

**b) Welche Vorteile bringt die Nutzung eines VFS mit sich? Liefern Sie Vergleiche in anderen Bereichen, in denen ähnliche Modelle mit dem selben Ziel verwendet werden. (/3)**  
Das virtuelle Dateisystem bietet ein einheitliches Interface für den Anwendungsentwickler. Somit muss dieser sich nicht mit verschiedenen konkreten Systemen beschäftigen und bekommt Funktionen wie Netzwerkspeicher ohne eigenes Zutun geschenkt. Dieses Abstraktionsprinzip kommt an vielen Stellen zum Einsatz. Die Java VM ist zum Beispiel in ähnlicher Weise eine eine Abstraktion vom konkreten Betriebssystem auf dem die Anwendung läuft. Aber auch das Betriebssystem abstrahiert die konkrete Hardware für Anwendungsprogramme und erlaubt ihnen unabhängig davon zu laufen was konkret verbaut ist.
