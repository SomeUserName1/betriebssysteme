# Answers

1.  ###### We’ll start by redoing the measurements within this chapter. Use the call `gettimeofday()` to measure time within your program. How accurate is this timer? What is the smallest interval it can measure? Gain confidence in its workings, as we will need it in all subsequent questions. You can also look into other timers, such as the `cycle counter` available on `x86` via the `rdtsc` instruction.

2.  ###### Now, build a simple concurrent counter and measure how long it takes to increment the counter many times as the number of threads increases. How many CPUs are available on the system you are using?

    -  Siehe: `concurrent_counter.c`, `concurrent_counter.h` sowie `concurrent_counter_measurement.txt`.
    -  Auf der Workstation stehen 12 CPUs zur Verfügung.

    ###### Does this number impact your measurements at all?

    Ja, denn wenn die Anzahl an erstellten Threads größer ist, als die verfügbare
    Anzahl an CPUs (bzw. CPU-Kernen) werden nicht mehr alle Threads tatsächlich
    parallel ausgeführt.

3.  ###### Next, build a version of the sloppy counter. Once again, measure its performance as the number of threads varies, as well as the threshold. Do the numbers match what you see in the chapter?

    -  Siehe: `sloppy_counter.c`, `sloppy_counter.h` sowie `sloppy_counter_measurement.txt`.
    -  Nein unsere Messungen entsprechen nicht den Daten der Messungen im Kapitel.
       Erklären kann man dies damit, dass solche Messungen Systemabhänig sind,
       und wir wohl ein schnelleres System verwenden.

       Der Trend der Kurve bleibt aber gleich: Mit ansteigendem `THRESHOLD` sinkt
       die Ausführungszeit immer mehr.

4.  ###### Build a version of a linked list that uses hand-over-hand locking [MS04], as cited in the chapter. You should read the paper first to understand how it works, and then implement it. Measure its performance. When does a hand-over-hand list work better than a standard list as shown in the chapter?

    -  Siehe: `concurrent_list.c`, `concurrent_list.h` sowie
       `concurrent_list_measurement.txt`

    -  Wenn beide Threads auf unterschiedlichen Knoten arbeiten, können nun diese
       wirklich parallel arbeiten, da nicht die gesamte Liste glocked wurde.

5.  ###### Pick your favorite interesting data structure, such as a B-tree or other slightly more interested structure. Implement it, and start with a simple locking strategy such as a single lock. Measure its performance as the number of concurrent threads increases.

    -  Siehe: `bin_tree_single_lock/bin_tree.c`, `bin_tree_single_lock/bin_tree.h`
       sowie &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`bin_tree_single_lock/bin_tree_single_lock_measurement`.

6.  ###### Finally, think of a more interesting locking strategy for this favorite data structure of yours. Implement it, and measure its performance. How does it compare to the straightforward locking approach?

    - Siehe `bin_tree_bin_tree_better_locking_strategy`.
