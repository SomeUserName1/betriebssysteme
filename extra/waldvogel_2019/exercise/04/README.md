# 4. Übungsblatt

**Abgabe** Optional bis zum 27. November, 4:00 Uhr.

## Aufgabe 1: Verständnisfragen
1. Warum gibt es in der Grafik "Process States" in 04a#9 keinen Übergang von "Ready" zu "Blocked"?
2. Nehmen Sie an ein Prozess hat zwei Threads A und B. A setzt nun die globale Variable `g` auf den Wert `5`. Welchen Wert hat `g` für B? Begründen Sie ihre Antwort.
3. Erklären Sie anhand eines Beispiels das Producer-Consumer Problem.
4. Was ist eine atomare Operation?
5. Was sind die Unterschiede zwischen einem Monitor und einer Semaphore? Wo liegen Gemeinsamkeiten?

## Aufgabe 2: Race Condition
1. Was ist die Basis-Bedingung das eine Race Conditions auftreten kann?
2. Wie nennt man den Bereich in der eine Race Condition auftreten kann?
3. Um Race Conditions erfolgreich zu vermeiden kann man jegliche Interrupts deaktivieren. Welche Nachteile existieren bei diesem Vorgehen und in welchem Fall kann diese Methode trotzdem angewendet werden?
4. Was versteht man unter dem Begriff "Busy waiting"?
5. Betrachten Sie das folgende Programm und beantworten Sie folgende Fragen:
   1. Bestimmen Sie die korrekte untere und obere Grenze des Endwerts der Ausgabe der gemeinsamen Variablen `anzGesamt` durch dieses nebenläufige Programm. Begründen Sie ihre Ergebnisse. Nehmen Sie dafür an, dass Prozesse mit jeder beliebigen relativen Geschwindigkeit ausgeführt werden können und dass ein Wert nur verändert werden kann, nachdem er mit Hilfe eines separaten Maschinenbefehls in ein Register geladen wurde.
   2. Nehmen Sie an, dass unter Anwendung der Voraussetzungen in Teil (1) eine willkürliche Anzahl dieser Prozesse parallel ausgeführt werden darf. Welche Auswirkungen hat diese Änderung auf die Bandbreite der Endwerte von `anzGesamt`?  Begründen Sie ihre Ergebnisse.

```
const int n=50;
int anzGesamt;

void total(){
   int count;
   for(count=0; count < n; count++) {
      if (count % 2 == 0)
         anzGesamt++;
      else
         anzGesamt--;
   }
}

int main(void) {
   anzGesamt=0;
   parbegin(total(), total());
   write(anzGesamt);
   return 0;
}
```

**Hinweis:** `parbegin(P1, P2, ..., Pn)` bedeutet: Suspendiere die Ausführung des Main-Programms, starte die Prozeduren `P1, P2, ..., Pn` nebenläufig und führe das Main-Programm weiter aus, nachdem alle `P1, P2, ..., Pn` terminiert sind.

## Aufgabe 3: Semaphoren
Allgemeine Semaphoren (mit höher möglichen Werten als 1) können durch die Nutzung binärer Semaphoren realisiert werden.
Vervollständigen Sie den Pseudocode aus dem unteren Code-Beispiel 1 für allgemeine Semaphoren.
Wobei `aSemDown()` und `aSemUp()` den Operationen `semDown()` und `semUp()` von binären Semaphoren entsprechen soll.

#### Code-Beispiel 1:
```
aSemaphore(Size) \\Initialisiere die Semaphore mit der gegebenen Größe
{
	aSemDown()
	{
		\\ToDo: Semaphorenverhalten nachstellen durch binäre Semaphoren
	}
	aSemUp()
	{
		\\ToDo: Semaphorenverhalten nachstellen durch binäre Semaphoren
	}
}
```

Folgender Ablauf (Beispiel 2) soll anschließend vollständig ohne Mithilfe anderer Funktionen (die Beispielsweise s erhöhen) möglich sein.

#### Code-Beispiel 2:
```
aSemaphore s = 20
for (int i = 0; i < 20; ++i)
	aSemDown(s);
```

