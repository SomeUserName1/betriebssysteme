# Answers

1.  ###### Generate random addresses with the following arguments: `-s 0 -n 10`, `-s 1 -n 10`, and `-s 2 -n 10`. Change the policy from `FIFO`, to `LRU`, to `OPT`. Compute whether each access in said address traces are hits or misses.

    **Vorgehensweise:**

    Um herauszufinden, ob bei ein Zugriff auf eine Page ein Cache `HIT` oder `MISS`
    vorliegt, geht man folgenermaßen vor:

    1.  Liegt die Page nicht im Cache so tritt ein Cache `MISS` auf und die Page
        muss von der Festplatte geladen werden. Diese wird dann in den Cache
        eingefügt, wodurch eine andere Page, die sich bereits im Cache befindet,
        verdängt werden kann, falls der Cache voll ist. Welche Page im Endeffekt
        verdrängt wird, hängt von der eingesetzten Replacement Policy ab.

    2.  Liegt die Page im Cache, so tritt eine Cache `HIT` auf, wodurch sehr
        schnell auf die Page zugegriffen werden kann.

    Letztendlich kann man für ein Sequenz von Pagezugriffen noch die Hitrate
    bestimmen:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`Hitrate = numberOfHits / (numberOfHits + numberOfMisses)`

    **Replacement Policies:**

    *  `OPT` (Optimal):

       Die `Optimal` Replacement Policy führt zu der kleinsten Anzahl an Misses,
       die möglich ist. Dafür muss sie in die Zukunft blicken, um herauszufinden,
       welche Page am besten ersetzt werden kann.

    *  `FIFO` (First-In-First-Out):

       Die `FIFO` Replacement Policy ersetzt immer die Page, welche sich bisher
       am längsten im Cache befindet (wurde vor den anderen Pages in den Cache
       eingefügt).

    *  `Random`:

       Die `Random` Replacement Policy sucht sich zufällig eine Page aus, welche
       ersetzt werden soll.

    *  `LRU` (Least-Recently-Used):

       Die `LRU` Replacement Policy ersetzt immer die Page, auf die am längsten
       nicht mehr zugegriffen wurde.

    *  `LFU` (Least-Frequently-Used):

       Die `LFU` Replacement Policy ersetzt die Page, auf die in der
       Vergangenheit am wenigsten zugegriffen wurde.

    *  `MRU` (Most-Recently-Used):

       Die `MRU` Replacement Policy ersetzt immer die Page, auf welche vor kurzem
       zugegriffen wurde.

    *  `MFU` (Most-Frequently-Used):

       Die `MFU` Replacement Policy ersetzt immer die Page, auf die im der
       Vergangenheit am meisten zugegriffen wurde.

    *  `CLOCK`:

       Die `CLOCK` Replacement Policy ist eine effizentere Version der `FIFO` Replacement Policy. Der `CLOCK`-Algorithmus nutzt eine zirkuläre Liste in der die Pages abgelegt werden. Es gibt einen sogenannten `hand`-Zeiger (Iterator), welcher auf die zuletzt verwendete Page zeigt. Wenn nun ein Pagefault auftritt, und kein Platzt mehr in der zirkulären Liste vorhanden ist, wird das R-Bit (Refrenz-Bit) an der `hand`-Position inspiziert. Ist dieses 0, wird die Page auf welche `hand` zeigt durch die zu ladende Page ersetzt und `hand` wird um eine Position erhöht. Anderenfalls wird das R-Bit zurückgesetzt und die Position von `hand` um 1 erhöht und der Prozess beginnt von vorne, bis eine Page gefunden wurde welche ersetzt werden kann.
    ---

    * `FIFO`:

      Der Programmaufruf `./paging-policy.py -s 0 -n 10` liefert folgende Ausgabe:

      ```
      $ ./paging-policy.py -s 0 -n 10
      ARG addresses -1
      ARG addressfile
      ARG numaddrs 10
      ARG policy FIFO
      ARG clockbits 2
      ARG cachesize 3
      ARG maxpage 10
      ARG seed 0
      ARG notrace False

      Assuming a replacement policy of FIFO, and a cache of size 3 pages, figure
      out whether each of the following page references hit or miss in the page
      cache.

      Access: 8  Hit/Miss?  State of Memory?
      Access: 7  Hit/Miss?  State of Memory?
      Access: 4  Hit/Miss?  State of Memory?
      Access: 2  Hit/Miss?  State of Memory?
      Access: 5  Hit/Miss?  State of Memory?
      Access: 4  Hit/Miss?  State of Memory?
      Access: 7  Hit/Miss?  State of Memory?
      Access: 3  Hit/Miss?  State of Memory?
      Access: 4  Hit/Miss?  State of Memory?
      Access: 5  Hit/Miss?  State of Memory?
      ```

      **Lösung:**

      ```
      policy:     FIFO
      cacheSize:  3
      ```

      *  `Access: 8`:

         ```
         Zustand des Caches:          FirstIn --> [] <-- LastIn

            --> MISS, insert 8
            --> Replaced: -

         Neuer Zustand des Caches:    FirstIn --> [8]  <-- LastIn

         numberOfHits:   0
         numberOfMisses: 1
         ```

      *  `Access: 7`:

         ```
         Zustand des Caches:          FirstIn --> [8]  <-- LastIn

            --> MISS, insert 7
            --> Replaced: -

         Neuer Zustand des Caches:    FirstIn --> [8, 7] <-- LastIn

         numberOfHits:   0
         numberOfMisses: 2
         ```

      *  `Access: 4`:

         ```
         Zustand des Caches:          FirstIn --> [8, 7] <-- LastIn

            --> MISS, insert 4
            --> Replaced: -

         Neuer Zustand des Caches:    FirstIn --> [8, 7, 4] <-- LastIn

         numberOfHits:   0
         numberOfMisses: 3
         ```

      *  `Access: 2`:

         ```
         Zustand des Caches:          FirstIn --> [8, 7, 4] <-- LastIn

            --> MISS, insert 2
            --> Replaced: 8

         Neuer Zustand des Caches:    FirstIn --> [7, 4, 2] <-- LastIn

         numberOfHits:   0
         numberOfMisses: 4
         ```

      *  `Access: 5`:

         ```
         Zustand des Caches:          FirstIn --> [7, 4, 2] <-- LastIn

            --> MISS, insert 5
            --> Replaced: 7

         Neuer Zustand des Caches:    FirstIn --> [4, 2, 5] <-- LastIn

         numberOfHits:   0
         numberOfMisses: 5
         ```

      *  `Access: 4`:

         ```
         Zustand des Caches:          FirstIn --> [4, 2, 5] <-- LastIn

            --> HIT
            --> Replaced: -

         Neuer Zustand des Caches:    FirstIn --> [4, 2, 5] <-- LastIn

         numberOfHits:   1
         numberOfMisses: 5
         ```

      *  `Access: 7`:

         ```
         Zustand des Caches:          FirstIn --> [4, 2, 5] <-- LastIn

            --> MISS, insert 7
            --> Replaced: 4

         Neuer Zustand des Caches:    FirstIn --> [2, 5, 7] <-- LastIn

         numberOfHits:   1
         numberOfMisses: 6
         ```

      *  `Access: 3`:

         ```
         Zustand des Caches:          FirstIn --> [2, 5, 7] <-- LastIn

            --> MISS, insert 3
            --> Replaced: 2

         Neuer Zustand des Caches:    FirstIn --> [5, 7, 3] <-- LastIn

         numberOfHits:   1
         numberOfMisses: 7
         ```

      *  `Access: 4`:

         ```
         Zustand des Caches:          FirstIn --> [5, 7, 3] <-- LastIn

            --> MISS, insert 4
            --> Replaced: 5

         Neuer Zustand des Caches:    FirstIn --> [7, 3, 4] <-- LastIn

         numberOfHits:   1
         numberOfMisses: 8
         ```

      *  `Access: 5`:

         ```
         Zustand des Caches:          FirstIn --> [7, 3, 4] <-- LastIn

            --> MISS, insert 5
            --> Replaced: 7

         Neuer Zustand des Caches:    FirstIn --> [3, 4, 5] <-- LastIn

         numberOfHits:   1
         numberOfMisses: 9
         ```

      ```
      Hitrate = numberOfHits / (numberOfHits + numberOfMisses) = 1 / (1 + 9) = 1 / 10 = 0.1 = 10%
      ```
    * `LRU`:

      Der Programmaufruf `./paging-policy.py -s 0 -n 10 -p LRU` liefert folgende
      Ausgabe:

      ```
      $ ./paging-policy.py -s 0 -n 10 -p LRU  
      ARG addresses -1
      ARG addressfile
      ARG numaddrs 10
      ARG policy LRU
      ARG clockbits 2
      ARG cachesize 3
      ARG maxpage 10
      ARG seed 0
      ARG notrace False

      Assuming a replacement policy of LRU, and a cache of size 3 pages, figure
      out whether each of the following page references hit or miss in the page
      cache.

      Access: 8  Hit/Miss?  State of Memory?
      Access: 7  Hit/Miss?  State of Memory?
      Access: 4  Hit/Miss?  State of Memory?
      Access: 2  Hit/Miss?  State of Memory?
      Access: 5  Hit/Miss?  State of Memory?
      Access: 4  Hit/Miss?  State of Memory?
      Access: 7  Hit/Miss?  State of Memory?
      Access: 3  Hit/Miss?  State of Memory?
      Access: 4  Hit/Miss?  State of Memory?
      Access: 5  Hit/Miss?  State of Memory?
      ```

      **Lösung:**

      ```
      policy:    LRU
      cacheSize: 3
      ```

      *  `Access: 8`:

         ```
         Zustand des Caches:          LRU --> [] <-- MRU

            --> MISS, insert 8
            --> Replaced: -

         Neuer Zustand des Caches:    LRU --> [8] <-- MRU

         numberOfHits:   0
         numberOfMisses: 1
         ```

      *  `Access: 7`:

         ```
         Zustand des Caches:          LRU --> [8] <-- MRU

            --> MISS, insert 7
            --> Replaced: -

         Neuer Zustand des Caches:    LRU --> [8, 7] <-- MRU

         numberOfHits:   0
         numberOfMisses: 2
         ```

      *  `Access: 4`:

         ```
         Zustand des Caches:          LRU --> [8, 7] <-- MRU

            --> MISS, insert 4
            --> Replaced: -

         Neuer Zustand des Caches:    LRU --> [8, 7, 4] <-- MRU

         numberOfHits:   0
         numberOfMisses: 3
         ```

      *  `Access: 2`:

         ```
         Zustand des Caches:          LRU --> [8, 7, 4] <-- MRU

            --> MISS, insert 2
            --> Replaced: 8

         Neuer Zustand des Caches:    LRU --> [7, 4, 2] <-- MRU

         numberOfHits:   0
         numberOfMisses: 4
         ```

      *  `Access: 5`:

         ```
         Zustand des Caches:          LRU --> [7, 4, 2] <-- MRU

            --> MISS, insert 5
            --> Replaced: 7

         Neuer Zustand des Caches:    LRU --> [4, 2, 5] <-- MRU

         numberOfHits:   0
         numberOfMisses: 5
         ```

      *  `Access: 4`:

         ```
         Zustand des Caches:          LRU --> [4, 2, 5] <-- MRU

            --> HIT
            --> Replaced: -

         Neuer Zustand des Caches:    LRU --> [2, 5, 4] <-- MRU

         numberOfHits:   1
         numberOfMisses: 5
         ```

      *  `Access: 7`:

         ```
         Zustand des Caches:          LRU --> [2, 5, 4] <-- MRU

            --> MISS, insert 7
            --> Replaced: 2

         Neuer Zustand des Caches:    LRU --> [5, 4, 7] <-- MRU

         numberOfHits:   1
         numberOfMisses: 6
         ```

      *  `Access: 3`:

         ```
         Zustand des Caches:          LRU --> [5, 4, 7] <-- MRU

            --> MISS, insert 3
            --> Replaced: 5

         Neuer Zustand des Caches:    LRU --> [4, 7, 3] <-- MRU

         numberOfHits:   1
         numberOfMisses: 7
         ```

      *  `Access: 4`:

         ```
         Zustand des Caches:          LRU --> [4, 7, 3] <-- MRU

            --> HIT
            --> Replaced: -

         Neuer Zustand des Caches:    LRU --> [7, 3, 4] <-- MRU

         numberOfHits:   2
         numberOfMisses: 7
         ```

      *  `Access: 5`:

         ```
         Zustand des Caches:          LRU --> [7, 3, 4] <-- MRU

            --> MISS, insert 5
            --> Replaced: 7

         Neuer Zustand des Caches:    LRU --> [3, 4, 5] <-- MRU

         numberOfHits:   2
         numberOfMisses: 8
         ```

      ```
      Hitrate = numberOfHits / (numberOfHits + numberOfMisses) = 2 / (2 + 8) = 2 / 10 = 0.2 = 20%
      ```

    * `OPT`:

      Der Programmaufruf `./paging-policy.py -s 0 -n 10 -p OPT` liefert folgende
      Ausgabe:

      ```
      ./paging-policy.py -s 0 -n 10 -p OPT
      ARG addresses -1
      ARG addressfile
      ARG numaddrs 10
      ARG policy OPT
      ARG clockbits 2
      ARG cachesize 3
      ARG maxpage 10
      ARG seed 0
      ARG notrace False

      Assuming a replacement policy of OPT, and a cache of size 3 pages, figure
      out whether each of the following page references hit or miss in the page
      cache.

      Access: 8  Hit/Miss?  State of Memory?
      Access: 7  Hit/Miss?  State of Memory?
      Access: 4  Hit/Miss?  State of Memory?
      Access: 2  Hit/Miss?  State of Memory?
      Access: 5  Hit/Miss?  State of Memory?
      Access: 4  Hit/Miss?  State of Memory?
      Access: 7  Hit/Miss?  State of Memory?
      Access: 3  Hit/Miss?  State of Memory?
      Access: 4  Hit/Miss?  State of Memory?
      Access: 5  Hit/Miss?  State of Memory?
      ```

      **Lösung:**

      ```
      policy:    OPT
      cacheSize: 3
      ```

      *  `Access: 8`:

         ```
         Zustand des Caches:          Left --> [] <-- Right

            --> MISS, insert 8
            --> Replaced: -

         Neuer Zustand des Caches:    Left --> [8] <-- Right

         numberOfHits:   0
         numberOfMisses: 1
         ```

      *  `Access: 7`:

         ```
         Zustand des Caches:          Left --> [8] <-- Right

            --> MISS, insert 7
            --> Replaced: -

         Neuer Zustand des Caches:    Left --> [8, 7] <-- Right

         numberOfHits:   0
         numberOfMisses: 2
         ```

      *  `Access: 4`:

         ```
         Zustand des Caches:          Left --> [8, 7] <-- Right

            --> MISS, insert 4
            --> Replaced: -

         Neuer Zustand des Caches:    Left --> [8, 7, 4] <-- Right

         numberOfHits:   0
         numberOfMisses: 3
         ```

      *  `Access: 2`:

         ```
         Zustand des Caches:          Left --> [8, 7, 4] <-- Right

            --> MISS, insert 2
            --> Replaced: 8

         Neuer Zustand des Caches:    Left --> [7, 4, 2] <-- Right

         numberOfHits:   0
         numberOfMisses: 4
         ```

      *  `Access: 5`:

         ```
         Zustand des Caches:          Left --> [7, 4, 2] <-- Right

            --> MISS, insert 5
            --> Replaced: 2

         Neuer Zustand des Caches:    Left --> [7, 4, 5] <-- Right

         numberOfHits:   0
         numberOfMisses: 5
         ```

      *  `Access: 4`:

         ```
         Zustand des Caches:          Left --> [7, 4, 5] <-- Right

            --> HIT
            --> Replaced: -

         Neuer Zustand des Caches:    Left --> [7, 4, 5] <-- Right

         numberOfHits:   1
         numberOfMisses: 5
         ```

      *  `Access: 7`:

         ```
         Zustand des Caches:          Left --> [7, 4, 5] <-- Right

            --> HIT
            --> Replaced: -

         Neuer Zustand des Caches:    Left --> [7, 4, 5] <-- Right

         numberOfHits:   2
         numberOfMisses: 5
         ```

      *  `Access: 3`:

         ```
         Zustand des Caches:          Left --> [7, 4, 5] <-- Right

            --> MISS, insert 3
            --> Replaced: 7

         Neuer Zustand des Caches:    Left --> [4, 5, 3] <-- Right

         numberOfHits:   2
         numberOfMisses: 6
         ```

      *  `Access: 4`:

         ```
         Zustand des Caches:          Left --> [4, 5, 3] <-- Right

            --> HIT
            --> Replaced: -

         Neuer Zustand des Caches:    Left --> [4, 5, 3] <-- Right

         numberOfHits:   3
         numberOfMisses: 6
         ```

      *  `Access: 5`:

         ```
         Zustand des Caches:          Left --> [4, 5, 3] <-- Right

            --> HIT
            --> Replaced: -

         Neuer Zustand des Caches:    Left --> [4, 5, 3] <-- Right

         numberOfHits:   4
         numberOfMisses: 6
         ```

      ```
      Hitrate = numberOfHits + (numberOfHits + numberOfMisses) = 4 / (4 + 6) = 4 / 10 = 0.4 = 40%
      ```
    Lösungsweg analog für die Programmaufrufe:  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`./paging-policy.py -s 1 -n 10`,  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`./paging-policy.py -s 2 -n 10`

2.  ###### For a cache of size 5, generate worst-case address reference streams for each of the following policies: `FIFO`, `LRU`, and `MRU` (worst-case reference streams cause the most misses possible).

    *  `FIFO` Replacement Policy:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`./paging-policy.py -C 5 -p FIFO -a 0,1,2,3,4,5,0,1,2,3,4,5 -c`,  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`./paging-policy.py -C 5 -p FIFO -a 0,1,2,3,4,5,6,7,8,9,10,11 -c`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--> `Hitrate = 0%`

    *  `LRU` Replacement Policy:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`./paging-policy.py -C 5 -p LRU -a 0,1,2,3,4,5,0,1,2,3,4,5 -c`,  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`./paging-policy.py -C 5 -p LRU -a 0,1,2,3,4,5,6,7,8,9,10,11 -c`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--> `Hitrate = 0%`

    *  `MRU` Replacement Policy:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`./paging-policy.py -C 5 -p MRU -a 0,1,2,3,4,5,4,5,4,5,4,5 -c`,  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`./paging-policy.py -C 5 -p MRU -a 0,1,2,3,4,5,6,7,8,9,10,11 -c`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--> `Hitrate = 0%`

    ###### For the worst case reference streams, how much bigger of a cache is needed
    to improve performance dramatically and approach `OPT`?

    *  `FIFO` Replacement Policy:

       -  `-a 0,1,2,3,4,5,0,1,2,3,4,5`:

          ```
          $ ./paging-policy.py -C 5 -p OPT -a 0,1,2,3,4,5,0,1,2,3,4,5 -c
          [...]
          FINALSTATS hits 5   misses 7   hitrate 41.67
          ```

          ```
          $ ./paging-policy.py -C 6 -p FIFO -a 0,1,2,3,4,5,0,1,2,3,4,5 -c
          [...]
          FINALSTATS hits 6   misses 6   hitrate 50.00
          ```

          Die cacheSize muss hier um 1 erhöht werden, um sich der Hitrate der `OPT`
          Replacement Policy anzunähern.

       -  `-a 0,1,2,3,4,5,6,7,8,9,10,11`:

          ```
          $ ./paging-policy.py -C 5 -p OPT -a 0,1,2,3,4,5,6,7,8,9,10,11 -c
          [...]
          FINALSTATS hits 0   misses 12   hitrate 0.00
          ```

          Bei diesem Address-Stream hat selbst die `OPT` Replacement Policy eine
          Hitrate von 0% (unabhänig von der Cache Größe), weshalb es egal ist wie sehr man die cacheSize bei der
          `FIFO` Replacement Policy erhöht, da die Hitrate immer 0% betragen
          wird.

    *  `LRU` Replacement Policy:

       -  `-a 0,1,2,3,4,5,0,1,2,3,4,5`:

          ```
          $ ./paging-policy.py -C 5 -p OPT -a 0,1,2,3,4,5,0,1,2,3,4,5 -c
          [...]
          FINALSTATS hits 5   misses 7   hitrate 41.67
          ```

          ```
          $ ./paging-policy.py -C 6 -p LRU -a 0,1,2,3,4,5,0,1,2,3,4,5 -c
          [...]
          FINALSTATS hits 6   misses 6   hitrate 50.00
          ```

          Hier muss die cacheSize ebenfalls um 1 erhöht werden, um die Hitrate
          stark zu erhöhen und sich der `OPT` Replacement Policy anzunähern.

       -  `-a 0,1,2,3,4,5,6,7,8,9,10,11`:

          analog zur `FIFO` Replacement Policy.

    *  `MRU` Replacement Policy:

       -  `-a 0,1,2,3,4,5,4,5,4,5,4,5`:

          ```
          $ ./paging-policy.py -C 5 -p OPT -a 0,1,2,3,4,5,4,5,4,5,4,5 -c
          [...]
          FINALSTATS hits 6   misses 6   hitrate 50.00
          ```

          ```
          $ ./paging-policy.py -C 6 -p MRU -a 0,1,2,3,4,5,4,5,4,5,4,5 -c
          [...]
          FINALSTATS hits 6   misses 6   hitrate 50.00
          ```

          Auch hier muss die cacheSize um 1 erhöht werden, um die Hitrate stark
          zu erhöhen und sich der `OPT` Replacement Policy anzunähern.

       -  `-a 0,1,2,3,4,5,6,7,8,9,10,11`:

          analog zur `FIFO` Replacement Policy.

3.  ###### Generate a random trace (use python or perl). How would you expect the different policies to perform on such a trace?
    Siehe: src/generate_random_trace.py und
    call_paging_policy_with_generated_addresses.sh

    *  `FIFO`:

       ```
       $ ./paging-policy.py -C 5 -p FIFO -a 10,9,5,3,6,4,9,3,5,7,10,6,3,9,7,3,10,11,9,10,3,8,10,8,5 -c
       [...]
       FINALSTATS hits 12   misses 13   hitrate 48.00
       ```

    *  `LRU`:

       ```
       $ ./paging-policy.py -C 5 -p LRU -a 10,9,5,3,6,4,9,3,5,7,10,6,3,9,7,3,10,11,9,10,3,8,10,8,5 -c
       [...]
       FINALSTATS hits 12   misses 13   hitrate 48.00
       ```
    *  `MRU`:

       ```
       $ ./paging-policy.py -C 5 -p MRU -a 10,9,5,3,6,4,9,3,5,7,10,6,3,9,7,3,10,11,9,10,3,8,10,8,5 -c
       [...]
       FINALSTATS hits 9   misses 16   hitrate 36.00
       ```

    *  `RAND`:

       ```
       $ ./paging-policy.py -C 5 -p RAND -a 10,9,5,3,6,4,9,3,5,7,10,6,3,9,7,3,10,11,9,10,3,8,10,8,5 -c
       [...]
       FINALSTATS hits 10   misses 15   hitrate 40.00
       ```

    *  `OPT`:

       ```
       $ ./paging-policy.py -C 5 -p RAND -a 10,9,5,3,6,4,9,3,5,7,10,6,3,9,7,3,10,11,9,10,3,8,10,8,5 -c
       [...]
       FINALSTATS hits 14   misses 11   hitrate 56.00
       ```

    *  `CLOCK`:

       ```
       $ ./paging-policy.py -C 5 -p CLOCK -a 10,9,5,3,6,4,9,3,5,7,10,6,3,9,7,3,10,11,9,10,3,8,10,8,5 -c
       [...]
       FINALSTATS hits 10   misses 15   hitrate 40.00
       ```

    Wie gut die Hitrate der einzelnen Policies bei einer zufälligen Pagesequenz
    ausfällt hängt stark von der Sequenz an sich ab:

    -  Besitzt sie eine gewisse lokalität, schneiden `LRU` und `CLOCK` deutlich
       besser ab als die anderen Verfahren (ausgenommen `OPT`, welches in der
       Praxis gar nicht existiert).

    -  Existiert keine Lokalität, ist es schwierig vorherzusagen, welche Policy
       die beste wäre.

4.  ###### Now generate a trace with some locality. How can you generate such a trace?

    Siehe: src/generate_trace_with_locality.py und
    call_paging_policy_with_generated_addresses.sh

    Relalisieren lässt sich eine Sequenz von Pages mit einer gewissen Lokalität
    mit Hilfe der Standardtnormalverteilung.

    ###### How does `LRU` perform on it?

    Da die `LRU` Replacement Policy immer die Page ersetzt, auf die in der
    Vergangenheit am wenigsten zugegriffen wurde und die Pagesequenz eine gewisse
    Lokalität aufweist, eignet sie sich relativ gut für dieses Szenario,
    jedoch muss der Cache auch groß genug sein:

    ```
    $ ./paging-policy.py -C 5 -p LRU -a 5,4,8,7,8,8,4,6,7,3 -c
    [...]
    FINALSTATS hits 15   misses 10   hitrate 60.00
    ```

    Die Anzahl an `HITS` ist jedoch auch stark abhänig von der chacheSize:

    ```
    $ ./paging-policy.py -C 4 -p LRU -a 5,4,8,7,8,8,4,6,7,3,4,3,9,4,5,4,3,8,8,3,6,5,6,4,3 -c
    [...]
    FINALSTATS hits 13   misses 12   hitrate 52.00
    ```

    Vegleich zur `OPT` Replacement Policy:

    ```
    $ ./paging-policy.py -C 5 -p OPT -a 5,4,8,7,8,8,4,6,7,3,4,3,9,4,5,4,3,8,8,3,6,5,6,4,3 -c
    [...]
    FINALSTATS hits 17   misses 8   hitrate 68.00
    ```

    ###### How much better than `RAND` is `LRU`?

    ```
    $ ./paging-policy.py -C 5 -p RAND -a 5,4,8,7,8,8,4,6,7,3,4,3,9,4,5,4,3,8,8,3,6,5,6,4,3 -c     
    FINALSTATS hits 17   misses 8   hitrate 68.00
    ```

    ```
    $ ./paging-policy.py -C 5 -p RAND -a 5,4,8,7,8,8,4,6,7,3,4,3,9,4,5,4,3,8,8,3,6,5,6,4,3 -c -s 2
    FINALSTATS hits 12   misses 13   hitrate 48.00
    ```

    `RAND` und `LRU` können gleich gute Ergebnisse liefern, jedoch ist im
    Allgemeinen `LRU` besser als `RAND`, da `LRU` die Vergangenheit mit
    einbezieht und dadurch öfters als `RAND` die "richtigen" Seiten austauscht.

    ###### How does `CLOCK` do?

    Auch `CLOCK` liefert in diesem Fall die selbe Hitrate wie `LRU` und `RAND`.

    ```
    $ ./paging-policy.py -C 5 -p CLOCK -a 5,4,8,7,8,8,4,6,7,3,4,3,9,4,5,4,3,8,8,3,6,5,6,4,3 -c
    [...]
    FINALSTATS hits 16   misses 9   hitrate 64.00
    ```

    ###### How about `CLOCK` with different numbers of clock bits?

    ```
    $ ./paging-policy.py -C 5 -p CLOCK -b 1 -a 5,4,8,7,8,8,4,6,7,3,4,3,9,4,5,4,3,8,8,3,6,5,6,4,3 -c
    [...]
    FINALSTATS hits 15   misses 10   hitrate 60.00
    ```

    ```
    $ ./paging-policy.py -C 5 -p CLOCK -b 2 -a 5,4,8,7,8,8,4,6,7,3,4,3,9,4,5,4,3,8,8,3,6,5,6,4,3 -c
    [...]
    FINALSTATS hits 16   misses 9   hitrate 64.00
    ```

    Je nach dem wie viele Clockbits verwendet werden, verbessert sich die Hitrate.
    Je mehr Clockbits desto besser sollte der Algorithmus herausfinden, welche
    Pages im Cache bleiben sollen und welche nicht.

5.  ###### Use a program like `valgrind` to instrument a real application and generate a virtual page reference stream. For example, running `valgrind --tool=lackey --trace-mem=yes ls` will output a nearly-complete reference trace of every instruction and data reference made by the program `ls`. To make this useful for the simulator above, you’ll have to first transform each virtual memory reference into a virtual page-number reference (done by masking off the offset and shifting the resulting bits downward). How big of a cache is needed for your application trace in order to satisfy a large fraction of requests?

    **Bsp. `VA 0x04001090`:**

    ```
    #Bits VA = 48
    virtualAddressSpaceSize = 2^48
    pageSize = 4096
    rootPageTableSize = virtualAddressSpaceSize / pageSize = 2^48 / 4096
                      = 2^48 / 2^12 = 2^36 = 68719476736
    #Bits VPN = log_2(rootPageTableSize) = log_2(2^36) = 36
    #Bits Offset = #Bits VA - #Bits VPN = 48 - 36 = 12

    VA = (4001090)_hex = (0100 0000 0000 0001 0000 1001 0000)_bin
                          |_________________| |____________|
                                   |                 |
                                  VPN              Offset
                                   =
                        1 + 131072 = 131073

    --> VPN = 134073
    ```

    Siehe auch src/determine_vpn.py, src/run_paging_policy_with_generated_addresses.sh

    *  `LRU`:

       ```
       chacheSize: 1
       FINALSTATS hits 13736   misses 7551   hitrate 64.53
       ```

       ```
       cacheSize: 2
       FINALSTATS hits 19732   misses 1555   hitrate 92.70
       ```

       ```
       cacheSize: 4
       FINALSTATS hits 21133   misses 154   hitrate 99.2
       ```

       ```
       cacheSize: 6
       FINALSTATS hits 21270   misses 17   hitrate 99.92
       ```

       ```
       cacheSize: 7
       FINALSTATS hits 21272   misses 15   hitrate 99.93
       ```

       ```
       cacheSize: 16
       FINALSTATS hits 21272   misses 15   hitrate 99.93
       ```

       ```
       cacheSize: 256
       FINALSTATS hits 21272   misses 15   hitrate 99.93
       ```

    *  `OPT`:

       ```
       cacheSize: 1
       [...]
       FINALSTATS hits 13736   misses 7551   hitrate 64.53
       ```

       ```
       cacheSize: 2
       FINALSTATS hits 19735   misses 1552   hitrate 92.71
       ```

       ```
       cacheSize: 4
       FINALSTATS hits 21180   misses 107   hitrate 99.50
       ```

       ```
       cacheSize: 16
       FINALSTATS hits 21272   misses 15   hitrate 99.93
       ```

       ```
       cacheSize: 256
       FINALSTATS hits 21272   misses 15   hitrate 99.93

       ```

    Bei einer Größe von 7 ist die Hitrate am größten und steigert sich bei
    weiterem vergrößern der Cachegröße nicht mehr.
