# Answers

1.  Der Programmaufruf `$ ./malloc.py -n 10 -H 0 -p BEST -s 0` liefet
    folgende Ausgabe:

    ```
    $ ./malloc.py -n 10 -H 0 -p BEST -s 0
    seed 0
    size 100
    baseAddr 1000
    headerSize 0
    alignment -1
    policy BEST
    listOrder ADDRSORT
    coalesce False
    numOps 10
    range 10
    percentAlloc 50
    allocList
    compute False

    ptr[0] = Alloc(3)  returned ?
    List?

    Free(ptr[0]) returned ?
    List?

    ptr[1] = Alloc(5)  returned ?
    List?

    Free(ptr[1]) returned ?
    List?

    ptr[2] = Alloc(8)  returned ?
    List?

    Free(ptr[2]) returned ?
    List?

    ptr[3] = Alloc(8)  returned ?
    List?

    Free(ptr[3]) returned ?
    List?

    ptr[4] = Alloc(2)  returned ?
    List?

    ptr[5] = Alloc(7)  returned ?
    List?
    ```

    Um herauszufinden, was `alloc()`  bzw. `free()` zurückliefert, sowie den
    Zustand der Free-Liste, geht man folgendermaßen vor:

    1.  Rückgabewert von `alloc()` bzw. `free()` bestimmen, sowie die Anzahl der
        Elemente die in der Free-Liste durchsucht werden (nur bei `alloc()`):

        *  **alloc():**  

           `elementsSearched =` Abhänig von der eingesetzten Strategie um den
           freien Speicher zu verwalten:

           *  **BEST FIT**:

              Die Free-Liste wird einmal **komplett** durchlaufen, um
              Speicherbereiche zu finden, welche größer oder gleich der
              angefragten Speichergröße sind.  
              Anschließend wird von den möglichen Kandidaten derjenige
              Speicherbereich ausgewählt, welcher am **kleinsten** ist.

           *  **WORST FIT**:

              Die Free-Liste wird ebenfalls einmal **komplett** durchlaufen, um
              Speicherbereiche zu finden welche größer oder gleich der
              angeforderten Speichergröße sind.
              Anschließend wird von den möglichen Kandidaten derjenige
              Speicherbereich ausgewählt, welcher am **größten** ist
              (**Gegenteil zu FIRST FIT**).

           *  **FIRST FIT**:

              Die Liste wird solange durchlaufen, bis ein Speicherblock gefunden
              wurde, welcher **größer oder gleich** der angeforderten
              Speichergröße ist.

           *  **NEXT FIT**:

              Anstatt immer mit dem ersten Element der Free-Liste bei der Suche
              nach einem geeignetem Speicherbereich zu beginnen, hat der
              NEXT FIT-Algorithmus einen Zeiger auf das zuletzt betrachtete
              Element der Free-Liste.

              Daher sucht man nun von dem zuletzt betrachteten Element der Liste
              solange weiter, bis man auf einen freien Speicherbereich trifft,
              der **groß** genug ist um den angeforderten Speicherbereich zu
              reservieren.

           `retValAlloc = addrOfFreeSpaceThatFits + headerSize`  
           `newSz = szOfFreeSpaceThatFits - bytesToAlloc`  

           Falls Speicher frei bleibt (`newSz > 0`):  
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`sizeOfNewFreeList = sizeOfOldFreeList`  
           Anderenfalls:  
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`sizeOfNewFreeList = sizeOfOldFreeList - 1`

        *  **free()**  
           `retValFree = 0`  
           `sizeOfNewFreeList = sizeOfOldFreeList + 1`  
           `newFreedEntry = [ adr:addrOfPointerToFree sz:szOfPointerToFree ]`  

    2.  Neue Free-Liste bestimmen

    **Lösung:**

    `baseAddr = 1000`  
    `initSizeOfFreeList = 100`  
    `headerSize = 0`  
    `policy = BEST`

    `initFreeList = Free List [ Size 1 ]:  [ addr:1000 sz:100 ]`

    ---

    *  `ptr[0] = Alloc(3)`:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`retValAlloc = addrOfFreeSpaceThatFits + headerSize = 1000 + 0 = 1000`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`numOfElementsSearched = sizeOfOldFreeList = 1`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `bytesToAlloc = 3`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newAddr = retValAlloc + bytesToAlloc = 1000 + 3 = 1003`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newSz = oldSz - bytesToAlloc = 100 - 3 = 97`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `sizeOfNewFreeList = sizeOfOldFreeList = 1`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`newFreeList = Free List [ Size 1 ]: [ addr:1003 sz:97 ]`
       ```
       ptr[0] = Alloc(3)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1003 sz:97 ]
       ```
    ---

    *  `Free(ptr[0])`:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`retValFree = 0`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `sizeOfNewFreeList = sizeOfOldFreeList + 1 = 1 + 1 = 2`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newFreedEntry = [ adr:addrOfPointerToFree sz:szOfPointerToFree] = [ adr:1000 sz:3 ]`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`newFreeList = Free List [ Size 2 ]: [ addr:1000 sz:3 ] [ addr:1003 sz:97 ]`

       ```
       Free(ptr[0]) returned 0
       Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:97 ]
       ```

    ---

    *  `ptr[1] = Alloc(5)`:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`retValAlloc = addrOfFreeSpaceThatFits + headerSize = 1003 + 0 = 1003`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`numOfElementsSearched = sizeOfOldFreeList = 2`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `bytesToAlloc = 5`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newAddr = retValAlloc + bytesToAlloc = 1003 + 5 = 1008`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newSz = szOfFreeSpaceThatFits - bytesToAlloc = 97 - 5 = 92`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `sizeOfNewFreeList = sizeOfOldFreeList = 2`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`newFreeList = Free List [ Size 2 ]: [ addr:1000 sz:3 ] [ addr:1008 sz:92 ]`

       ```
       ptr[1] = Alloc(5)  returned 1003 (searched 2 elements)
       Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:92 ]
       ```
    ---

    *  `Free(ptr[1])`:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`retValFree = 0`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `sizeOfNewFreeList = sizeOfOldFreeList + 1 = 2 + 1 = 3`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newFreedEntry = [ adr:addrOfPointerToFree sz:szOfPointerToFree] = [ adr:1003 sz:5 ]`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`newFreeList = Free List [ Size 3 ]: [ addr:1000 sz:3 ] [ addr:1003 sz:5 ]`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `[ addr:1003 sz:97 ]`

       ```
       Free(ptr[1]) returned 0
       Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:92 ]
       ```
    ---

    *  `ptr[2] = Alloc(8)`:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`retValAlloc = addrOfFreeSpaceThatFits + headerSize = 1008 + 0 = 1008`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`numOfElementsSearched = sizeOfOldFreeList = 3`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `bytesToAlloc = 8`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newAddr = retValAlloc + bytesToAlloc = 1008 + 8 = 1016`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newSz = szOfFreeSpaceThatFits - bytesToAlloc = 92 - 8 = 84`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `sizeOfNewFreeList = sizeOfOldFreeList = 3`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`newFreeList = Free List [ Size 3 ]: [ addr:1000 sz:3 ] [ addr:1003 sz:5 ]`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `[ addr:1016 sz:84 ]`

       ```
       ptr[2] = Alloc(8)  returned 1008 (searched 3 elements)
       Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]
       ```
    ---

    *  `Free(ptr[2])`:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`retValFree = 0`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `sizeOfNewFreeList = sizeOfOldFreeList + 1 = 3 + 1 = 4`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newFreedEntry = [ adr:addrOfPointerToFree sz:szOfPointerToFree] = [ adr:1008 sz:8 ]`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`newFreeList = Free List [ Size 4 ]: [ addr:1000 sz:3 ] [ addr:1003 sz:5 ]`    
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `[ addr:1008 sz:8 ] [ addr:1016 sz:84 ]`

       ```
       Free(ptr[2]) returned 0
       Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]
       ```
    ---

    *  `ptr[3] = Alloc(8)`:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`retValAlloc = addrOfFreeSpaceThatFits + headerSize = 1008 + 0 = 1008`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`numOfElementsSearched = sizeOfOldFreeList = 4`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `bytesToAlloc = 8`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newAddr = retValAlloc + bytesToAlloc = 1008 + 8 = 1016`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newSz = szOfFreeSpaceThatFits - bytesToAlloc = 8 - 8 = 0`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `sizeOfNewFreeList = sizeOfOldFreeList - 1 = 3`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`newFreeList = Free List [ Size 3 ]: [ addr:1000 sz:3 ] [ addr:1003 sz:5 ]`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `[ addr:1016 sz:84 ]`

       ```
       ptr[3] = Alloc(8)  returned 1008 (searched 4 elements)
       Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]
       ```
    ---

    *  `Free(ptr[3])`:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`retValFree = 0`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `sizeOfNewFreeList = sizeOfOldFreeList + 1 = 3 + 1 = 4`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newFreedEntry = [ adr:addrOfPointerToFree sz:szOfPointerToFree] = [ adr:1008 sz:8 ]`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`newFreeList = Free List [ Size 4 ]: [ addr:1000 sz:3 ] [ addr:1003 sz:5 ]`    
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `[ addr:1008 sz:8 ] [ addr:1016 sz:84 ]`

       ```
       Free(ptr[3]) returned 0
       Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]
       ```
    ---

    *  `ptr[4] = Alloc(2)`:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`retValAlloc = addrOfFreeSpaceThatFits + headerSize = 1000 + 0 = 1000`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`numOfElementsSearched = sizeOfOldFreeList = 4`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `bytesToAlloc = 2`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newAddr = retValAlloc + bytesToAlloc = 1000 + 2 = 1002`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newSz = szOfFreeSpaceThatFits - bytesToAlloc = 3 - 2 = 1`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `sizeOfNewFreeList = sizeOfOldFreeList = 4`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`newFreeList = Free List [ Size 4 ]: [ addr:1002 sz:1 ] [ addr:1003 sz:5 ]`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `[ addr:1008 sz:8 ] [ addr:1016 sz:84 ]`

       ```
       ptr[4] = Alloc(2)  returned 1000 (searched 4 elements)
       Free List [ Size 4 ]:  [ addr:1002 sz:1 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]
       ```

    ---

    *  `ptr[5] = Alloc(7)`:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`retValAlloc = addrOfFreeSpaceThatFits + headerSize = 1008 + 0 = 1008`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`numOfElementsSearched = sizeOfOldFreeList = 4`

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `bytesToAlloc = 7`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newAddr = retValAlloc + bytesToAlloc = 1008 + 7 = 1015`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `newSz = szOfFreeSpaceThatFits - bytesToAlloc = 8 - 7 = 1`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `sizeOfNewFreeList = sizeOfOldFreeList = 4`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       -->`newFreeList = Free List [ Size 4 ]: [ addr:1002 sz:1 ] [ addr:1003 sz:5 ]`  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `[ addr:1015 sz:1 ] [ addr:1016 sz:84 ]`

       ```
       ptr[5] = Alloc(7)  returned 1008 (searched 4 elements)
       Free List [ Size 4 ]:  [ addr:1002 sz:1 ] [ addr:1003 sz:5 ] [ addr:1015 sz:1 ] [ addr:1016 sz:84 ]
       ```
    ---

    Über die Zeit fällt auf, dass die Free-Liste über die Zeit immer größer wird,
    jedoch sinkt ebenfalls die Speichergröße der einzelnen Blöcke -->
    **externe Fragmentierung wächst**.

2.  Free-Liste nach vollständigem Durchlauf des Programms `malloc.py` mit
    `BEST FIT`-Policy:

    ```
    $ ./malloc.py -n 10 -H 0 -p BEST -s 0 -c

    [...]

    Free List [ Size 4 ]:  [ addr:1002 sz:1 ] [ addr:1003 sz:5 ] [ addr:1015 sz:1 ] [ addr:1016 sz:84 ]
    ```

    Ausgabe des Programms `malloc.py` mit `WORST FIT`-Policy:

    ```
    $ ./malloc.py -n 10 -H 0 -p WORST -s 0 -c
    seed 0
    size 100
    baseAddr 1000
    headerSize 0
    alignment -1
    policy WORST
    listOrder ADDRSORT
    coalesce False
    numOps 10
    range 10
    percentAlloc 50
    allocList
    compute True

    ptr[0] = Alloc(3)  returned 1000 (searched 1 elements)
    Free List [ Size 1 ]:  [ addr:1003 sz:97 ]

    Free(ptr[0]) returned 0
    Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:97 ]

    ptr[1] = Alloc(5)  returned 1003 (searched 2 elements)
    Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:92 ]

    Free(ptr[1]) returned 0
    Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:92 ]

    ptr[2] = Alloc(8)  returned 1008 (searched 3 elements)
    Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]

    Free(ptr[2]) returned 0
    Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

    ptr[3] = Alloc(8)  returned 1016 (searched 4 elements)
    Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1024 sz:76 ]

    Free(ptr[3]) returned 0
    Free List [ Size 5 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:8 ]
                           [ addr:1024 sz:76 ]

    ptr[4] = Alloc(2)  returned 1024 (searched 5 elements)
    Free List [ Size 5 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:8 ]
                           [ addr:1026 sz:74 ]

    ptr[5] = Alloc(7)  returned 1026 (searched 5 elements)
    Free List [ Size 5 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:8 ]
                           [ addr:1033 sz:67 ]
    ```

    Verwendet man anstatt der `BEST FIT`-Ploicy die `WORST FIT`-Ploicy, wird
    immer der **größtmögliche** freie Speicherblock verwendet, anstatt der
    kleinstmögliche freie Speicherblock (Gegenteil von `BEST FIT`-Policy).

    Dadurch wird versucht große freie Speicherblöcke frei zu lassen, anstatt
    viele kleine Speicherblöcke.

    Bei der `WORST FIT`-Policy werden jedoch kleine erzeugte Speicherbereiche
    erst wieder verwendet, wenn keine großen Speicherbereiche mehr existieren.

3.  Die `FIRST FIT`-Policy versucht im Gegensatz zur `BEST FIT`-Policy sowie
    `WORST FIT`-Policy das Durchlaufen der gesamten Free-Liste zu vermeiden,
    indem sie die Liste von vorne durchläuft, bis ein geeigneter Speicherblock
    gefunden wurde. Hierdurch wird die Suche nach einem geeignetem Speicherblock
    beschleunigt.

    Ausgabe des Programms `malloc.py` mit `FIRST FIT`-Policy:

    ```
    $ ./malloc.py -n 10 -H 0 -p FIRST -s 0 -c
    seed 0
    size 100
    baseAddr 1000
    headerSize 0
    alignment -1
    policy FIRST
    listOrder ADDRSORT
    coalesce False
    numOps 10
    range 10
    percentAlloc 50
    allocList
    compute True

    ptr[0] = Alloc(3)  returned 1000 (searched 1 elements)
    Free List [ Size 1 ]:  [ addr:1003 sz:97 ]

    Free(ptr[0]) returned 0
    Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:97 ]

    ptr[1] = Alloc(5)  returned 1003 (searched 2 elements)
    Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:92 ]

    Free(ptr[1]) returned 0
    Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:92 ]

    ptr[2] = Alloc(8)  returned 1008 (searched 3 elements)
    Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]

    Free(ptr[2]) returned 0
    Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

    ptr[3] = Alloc(8)  returned 1008 (searched 3 elements)
    Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]

    Free(ptr[3]) returned 0
    Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

    ptr[4] = Alloc(2)  returned 1000 (searched 1 elements)
    Free List [ Size 4 ]:  [ addr:1002 sz:1 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

    ptr[5] = Alloc(7)  returned 1008 (searched 3 elements)
    Free List [ Size 4 ]:  [ addr:1002 sz:1 ] [ addr:1003 sz:5 ] [ addr:1015 sz:1 ] [ addr:1016 sz:84 ]
    ```

4.  *  `BEST FIT`-Policy mit `ADDRSORT`, `SIZESORT+`,
       sowie `SIZESORT-` Sortierung:

       Die Sortierung hat keine Auswirkung, da sowieso die ganze Liste durchsucht
       werden muss.

    *  `WORST FIT`-Policy mit `ADDRSORT`, `SIZESORT+`,
       sowie `SIZESORT-` Sortierung:

       Analog zur `BEST FIT`-Policy.

    *  `FIRST FIT`-Policy mit `ADDRSORT` Sortierung:

       Die `ADDRSORT` Sortierung hat keine Auswirkungen auf die Geschwindigkeit
       der Suche mit der `FIRST FIT`-Policy, da die Geschwindigkeit nicht von
       den Adressen abhängt, sondern von den Größen der freien Speicherblöcke.

    *  `FIRST FIT`-Policy mit `SIZESORT+` Sortierung:

       Die `SIZESORT+` Sortierung (aufsteigend) kann eine negative Auswirkung auf die
       Geschwindigkeit der Suche mittels `FIRST FIT`-Policy haben, wenn
       es sehr viele kleine Speicherbereiche gibt, aber nur wenige große
       Speicherbereiche. Dadurch muss die Liste fast (oder sogar ganz) bis zum
       Ende durchlaufen werden, für große Speicheranfragen.

    *  `FIRST FIT`-Policy mit `SIZESORT-` Sortierung:

       Die `SIZESORT-` Sortierung (absteigend) hat eine positive Auswirkung auf
       die Geschwindigkeit der Suche mittels `FIRST FIT`-Policy, da nun die
       größten freien Speicherblöcke am Anfang der Free-Liste stehen und somit
       immer das erste Element den Speicheranfragen genügt. Dies trifft solange
       zu, bis eine Speicheranfrage gestellt wird, die größer als der größte
       verfügbare Speicherblock in der Free-Liste ist (1. Element der Free-Liste).

5.  *  Wenn keine `Coalescing` ("Verschmelzen") verwendet wird, und die Anzahl an
       Allokierungen stark zunimmt  
       (hier `-n 1000`), kommt es über die Zeit vor,
       dass `alloc()` für Speicheranfragen `-1` zurückliefert, da keine genügend großen
       Speicherblöcke in der Free-Liste vorhanden sind (--> **sehr starke externe
       Fragmentierung der Free-Liste**).  
       Es wäre zwar genügend Speicher vorhanden, jedoch nicht zusammenhängend.

       **Beispiel ohne Coalescing:**

       ```
       $ ./malloc.py -n 1000 -c

       ptr[0] = Alloc(3)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1003 sz:97 ]

       Free(ptr[0]) returned 0
       Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:97 ]

       [...]

       ptr[590] = Alloc(9)  returned -1 (searched 31 elements)
       Free List [ Size 31 ]:  [ addr:1000 sz:2 ] [ addr:1002 sz:1 ] [ addr:1006 sz:1 ] [ addr:1007 sz:1 ]
                               [ addr:1008 sz:5 ] [ addr:1013 sz:1 ] [ addr:1014 sz:1 ] [ addr:1015 sz:1 ]
                               [ addr:1016 sz:5 ] [ addr:1021 sz:1 ] [ addr:1022 sz:3 ] [ addr:1031 sz:1 ]
                               [ addr:1032 sz:2 ] [ addr:1034 sz:3 ] [ addr:1037 sz:4 ] [ addr:1041 sz:1 ]
                               [ addr:1042 sz:2 ] [ addr:1052 sz:1 ] [ addr:1053 sz:6 ] [ addr:1059 sz:2 ]
                               [ addr:1061 sz:1 ] [ addr:1068 sz:1 ] [ addr:1069 sz:3 ] [ addr:1072 sz:5 ]
                               [ addr:1077 sz:3 ] [ addr:1080 sz:1 ] [ addr:1081 sz:5 ] [ addr:1086 sz:3 ]
                               [ addr:1089 sz:5 ] [ addr:1094 sz:2 ] [ addr:1096 sz:4 ]
       ```

       Der Ausschnitt der Free-Liste:  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
       `[ addr:1006 sz:1 ] [ addr:1007 sz:1 ] [ addr:1008 sz:5 ] [ addr:1013 sz:1 ] [ addr:1014 sz:1 ]`  
       wäre verschmolzen groß genug um der Speicheranfrage von 9b zu genügen.

       Zusätzlich wird die Suche der Free-Liste verlangsamt, da sehr viele
       Elemente (im Gegensatz zum `Coalescing`-Verfahren) in der Free-Liste
       vorhanden sind und diese durchsucht werden müssen. Dies gilt besonders
       für die `BEST FIT`-Policy, sowie die `WORST FIT`-Policy.  
       Es kann jedoch auch Auswirkungen auf die `FIRST FIT`-Policy haben
       (ohne `SIZESORT-` Sortierung).

    *  Verwendet man zusätzlich `Coalescing`, werden bei `free()`-Aufrufen,
       benachbarte Speicherbereiche miteinander verschmolzen, um die externe
       Fragmentierung zu verringern.

       **Beispiel mit Coalescing:**

       ```
       $ ./malloc.py -n 1000 -C -c

       ptr[0] = Alloc(3)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1003 sz:97 ]

       Free(ptr[0]) returned 0
       Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

       [...]

       ptr[514] = Alloc(2)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1002 sz:98 ]
       ```

       Man kann sehr gut erkennen, dass die Free-Liste sehr viel kleiner geworden
       ist, obwohl die selben `alloc()` bzw. `free()`-Aufrufe stattgefunden haben.

    *  Die Sortierung der Free-Liste hat lediglich Auswirkungen auf die
       `FIRST FIT`-Policy.

6.  *  Wenn man den prozentualen Anteil von Allokationen über 50 setzt, werden die
       meisten Operationen Allokierungen sein.

       **Beispiel:**

       ```
       $ ./malloc.py -n 10 -H 0 -p BEST -P 70 -s 0 -c
       seed 0
       size 100
       baseAddr 1000
       headerSize 0
       alignment -1
       policy BEST
       listOrder ADDRSORT
       coalesce False
       numOps 10
       range 10
       percentAlloc 70
       allocList
       compute True

       ptr[0] = Alloc(3)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1003 sz:97 ]

       ptr[1] = Alloc(5)  returned 1003 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1008 sz:92 ]

       Free(ptr[0]) returned 0
       Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:92 ]

       ptr[2] = Alloc(6)  returned 1008 (searched 2 elements)
       Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1014 sz:86 ]

       Free(ptr[2]) returned 0
       Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:6 ] [ addr:1014 sz:86 ]

       ptr[3] = Alloc(8)  returned 1014 (searched 3 elements)
       Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:6 ] [ addr:1022 sz:78 ]

       ptr[4] = Alloc(3)  returned 1000 (searched 3 elements)
       Free List [ Size 2 ]:  [ addr:1008 sz:6 ] [ addr:1022 sz:78 ]

       Free(ptr[4]) returned 0
       Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:6 ] [ addr:1022 sz:78 ]

       Free(ptr[3]) returned 0
       Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:6 ] [ addr:1014 sz:8 ] [ addr:1022 sz:78 ]

       ptr[5] = Alloc(8)  returned 1014 (searched 4 elements)
       Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:6 ] [ addr:1022 sz:78 ]
       ```
       --> Anzahl an Allokierungen = 6  
       --> Anzahl an Speicherfreigaben = 4  
       --> prozentualer Anteil an Allokierungen = (6 / 10) * 100 = 60%  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(nähert sich bei größerer Anzahl von Operationen 70%)  
       --> prozentualer Anteil an Speicherfreigaben = (4 / 10) * 100 = 40%

    *  Setzt man den prozentualen Anteil von Allokationen nahe 100, wereden fast
       alle Operationen Allokierungen sein.

       **Beispiel:**

       ```
       $ ./malloc.py -n 10 -H 0 -p BEST -P 90 -s 0 -c
       seed 0
       size 100
       baseAddr 1000
       headerSize 0
       alignment -1
       policy BEST
       listOrder ADDRSORT
       coalesce False
       numOps 10
       range 10
       percentAlloc 90
       allocList
       compute True

       ptr[0] = Alloc(8)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1008 sz:92 ]

       ptr[1] = Alloc(3)  returned 1008 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1011 sz:89 ]

       ptr[2] = Alloc(5)  returned 1011 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1016 sz:84 ]

       ptr[3] = Alloc(4)  returned 1016 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1020 sz:80 ]

       ptr[4] = Alloc(6)  returned 1020 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1026 sz:74 ]

       Free(ptr[2]) returned 0
       Free List [ Size 2 ]:  [ addr:1011 sz:5 ] [ addr:1026 sz:74 ]

       ptr[5] = Alloc(8)  returned 1026 (searched 2 elements)
       Free List [ Size 2 ]:  [ addr:1011 sz:5 ] [ addr:1034 sz:66 ]

       ptr[6] = Alloc(3)  returned 1011 (searched 2 elements)
       Free List [ Size 2 ]:  [ addr:1014 sz:2 ] [ addr:1034 sz:66 ]

       Free(ptr[6]) returned 0
       Free List [ Size 3 ]:  [ addr:1011 sz:3 ] [ addr:1014 sz:2 ] [ addr:1034 sz:66 ]

       ptr[7] = Alloc(10)  returned 1034 (searched 3 elements)
       Free List [ Size 3 ]:  [ addr:1011 sz:3 ] [ addr:1014 sz:2 ] [ addr:1044 sz:56 ]
       ```
       --> Anzahl an Allokierungen = 8;  
       --> Anzahl an Speicherfreigaben = 2;  
       --> prozentualer Anteil von Allokierungen = (8 / 10) * 100  = 80%  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(nähert sich bei größerer Anzahl von Operationen 90%)  
       --> prozentualer Anteil an Speicherfreigaben = (2 / 10) * 100 = 20%

    *  Setzt man den prozentualen Anteil von Allokationen nahe 0, werden sowohl der
       prozentuale Anteil an Allokierungen, als auch der prozentuale Anteil an
       Speicherfreigaben bei ca. 50% liegen, da man Speicher nur freigeben kann, wenn
       zuvor Speicher allokiert wurde.   

       **Beispiel:**

       ```
       ptr[0] = Alloc(8)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1008 sz:92 ]

       Free(ptr[0]) returned 0
       Free List [ Size 2 ]:  [ addr:1000 sz:8 ] [ addr:1008 sz:92 ]

       ptr[1] = Alloc(5)  returned 1000 (searched 2 elements)
       Free List [ Size 2 ]:  [ addr:1005 sz:3 ] [ addr:1008 sz:92 ]

       Free(ptr[1]) returned 0
       Free List [ Size 3 ]:  [ addr:1000 sz:5 ] [ addr:1005 sz:3 ] [ addr:1008 sz:92 ]

       ptr[2] = Alloc(4)  returned 1000 (searched 3 elements)
       Free List [ Size 3 ]:  [ addr:1004 sz:1 ] [ addr:1005 sz:3 ] [ addr:1008 sz:92 ]

       Free(ptr[2]) returned 0
       Free List [ Size 4 ]:  [ addr:1000 sz:4 ] [ addr:1004 sz:1 ] [ addr:1005 sz:3 ] [ addr:1008 sz:92 ]

       ptr[3] = Alloc(8)  returned 1008 (searched 4 elements)
       Free List [ Size 4 ]:  [ addr:1000 sz:4 ] [ addr:1004 sz:1 ] [ addr:1005 sz:3 ] [ addr:1016 sz:84 ]

       Free(ptr[3]) returned 0
       Free List [ Size 5 ]:  [ addr:1000 sz:4 ] [ addr:1004 sz:1 ] [ addr:1005 sz:3 ] [ addr:1008 sz:8 ]
                              [ addr:1016 sz:84 ]

       ptr[4] = Alloc(7)  returned 1008 (searched 5 elements)
       Free List [ Size 5 ]:  [ addr:1000 sz:4 ] [ addr:1004 sz:1 ] [ addr:1005 sz:3 ] [ addr:1015 sz:1 ]
                              [ addr:1016 sz:84 ]

       Free(ptr[4]) returned 0
       Free List [ Size 6 ]:  [ addr:1000 sz:4 ] [ addr:1004 sz:1 ] [ addr:1005 sz:3 ] [ addr:1008 sz:7 ]
                              [ addr:1015 sz:1 ] [ addr:1016 sz:84 ]
       ```
       --> Anzahl an Allokierungen = 5  
       --> Anzahl an Speicherfreigaben = 5  
       --> prozentualer Anteil an Allokierungen = (5 / 10) *  100 = 50%  
       --> prozentualer Anteil an Speicherfreigaben = (5 / 10) * 100 = 50%

7.  *  Programmaufruf, um eine sehr fragmentierte Free-Liste zu erhalten:

       ```
       $ ./malloc.py -A +1,-0,+2,-1,+3,-2,+4,-3,+5,-4,+6,-5,+7,-6,+8,-7,+9,-8,+10,-9 -c
       seed 0
       size 100
       baseAddr 1000
       headerSize 0
       alignment -1
       policy BEST
       listOrder ADDRSORT
       coalesce False
       numOps 10
       range 10
       percentAlloc 50
       allocList +1,-0,+2,-1,+3,-2,+4,-3,+5,-4,+6,-5,+7,-6,+8,-7,+9,-8,+10,-9
       compute True

       ptr[0] = Alloc(1)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1001 sz:99 ]

       Free(ptr[0]) returned 0
       Free List [ Size 2 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:99 ]

       ptr[1] = Alloc(2)  returned 1001 (searched 2 elements)
       Free List [ Size 2 ]:  [ addr:1000 sz:1 ] [ addr:1003 sz:97 ]

       Free(ptr[1]) returned 0
       Free List [ Size 3 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:97 ]

       ptr[2] = Alloc(3)  returned 1003 (searched 3 elements)
       Free List [ Size 3 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1006 sz:94 ]

       Free(ptr[2]) returned 0
       Free List [ Size 4 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:94 ]

       ptr[3] = Alloc(4)  returned 1006 (searched 4 elements)
       Free List [ Size 4 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1010 sz:90 ]

       Free(ptr[3]) returned 0
       Free List [ Size 5 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                              [ addr:1010 sz:90 ]

       ptr[4] = Alloc(5)  returned 1010 (searched 5 elements)
       Free List [ Size 5 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                              [ addr:1015 sz:85 ]

       Free(ptr[4]) returned 0
       Free List [ Size 6 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                              [ addr:1010 sz:5 ] [ addr:1015 sz:85 ]

       ptr[5] = Alloc(6)  returned 1015 (searched 6 elements)
       Free List [ Size 6 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                              [ addr:1010 sz:5 ] [ addr:1021 sz:79 ]

       Free(ptr[5]) returned 0
       Free List [ Size 7 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                              [ addr:1010 sz:5 ] [ addr:1015 sz:6 ] [ addr:1021 sz:79 ]

       ptr[6] = Alloc(7)  returned 1021 (searched 7 elements)
       Free List [ Size 7 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                              [ addr:1010 sz:5 ] [ addr:1015 sz:6 ] [ addr:1028 sz:72 ]

       Free(ptr[6]) returned 0
       Free List [ Size 8 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                              [ addr:1010 sz:5 ] [ addr:1015 sz:6 ] [ addr:1021 sz:7 ] [ addr:1028 sz:72 ]

       ptr[7] = Alloc(8)  returned 1028 (searched 8 elements)
       Free List [ Size 8 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                              [ addr:1010 sz:5 ] [ addr:1015 sz:6 ] [ addr:1021 sz:7 ] [ addr:1036 sz:64 ]

       Free(ptr[7]) returned 0
       Free List [ Size 9 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                              [ addr:1010 sz:5 ] [ addr:1015 sz:6 ] [ addr:1021 sz:7 ] [ addr:1028 sz:8 ]
                              [ addr:1036 sz:64 ]

       ptr[8] = Alloc(9)  returned 1036 (searched 9 elements)
       Free List [ Size 9 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                              [ addr:1010 sz:5 ] [ addr:1015 sz:6 ] [ addr:1021 sz:7 ] [ addr:1028 sz:8 ]
                              [ addr:1045 sz:55 ]

       Free(ptr[8]) returned 0
       Free List [ Size 10 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                               [ addr:1010 sz:5 ] [ addr:1015 sz:6 ] [ addr:1021 sz:7 ] [ addr:1028 sz:8 ]
                               [ addr:1036 sz:9 ] [ addr:1045 sz:55 ]

       ptr[9] = Alloc(10)  returned 1045 (searched 10 elements)
       Free List [ Size 10 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                               [ addr:1010 sz:5 ] [ addr:1015 sz:6 ] [ addr:1021 sz:7 ] [ addr:1028 sz:8 ]
                               [ addr:1036 sz:9 ] [ addr:1055 sz:45 ]

       Free(ptr[9]) returned 0
       Free List [ Size 11 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                               [ addr:1010 sz:5 ] [ addr:1015 sz:6 ] [ addr:1021 sz:7 ] [ addr:1028 sz:8 ]
                               [ addr:1036 sz:9 ] [ addr:1045 sz:10 ] [ addr:1055 sz:45 ]
       ```

    *  Programmaufruf fragmentierter Free-Liste mit `Coalescing`:

       ```
       $ ./malloc.py -A +1,-0,+2,-1,+3,-2,+4,-3,+5,-4,+6,-5,+7,-6,+8,-7,+9,-8,+10,-9 -C -c
       seed 0
       size 100
       baseAddr 1000
       headerSize 0
       alignment -1
       policy BEST
       listOrder ADDRSORT
       coalesce True
       numOps 10
       range 10
       percentAlloc 50
       allocList +1,-0,+2,-1,+3,-2,+4,-3,+5,-4,+6,-5,+7,-6,+8,-7,+9,-8,+10,-9
       compute True

       ptr[0] = Alloc(1)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1001 sz:99 ]

       Free(ptr[0]) returned 0
       Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

       ptr[1] = Alloc(2)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1002 sz:98 ]

       Free(ptr[1]) returned 0
       Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

       ptr[2] = Alloc(3)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1003 sz:97 ]

       Free(ptr[2]) returned 0
       Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

       ptr[3] = Alloc(4)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1004 sz:96 ]

       Free(ptr[3]) returned 0
       Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

       ptr[4] = Alloc(5)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1005 sz:95 ]

       Free(ptr[4]) returned 0
       Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

       ptr[5] = Alloc(6)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1006 sz:94 ]

       Free(ptr[5]) returned 0
       Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

       ptr[6] = Alloc(7)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1007 sz:93 ]

       Free(ptr[6]) returned 0
       Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

       ptr[7] = Alloc(8)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1008 sz:92 ]

       Free(ptr[7]) returned 0
       Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

       ptr[8] = Alloc(9)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1009 sz:91 ]

       Free(ptr[8]) returned 0
       Free List [ Size 1 ]:  [ addr:1000 sz:100 ]

       ptr[9] = Alloc(10)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1010 sz:90 ]

       Free(ptr[9]) returned 0
       Free List [ Size 1 ]:  [ addr:1000 sz:100 ]
       ```
       Die Free Liste ist somit nicht mehr fragmentert, da mittels `Coalescing`
       benachbarte Speicherbereiche wieder zusammengefasst werden.

    *  Programmaufruf fragmentierter Free-Liste mit `WORST FIT`-Policy:

       ```
       $ ./malloc.py -A +1,-0,+2,-1,+3,-2,+4,-3,+5,-4,+6,-5,+7,-6,+8,-7,+9,-8,+10,-9 -H 0 -p WORST -s 0 -c
       seed 0
       size 100
       baseAddr 1000
       headerSize 0
       alignment -1
       policy WORST
       listOrder ADDRSORT
       coalesce False
       numOps 10
       range 10
       percentAlloc 50
       allocList +1,-0,+2,-1,+3,-2,+4,-3,+5,-4,+6,-5,+7,-6,+8,-7,+9,-8,+10,-9
       compute True

       ptr[0] = Alloc(1)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1001 sz:99 ]

       [...]

       Free(ptr[9]) returned 0
       Free List [ Size 11 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                               [ addr:1010 sz:5 ] [ addr:1015 sz:6 ] [ addr:1021 sz:7 ] [ addr:1028 sz:8 ]
                               [ addr:1036 sz:9 ] [ addr:1045 sz:10 ] [ addr:1055 sz:45 ]
       ```

       Die `WORST FIT`-Policy hat keine Auswirkung auf die Fragmentierung der
       Free-Liste

    *  `FIRST FIT`-Policy:
       ```
       $ ./malloc.py -A +1,-0,+2,-1,+3,-2,+4,-3,+5,-4,+6,-5,+7,-6,+8,-7,+9,-8,+10,-9 -H 0 -p FIRST -s 0 -c
       seed 0
       size 100
       baseAddr 1000
       headerSize 0
       alignment -1
       policy FIRST
       listOrder ADDRSORT
       coalesce False
       numOps 10
       range 10
       percentAlloc 50
       allocList +1,-0,+2,-1,+3,-2,+4,-3,+5,-4,+6,-5,+7,-6,+8,-7,+9,-8,+10,-9
       compute True

       ptr[0] = Alloc(1)  returned 1000 (searched 1 elements)
       Free List [ Size 1 ]:  [ addr:1001 sz:99 ]

       [...]

       Free(ptr[9]) returned 0
       Free List [ Size 11 ]:  [ addr:1000 sz:1 ] [ addr:1001 sz:2 ] [ addr:1003 sz:3 ] [ addr:1006 sz:4 ]
                               [ addr:1010 sz:5 ] [ addr:1015 sz:6 ] [ addr:1021 sz:7 ] [ addr:1028 sz:8 ]
                               [ addr:1036 sz:9 ] [ addr:1045 sz:10 ] [ addr:1055 sz:45 ]

       ```

       Die `FIRST FIT`-Policy hat ebenfalls keinerlei Auswirkungen auf den Grad
       der Fragmentierung der Free-Liste.
