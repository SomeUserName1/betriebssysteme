# Lösungen zum 5\. Übungsblatt

# Klopfer, Fabian und Bamberger, Jannik

## Gesamt: 11/20

## Aufgabe 1: Allgemein 6/9

1. **Erklären Sie, mit eigenen Worten, worum es sich bei einem Deadlock handelt, und welche Kontermaßnahmen man ergreifen kann?**

	Bei einem Deadlock ist eine Menge von Prozessen durch sich selbst permanent blockiert. Das heißt die Prozesse haben Ressourcen so angefordert, dass sie jeweils auf einen anderen Prozess aus der Menge warten. So kann kein Prozess die Ressourcen freigeben, da jeder auf einen Anderen wartet. Um Deadlocks zu verhindern gibt es verschiedene Möglichkeiten:
		- Prevention: Es wird, bevor Ressourcen angefordert werden geprüft, ob es zu einem Deadlock kommen kann.
		- Avoidance: Es wird während der Ausführung überprüft, ob es zu einem Deadlock kommt und es werden entsprechende Änderungen vorgenommen.
		- Detection: Alle Ressourcenzugriffe werden gewährt. Es wird immer wieder geprüft, ob es zu einem Deadlock kam. Dieser wird dann aufgelöst.

2. **Welche Bedingungen müssen erfüllt sein, damit es zu einem Deadlock kommen kann?**

	- Exklusiver Zugriff auf Ressourcen
	- Halten von Ressourcen und auf Weitere warten
	- Ressourcen die gehalten werden können dem Prozess nicht weggenommen werden
	- Zirkuläres Warten: Prozesse warten in einem geschlossenen Kreis aufeinander

3. **Was sind die Unterschiede zwischen einem Monitor und einer Semaphore? Wo liegen Gemeinsamkeiten?**

	Ein Monitor steuert den Zugriff auf eine Datenstruktur. Er beinhaltet Prozeduren, um die Datenstruktur zu bearbeiten. Es kann immer nur ein Prozess auf einmal auf die Daten zugreifen. Eine Semaphore hingegen ist ein allgemeines Mittel zur Zugriffskontrolle. Die Semaphore überlässt dem Programmierer die Verantwortung, an den richtigen Stellen die Semaphore zu benutzen. Bei dem Monitor wird automatisch jeder Zugriff auf die Datenstruktur als kritischer Abschnitt betrachtet. **Gemeinsamkeiten? 1/2**

4. **Beim Messagepassing kann zwischen jeweils Arten des Sendens und Empfangens unterschieden werden. Welchen? Wozu dienen Sie?**

	- *direkte Addressierung*: Es wird ein Prozess angegeben, von dem empfangen/zu dem gesendet werden soll. Es müssen beide Prozesse den jeweils anderen kennen. Es ist damit möglich, parallele Prozesse effizient miteinander kommunizieren zu lassen. Einen "Server" der Anfragen von unbekannten Prozessen akzeptiert kann man so allerdings nicht realisieren.
	- *indirekte Addressierung*: Es gibt eine geteilte Datenstruktur, auf die beide Prozesse zugriff haben. So können auch unbekannte Prozesse miteinander kommunizieren. Es ist möglich Nachrichten an mehr als einen Prozess zuzustellen. **0/2**

## Aufgabe 2: Semaphoren 1.5/4
 **Allgemeine Semaphoren (mit höher möglichen Werten als 1) können durch die Nutzung binärer Semaphoren realisiert werden. Verfollständigen Sie den Pseudocode aus Codebeispiel 1 für allgemeine Semaphoren. Wobei aSemWait() und aSemSignal() den Operationen semWait() und semSignal() von binären Semaphoren entsprechen soll. Folgener Ablauf soll anschließend vollständig ohne Mithilfe anderer Funktionen (die Beispielsweise s erhöhen) möglich sein**

```
aSemaphore(Size)
{
	int cnt = Size;
	Semaphore c_lock; //binäre Semaphore
	Semaphore lock; //binäre Semaphore

	aSemWait() {
		semWait(lock);
		cnt--;
		if(cnt < 0) { // keine weiteren parallellen Zugriffe => Sperren
			semSignal(lock);
			semWait(c_lock);
		}
		semSignal(lock);
	}

	aSemSignal() {
		semWait(lock);
		cnt++;
		if(cnt > 0) { // neuer Platz frei => löse Sperre
			semSignal(c_lock);
		}
		semSignal(lock);
	}
}
```
**Bei eurer Lösung werden nur c_locks entsperrt, wenn cnt > 0 ist. Problem daran: Warten muss ein Aufrufer nur dann, wenn cnt aufgebraucht ist (< 0). Signale werden nur gesendet, wenn cnt > 0 ist**
**Ergebnis:**
**initialisiere mit 0**
**4 mal aSemWait => cnt == -4, alle müssen warten**
**4 mal aSemSignal => cnt == 0, kein Signal gesendet, alle warten noch**
**Ändert ihr die Abfrage bei aSemSignal in < 0, so wäre das Problem schonmal behoben. Aber auch ohne das if wäre es schon möglich**
**Problem zwei ist die Möglichkeit Signale verpuffen zu lassen, da der wirkliche Sperrlock zwischen semSignal(lock) semWait(c_lock) aufgehoben wird. Somit: cnt = 0, zwei Mal wait, beide halten vor semWait(c_lock) an. Dann kommen signale, die korrekt erhöhen würden. Aber: Die verpuffen, weil keiner wartet.**
**Falls die Grundidee auf dem Stallingsabgeschrieben ist und ihr versucht habt die "eine Zeile" zu finden, die ihr ändern müsst: Da liegt das Problem. Das Stallingsbeispiel hat zwei große Probleme, weswegen diese Aufgabe nicht verwendet wurde :)** 

## Aufgabe 3: Monitore 3.5/7

1. **Entwerfen Sie, im Pseudocode, ein System, diesem Motor effizient und automatisch zu steuern, so dass möglichst wenig Rückstau auf beiden Seiten entsteht. Verwenden Sie für ihre Lösung einen Monitor.**

	```
	/* program golden gate bridge*/

	/*
	 * Richtung:   2         1
	 *             v         ^
	 * Spur:      |1|2|3|4|5|6|
	 * Position:    0 1 2 3 4
	 */

	monitor m;
	int dir1_queue;
	int dir2_queue;
	int direction1_cnt;
	int direction2_cnt;
	int position;
	cond direction1, direction2;

	/**
	 * Auto will auf die Brücke in Richtung d fahren. Prüfe, ob die Trennwand verschoben werden muss
	 * */
	void enter(direction d) {
		if(!free(d)) { //kein Platz => Warten
			d == 1 ? dir1_queue++ : dir2_queue++; //Ein Auto mehr in der Warteschlange
			cwait(d == 1 ? direction1 : direction2); //Pausieren
			d == 1 ? dir1_queue-- : dir2_queue--; //Warten zu ende
		}
		d == 1 ? direction1_cnt++ : direction2_cnt++; //Brücke befahren
		drive(); **Das sollte nicht im Monitor sein, denn damit gehört es zur kritischen Sektion und kann nur von einem gleichzeitig genutzt werden. Ergo: Ihr habt immer nur genau ein Auto auf der Brücke. Ein Wenig Einsam.**
	}

	void leave(direction d) {
		d == 1 ? direction1_cnt-- : direction2_cnt--; //Brücke wurde verlassen
		if(free(d)) { //Gibt es neue Möglichkeiten die Barriere zu verschieben?
			csignal(d == 1 ? direction1 : direction2); //Es hat Platz => nächstes Auto
		}
	}

	int free(direction d) {
		if((200 + (4 - position) * 200) - direction1_cnt &&
		 	dir1_queue < dir2_queue) {
			//dir1 hat 200 Plätze und eine kürzere Warteschlange => Barriere verschieben
			if(position > 0) { //Barriere kann verschoben werden **Kommt keine Prüfung, ob da noch Autos in der Spur sind?**
				position--;
				moveBarrier(position); //verschieben

				int len;
				if(d == 2) len = dir2_queue < 200 ? dir2_queue : 199; // in Richtung d kommt noch ein Auto dazu
				else len = dir2_queue <= 200 ? dir2_queue : 200:
				for(1..len) csignal(direction2); //Warteschlage auflösen
			}
		} else if((200 + position * 200) - direction2_cnt && dir1_queue > dir2_queue) {
			//dir2 hat 200 Plätze und eine kürzere Warteschlange => Barriere verschieben
			if(position < 4) { //Barriere kann verschoben werden 
				position++;
				moveBarrier(position); //verschieben

				int len;
				if(d == 1) len = dir1_queue < 200 ? dir1_queue : 199; // in Richtung d kommt noch ein Auto dazu
				else len = dir1_queue <= 200 ? dir1_queue : 200;
				for(1..len) csignal(direction1); //Warteschlange auflösen
			}
		}

		if(d == 1) {
			return 200 + (4 - position) * 200 > direction1_cnt; //Platz in dir1?
		} else {
			return 200 + position * 200 > direction2_cnt;       //Platz in dir2?
		}
	}

	//init
	{
		dir1_queue = 0, dir2_queue = 0,
		direction1_cnt = 0, direction2_cnt = 0,
		position = 2; // Mitte
	}

	```

	```
	void enter1() {
		while(true) {
			enter(1);
		}
	}

	void leave1() {
		while(true) {
			leave(1);
		}
	}

	void enter2() {
		while(true) {
			enter(2);
		}
	}

	void leave2() {
		while(true) {
			leave(2);
		}
	}

	void main() {
		parbegin(enter1, leave1, enter2, leave2);
	}
	```

2. **Kann es in ihrer Lösung zu Deadlock kommen? Begründen Sie.**
	Nein, es kann keinen Deadlock geben, da es keine Zirkulären Beziehungen gibt. Für jedes neue Auto wird zuerst geprüft, ob es einen Platz gibt. Falls nicht wartet das Auto, blockiert dabei aber keine anderen neu ankommenden Autos.
