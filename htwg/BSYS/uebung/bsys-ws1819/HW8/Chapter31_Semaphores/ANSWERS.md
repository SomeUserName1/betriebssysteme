# Answers

1.  ###### The first problem is just to implement and test a solution to the **fork/join problem**, as described in the text. Even though this solution is described in the text, the act of typing it in on your own is worthwhile; even Bach would rewrite Vivaldi, allowing one soon-to be master to learn from an existing one. See `fork-join.c` for details. Add the call `sleep(1)` to the child toensure it is working.

    -  Siehe: `src/fork-join.c`.

2.  ###### Let’s now generalize this a bit by investigating the **rendezvous problem**. The problem is as follows: you have two threads, each of which are about to enter the rendezvous point in the code. Neither should exit this part of the code before the other enters it. Consider using two semaphores for this task, and see `rendezvous.c` for details.

    -  Siehe: `src/rendezvous.c`.

3.  ###### Now go one step further by implementing a general solution to **barrier synchronization**. Assume there are two points in a sequential piece of code, called `P1` and `P2`. Putting a barrier between `P1` and `P2` guarantees that all threads will execute `P1` before any one thread executes `P2`. Your task: write the code to implement a `barrier()` function that can be used in this manner. It is safe to assume you know N (the total number of threads in the running program) and that all N threads will try to enter the barrier. Again, you should likely use two semaphores to achieve the solution, and some other integers to count things. See `barrier.c` for details.

    -  Siehe: `src/barrier.c`.

4.  ###### Now let’s solve the **reader-writer problem**, also as described in the text. In this first take, don’t worry about starvation. See the code in `reader-writer.c` for details. Add `sleep()` calls to your code to demonstrate it works as you expect.

    -  Siehe: `src/reader-writer.c`.

    ###### Can you show the existence of the starvation problem?

    -  Nehmen wir folgendes Szenario an:

       1.  Es befinden sich bereits Reader im kritischen Bereich.

       2.  Wenn nun ein Writer-Thread (`WT`) erzeugt wird, wird dieser blockiert,
           da der Lock noch durch die Reader gehalten wird.

           Werden nun immer wieder neue Reader-Threads erzeugt, bevor der letzte
           Reader den kritischen Bereich verlässt und somit den Lock frei gibt,
           hat der `WT` keine Möglichkeit jemals den kritischen Bereich zu
           betreten und verhungert somit.

       3.  Erst wenn keine neuen Reader-Threads mehr erzeugt werden und der
           letzte Reader der kritischen Bereich verlässt, wird `WT` wieder
           geweckt und kann den kritischen Bereich betreten.

5.  ###### Let’s look at the **reader-writer problem** again, but this time, worry about starvation. How can you ensure that all readers and writers eventually make progress? See `reader-writer-nostarve.c` for details.

    -  Siehe: `src/reader-writer-nostarve.c`.

    -  Um das Verhungern von Threads zu verhindern, baut man eine weitere
       Semaphore (`turnstile`) in das Programm ein:

       Wenn der kritische Bereich durch eine gewisse Anzahl an Readern belegt
       ist, und ein Writer ebenfalls gerne Zugriff auf den kritischen
       Bereich hätte, so locked er `turnstile` um weitere Reader daran zu
       hindern den kritischen Bereich zu betreten. Der Bereich bleibt nun
       solange für die Reader gelocked, bis der Writer den kritischen Bereich
       betreten kann (sprich wenn alle anderen Reader welche sich noch im
       kritischen Bereich befinden ihre Aktionen abgeschlossen haben) und diesen
       ausgeführt hat. Anschließend gibt der Writer den kritischen Bereich wieder
       für die Reader frei. Danach wird einer der wartenden Reader wieder geweckt,
       welcher somit den kritischen Bereich für die Reader reservieren kann,
       bis ein neuer Writer Zugriff haben möchte.

6.  ###### Use semaphores to build a **no-starve mutex**, in which any thread that tries to acquire the mutex will eventually obtain it. See the code in `mutex-nostarve.c` for more information.

    -  Siehe: `src/mutex-nostarve.c`.

    ###### How can you show that a thread does not starve when attempting to acquire this mutex you build?

    -  Nehmen wir folgendes Szenario an:

       1.  Es existieren **endlich** viele Threads.

       2.  Es befinden sich bereits mehrere Threads in Warteraum 1 (`W1`).

       3.  Wenn nun einer von den Threads, welche sich in `W1` befinden, den
           Warteraum 2 (`W2`) betritt (Instruktion in Zeile 29 wurde ausgeführt:
           `sem_wait(&m->turnstile1)`), hält dieser Thread (`T1`) nun den Lock
           `turnstile1`.

           Wenn der Scheduler nun einen Kontextwechsel zu einem der Theads in
           `W1` durchführt, legt sich dieser in Zeile 29 nun schlafen. Dies gilt
           auch für alle weiteren Threads aus `W1` die noch vor `T1` gescheduled
           werden.

           Sobald `T1` wieder vom Scheduler ausgewählt wurde und dieser genügend
           Zeit hat, die Instruktion in Zeile 39 (`sem_post(&m->turnstile1)`)
           auszuführen, wird einer der auf `turnstile1` wartenden Threads geweckt,
           welcher gleich wie `T1` vorgeht. Dies ist solange der Fall, bis die
           Anzahl der Threads in `W1` gleich 0 ist. Kommt in der Zwischenzeit
           einer der Threads in `W2` erneut dran, so legt dieser sich in Zeile 42
           schlafen und hält damit den Lock auf `turnstile2`. Keiner der Threads
           in `W2` kann also fortfahren, bis `turnstile2` wieder freigeben wurde.

           Da es nur endlich viele Threads gibt, kommt irgendwann ein Thread (`T2`)
           aus `W1` in den Warteraum 2, wobei dann die Anzahl an Threads in `W1`
           0 beträgt. Dieser Thread gibt dann den Lock von `turnstile2` frei,
           wodurch die Threads in `W2` nun fortfahren könnten. Der Thread `T2`,
           welcher `turnstile2` freigeben hat, hält jedoch weiterhin noch den Lock
           von `turnstile1`, um Threads welche fortfahren konnten und ein weiteres
           mal `ns_mutex_acquire()` aufrufen, daran zu hindern, `W1` zu verlassen,
           anderenseits könnte es wieder zu verhungern von Threads kommen.

       4.  Jeder Thread, welcher die `ns_mutex_release()`-Funktion ausgeführt hat,
           weckt einen anderen Thread in `W2`, wodurch dieser ebenfalls die
           Möglichkeit hat den kritischen Bereich auszuführen.

           Sobald der letzte Thread aus `W2` den kritischen Breich ausgeführt hat
           und `ns_mutex_release()`-Funktion aufgrufen hat, lässt dieser
           `turnstile2` gelocked und gibt nun `turnstile1` wieder frei, wodurch
           die Threads die in `W1` sind wieder `W2` betreten können.

           Hierdurch befinden wir uns quasi wieder im Anfangsstadium (Es sind
           mehrere Threads in `W1` und ein Thread in `W2` öffnet `turnstile1`
           und `turnstile2` ist gelocked).

    -  Dadurch, das bei einem erneuten Aufruf von `ns_mutex_acquire()` eines
       bereits durchgelaufenen Threads (sprich der kritische Bereich wurde
       ausgeführt und `ns_mutex_release()` wurde aufgrufen), der Thread bei
       `turnstile1` blockiert, hat jeder Thread, welcher noch nicht an der Reihe
       war, die Chance den kritischen Bereich auszuführen, bevor durchgelaufene
       Threads erneut die Möglichkeit haben den kritischen Bereich auszuführen.
