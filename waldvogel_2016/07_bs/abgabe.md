# Lösungen zum 7\. Übungsblatt

# Bamberger, Jannik und Klopfer, Fabian

## Gesamt: 19/20

## Aufgabe 1: Allgemeines 3/3

1. **Nennen Sie zwei Beispiele für die Nutzung von Threads in heutigen Systemen?**
	- Ein File-Server kann für jede ankommende Anfrage einen neuen Thread erstellen, in dem diese bearbeitet wird. Dadurch kann eine gute Ressourcennutzung gewährleistet werden, da es nur einen kleinen Overhead zum erzeugen der Threads gibt, aber dafür der Speicher besser ausgelastet ist.
	- Es können Remote-procedur-calls durch Threads einfach parallelistiert werden. So wird die Wartezeit auf die Ergebnisse bei vielen sequenziellen Aufrufen stark reduziert.
2. **Erläutern Sie kurz die Unterschiede zwischen Short-, Mid- und Longtermscheduling.**
	Longtermscheduling entscheidet, welche Prozesse überhaupt in den Prozesspool aufgenommen werden, also ausgeführt werden können. Midtermscheduling entscheidet, welche und wie viele Prozesse suspended sind und welche im Hauptspeicher liegen. Shorttermscheduling entscheidet, welcher der Ready-Prozesse wirklich ausgeführt wird.
3. **Einige Schedulingverfahren nutzen verschiedene Zeitquanta in verschiedenen Schedulingqueues. Für welche Situationen könnte dies sinnvoll sein?**
	Durch die Nutung verschiedener Zeitquanta kann zum Beispiel IO-lastigen Prozessen mehr Rechenzeit zur verfügung gestellt werden. Dadurch dass diese sowieso schnell wieder blockieren und auf IO warten bremsen sie das restliche System nicht stark aus, aber es werden die IO-Geräte besser ausgelastet, da sie so besser parallel arbeiten können. Es können außerdem durch unterschidlicher Zeitquanta Prioritäten realisiert werden. Wichtige Prozesse laufen dann einfach wenn sie dran sind entsprechend länger und sind damit wichtiger.

## Aufgabe 2: Deadlock Prevention 6/6

1. **Es ist bekannt, dass es gelegentlich zu Deadlocks bei der Ausführung dieser Prozesse kommen kann. Warum ist das so? (Begründen Sie z.B. an Hand einer Ausführungsreihenfolge, die zu einem Deadlock führt)**
	P0 führt 'get(A)' und 'get(B)' aus. Dann kommt P1 an die Reihe und führt 'get(D)' und 'get(E)' aus. Jetzt ist  P2 dran und läuft soweit es möglich ist. Bei 'get(D)' blockiert P2, da D bereits von P1 gehalten wird. Auch die anderen beiden können nicht weiterlaufen, da P0 C (gehalten von P2) benötigt und P1 B (gehalten von P0). somit sind alle Prozesse blockiert.
2. **Welche der Vorraussetzungen für einen Deadlock sind ihrer Meinung nach in diesem Beispiel vorhanden, so dass ein solcher auftreten kann? Zählen Sie diese auf.**
	- Mutual Exclusion
	- Hold and Wait
	- keine Preemption (muss es geben, sonst wäre es kein Deadlock)
	- zirkuläres Warten (P0 -> P2 -> P1 -> P0)
3. **Verändern Sie den Code so, dass Deadlocks ausgeschlossen werden können. Nutzen Sie hierfür nur schon vorhandene Ressourcen. Sperren Sie nicht alle Prozesse durch ein vorheriges Belegen einer gemeinsamen, neuen, Ressource. Begründen Sie, wieso es nun nicht mehr zu einem Deadlock kommen kann.**
	```
		void P0() {
			while(true) {
				get(C);
				get(B);
				get(A);
				//critical region
				release(A);
				release(B);
				release(C);
			}
		}
		```
	```
		void P1() {
			while(true) {
				get(B);
				get(D);
				get(E);
				//critical region
				release(D);
				release(E);
				release(B);
			}
		}
		```
	```
		void P2() {
			while(true) {
				get(C);
				get(D);
				get(F);
				//critical region
				release(C);
				release(F);
				release(D);
			}
		}
		```
	So kann es kein Zirkuläres Warten mehr geben, da immer mindestens ein Prozess alle Ressourcen bekommt die er benötigt. Somit ist ein Deadlock ausgeschlossen.
	- P0 zuerst, dann ist P2 blockiert und es kann entweder P1 oder P2 durchlaufen.
	- P1 zuerst, entscheidet der nächste Prozess darüber, wer weiterlaufen kann (bei P0 wird P0 oder P1 fertig, bei P2 wird P2 oder P1 fertig).
	- P2 zuerst, dann ist P0 blockiert und P1 oder P2 kann alle Locks aufheben.

## Aufgabe 3: Race Condition: Mutual Exclusion 6/7

1. **Warum liegt hier eine Race Condition vor?**
	Auf n wird von beiden Prozessen zugegriffen und n wird von beiden modifiziert. So kann es passieren, dass ein Prozess n liest, der zweite liest, dekrementiert und schreibt und dann der zweite dekrementiert und schreibt. Dann ist im Endeffekt nur eine dekrementierung in der Variable zu sehen, obwohl es zwei gab.
2. **Bestimmen Sie die korrekte untere und obere Grenze des Endwerts der Ausgabe der gemeinsamen Variablen anzGesamt durch dieses nebenläufige Programm. Begründen Sie ihre Ergebnisse. Nehmen Sie dafür an, dass Prozesse mit jeder beliebigen relativen Geschwindigkeit ausgeführt werden können und dass ein Wert nur verändert werden kann, nachdem er mit Hilfe eines separaten Maschinenbefehls in ein Register geladen wurde.**
	Es wird maximal ``50 + 49 * 50 / 2 = 1275`` mal inkrementiert, somit ist dies auch das Maximum. Dafür wird n vom ersten Prozess gelesen, dann läuft der zweite 49 mal durch die Schleife (bis n = 1). Nun schreibt der erste Prozess den neuen Wert von n, also 49. Damit geht das ganze erneut los, bis der erste Prozess fertig ist. Es gibt also ``50`` Inkrementierungen durch P1 und ``49 + 48 + ... + 1`` durch P2.
	Minimal kann es ``50`` sein, denn es muss n um mindestens 50 heruntergezählt werden. Dann hat aber P2 eine abweisende Schleife und macht also nichts. **1/2 Man kann für das Maximum auch alle Durchläufe nutzen. Nur die Prüfung auf das Ende der Schleife darf noch nicht passieren. Somit fehlen euch 50 Additionen**

3. **Nehmen Sie an, dass unter Anwendung der Voraussetzungen in Teil (a) eine willkürliche Anzahl dieser Prozesse parallel ausgeführt werden darf. Welche Auswirkungen hat diese Änderung auf die Bandbreite der Endwerte von anzGesamt? Begründen Sie ihre Ergebnisse.**
	Das Minimum bleibt mit der gleichen Argumentation wie bei 2. bei ``50``.
	Das Maximum ist jetzt ``inc(p, 50)``, wobei p die Anzahl Prozesse ist und ``inc()`` wie folgt definiert:
	```
	inc(1,n) := n
	inc(p,n) := 0 für p<1
	inc(p,n) := n + sum i=1 to n of inc(p-1, i)
	```
	Das liegt daran, dass für jeden Schleifendurchlauf des ersten Prozesses der zweite Prozess so oft seine Schleife durchlaufen kann, wie n-1 von P1 gesetzt wurde. Für jeden Schleifendurchlauf von P2 verhält sich aber P3 zu P2 wie P2 zu P1 und so weiter. Da in jedem Durchlauf einmal inkrementiert wird ist die Anzahl Durchläufe gleich zu dem Endwert von anzGesamt. **2/2**

4. **Lösen Sie die Race Condition durch die Nutzung eines Monitors auf.**
	```
	int anzGesamt = 1 ;
	Semaphore lock = 1 ;
	void total() {
		int count;
		for(count=0; count < read() ; decrement()) {
			semWait(lock);
			anzGesamt++;
			semSignal(lock);
		}
	}

	int main(void) {
		anzGesamt=0;
		parbegin(total(), total());
		write(anzGesamt);
		return 0;
	}

	```
	```
	monitor m;
	int n = 50;

	void decrement() {
		n--;
	}

	int read() {
		return n;
	}
	```


## Aufgabe 4: Selbststudium: Threading 4/4
**Reine User-Level-Threads waren lange Zeit die einzig möglichen Threads in Java (unter der Bezeichnung "Green Threads". Seit einiger Zeit werden Sie jedoch in der Sun Referenzimplementierung von Sun/Oracle der JVM nicht mehr unterstützt. Wodurch wurden Sie abgelöst? Wie wird Threading in der Referenz-JVM heutzutage bewerkstelligt?**
	Jeder Thread in Java hat entspricht einem native Thread, d.h. er wird vom Betriebssystem gescheduled. Die JVM bereitet alle Daten, Stack Program Counter etc. vor und lässt dann vom System einen Thread erzeugen. In diesem wird die run Methode des Java-Programms ausgeführt. Wenn diese terminiert werden unbehandelte Exceptions verarbeitet und der Thread beendet. Falls es der letzte Thread war der noch laufen sollte wird auch die VM beendet.
