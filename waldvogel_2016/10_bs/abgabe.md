# Lösungen zum 10\. Übungsblatt

# Bamberger, Jannik und Klopfer, Fabian

## Gesamt: 18/20

## Aufgabe 1: Segmentation 3/3
1. 660 + 195 = 855
2. Segmentation fault
3. 1754 + 421 = 2175
4. 996 + 462 = 1458
5. Segmentation fault
6. Segmentation fault

## Aufgabe 2: Paging 13/13
1. Die Virtuelle Adresse wird in einen Offset und eine Pagenummer zerlegt. Dann schaut die CPU, ob die Page in dem TLB ist. Wenn ja kann direkt die physikalische Addresse berechnet werden (aus Framenummer Offset). Wenn kein Eintrag im TLB war, dann wird die Pagetable untersucht. Falls die Page im Hauptspeicher ist wird der TLB aktualisiert und die physikalische Addresse berechnet. Mit dieser Addresse wird der Cache angesprochen. Bei einem Hit wird direkt der entsprechende Wert zurückgeliefert, sonst wird der Hauptspeicher genutzt, um den Wert zu laden. Falls die Page nicht im Hauptspeicher ist wird das Betriebssystem aufgefordert, die Page zu laden. Falls genügend Platz vorhanden ist wird die Page geladen, falls nicht wird eine andere Page ausgetauscht. Dann wird die Pagetabelle aktualisiert. Jetzt geht der ganze Prozess von vorne los, um die neue Page im Speicher zu benutzen.
2. ```
func getPAddress(int vAddress) {
	int mask = 0xFFFFFC00; // 11111111 11111111 11111100 00000000
	int pagenum = vAddress & mask;		//get higher 22 bits of vAddress
	int offset = vAddress & !mask;		//get lower 10 bits of vAddress
		if(!pagetable[pagenum][1]) { //page is not in main memory
		contact os to load page
	}
	int framenum = pagetable[pagenum][3];	//get pagenum th entry from pagetable.
	return framenumber << 10 | offset; //concat framenumber and offset
}
```
3. Jetzt funktioniert es nicht mehr, die einzelnen Teile der Adressen einfach hintereinander zu schreiben (die größte Adresse besteht also nicht nur aus Einsen). Es müsste also immer der numerische Wert der Adresse berechnet und verglichen werden, anstatt nur Bits zu verarbeiten.  

4.
 1. 00000000 00000000 000101|01 10110011 -> Pagenum = 5 -> Framenum = 0 -> Adresse = 00000000 00000000 00000001 10110011 = ‭0x000001B3‬
 2. ‭00000000 00000000 000100|00 00000100‬ -> Pagenum = 4 -> nicht present -> Pagefault
 3. 00000000 00000000 0000‭01|11 11111111‬ -> Pagenum = 1 -> Framenum = 4 -> Adresse = 00000000 00000000 00010011 11111111 = ‭0x000013FF‬
 4. 00000000 00000000 ‭000010|00 00000000‬ -> Pagenum = 2 -> nicht present -> Pagefault

## Aufgabe 3: Selbststudium: Overlaying 2/4
1. Beim Overlaying ist das Programm so strukturiert, wie ein Baum. Dabei sind die Knoten in einer Ebene von einander unabhängig. Wenn also zu wenig Hauptspeicher verfügbar ist bleibt aus jeder Ebene nur ein Programmteil im Speicher. Dies funktioniert, da immer nur eine Komponente pro Ebene auf einmal benutzt werden kann. Dabei hat das Hauptprogramm aber die Aufgabe, die einzelnen Komponenten auszutauschen, und es ist zusätzlicher Aufwand für den Programmierer nötig.
2.
