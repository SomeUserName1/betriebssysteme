# Answers

1.  ###### To start things off, let’s learn how to use the simulator to study how to build an effective multi-processor scheduler. The first simulation will run just one job, which has a run-time of 30, and a working-set size of 200. Run this job (called job ’a’ here) on one simulated CPU as follows: `./multi.py -n 1 -L a:30:200`. How long will it take to complete? Turn on the `-c` flag to see a final answer, and the `-t` flag to see a tick-by-tick trace of the job and how it is scheduled.

    -  Um den Job `a` auszuführen werden 30 Zeiteinheiten (ZE) benötigt, da
       dieser eine Joblaufzeit von 30 besitzt und sich keine anderen Jobs im System
       befinden, zwischen denen der Scheduler wechseln könnte.

       Der Programmaufruf `./multi.py -n 1 -L a:30:200 -c -t` liefert folgende
       Ausgabe:

       ```
       $ ./multi.py -n 1 -L a:30:200 -c -t

       ARG seed 0
       ARG job_num 3
       ARG max_run 100
       ARG max_wset 200
       ARG job_list a:30:200
       ARG affinity
       ARG per_cpu_queues False
       ARG num_cpus 1
       ARG quantum 10
       ARG peek_interval 30
       ARG warmup_time 10
       ARG cache_size 100
       ARG random_order False
       ARG trace True
       ARG trace_time False
       ARG trace_cache False
       ARG trace_sched False
       ARG compute True

       Job name:a run_time:30 working_set_size:200

       Scheduler central queue: ['a']

       0   a      
       1   a      
       2   a      
       3   a      
       4   a      
       5   a      
       6   a      
       7   a      
       8   a      
       9   a      
       ----------
       10   a      
       11   a      
       12   a      
       13   a      
       14   a      
       15   a      
       16   a      
       17   a      
       18   a      
       19   a      
       ----------
       20   a      
       21   a      
       22   a      
       23   a      
       24   a      
       25   a      
       26   a      
       27   a      
       28   a      
       29   a      

       Finished time 30

       Per-CPU stats
           CPU 0  utilization 100.00 [ warm 0.00 ]
       ```

2.  ###### Now increase the cache size so as to make the job’s working set (size=200) fit into the cache (which, by default, is size=100); for example, run `./multi.py -n 1 -L a:30:200 -M 300`. Can you predict how fast the job will run once it fits in cache? (hint: remember the key parameter of the warm rate, which is set by the `-r` flag) Check your answer by running with the solve flag (`-c`) enabled.

    -  Hier wird ein Job `a` mit einer Laufzeit von 30 erstellt. Die
       Cache-Warmup-Zeit beträgt 10 ZE und die Cache-Warm-Rate beträgt 2. Die
       Cache-Warm-Rate gibt an wie viel schneller der Job abgearbeitet werden
       kann, sobald der Cache "warm" ist. In diesem Fall kann der Job dann
       doppelt, so schnell abgearbeitet werden, sobald der Cache "warm" ist.

       Mit Hilfe dieser Informationen können wir die Laufzeit von Job `a`
       folgendermaßen bestimmen:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Joblaufzeit = Cache-Warmup-Zeit + (Laufzeit des Jobs - Cache-Warmup-Zeit) / Cache-Warm-Rate**  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**= 10 ZE + (30 ZE - 10 ZE) / 2 = 10 ZE + 20 ZE / 2 = 10 ZE + 10 ZE = 20 ZE**

       Der Programmaufruf `./multi.py -n 1 -L a:30:200 -M 300 -c -t` liefert
       folgende Ausgabe:

       ```
       $ ./multi.py -n 1 -L a:30:200 -M 300 -c -t

       ARG seed 0
       ARG job_num 3
       ARG max_run 100
       ARG max_wset 200
       ARG job_list a:30:200
       ARG affinity
       ARG per_cpu_queues False
       ARG num_cpus 1
       ARG quantum 10
       ARG peek_interval 30
       ARG warmup_time 10
       ARG cache_size 300
       ARG random_order False
       ARG trace True
       ARG trace_time False
       ARG trace_cache False
       ARG trace_sched False
       ARG compute True

       Job name:a run_time:30 working_set_size:200

       Scheduler central queue: ['a']

       0   a      
       1   a      
       2   a      
       3   a      
       4   a      
       5   a      
       6   a      
       7   a      
       8   a      
       9   a      
       ----------
       10   a      
       11   a      
       12   a      
       13   a      
       14   a      
       15   a      
       16   a      
       17   a      
       18   a      
       19   a      

       Finished time 20

       Per-CPU stats
           CPU 0  utilization 100.00 [ warm 50.00 ]
       ```

3.  ###### One cool thing about `multi.py` is that you can see more detail about what is going on with different tracing flags. Run the same simulation as above, but this time with time left tracing enabled (`-T`). This flag shows both the job that was scheduled on a CPU at each time step, as well as how much run-time that job has left after each tick has run. What do you notice about how that second column decreases?

    -  Der Programmaufruf `./multi.py -n 1 -L a:30:200 -M 300 -T` liefert
       folgende Ausgabe:

       ```
       ARG seed 0
       ARG job_num 3
       ARG max_run 100
       ARG max_wset 200
       ARG job_list a:30:200
       ARG affinity
       ARG per_cpu_queues False
       ARG num_cpus 1
       ARG quantum 10
       ARG peek_interval 30
       ARG warmup_time 10
       ARG cache_size 300
       ARG random_order False
       ARG trace False
       ARG trace_time True
       ARG trace_cache False
       ARG trace_sched False
       ARG compute False

       Job name:a run_time:30 working_set_size:200

       Scheduler central queue: ['a']

       0   a [ 29]      
       1   a [ 28]      
       2   a [ 27]      
       3   a [ 26]      
       4   a [ 25]      
       5   a [ 24]      
       6   a [ 23]      
       7   a [ 22]      
       8   a [ 21]      
       9   a [ 20]      
       ----------------
       10   a [ 18]      
       11   a [ 16]      
       12   a [ 14]      
       13   a [ 12]      
       14   a [ 10]      
       15   a [  8]      
       16   a [  6]      
       17   a [  4]      
       18   a [  2]      
       19   a [  0]     
       ```

       Solange der Cache "kalt" ist, wird die verbleibende Joblaufzeit (2.
       Spalte der Ausgabe) nach jedem Tick um 1 verringert. Sobald der Cache jedoch
       "warm" gelaufen ist, wird nun die verbleibende Joblaufzeit nach jedem Tick
       um 2 verringert, da die Cache-Warm-Rate 2 beträgt.

4.  ###### Now add one more bit of tracing, to show the status of each CPU cache for each job, with the `-C` flag. For each job, each cache will either show a blank space (if the cache is cold for that job) or a ’w’ (if the cache is warm for that job). At what point does the cache become warm for job ’a’ in this simple example?

    -  Der Programmaufruf `./multi.py -n 1 -L a:30:200 -M 300 -T -C` liefert folgende Ausgabe:

       ```
       $ ./multi.py -n 1 -L a:30:200 -M 300 -T -C

       ARG seed 0
       ARG job_num 3
       ARG max_run 100
       ARG max_wset 200
       ARG job_list a:30:200
       ARG affinity
       ARG per_cpu_queues False
       ARG num_cpus 1
       ARG quantum 10
       ARG peek_interval 30
       ARG warmup_time 10
       ARG cache_size 300
       ARG random_order False
       ARG trace False
       ARG trace_time True
       ARG trace_cache True
       ARG trace_sched False
       ARG compute False

       Job name:a run_time:30 working_set_size:200

       Scheduler central queue: ['a']

       0   a [ 29] cache[ ]     
       1   a [ 28] cache[ ]     
       2   a [ 27] cache[ ]     
       3   a [ 26] cache[ ]     
       4   a [ 25] cache[ ]     
       5   a [ 24] cache[ ]     
       6   a [ 23] cache[ ]     
       7   a [ 22] cache[ ]     
       8   a [ 21] cache[ ]     
       9   a [ 20] cache[w]     
       -------------------------
       10   a [ 18] cache[w]     
       11   a [ 16] cache[w]     
       12   a [ 14] cache[w]     
       13   a [ 12] cache[w]     
       14   a [ 10] cache[w]     
       15   a [  8] cache[w]     
       16   a [  6] cache[w]     
       17   a [  4] cache[w]     
       18   a [  2] cache[w]     
       19   a [  0] cache[w]
       ```  
       Da die Cache-Warmup-Zeit 10 beträgt, ist der Cache im 10. Tick "warm"
       gelaufen.

    ###### What happens as you change the warmup time parameter (`-w`) to lower or higher values than the default?

    -  Mit niedrigeren Werten als der Standardwert der Cache-Warmup-Zeit (10),
       läuft der Cache schneller "warm", wodurch der Job schneller abgearbeitet
       werden kann (abhängig von der Cache-Warm-Rate).

    -  Mit höheren Werten als der Standardwert der Cache-Warmup-Zeit, dauert es
       länger bis der Cache "warm" gelaufen ist, worduch der Job länger braucht
       um vollständig ausgeführt zu werden.

5.  ###### At this point, you should have a good idea of how the simulator works for a single job running on a single CPU. But hey, isn’t this a multi-processor CPU scheduling chapter? Oh yeah! So let’s start working with multiple jobs. Specifically, let’s run the following three jobs on a two-CPU system (i.e., type `./multi.py -n 2 -L a:100:100,b:100:50,c:100:50`). Can you predict how long this will take, given a round-robin centralized scheduler? Use `-c` to see if you were right, and then dive down into details with `-t` to see a step-by-step and then `-C` to see whether caches got warmed effectively for these jobs.

    -  Die gesamte Laufzeit um alle drei Jobs auszuführen, bestimmt sich
       folgendermaßen:

       *  Da es nur 2 CPUs aber jedoch 3 Jobs im System gibt, werden die Jobs
          je nach dem wie sie in der Schduler-Central-Queue (hier: `[a,b,c]`)
          liegen nacheinander auf die 2 CPUs aufgeteilt. Dadurch ergibt sich
          folgende Ausführungsreihenfolge:
          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`CPU_0 -> a, CPU_1 -> b`,  
          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`CPU_0 -> c, CPU_1 -> a`,    
          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`CPU_0 -> b, CPU_1 -> c`,  
          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`CPU_0 -> a, CPU_1 -> b`,  
          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`...`

       *  Durch die Ausführungsreihenfolge werden leider immer Cachemisses
          produziert, weshalb sich die gesamte Laufzeit folgendermaßen bestimmt:

          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Gesamt LZ = (LZ Job a + LZ Job b + LZ Job c) / anz. CPUs**  
          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**= (100 ZE + 100 ZE + 100 ZE) / 2 = 300 ZE / 2 = 150 ZE**

    -  Der Programmaufruf `./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -c -t`
       liefert folgende Ausgabe:

       ```
       $ ./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -c -t

       [...]

       Job name:a run_time:100 working_set_size:100
       Job name:b run_time:100 working_set_size:50
       Job name:c run_time:100 working_set_size:50

       Scheduler central queue: ['a', 'b', 'c']

       0   a      b      
       1   a      b      
       2   a      b      
       3   a      b      
       4   a      b      
       5   a      b      
       6   a      b      
       7   a      b      
       8   a      b      
       9   a      b      
       -----------------
       10   c      a      
       11   c      a      
       12   c      a      
       13   c      a      
       14   c      a      
       15   c      a      
       16   c      a      
       17   c      a      
       18   c      a      
       19   c      a      
       -----------------
       20   b      c      
       21   b      c      
       22   b      c      
       23   b      c      
       24   b      c      
       25   b      c      
       26   b      c      
       27   b      c      
       28   b      c      
       29   b      c      
       -----------------
       30   a      b      
       31   a      b      
       32   a      b      
       33   a      b      
       34   a      b      
       35   a      b      
       36   a      b      
       37   a      b      
       38   a      b      
       39   a      b      
       -----------------
       [...]
       -----------------
       140   b      c      
       141   b      c      
       142   b      c      
       143   b      c      
       144   b      c      
       145   b      c      
       146   b      c      
       147   b      c      
       148   b      c      
       149   b      c      

       Finished time 150

       Per-CPU stats
           CPU 0  utilization 100.00 [ warm 0.00 ]
           CPU 1  utilization 100.00 [ warm 0.00 ]
       ```

    -  Des weiteren liefert der Programmaufruf
       `./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -C` folgende Ausgabe:

       ```
       $ ./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -C      

       [...]

       Job name:a run_time:100 working_set_size:100
       Job name:b run_time:100 working_set_size:50
       Job name:c run_time:100 working_set_size:50

       Scheduler central queue: ['a', 'b', 'c']

       0   a cache[   ]     b cache[   ]     
       1   a cache[   ]     b cache[   ]     
       2   a cache[   ]     b cache[   ]     
       3   a cache[   ]     b cache[   ]     
       4   a cache[   ]     b cache[   ]     
       5   a cache[   ]     b cache[   ]     
       6   a cache[   ]     b cache[   ]     
       7   a cache[   ]     b cache[   ]     
       8   a cache[   ]     b cache[   ]     
       9   a cache[w  ]     b cache[ w ]     
       ---------------------------------------
       10   c cache[w  ]     a cache[ w ]     
       11   c cache[w  ]     a cache[ w ]     
       12   c cache[w  ]     a cache[ w ]     
       13   c cache[w  ]     a cache[ w ]     
       14   c cache[w  ]     a cache[ w ]     
       15   c cache[w  ]     a cache[ w ]     
       16   c cache[w  ]     a cache[ w ]     
       17   c cache[w  ]     a cache[ w ]     
       18   c cache[w  ]     a cache[ w ]     
       19   c cache[  w]     a cache[w  ]     
       ---------------------------------------
       20   b cache[  w]     c cache[w  ]     
       21   b cache[  w]     c cache[w  ]     
       22   b cache[  w]     c cache[w  ]     
       23   b cache[  w]     c cache[w  ]     
       24   b cache[  w]     c cache[w  ]     
       25   b cache[  w]     c cache[w  ]     
       26   b cache[  w]     c cache[w  ]     
       27   b cache[  w]     c cache[w  ]     
       28   b cache[  w]     c cache[w  ]     
       29   b cache[ ww]     c cache[  w]     
       ---------------------------------------
       30   a cache[ ww]     b cache[  w]     
       31   a cache[ ww]     b cache[  w]     
       32   a cache[ ww]     b cache[  w]     
       33   a cache[ ww]     b cache[  w]     
       34   a cache[ ww]     b cache[  w]     
       35   a cache[ ww]     b cache[  w]     
       36   a cache[ ww]     b cache[  w]     
       37   a cache[ ww]     b cache[  w]     
       38   a cache[ ww]     b cache[  w]     
       39   a cache[w  ]     b cache[ ww]     
       ---------------------------------------
       [...]  
       ---------------------------------------
       140   b cache[  w]     c cache[w  ]     
       141   b cache[  w]     c cache[w  ]     
       142   b cache[  w]     c cache[w  ]     
       143   b cache[  w]     c cache[w  ]     
       144   b cache[  w]     c cache[w  ]     
       145   b cache[  w]     c cache[w  ]     
       146   b cache[  w]     c cache[w  ]     
       147   b cache[  w]     c cache[w  ]     
       148   b cache[  w]     c cache[w  ]     
       149   b cache[ ww]     c cache[  w]
       ```

    ###### What do you notice?

    -  Durch die festgelegte Ausführungsreihenfolge kommt es immer zu Cachemisses,
       was zu einer schlechten Gesamtlaufzeit führt, da man die zeitliche sowie
       räumliche Lokalität somit nicht berücksichtigt (**&rarr;Cache Affinität**).

6.  ###### Now we’ll apply some explicit controls to study cache affinity, as described in the chapter. To do this, you’ll need the `-A` flag. This flag can be used to limit which CPUs the scheduler can place a particular job upon. In this case, let’s use it to place jobs ’b’ and ’c’ on CPU 1, while restricting ’a’ to CPU 0. This magic is accomplished by typing this `./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -A a:0,b:1,c:1`; don’t forget to turn on various tracing options to see what is really happening! Can you predict how fast this version will run?

    -  Die Laufzeit der einzelnen Jobs berechnet sich folgendermaßen:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**LZ Job a = 10 ZE + (100 ZE - 10 ZE) / 2 = 10 ZE + 90 ZE / 2 = 10 ZE + 45 ZE = 55 ZE**  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**LZ Job b = 10 ZE + (100 ZE - 10 ZE) / 2 = 55 ZE**  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**LZ Job c = 10 ZE + (100 ZE - 10 ZE) / 2 = 55 ZE**

       (Job b und c brauchen gleich lange, da der Cache genug Platz hat um die
       Daten beider Jobs gleichzeitg zu halten!)

       Da Job a immer parallel zu Job b oder c läuft ergibt sich folgende
       Gesamtlaufzeit:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Gesamt LZ = LZ Job b + LZ Job c = 55 ZE + 55 ZE = 110 ZE**

    -  Der Programmaufruf `./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -A a:0,b:1,c:1 -c -C`
       liefert folgende Ausgabe:

       ```
       $ ./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -A a:0,b:1,c:1 -c -C

       [...]

       Job name:a run_time:100 working_set_size:100
       Job name:b run_time:100 working_set_size:50
       Job name:c run_time:100 working_set_size:50

       Scheduler central queue: ['a', 'b', 'c']

       0   a cache[   ]     b cache[   ]     
       1   a cache[   ]     b cache[   ]     
       2   a cache[   ]     b cache[   ]     
       3   a cache[   ]     b cache[   ]     
       4   a cache[   ]     b cache[   ]     
       5   a cache[   ]     b cache[   ]     
       6   a cache[   ]     b cache[   ]     
       7   a cache[   ]     b cache[   ]     
       8   a cache[   ]     b cache[   ]     
       9   a cache[w  ]     b cache[ w ]     
       ---------------------------------------
       10   a cache[w  ]     c cache[ w ]     
       11   a cache[w  ]     c cache[ w ]     
       12   a cache[w  ]     c cache[ w ]     
       13   a cache[w  ]     c cache[ w ]     
       14   a cache[w  ]     c cache[ w ]     
       15   a cache[w  ]     c cache[ w ]     
       16   a cache[w  ]     c cache[ w ]     
       17   a cache[w  ]     c cache[ w ]     
       18   a cache[w  ]     c cache[ w ]     
       19   a cache[w  ]     c cache[ ww]     
       ---------------------------------------
       20   a cache[w  ]     b cache[ ww]     
       21   a cache[w  ]     b cache[ ww]     
       22   a cache[w  ]     b cache[ ww]     
       23   a cache[w  ]     b cache[ ww]     
       24   a cache[w  ]     b cache[ ww]     
       25   a cache[w  ]     b cache[ ww]     
       26   a cache[w  ]     b cache[ ww]     
       27   a cache[w  ]     b cache[ ww]     
       28   a cache[w  ]     b cache[ ww]     
       29   a cache[w  ]     b cache[ ww]     
       ---------------------------------------
       [...]
       ---------------------------------------
       100   - cache[w  ]     b cache[ ww]     
       101   - cache[w  ]     b cache[ ww]     
       102   - cache[w  ]     b cache[ ww]     
       103   - cache[w  ]     b cache[ ww]     
       104   - cache[w  ]     b cache[ ww]     
       105   - cache[w  ]     c cache[ ww]     
       106   - cache[w  ]     c cache[ ww]     
       107   - cache[w  ]     c cache[ ww]     
       108   - cache[w  ]     c cache[ ww]     
       109   - cache[w  ]     c cache[ ww]     

       Finished time 110

       Per-CPU stats
           CPU 0  utilization 50.00 [ warm 40.91 ]
           CPU 1  utilization 100.00 [ warm 81.82 ]
       ```

    ###### Why does it do better?

    -  Da hier das Prinzip der Cache Affinität eingehalten wird, gibt es außer
       in der Warmup-Pahse immer Cace-Hits, wodurch die Ausführungszeit der Jobs
       zusätzlich beschleunigt werden.

    ###### Will other combinations of ’a’, ’b’, and ’c’ onto the two processors run faster or slower?

    -  Ja, wenn Job b auf CPU 0 läuft und Job a und c auf der CPU 1 laufen, wird
       eine längere Gesamtlaufzeit benötigt, da der Cache von CPU 1 nicht groß
       genug ist um die Daten beider Jobs gleichzeitg zu halten. Daher werden
       bei CPU 1 wieder Cachemisses produziert, was die Gesamtlaufzeit negativ
       beeinträchtigt. Hierbei bestimmt sich die einzelnen Joblaufzeiten wie
       folgt:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**LZ Job a = 100 ZE**  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**LZ Job b = 10 ZE + (100 ZE - 10 ZE) / 2 = 55**  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**LZ Job c = 100 ZE**

       Da b parallel zu b und c laufen kann ergibt sich folgende Gesamtlaufzeit:  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Gesamt LZ = LZ Job a + LZ Job b = 100 ZE + 100 ZE = 200 ZE**  

    -  Eine schnellere Gesamtlaufzeit als wenn b und c auf der selben CPU laufen
       ist in diesem Fall nicht möglich.

7.  ###### One interesting aspect of caching multiprocessors is the opportunity for better-than-expected speed up of jobs when using multiple CPUs (and their caches) as compared to running jobs on a single processor. Specifically, when you run on N CPUs, sometimes you can speed up by more than a factor of N, a situation entitled super-linear speedup. To experiment with this, use the job description here (`-L a:100:100,b:100:100,c:100:100`) with a small cache (`-M 50`) to create three jobs. Run this on systems with 1, 2, and 3 CPUs (`-n 1`, `-n 2`, `-n 3`).

    -  Für den Programmaufruf `./multi.py -L a:100:100,b:100:100,c:100:100 -M 50`
       ergeben sich folgende Gesamtlaufzeiten mit steigender CPU-Anzahl:

       | Anzahl CPUs   | Gesamtlaufzeit | Berechnung                     |
       | ------------- | -------------- | ------------------------------ |
       | 1             | 300            | 100 ZE + 100 ZE + 100 ZE       |
       | 2             | 150            | (100 ZE + 100 ZE + 100 ZE) / 2 |
       | 3             | 100            | (100 ZE + 100 ZE + 100 ZE) / 3 |

    ###### Now, do the same, but with a larger per-CPU cache of size 100. What do you notice about performance as the number of CPUs scales? Use `-c` to confirm your guesses, and other tracing flags to dive even deeper.

    -  Für den Programmaufruf `./multi.py -L a:100:100,b:100:100,c:100:100 -M 100`
       ergeben sich folgende Gesamtlaufzeiten mit steigender CPU-Anzahl:

       | Anzahl CPUs   | Gesamtlaufzeit | Berechnung                     |
       | ------------- | -------------- | ------------------------------ |
       | 1             | 300            | 100 ZE + 100 ZE + 100 ZE       |
       | 2             | 150            | (100 ZE + 100 ZE + 100 ZE) / 2 |
       | 3             | 55             | 10 ZE + (100 ZE - 10 ZE) / 2   |

8.  ###### One other aspect of the simulator worth studying is the per-CPU scheduling option, the `-p` flag. Run with two CPUs again, and this three job configuration (`-L a:100:100,b:100:50,c:100:50`). How does this option do, as opposed to the hand-controlled affinity limits you put in place above?

    -  Im Gegensatz zum Single-Queue Scheduling, welche nur eine Queue besitzt
       gibt es beim Multi-Queue-Scheduling pro CPU eine eigne Queue in der Jobs
       eingereiht werden können. In diesem Fall werden in der CPU_0-Queue die
       Jobs a und c eingereiht und in der CPU_1-Queue der Job b. Die Laufzeit der
       einzelnen Jobs bestimmt sich dann folgendermaßen:

       Da der Job b eine CPU (hier: CPU_1) für sich alleine hat benötigt dieser
       nur 55 ZE (10 + (100 - 10) / 2), aufgrund der Cache Affinität.
       Währenddessen wird auf der CPU_0 zwischen den Jobs a und c hin und her
       gewechselt. Dadurch bleiben bei den Jobs a und c nach Beendigung von Job
       b noch 70 ZE übrig (60 ZE sind bisher vergangen), die noch abgearbeitet
       werden müssen. Da auf der CPU_1 nun keine Jobs mehr laufen, wird der
       Job a dorthin verschoben. Nun laufen a und c ebenfalls parallel. Nach 10
       ZE sind die Caches "warm" gelaufen, weshalb nun noch 30 ZE benötigt
       werden um beide Jobs abzuschließen. Es ergibt sich hiermit eine
       **Gesamtlaufzeit** von: **60 ZE + 10 ZE + 30 ZE = 100 ZE**

    -  Der Programmaufruf `./multi.py -L a:100:100,b:100:50,c:100:50 -p -c -t`
       liefert folgende Ausgabe:

       ```
       $ ./multi.py -L a:100:100,b:100:50,c:100:50 -p -c -t

       [...]

       Job name:a run_time:100 working_set_size:100
       Job name:b run_time:100 working_set_size:50
       Job name:c run_time:100 working_set_size:50

       Scheduler CPU 0 queue: ['a', 'c']
       Scheduler CPU 1 queue: ['b']

       [...]

       Finished time 100

       Per-CPU stats
           CPU 0  utilization 95.00 [ warm 35.00 ]
           CPU 1  utilization 95.00 [ warm 75.00 ]
       ```

    ###### How does performance change as you alter the ’peek interval’ (`-P`) to lower or higher values?

    -  Für den Programmaufruf `./multi.py -L a:100:100,b:100:50,c:100:50`
       ergeben sich folgende Gesamtlaufzeiten mit steigendem Peek-Intervall:

       | Peak-Intervall | Gesamtlaufzeit |
       | -------------- | -------------- |
       | 1              | 90             |
       | 5              | 90             |
       | 10             | 100            |
       | 15             | 115            |
       | 20             | 100            |
       | 25             | 105            |
       | 30 (default)   | 100            |
       | 35             | 130            |
       | 40             | 115            |
       | 45             | 100            |
       | 50             | 130            |
       | 55             | 95             |
       | 60             | 100            |

       Je nach wie der Peak-Intervall gesetzt wird, wird zu unterschiedlichen
       Zeitpunkten nachgeschaut ob eine CPU mehr Jobs in seiner Queue hat, als
       andere CPUs. Ist dies der Fall, wird der Job einem anderen CPU zugteilt,
       um die Arbeitslast gleichmäßig auf die CPUs aufzuteilen. Dieses Verfahren
       kann einerseits zu einer Perfomancesteigerung führen (bei geeignetem
       Peak-Intervall), anderenseits kann sich die Performance auch verschlechtern,
       wenn der Peak-Intervall ungünstig gewählt wird.

    ###### How does this per-CPU approach work as the number of CPUs scales?

    -  Für den Programmaufruf `./multi.py -L a:100:100,b:100:50,c:100:50`
       ergeben sich folgende Gesamtlaufzeiten mit steigender CPU-Anzahl:

       | Anzahl CPUs   | Gesamtlaufzeit | Berechnung                        |
       | ------------- | -------------- | --------------------------------- |
       | 1             | 300            | 100 ZE + 100 ZE + 100 ZE          |
       | 2             | 100            | 60 ZE + 10 ZE + 30 ZE (siehe oben)|
       | 3             | 55             | 10 ZE + (100 ZE - 10 ZE) / 2      |

       Das Multi-Queue-Scheduling liefert bei 2 CPUs schnellere Ergebnisse,
       aufgrund des eigesetzten Worksstealings.

9.  ###### Finally, feel free to just generate random workloads and see if you can predict their performance on different numbers of processors, cache sizes, and scheduling options. If you do this, you’ll soon be a multi-processor scheduling master, which is a pretty awesome thing to be. Good luck!

    -  Hmkay...
