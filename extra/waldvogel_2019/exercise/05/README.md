# 4. Übungsblatt

**Abgabe** Optional bis zum 4. Dezember, 4:00 Uhr.

## Aufgabe 1: The Dining Philosophers Problem (DPP)
1. Bringen Sie die Begriffe Starvation und Deadlock in Relation.
2. Betrachten Sie das folgende Code-Beispiel zur Lösung des DPP aus dem Buch
"Operating Systems - Design and Implementation" und erklären Sie warum der
`state` auf `HUNGRY` gesetzt werden muss.

```
#define N 5					// number of philosophers
#define LEFT (i+N-1)%N	// number of i's left neighbor
#define RIGHT (i+1)%N	// number of i's right neighbor
#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef int semaphore;
int state[N];
semaphore mutex = 1;
semaphore s[N];

// i: philosopher number, from 0 to N-1

void philosopher(int i)
{
	while (TRUE){
		think();
		take_forks(i);
		eat();
		put_forks(i);
	}
}

void take_forks(int i)
{
	down(&mutex);			// enter critical region
	state[i] = HUNGRY;	// Warum?
	test(i);
	up(&mutex);				// exit critical region
	down(&s[i]);			// block if forks were not acquired
}

void put_forks(i)
{
	down(&mutex);
	state[i] = THINKING;
	test(LEFT);
	test(RIGHT);
	up(&mutex);
}

void test(i)
{
	if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
		state[i] = EATING;
		up(&s[i]);
	}
}
```

## Aufgabe 2: The Readers and Writers Problem
Erklären Sie das Readers and Writers Problem anhand des folgenden Code Beispiels
und welche Nachteile diese Implementierung haben könnte.

```
typedef int semaphore;
semaphore mutex = 1;
semaphore db = 1;
int rc = 0;

void reader(void)
{
	while (TRUE){
		down(&mutex);
		rc++;
		if (rc == 1)
			down(&db);
		up(&mutex);
		read_data_base();
		down(&mutex);
		rc--;
		if (rc == 0)
			up(&db);
		up(&mutex);
		use_data_read(); /* noncritical region */
	}
}

void writer(void)
{
	while (TRUE){
		think_up_data(); /* noncritical region */
		down(&db);
		write_data_base();
		up(&db);
	}
}
```

## Aufgabe 3: Scheduling
1. Erklären Sie den Unterschied von Non-Preemptive und Preemptive Scheduling Algorithmen.
2. Tanenbaum und Woodhull postulieren Fairness als ein Ziel von Scheduling Algorithmen. Diskutieren Sie diese Aussage.
3. Diskutieren Sie folgende Aussage: "Je höher der Throughput eines Scheduling Algorithmus ist, desto besser ist er".
4. Welche Voraussetzung muss gelten um Shortest-Job-First effektiv anwenden zu können?
5. Über die Länge des Quantum kann die Performance von Round-Robin beeinflusst werden. Erläutern Sie wie man das Optimum erreichen kann.
6. Round-Robin behandelt alle Prozesse gleich was bei Interaktiven Systemen nicht wünschenswert ist. Erläutern Sie eine mögliche Lösung und diskutieren Sie etwaige Probleme.

