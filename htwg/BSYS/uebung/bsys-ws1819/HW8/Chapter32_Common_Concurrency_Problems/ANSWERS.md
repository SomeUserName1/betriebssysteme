# Answers

1. ###### First let’s make sure you understand how the programs generally work, and some of the key options. Study the code in `vector-deadlock.c`, as well as in `main-common.c` and related files. Now, run `./vector-deadlock -n 2 -l 1 -v`, which instantiates two threads (`-n 2`), each of which does one vector add (`-l 1`), and does so in verbose mode (`-v`). Make sure you understand the output. How does the output change from run to run?

    -  Das Programm `vector-deadlock.c` addiert nebenläufig zwei Vektoren miteinander.

    -  Der Programmaufruf `./vector-deadlock -n 2 -l 1 -v` liefert folgende
       Ausgabe:

       ```
       ./vector-deadlock -n 2 -l 1 -v
       ->add(0, 1)
       <-add(0, 1)
                    ->add(0, 1)
                    <-add(0, 1)
       ```

    -  Ruft man das Programm mit `watch` folgendermaßen auf:
       `watch -n 0.1 ./vector-deadlock -n 2 -l 1 -v` so ändert sich manchmal
       die Ausführungsreihenfolge der beiden Threads. Bei einer Änderung der
       Ausführungsreihenfolge ergibt sich folgende Ausgabe des Programms:

       ```
       ./vector-deadlock -n 2 -l 1 -v
                    ->add(0, 1)
                    <-add(0, 1)
       ->add(0, 1)
       <-add(0, 1)

       ```

2.  ###### Now add the `-d` flag, and change the number of loops (`-l`) from 1 to higher numbers. What happens? Does the code (always) deadlock?

    -  Ob das Programm `vector-deadlock.c` "deadlocked" ist unabhängig von der
       Anzahl an Loops (`-l`).

    -  Mit dem Programmaufruf `while true; do ./vector-deadlock -n 2 -l 1 -d -v; done;`
       lässt sich der Deadlock im Code relativ gut reproduzieren. Daher ist es
       potentiell möglich, dass ein Deadlock im Programm auftritt, auch wenn
       es in den meisten Fällen ordnungsgemäß ausgeführt wird.

    -  Thread 0 (`T0`) möchte `vector_add(v1, v2)` ausführen und Thread 1 (`T1`)
       `vector_add(v2, v1)`. Nehmen wir an, `T0` "locked" `v1` und anschließend
       tritt ein Kontextwechsel auf, welcher zu `T1` wechselt. `T1` lockt nun `v2`
       und legt sich anschließend schlafen, da er den Lock von `v1` nicht anfordern
       kann, weil dieser schon von `T0` "gelocked" wurde. Nun tritt wieder ein
       Kontextwechsel auf, der wieder zu `T0` wechselt. `T0` legt sich nun ebenfalls
       schlafen, da `v2` nun von `T1` "gelocked" wurde. Keiner der beiden Threads
       wird jemals wieder geweckt werden, weshalb das Programm sich nun in einem
       Deadlock befindet.


3.  ###### How does changing the number of threads (`-n`) change the outcome of the program?

    -  Der Programmaufruf `./vector-deadlock -n 3 -l 1 -v` liefert folgende
       Ausgabe:

       ```
       ./vector-deadlock -n 3 -l 1 -v
       ->add(0, 1)
       <-add(0, 1)
                    ->add(0, 1)
                    <-add(0, 1)
                                 ->add(0, 1)
                                 <-add(0, 1)
       ```

       Für jeden weiteren Thread wird eine zusätzliche Spalte in der Ausgabe
       des Programms hinzugefügt. Damit erhöht sich auch gleichzeitig die Anzahl
       an verschiedenen Ausführungsmöglichkteiten.

    ###### Are there any values of `-n` that ensure no deadlock occurs?

    -  Ja, für `n = 1` kann kein Deadlock auftreten, da kein anderer Thread
       existiert, welcher die Ressourcen in umgekehrter Reihenfolge anfordern
       möchte (**Circular Wait** ist damit ausgeschlossen). Daher kann es zu
       keinem Deadlock kommen.

    -  Auch für `n <= 0` kann kein Deadlock auftreten, was jedoch nicht sehr viel
       Sinn macht, da das Programm somit nichts mehr tut, außer sich direkt zu
       beenden.

4.  ###### Now examine the code in `vector-global-order.c`. First, make sure you understand what the code is trying to do; do you understand why the code avoids deadlock?

    -  Der Code in `vector-global-order.c` führt eine Lockreihenfolge ("lock
       ordering") über die Adressen der Vektoren ein. Dadurch wird das zirkuläre
       Warten (**Circular Wait**) verhindert, wodurch kein Deadlock mehr
       auftreten kann.

    ###### Also, why is there a special case in this `vector_add()` routine when the source and destination vectors are the same?

    -  Wenn zwischen diesem Fall und den anderen Fällen nicht unterschieden werden
       würde und man versuchen würde erst `v_src` und dann `v_dst` zu locken
       (bzw. umgekehrt), würde der zweite Lock den aufrufenden Thread schlafen
       legen, da es sich hierbei um den selben Lock handelt und dieser Thread ihn
       bereits hält. Dadurch würde wieder ein Deadlock auftreten, da niemand den
       schlafenden Thread wieder wecken würde.

5.  ###### Now run the code with the following flags: `-t -n 2 -l 100000 -d`. How long does the code take to complete?

    -  Der Programmaufruf `./vector-global-order -n 2 -l 100000 -d -t` benötigt
       zwischen 0.04s und 0.17s  
       (siehe: `src/measurements/vector-global-order_n_2_l_100000_loops_measurement.txt`).
       Es wurden hierbei 100x Messungen des Programms vorgenommen.

    ###### How does the total time change when you increase the number of loops, or the number of threads?

    -  Wenn man die Anzahl der Loops (`-l`) erhöht, benötigt das Programm länger
       als zuvor. Das ist logisch, da nun `vector_add()` mehrmals als zuvor von
       den Threads aufgrufen wird.

    -  Wenn man die Anzahl der Threads (`-n`) erhöht, erhöht sich ebenfalls die
       Ausführungszeit des Programms. Dies liegt daran, dass das `-p`-Flag nicht
       gesetzt wurde, weshalb alle Threads nur auf zwei Vektoren (`v1` und `v2`)
       arbeiten. Dadurch müssen Threads nun auf die Freigabe der Locks von `v1`
       und `v2` warten, falls ein anderer Thread diese gerade hält.

6.  ###### What happens if you turn on the parallelism flag (`-p`)?

    -  Jeder Thread arbeitet mit anderen Vektoren, wodurch alle Threads nun
       wirklich parallel ausgeführt werden können, da keiner auf die Freigabe
       von Locks eines anderen Threads warten muss.

    ###### How much would you expect performance to change when each thread is working on adding different vectors (which is what `-p` enables) versus working on the same ones?

    -  Der Programmaufruf `./vector-global-order -n 3 -l 100000 -d -t` liefert
       folgende Ausgabe:

       ```
       ./vector-global-order -n 3 -l 100000 -d -t
       Time: 0.20 seconds
       ```

       wohingegen der Programmaufruf `./vector-global-order -n 3 -l 100000 -d -p -t`
       folgende Ausgabe liefert:

       ```
       ./vector-global-order -n 3 -l 100000 -d -p -t
       Time: 0.05 seconds
       ```

    -  Die Performace erhöht sich drastisch, da die Threads nun wirklich parallel
       arbeiten und nicht mehr aufeinander warten müssen.

    -  Siehe auch `src/measurements/vector-global-order_n_2_l_100000_p_measurement.txt`.

7.  ###### Now let’s study `vector-try-wait.c`. First make sure you understand the code. Is the first call to `pthread_mutex_trylock()` really needed?

    -  Ja, der Aufruf von `pthread_mutex_trylock(&v_dst->lock)` ist notwendig,
       da sonst `dst` nicht gelocked werden würde.

    ###### Now run the code. How fast does it run compared to the global order approach?

    -  Siehe `src/measurements/vector-try-wait_n_2_l_100000_measurement.txt` (100 Messungen).

    -  Im Vergleich zum `vector-global-order.c` Programm, braucht `vector-try-wait.c`
       länger für die Ausführung eines gleichen Programmaufrufs. Die Ausführungszeit
       liegt hierbei für den Programmaufruf `./vector-try-wait -n 2 -l 100000 -d -t`
       zwischen 0.05s und 0.47s. Auf kleine Werte wie 0.05s kommt `vector-try-wait.c`
       dabei nur selten.

    ###### How does the number of retries, as counted by the code, change as the number of threads increases?

    -  Je größer die Anzahl an Threads (`-n`) wird desto größer wird auch die
       Anzahl an Wiederholungen ("retries"). Hierbei wurde das `-p`-Flag natürlich
       nicht mit angegeben.

8.  ###### Now let’s look at `vector-avoid-hold-and-wait.c`. What is the main problem with this approach?

    -  Das hauptsächliche Problem an `vector-avoid-hold-and-wait.c` ist, dass
       die Nebenläufigkeit im Gegensatz zu den anderen Versionen, verringert
       wird.

    -  Man muss alle Locks die gehalten werden müssen kennen,
       sowie diese im Voraus halten.

    ###### How does its performance compare to the other versions, when running both with `-p` and without it?

    -  Siehe `src/measurements/vector-try-wait_n_2_l_100000_measurement.txt`
       sowie `src/measurements/vector-try-wait_n_2_l_100000_p_measurement.txt`.
       Es wurden wieder 100 Messungen getätigt.

    -  Für den Programmaufruf `./vector-try-wait -n 2 -l 100000 -d -t` benötigt
       das Programm zwischen 0.05s und 0.47s. Das Programm verhält sich hierbei
       sehr ähnlich wie `vector-try-wait.c`.

    -  Für den Programmaufruf `./vector-try-wait -n 2 -l 100000 -d -p -t`
       benötigt das Programm zwischen 0.02s und 0.08s. Das Programm verhält sich
       hierbei ähnlich wie `./vector-gobal-order.c`.

9.  ###### Finally, let’s look at `vector-nolock.c`. This version doesn’t use locks at all; does it provide the exact same semantics as the other versions? Why or why not?

    -  Die Benutzung der `vector_add()`-Funktion bleibt gleich, aber die
       Funktionsweiße, wie die Vektoren addiert werden ändert sich. In diesem
       Fall wird bewusst auf Locks verzichtet und dafür eine atomare Funktion
       (`fetch_and_add()`) entworfen, welche die Vektoren atomar addieren kann.
       Dadurch können einerseits keine Deadlocks auftreten und anderenseits
       werden durch die atomarität "Data-Races" vermieden.

    -  Bei der Verwendung von `vector_add()`, sollte man sich der Funktionsweiße
       bewusst sein.

10.  ###### Now compare its performance to the other versions, both when threads are working on the same two vectors (no `-p`) and when each thread is working on separate vectors (`-p`). How does this no-lock version perform?

     -  Siehe `src/measurements/vector-nolock_n_2_l_100000_measurement.txt`
        sowie `src/measurements/vector-nolock_n_2_l_100000_p_measurement.txt`.

     -  Für den Programmaufruf `./vector-nolock -n 2 -l 100000 -d -t` benötigt
        das Programm zwischen 0.49s und 1.38s. Auch hier sind kleine Werte wie
        0.49 eher eine Seltenheit.

     -  Für den Programmaufruf `./vector-nolock -n 2 -l 100000 -d -p -t`
        benötigt das Programm zwischen 0.14s und 0.26s.

     -  Das Programm `vector-nolock.c` ist somit langsamer als die anderen
        Versionen, egal ob das `-p`-Flag mit angegeben wurde oder nicht.
