# Questions

1.  ###### Let’s examine a simple program, `loop.s`. First, just read and understand it. Then, run it with these arguments (`./x86.py -p loop.s -t 1 -i 100 -R dx`) This specifies a single thread, an interrupt every 100 instructions, and tracing of register `%dx`. What will `%dx` be during the run? Use the `-c` flag to check your answers; the answers, on the left, show the value of the register (or memory value) after the instruction on the right has run.

    -  Der Programmaufruf `./x86.py -p loop.s -t 1 -i 100 -R dx` liefert folgende Ausgabe:

       ```
       $ ./x86.py -p loop.s -t 1 -i 100 -R dx
       [...]

       dx          Thread 0         
        ?   
        ?   1000 sub  $1,%dx
        ?   1001 test $0,%dx
        ?   1002 jgte .top
        ?   1003 halt
       ```

    -  **Vorgehensweiße zur Bestimmung des `%dx` Registers:**

       *  Da kein Initialwert für das Register `%dx` gesetzt wurde, wird dieses
          automatisch mit 0 initialisiert.

       *  Beim ersten Befehl: `sub $1,%dx` wird der Wert des `%dx` Registers um 1
          verringert:

          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`%dx = %dx - 1 = 0 - 1 = -1`

       *  Beim zweiten Befehl: `test $0,%dx` wird der Wert des `%dx` Registers
          mit 0 verglichen. Der dritte Befehl: `jgte .top` spezifiziert dabei die
          Vergleichsopertation (hier: `>=`). Trifft der Vergleich zu, wird zur Marke
          `.top` gesprungen und der Vorgang wiederholt sich. Anderenfalls wird das
          Programm mit Hilfe des `halt` Befehls beendet:

          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`-1 < 0` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          &nbsp;&rightarrow;&nbsp;&nbsp;&nbsp; springe nicht zur Marke `.top` und
          beende das Programm.

       Daraus ergibt sich folgende Lösung:

       ```
       dx          Thread 0         
        0   
       -1   1000 sub  $1,%dx
       -1   1001 test $0,%dx
       -1   1002 jgte .top
       -1   1003 halt
       ```

2.  ###### Same code, different flags: (`./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx`) This specifies two threads, and initializes each `%dx` to 3. What values will `%dx` see?

    -  Der Programmaufruf `./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx`
       liefert folgende Ausgabe:

       ```
       $ ./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx
       ARG numthreads 2
       ARG program loop.s
       ARG interrupt frequency 100
       ARG argv dx=3,dx=3
       ARG load address 1000
       [...]

       dx          Thread 0                Thread 1         
        ?   
        ?   1000 sub  $1,%dx
        ?   1001 test $0,%dx
        ?   1002 jgte .top
        ?   1000 sub  $1,%dx
        ?   1001 test $0,%dx
        ?   1002 jgte .top
        ?   1000 sub  $1,%dx
        ?   1001 test $0,%dx
        ?   1002 jgte .top
        ?   1000 sub  $1,%dx
        ?   1001 test $0,%dx
        ?   1002 jgte .top
        ?   1003 halt
        ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
        ?                            1000 sub  $1,%dx
        ?                            1001 test $0,%dx
        ?                            1002 jgte .top
        ?                            1000 sub  $1,%dx
        ?                            1001 test $0,%dx
        ?                            1002 jgte .top
        ?                            1000 sub  $1,%dx
        ?                            1001 test $0,%dx
        ?                            1002 jgte .top
        ?                            1000 sub  $1,%dx
        ?                            1001 test $0,%dx
        ?                            1002 jgte .top
        ?                            1003 halt
       ```

    -  **Lösung:**

       ```
       dx          Thread 0                Thread 1         
        3   
        2   1000 sub  $1,%dx
        2   1001 test $0,%dx
        2   1002 jgte .top
        1   1000 sub  $1,%dx
        1   1001 test $0,%dx
        1   1002 jgte .top
        0   1000 sub  $1,%dx
        0   1001 test $0,%dx
        0   1002 jgte .top
       -1   1000 sub  $1,%dx
       -1   1001 test $0,%dx
       -1   1002 jgte .top
       -1   1003 halt
        3   ----- Halt;Switch -----  ----- Halt;Switch -----  
        2                            1000 sub  $1,%dx
        2                            1001 test $0,%dx
        2                            1002 jgte .top
        1                            1000 sub  $1,%dx
        1                            1001 test $0,%dx
        1                            1002 jgte .top
        0                            1000 sub  $1,%dx
        0                            1001 test $0,%dx
        0                            1002 jgte .top
       -1                            1000 sub  $1,%dx
       -1                            1001 test $0,%dx
       -1                            1002 jgte .top
       -1                            1003 halt
       ```

    ###### Does the presence of multiple threads affect your calculations?

    -  Da die Interruptfrequenz (`-i` Flag) auf 100 Operationen gesetzt wurde,
       hat ein Thread genügend Zeit den kompletten Programmablauf auszuführen.
       Daher hat die Erhöhung der Threads keine Auswirkungungen auf das Endergebnis
       der Berechnung.

    ###### Is there a race in this code?

    -  Da die Threads auf keine globalen Ressourcen zugreifen, ist kein "Data Race"
       im Code vorhanden. Erst wenn schreibend auf globale Ressourcen zugegriffen
       wird, kann es zu "Data Races" kommen.

3.  ###### Run this: `./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx`. This makes the interrupt interval small/random; use different seeds (`-s`) to see different interleavings. Does the interrupt frequency change anything?

    *  `./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx -s 0`:

       -  Der Programmaufruf `./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx -s 0`
          liefert folgende Ausgabe:

          ```
          $ ./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx -s 0
          ARG seed 0
          ARG program loop.s
          ARG numthreads 2
          ARG interrupt frequency 3
          ARG interrupt randomness True
          ARG argv dx=3,dx=3
          ARG load address 1000

          dx          Thread 0                Thread 1         
           ?   
           ?   1000 sub  $1,%dx
           ?   1001 test $0,%dx
           ?   1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1000 sub  $1,%dx
           ?                            1001 test $0,%dx
           ?                            1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?   1000 sub  $1,%dx
           ?   1001 test $0,%dx
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1000 sub  $1,%dx
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?   1002 jgte .top
           ?   1000 sub  $1,%dx
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1001 test $0,%dx
           ?                            1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?   1001 test $0,%dx
           ?   1002 jgte .top
           ?   1000 sub  $1,%dx
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1000 sub  $1,%dx
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?   1001 test $0,%dx
           ?   1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1001 test $0,%dx
           ?                            1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?   1003 halt
           ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
           ?                            1000 sub  $1,%dx
           ?                            1001 test $0,%dx
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1002 jgte .top
           ?                            1003 halt
          ```

       -  **Lösung:**

          ```
          dx          Thread 0                Thread 1         
           3   
           2   1000 sub  $1,%dx
           2   1001 test $0,%dx
           2   1002 jgte .top
           3   ------ Interrupt ------  ------ Interrupt ------  
           2                            1000 sub  $1,%dx
           2                            1001 test $0,%dx
           2                            1002 jgte .top
           2   ------ Interrupt ------  ------ Interrupt ------  
           1   1000 sub  $1,%dx
           1   1001 test $0,%dx
           2   ------ Interrupt ------  ------ Interrupt ------  
           1                            1000 sub  $1,%dx
           1   ------ Interrupt ------  ------ Interrupt ------  
           1   1002 jgte .top
           0   1000 sub  $1,%dx
           1   ------ Interrupt ------  ------ Interrupt ------  
           1                            1001 test $0,%dx
           1                            1002 jgte .top
           0   ------ Interrupt ------  ------ Interrupt ------  
           0   1001 test $0,%dx
           0   1002 jgte .top
          -1   1000 sub  $1,%dx
           1   ------ Interrupt ------  ------ Interrupt ------  
           0                            1000 sub  $1,%dx
          -1   ------ Interrupt ------  ------ Interrupt ------  
          -1   1001 test $0,%dx
          -1   1002 jgte .top
           0   ------ Interrupt ------  ------ Interrupt ------  
           0                            1001 test $0,%dx
           0                            1002 jgte .top
          -1   ------ Interrupt ------  ------ Interrupt ------  
          -1   1003 halt
           0   ----- Halt;Switch -----  ----- Halt;Switch -----  
          -1                            1000 sub  $1,%dx
          -1                            1001 test $0,%dx
          -1   ------ Interrupt ------  ------ Interrupt ------  
          -1                            1002 jgte .top
          -1                            1003 halt
          ```

    *  `./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx -s 1`:

       -  Die Ausgabe des Programmaufrufs
          `./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx -s 1` sieht
          folgedermaßen aus:

          ```
          $ ./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx -s 1
          ARG seed 1
          ARG numthreads 2
          ARG program loop.s
          ARG interrupt frequency 3
          ARG interrupt randomness True
          ARG argv dx=3,dx=3
          ARG load address 1000

          dx          Thread 0                Thread 1         
           ?   
           ?   1000 sub  $1,%dx
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1000 sub  $1,%dx
           ?                            1001 test $0,%dx
           ?                            1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?   1001 test $0,%dx
           ?   1002 jgte .top
           ?   1000 sub  $1,%dx
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1000 sub  $1,%dx
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?   1001 test $0,%dx
           ?   1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1001 test $0,%dx
           ?                            1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?   1000 sub  $1,%dx
           ?   1001 test $0,%dx
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1000 sub  $1,%dx
           ?                            1001 test $0,%dx
           ?                            1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?   1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1000 sub  $1,%dx
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?   1000 sub  $1,%dx
           ?   1001 test $0,%dx
           ?   1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?                            1001 test $0,%dx
           ?                            1002 jgte .top
           ?   ------ Interrupt ------  ------ Interrupt ------  
           ?   1003 halt
           ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
           ?                            1003 halt
          ```

       -  **Lösung:**

          ```
          dx          Thread 0                Thread 1         
           3   
           2   1000 sub  $1,%dx
           3   ------ Interrupt ------  ------ Interrupt ------  
           2                            1000 sub  $1,%dx
           2                            1001 test $0,%dx
           2                            1002 jgte .top
           2   ------ Interrupt ------  ------ Interrupt ------  
           2   1001 test $0,%dx
           2   1002 jgte .top
           1   1000 sub  $1,%dx
           2   ------ Interrupt ------  ------ Interrupt ------  
           1                            1000 sub  $1,%dx
           1   ------ Interrupt ------  ------ Interrupt ------  
           1   1001 test $0,%dx
           1   1002 jgte .top
           1   ------ Interrupt ------  ------ Interrupt ------  
           1                            1001 test $0,%dx
           1                            1002 jgte .top
           1   ------ Interrupt ------  ------ Interrupt ------  
           0   1000 sub  $1,%dx
           0   1001 test $0,%dx
           1   ------ Interrupt ------  ------ Interrupt ------  
           0                            1000 sub  $1,%dx
           0                            1001 test $0,%dx
           0                            1002 jgte .top
           0   ------ Interrupt ------  ------ Interrupt ------  
           0   1002 jgte .top
           0   ------ Interrupt ------  ------ Interrupt ------  
          -1                            1000 sub  $1,%dx
           0   ------ Interrupt ------  ------ Interrupt ------  
          -1   1000 sub  $1,%dx
          -1   1001 test $0,%dx
          -1   1002 jgte .top
          -1   ------ Interrupt ------  ------ Interrupt ------  
          -1                            1001 test $0,%dx
          -1                            1002 jgte .top
          -1   ------ Interrupt ------  ------ Interrupt ------  
          -1   1003 halt
          -1   ----- Halt;Switch -----  ----- Halt;Switch -----  
          -1                            1003 halt
          ```

       -  Nein, das verändern der Interruptfrequenz ändert nichts an der Berechnung
          des Programms. Dies liegt daran, dass jeder Thread seinen eigenen Stack
          besitzt (Speicherort der lokalen Variablen) und es keine globalen
          Ressourcen gibt, die von den Threads verwaltet werden müssen.

4.  ###### Now, a different program, `looping-race-nolock.s`, which accesses a shared variable located at address 2000; we’ll call this variable `value`. Run it with a single thread to confirm your understanding: `./x86.py -p looping-race-nolock.s -t 1 -M 2000`. What is `value` (i.e., at memory address 2000) throughout the run? Use `-c` to check.

    -  Der Programmaufruf `./x86.py -p looping-race-nolock.s -t 1 -M 2000`
       liefert folgende Ausgabe:

       ```
       $ ./x86.py -p looping-race-nolock.s -t 1 -M 2000
       ARG numthreads 1
       ARG program looping-race-nolock.s
       ARG interrupt frequency 50

       2000          Thread 0         
          ?   
          ?   1000 mov 2000, %ax
          ?   1001 add $1, %ax
          ?   1002 mov %ax, 2000
          ?   1003 sub  $1, %bx
          ?   1004 test $0, %bx
          ?   1005 jgt .top
          ?   1006 halt
       ```

    -  **Lösung:**

       ```
       2000          Thread 0         
          0   
          0   1000 mov 2000, %ax
          0   1001 add $1, %ax
          1   1002 mov %ax, 2000
          1   1003 sub  $1, %bx
          1   1004 test $0, %bx
          1   1005 jgt .top
          1   1006 halt
       ```

    -  Die Variable `value` (an Speicheradresse 2000) enthält nach dem Durchlauf
       des Threads den Wert 1 (zovor 0).

5.  ###### Run with multiple iterations/threads: `./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000` Why does each thread loop three times?

    -  Die Ausgabe des Programmaufrufs `./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000`
       liefert folgende Ausgabe:

       ```
       $ ./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000
       ARG numthreads 2
       ARG program looping-race-nolock.s
       ARG interrupt frequency 50
       ARG argv bx=3

       2000          Thread 0                Thread 1         
          ?   
          ?   1000 mov 2000, %ax
          ?   1001 add $1, %ax
          ?   1002 mov %ax, 2000
          ?   1003 sub  $1, %bx
          ?   1004 test $0, %bx
          ?   1005 jgt .top
          ?   1000 mov 2000, %ax
          ?   1001 add $1, %ax
          ?   1002 mov %ax, 2000
          ?   1003 sub  $1, %bx
          ?   1004 test $0, %bx
          ?   1005 jgt .top
          ?   1000 mov 2000, %ax
          ?   1001 add $1, %ax
          ?   1002 mov %ax, 2000
          ?   1003 sub  $1, %bx
          ?   1004 test $0, %bx
          ?   1005 jgt .top
          ?   1006 halt
          ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
          ?                            1000 mov 2000, %ax
          ?                            1001 add $1, %ax
          ?                            1002 mov %ax, 2000
          ?                            1003 sub  $1, %bx
          ?                            1004 test $0, %bx
          ?                            1005 jgt .top
          ?                            1000 mov 2000, %ax
          ?                            1001 add $1, %ax
          ?                            1002 mov %ax, 2000
          ?                            1003 sub  $1, %bx
          ?                            1004 test $0, %bx
          ?                            1005 jgt .top
          ?                            1000 mov 2000, %ax
          ?                            1001 add $1, %ax
          ?                            1002 mov %ax, 2000
          ?                            1003 sub  $1, %bx
          ?                            1004 test $0, %bx
          ?                            1005 jgt .top
          ?                            1006 halt
       ```

    -  **Lösung:**

       ```
       2000          Thread 0                Thread 1         
          0   
          0   1000 mov 2000, %ax
          0   1001 add $1, %ax
          1   1002 mov %ax, 2000
          1   1003 sub  $1, %bx
          1   1004 test $0, %bx
          1   1005 jgt .top
          1   1000 mov 2000, %ax
          1   1001 add $1, %ax
          2   1002 mov %ax, 2000
          2   1003 sub  $1, %bx
          2   1004 test $0, %bx
          2   1005 jgt .top
          2   1000 mov 2000, %ax
          2   1001 add $1, %ax
          3   1002 mov %ax, 2000
          3   1003 sub  $1, %bx
          3   1004 test $0, %bx
          3   1005 jgt .top
          3   1006 halt
          3   ----- Halt;Switch -----  ----- Halt;Switch -----  
          3                            1000 mov 2000, %ax
          3                            1001 add $1, %ax
          4                            1002 mov %ax, 2000
          4                            1003 sub  $1, %bx
          4                            1004 test $0, %bx
          4                            1005 jgt .top
          4                            1000 mov 2000, %ax
          4                            1001 add $1, %ax
          5                            1002 mov %ax, 2000
          5                            1003 sub  $1, %bx
          5                            1004 test $0, %bx
          5                            1005 jgt .top
          5                            1000 mov 2000, %ax
          5                            1001 add $1, %ax
          6                            1002 mov %ax, 2000
          6                            1003 sub  $1, %bx
          6                            1004 test $0, %bx
          6                            1005 jgt .top
          6                            1006 halt
       ```
    -  Jeder Thread "loopt" genau 3x, da das `%bx` Register initial auf den Wert
       3 gesetzt wird, und in jedem Loop-Schritt `%bx` um 1 verringert wird. Der
       Loop wird nur fortgesetzt, falls `%bx >= 0` ist.

    ###### What is final value of `value`?

    -  Der endgültige Wert von `value` beträgt 6, nachdem beide Threads
       durchgelaufen sind (aber nur, da die Interruptfrequenz groß genug ist!).

6.  ###### Run with random interrupt intervals: `./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0` with different seeds (`-s 1`, `-s 2`, etc.). Can you tell by looking at the thread interleaving what the final value of value will be?

    -  Ja, man kann anhand des "Thread interleavings" den endgültigen Wert der
       Variablen `value` bestimmen.

    -  **Bsp `./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 1`:**

       Der Programmaufruf `./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 1`
       liefert folgende Ausgabe:

       ```
       $ ./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 1
       ARG seed 1
       ARG numthreads 2
       ARG program looping-race-nolock.s
       ARG interrupt frequency 4
       ARG interrupt randomness True

       2000          Thread 0                Thread 1         
          ?   
          ?   1000 mov 2000, %ax
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?                            1000 mov 2000, %ax
          ?                            1002 mov %ax, 2000
          ?                            1003 sub  $1, %bx
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?   1001 add $1, %ax
          ?                            1001 add $1, %ax
          ?   1002 mov %ax, 2000
          ?   1003 sub  $1, %bx
          ?   1004 test $0, %bx
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?                            1004 test $0, %bx
          ?                            1005 jgt .top
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?   1005 jgt .top
          ?   1006 halt
          ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?                            1006 halt
       ```

    -  **Lösung:**

       ```
       2000          Thread 0                Thread 1         
          0   
          0   1000 mov 2000, %ax
          0   ------ Interrupt ------  ------ Interrupt ------  
          0                            1000 mov 2000, %ax
          0                            1001 add $1, %ax
          1                            1002 mov %ax, 2000
          1                            1003 sub  $1, %bx
          1   ------ Interrupt ------  ------ Interrupt ------  
          1   1001 add $1, %ax
          1   1002 mov %ax, 2000
          1   1003 sub  $1, %bx
          1   1004 test $0, %bx
          1   ------ Interrupt ------  ------ Interrupt ------  
          1                            1004 test $0, %bx
          1                            1005 jgt .top
          1   ------ Interrupt ------  ------ Interrupt ------  
          1   1005 jgt .top
          1   1006 halt
          1   ----- Halt;Switch -----  ----- Halt;Switch -----  
          1   ------ Interrupt ------  ------ Interrupt ------  
          1                            1006 halt
       ```

    -  Die Variable `value` hat in diesem Beispiel einen endgültigen Wert von 1.

    ###### Does the timing of the interrupt matter?

    -  Ja die zeitliche Koordinierung der Interrupts spielt eine Rolle, da zum
       Beispiel beim Aufruf des Programms mit dem "Random Seed" 0 die Variable
       `value` den endgültigen Wert 2 besitzt. Beim Aufruf mit einem "Random Seed"
       von 1 hingegen, besitzt `value` nun den endgültigen Wert von 1.

    ###### Where can it safely occur? Where not? In other words, where is the critical section exactly?

    -  Der kritische Bereich besteht aus den folgenden Zeilen des Programms
       `looping-race-nolock.s`:

       ```
       mov 2000, %ax  # get 'value' at address 2000
       add $1, %ax    # increment it
       mov %ax, 2000  # store it back
       ```

    -  Tritt ein Kontextwechsel vor oder nach diesem Bereich auf, hat dies
       keinerlei Auswirkungen auf die Berechnung des Programms und ist somit sicher.

    -  Anderenfalls ist das Verhalten des Codes nicht mehr deterministisch und
       somit ist das endgültige Ergebnis undefiniert, bzw. nicht vorherzusagen
       (ohne den hier verwendetetn Simulator, da man anderenfalls keine genauen
       Informationen darüber hat, wann ein Kontextwechsel stattfinden wird und
       wann nicht &rightarrow; **Der Scheduler ist böse!**).

7.  ###### Now examine fixed interrupt intervals: `./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1`. What will the final value of the shared variable `value` be?

    -  Der Programmaufruf `./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1`
       liefert folgende Ausgabe:

       ```
       $ ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1
       ARG seed 0
       ARG numthreads 2
       ARG program looping-race-nolock.s
       ARG interrupt frequency 1
       ARG argv bx=1

       2000          Thread 0                Thread 1         
          ?   
          ?   1000 mov 2000, %ax
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?                            1000 mov 2000, %ax
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?   1001 add $1, %ax
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?                            1001 add $1, %ax
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?   1002 mov %ax, 2000
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?                            1002 mov %ax, 2000
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?   1003 sub  $1, %bx
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?                            1003 sub  $1, %bx
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?   1004 test $0, %bx
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?                            1004 test $0, %bx
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?   1005 jgt .top
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?                            1005 jgt .top
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?   1006 halt
          ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
          ?   ------ Interrupt ------  ------ Interrupt ------  
          ?                            1006 halt
       ```

    -  **Lösung:**

       ```
       2000          Thread 0                Thread 1         
          0   
          0   1000 mov 2000, %ax
          0   ------ Interrupt ------  ------ Interrupt ------  
          0                            1000 mov 2000, %ax
          0   ------ Interrupt ------  ------ Interrupt ------  
          0   1001 add $1, %ax
          0   ------ Interrupt ------  ------ Interrupt ------  
          0                            1001 add $1, %ax
          0   ------ Interrupt ------  ------ Interrupt ------  
          1   1002 mov %ax, 2000
          1   ------ Interrupt ------  ------ Interrupt ------  
          1                            1002 mov %ax, 2000
          1   ------ Interrupt ------  ------ Interrupt ------  
          1   1003 sub  $1, %bx
          1   ------ Interrupt ------  ------ Interrupt ------  
          1                            1003 sub  $1, %bx
          1   ------ Interrupt ------  ------ Interrupt ------  
          1   1004 test $0, %bx
          1   ------ Interrupt ------  ------ Interrupt ------  
          1                            1004 test $0, %bx
          1   ------ Interrupt ------  ------ Interrupt ------  
          1   1005 jgt .top
          1   ------ Interrupt ------  ------ Interrupt ------  
          1                            1005 jgt .top
          1   ------ Interrupt ------  ------ Interrupt ------  
          1   1006 halt
          1   ----- Halt;Switch -----  ----- Halt;Switch -----  
          1   ------ Interrupt ------  ------ Interrupt ------  
          1                            1006 halt
       ```

    -  Der endgültige Wert der Variable `value` beträgt hier 1. Dies ist jedoch
       falsch, da wenn das Programm sequentiell ausgeführt werden würde die
       Variable `value` einen endgültigen Wert von 2 haben würde.

    ###### What about when you change `-i 2`, `-i 3`, etc.?

    -  Folgende Tabelle ergibt sich für den Programmaufruf
       `./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000`:

       | Wert von `-i` | endgültiger Wert der Variable `value` |
       | :-----------: | :-----------------------------------: |
       | 2             | 1                                     |
       | 3             | 2                                     |
       | > 3           | 2                                     |

    ###### For which interrupt intervals does the program give the “correct” answer?

    -  Wenn der Interruptintervall >= 3 ist, dann wird der kritische Bereich immer
       vor einem Kontextwechsel ausgeführt, wodurch das berechnete Ergebnis immer
       richtig ist (man könnte sagen, der kritische Bereich wird nun "atomar"
       ausgeführt, da während dessen kein Kontextwechsel auftreten kann). Dies
       funktioniert aber nur solange, wenn beide Threads nur einen Loop (`%bx=1`)
       ausführen. Erhöht man `%bx`, ist dies nicht mehr der Fall.

8.  ###### Run the same for more loops (e.g., set `-a bx=100`). What interrupt intervals (`-i`) lead to a correct outcome?

    -  Folgende Tabelle ergibt sich für den Programmaufruf
       `./x86.py -p looping-race-nolock.s -a bx=100 -t 2 -M 2000`:

       | Wert von `-i` | endgültiger Wert der Variable `value` |
       | :-----------: | :-----------------------------------: |
       | 1             | 100                                   |
       | 2             | 100                                   |
       | 3             | 200                                   |
       | 4             | 150                                   |
       | 5             | 160                                   |
       | 6             | 200                                   |
       | 9             | 200                                   |
       | 12            | 200                                   |
       | 15            | 200                                   |
       | 18            | 200                                   |
       | 19            | 163                                   |
       | 20            | 160                                   |

       Setzt man für `-i` Werte ein, welche vielfache von 3 sind, ist das berechnete
       Ergbenis immer korrekt. Dies ist nicht sehr überraschend, da der kritische
       Bereich 3 Instruktionen enthält und der Loopmechanismums ebenfalls
       3 Instruktionen enthält. Daher wird der kritische Bereich immer "atomar"
       ausgeführt, wodurch ein richtiges Endergebnis gewährleistet wird.

    ###### Which intervals are surprising?

    -  Beispielsweiße 1 und 2 oder 5 und 20, da hierbei die selben falschen
       Ergebnisse produziert werden.

9.  ###### One last program: `wait-for-me.s`. Run: `./x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000`. This sets the `%ax` register to 1 for thread 0, and 0 for thread 1, and watches `%ax` and memory location 2000. How should the code behave?

    -  Thread 0 schreibt eine 1 an die Speicheradresse 2000 und Thread 1 "loopt"
       solange bis die 1 an der Speicheradresse 2000 steht.

       D.h. Thread 0 wartet solange bis Thread 1 seine Aktion abgeschlossen hat,
       und beendet sich dann auch.

    -  Das Verhalten des Codes kann also volgendermaßen aussehen:

       1.  Thread 1 wird zuerst ausgeführt:

           Wenn zuerst Thread 1 ausgeführt wird, bleibt dieser solange in der Loop,
           bis ein Kontextwechsel auftritt und Thread 0 an die Reihe kommt. Sobald
           Thread 1 wieder vom Scheduler ausgewählt wird, beendet auch dieser sich,
           da nun die 1 an der Speicheradresse 2000 steht.

       2.  Thread 0 wird zuerst ausgeführt:

           Wenn Thread 0 zuerst ausgeführt wird, schreibt dieser zuerst den Wert 1
           an die Speicheradresse 2000. Wird anschließend Thread 1 vom Scheduler
           ausgewählt, betritt dieser die Loop, beendet diese aber direkt, da die
           1 schon an der Speicheradresse 2000 steht.

    ###### How is the value at location 2000 being used by the threads?

    - Thread 0 greift schreibend auf die Speicheradresse 2000 zu, wohingegen
      Thread 1 lesend darauf zugreift.

    ###### What will its final value be?

    -  Der endgültige Wert an der Speicheradresse 2000 wird 1 sein.

10.  ###### Now switch the inputs: `./x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000`. How do the threads behave?

     -  Thread 0 "loopt" nun solange bis ein Kontextwechsel auftritt und Thread 1
        an die Reihe kommt. Nach Beendigung von Thread 1 beendet sich anschließend
        auch Thread 0.

     ###### What is thread 0 doing?

     -  Thread 0 wartet auf die Beendigung von Thread 1.

     ###### How would changing the interrupt interval (e.g., `-i 1000`, or perhaps to use random intervals) change the trace outcome?

     *  `-i 1000`:

        Thread 0 "loopt" nun sehr viel länger als zuvor. Das "loopen" ist quasi
        aktives Warten.

     *  `-r`:

        Wie lange Thread 0 nun "loopt" ist abhänig vom gewählten "Random Seed".

     ###### Is the program efficiently using the CPU?

     -  Nein das Programm benutzt nicht effizient die CPU, da aktives Warten
        betrieben wird, d.h. während der aktiven Wartezeit, könnte
        Thread 0 die CPU mittels dem `yield()`-Aufruf (nach einer kleinen
        Zeitscheibe) die CPU für andere rechenenbereite Threads freigeben.
