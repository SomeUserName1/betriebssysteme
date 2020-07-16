# Lösungen zum 3\. Übungsblatt

# Klopfer, Fabian und Bamberger, Jannik

## Gesamt: 15/20

## Aufgabe 1: Allgemein 6/8

1. **Welches sind die zwei getrennten und potenziell unabhängigen Merkmale, die durch das Prozesskonzept verkörpert werden?**

  - Ressourcenbesitz: Ein Prozess enthält einen virtuellen Addressraum, der das Prozess-Abbild (Programme, Daten, Stackinhalt und Attribute, die im Prozesskontrollblock definiert wurden) enthält. Ein Prozess kann z.B. Arbeitsspeicher, I/O-Ressourcen und Dateien zugewiesen bekommen oder besitzen.
  - Scheduling und Ausführung: Die Ausführung eines Prozesses folgt einem Ausführungspfad durch eins oder mehrere Programme. Der Prozess kann hier bei andere Prozesse verschachteln. Jeder Prozess hat einen Ausführungsstatus und eine Priorität. Beim Scheduling wird nach Prozessstatus und Priorität geschedulet und dispatcht.

2. **Welche Ressourcen werden in der Regel gemeinsam von allen Threads eines Prozesses genutzt?**

  - Der virtuelle Addressraum der das Prozess-Abbild enthält.
  - Andere Prozesse (z.B. für IPC)
  - Geschützten Prozessorzugang
  - Dateien
  - I/O Ressourcen

3. **Wird ein Prozess beendet und es existieren noch laufende Threads dieses Prozesses, können diese weiterlaufen?**

  - Nein, weil der Adressraum der Threads in dem des Prozesses liegt und wenn dieser beendet wird, wird der Addressraum freigegeben.

4. **Nennen Sie je zwei Vor- und Nachteile von Benutzer-Threads gegenüber Kernel-Threads.**

  _Benutzer-Threads:_

  - Das Threadmanagement ist vom Kernel abgekapselt
  - Scheduling kann Programm spezifisch sein
  - Kann auf jedem System ausgeführt werden, da die Threads lib Kernel-unabhängig ist.

  _Kernel-Threads:_

  - Wenn ein Systemcall eines Threads blockt (z.B. wegen I/O Wartezeit) werden alle Threads im zugehörigen Prozess geblockt. beim Kernel-Thread wird nur der jeweilige geblockt der den Syscall aufgerugen hat.
  - Mit ULTs kann nur die Eigenschaft des Mutlithreaddings ausgenutzt werden, nicht aber die des Multiprocessing. Scheduling funktioniert auf Thread Basis (S.168).

5. **Gibt es einen Unterschied zwischen Thread- und Prozesswechseln bezüglich ihrem (Zeit)Aufwand? Geben Sie zwei mögliche Gründe für das von Ihnen vermutete Verhalten an.**

  - Kommt drauf an. Bei Kernel-Threads wird Thread-basiert geschedulet, bei ULTs wird das Scheduling programmspezifisch geregelt. D.h. bei einem Kernel-Thread kann es sein, dass ein neuer Prozesskontrollblock geladen werden muss bei einem Wechsel zwischen Threads, also wird der gleiche Aufwand wie beim Prozesswechsel bennötigt. Bei ULTs ist das Wechseln schneller, da der Prozesskontrollblock nicht neu geladen werden muss beim Threadwechsel. **Punkt 1 ist halbwegs korrekt, aber der Schnelligkeitsvorteil bei Threadwechseln innerhalb des selben Prozesses fehlt. Kleinerer TCP, ergo weniger zum wechseln als beim lesen/schreiben eines neuen PCB. Dazu die ganze SPeichergschichte, die bei Threads geteilt wird 1/3**

## Aufgabe 2: Race Condition 4/4

1. **Bestimmen Sie die korrekte untere und obere Grenze des Endwerts der Ausgabe der gemeinsamen Variablen anzGesamt durch dieses nebenläufige Programm. Begründen Sie ihre Ergebnisse. Nehmen Sie dafür an, dass Prozesse mit jeder beliebigen relativen Geschwindigkeit ausgeführt werden können und dass ein Wert nur verändert werden kann, nachdem er mit Hilfe eines separaten Maschinenbefehls in ein Register geladen wurde.**<br>
  Das Ergebnis kann zwischen -49 und 49 liegen:
  Für das Maximum wird immer von einem Thread gelesen, dann vom anderen gelesen, dekrementieretund geschrieben. Dann vom ersten  inrementiert und geschrieben, so dass im Endeffekt die Dekrementierung ignoriert wurde. Dies geht in allen Fällen, bis auf den letzten, so dass hier eine Dekrementierung durchkommt (die letzte Operation ist eine Dekrementierung weil count bei 49 aufhört). Es sind also 25 Inkrementirungen pro Thread und eine Dekrementierung von allen zusammen.

  Für das Minimum gilt prinzipiell das Gleiche. Der einzige Unterschied ist, dass hier am Anfang eine Inkrementirung durchkommt, und nicht am Ende.

2.**Nehmen Sie an, dass unter Anwendung der Voraussetzungen in Teil (a) eine willkürliche Anzahl dieser Prozesse parallel ausgeführt werden darf. Welche Auswirkungen hat diese Änderung auf die Bandbreite der Endwerte von anzGesamt? Begründen Sie ihre Ergebnisse.**

Es gilt das gleiche wie bei (a). Es sind also bei n Threads als Minimum -25n + 1 und als Maximum 25n - 1.

## Aufgabe 3: User-Level-Threads 0/3

**Betrachten Sie ein System, in dem die Threads vollständig im Benutzeradressraum realisiert sind und das Laufzeitsystem einmal in der Sekunde ein Zeitsignal (Timer-Interrupt) bekommt. Nehmen Sie an, dass ein Zeitsignal auftritt während ein Thread im Laufzeitsystem ausgeführt wird. Ein mögliches Problem in diesem Szenario wäre, daß das Laufzeitsystem gerade dabei sein könnte die Schedulingqueues zu bearbeiten, wenn der Interrupthandler des Zeitsignals seine Arbeit aufnimmt. Warum? Können Sie eine Lösung vorschlagen?**

Wenn der Threadscheduler keine Rechenzeit mehr bekommt um die nächsten Aufgaben korrekt in die Queue einzufügen, so können im Prozess nach einiger Zeit keine Threads mehr bearbeitet werden, wenn der Threadscheduler sich nicht mehr selbst wieder in die Queue hinzufügen konnte, um weiter zu schedulen. Eine Lösung für dieses Problem, wäre immer zunächst den Thread der das Scheduling im Prozess regelt zuerst auszuführen. Viel hängt hier von Implementationsdetails ab z.B. wie genau der ULT-Scheduler implementiert ist, ob der Timer-Interrupt auch das Ende der zustehenden Prozessor-Zeit/ein Timeout bedeutet, in wie fern der Prozessscheduler implementiert ist, etc. **Leider am Problem vorbei**

## Aufgabe 4: Threadkontrollblock 5/5

Prozesskontrollblock: Das kommt darauf an wie man implementiert.
Definitiv notwendig sind alle Identifiers, alle Data Structuring Felder.  
Alle Scheduling und Stateinformations, je nach Kernel oder User-level Thread; bei Kernel-Threads können manche ausgelagert werden (Thread basiertes Scheduling). Der Prozesskontrollblock, der auf User-level-Threads basiert, bennötigt allerdings alle Felder die bennötigt werden um selbst vom Kernel geschedulet zu werden.
Am meisten hängt aber die Nutzung von Control und Status registern ab. Die Statusinformation kann Threadweise gesetzt werden; es ist aber auch sinnvoll dies prozessweise zu regeln. Einen Stack Pointer könnte der Prozess bennötigen um Thread aufrufe zu Verwalten, dies könnte aber auch im Scheduling Thread passieren (User-level-Threads). Condition Codes können ebenfalls beide Blöcke tragen, um mehr Fehlertoleranz zu schaffen, falls ein Thread abstürzt so stünde trotzdem die bisher getätigte Arbeit im Speicher sodass man nicht von vorne anfangen muss, selbst wenn mehrere Threads auf einmal beendet werden (solange der Prozess nicht beendet wird). Auch Visible User Register können hilfreich sein, falls dynamisch, je nach Eingabe und zur verfügung stehenden Ressourcen Threads erzeugt werden.

Thread:

- User Visible Registers
- Stack Pointer
- Program Counter
- Condition code
- Thread state
- Identifier of it's parent process
