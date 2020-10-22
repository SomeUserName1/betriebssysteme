# 7. Übungsblatt

**Abgabe** Optional bis zum 18. Dezember, 4:00 Uhr.

## Aufgabe 1: Kernel
1. Warum muss man zwischen Kernel und user programs unterscheiden? Wie wird dies gemacht?
2. Welche Möglichkeiten hat ein user program priviligierte Operationen auszuführen?
3. Geben Sie eine grobe Übersicht über die Funktionsweise der CPU.
4. Erklären Sie den Unterschied von User level und User space.
5. Was ist eine Trap?
6. Nehmen Sie an sie würden einen Kernel designen. Welche Komponenten würden sie integrieren und welche auslagern? Begründen Sie.
7. Welche Vorteile/Nachteile hat ein Monolithic Kernel gegenüber einem Microkernel?

## Aufgabe 2: OS Design
1. Bis Sie sich als Benutzer an einem System anmelden können sind seit dem Start des Computers viele unterschiedliche Komponenten involviert. Warum wird dies nicht vereinfacht und innerhalb einer Komponente erledigt?
2. Wie unterscheidet sich der Windows boot process von dem vorgestellten? (Eigenstudium)
3. Was sind die Aufgaben von GRUB? Gibt es alternativen?
4. Welchen runlevel hat ihre virtuelle Maschine? Wie können Sie dies ermitteln?
5. Was ist die Grundidee eines Daemons?

## Aufgabe 3: Assembly (Eigenstudium)
Um die Funktionsweise der CPU noch besser zu verstehen, ist es hilfreich sich etwas mit Assembler auseinander zu setzen. GCC bietet glücklicher Weise die Möglichkeit den Assemblercode auszugeben. Rufen Sie hierzu `gcc -S example.c` auf. Anschließend sollten Sie den Code in `example.s` finden. Geben Sie eine grobe Beschreibung über den Ablauf des Programs. Sie müssen hierbei nicht auf genauer auf den Anfang bzw. Ende des Codes eingehen. Eine Übersicht über die wichtigsten Symbole finden Sie in [diesem Tutorial](https://pages.hep.wisc.edu/~pinghc/x86AssmTutorial.htm). Wie verändert sich der Code wenn Sie die Optimierungen (`-O1`) von gcc einschalten?

