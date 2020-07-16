# Answers

1.  *  **Cenario 1**
       Der Programmaufruf `$ ./mlfq.py -j 2 -n 2 -m 10 -M 0` liefert folgende
       Ausgabe:
       ```
       Here is the list of inputs:
       OPTIONS jobs 2
       OPTIONS queues 2
       OPTIONS allotments for queue  1 is   1
       OPTIONS quantum length for queue  1 is  10
       OPTIONS allotments for queue  0 is   1
       OPTIONS quantum length for queue  0 is  10
       OPTIONS boost 0
       OPTIONS ioTime 5
       OPTIONS stayAfterIO False
       OPTIONS iobump False


       For each job, three defining characteristics are given:
          startTime : at what time does the job enter the system
          runTime   : the total CPU time needed by the job to finish
          ioFreq    : every ioFreq time units, the job issues an I/O
                      (the I/O takes ioTime units to complete)

       Job List:
         Job  0: startTime   0 - runTime   8 - ioFreq   0
         Job  1: startTime   0 - runTime   4 - ioFreq   0

       Compute the execution trace for the given workloads.
       If you would like, also compute the response and turnaround
       times for each of the jobs.

       Use the -c flag to get the exact results when you are finished.
       ```
       Hierbei werden zwei Jobs erstellt (`-j 2`), sowie 2 Priority Queues (`-n 2`)
       erstellt. Beide Jobs haben eine maximale Laufzeit von 10 ms (`-m 10`) und
       enthalten keine E/A-Anfragen (`-M 0`).

       Da beide Jobs gleichzeitig in das System kommen (`startTime: 0`) befinden
       sie sich in der höchsen Priority Queue (`queue: 1`). Daher wird nun das
       RR-Schedling-Verfahren angewendet, wobei Job 0 als erster ausgewählt wird.
       Job 0 wird nun für 7ms ausgeführt und ist dann abgeschlossen. Da er die
       Quantumlänge nicht überschritten hatte, blieb er für die vollstänidge
       Laufzeit in der höchsten Priority Queue.

       Als nächstes wird nun mit Job 1 analog verfahren.

       Die Response-Time von Job 0 beträgt hierbei 0ms und die Turnaround-Time 8ms.
       Job 1 hat eine Response-Time von 8ms und eine Turnaround Time von 12 ms.
       Im Mittel ergibt sich eine Response-Time vom 4ms und eine Turnaround-Time
       von 10ms.

       Die Ausgabe des Programms mit dem zusätzlichen `-c` Flag führt zu folgendem
       Output:
       ```
       Here is the list of inputs:
       OPTIONS jobs 2
       OPTIONS queues 2
       OPTIONS allotments for queue  1 is   1
       OPTIONS quantum length for queue  1 is  10
       OPTIONS allotments for queue  0 is   1
       OPTIONS quantum length for queue  0 is  10
       OPTIONS boost 0
       OPTIONS ioTime 5
       OPTIONS stayAfterIO False
       OPTIONS iobump False


       For each job, three defining characteristics are given:
         startTime : at what time does the job enter the system
         runTime   : the total CPU time needed by the job to finish
         ioFreq    : every ioFreq time units, the job issues an I/O
                     (the I/O takes ioTime units to complete)

       Job List:
         Job  0: startTime   0 - runTime   8 - ioFreq   0
         Job  1: startTime   0 - runTime   4 - ioFreq   0


       Execution Trace:

       [ time 0 ] JOB BEGINS by JOB 0
       [ time 0 ] JOB BEGINS by JOB 1
       [ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 7 (of 8) ]
       [ time 1 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 6 (of 8) ]
       [ time 2 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 5 (of 8) ]
       [ time 3 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 4 (of 8) ]
       [ time 4 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 3 (of 8) ]
       [ time 5 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 2 (of 8) ]
       [ time 6 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 1 (of 8) ]
       [ time 7 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 0 (of 8) ]
       [ time 8 ] FINISHED JOB 0
       [ time 8 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 3 (of 4) ]
       [ time 9 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 2 (of 4) ]
       [ time 10 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 1 (of 4) ]
       [ time 11 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 0 (of 4) ]
       [ time 12 ] FINISHED JOB 1

       Final statistics:
         Job  0: startTime   0 - response   0 - turnaround   8
         Job  1: startTime   0 - response   8 - turnaround  12

         Avg  1: startTime n/a - response 4.00 - turnaround 10.00
       ```

    *  **Cenario 2**
        Der Programmaufruf `$ ./mlfq.py -j 2 -n 2 -m 20 -M 0 ` liefert folgende
        Ausgabe:
        ```
        Here is the list of inputs:
        OPTIONS jobs 2
        OPTIONS queues 2
        OPTIONS allotments for queue  1 is   1
        OPTIONS quantum length for queue  1 is  10
        OPTIONS allotments for queue  0 is   1
        OPTIONS quantum length for queue  0 is  10
        OPTIONS boost 0
        OPTIONS ioTime 5
        OPTIONS stayAfterIO False
        OPTIONS iobump False


        For each job, three defining characteristics are given:
          startTime : at what time does the job enter the system
          runTime   : the total CPU time needed by the job to finish
          ioFreq    : every ioFreq time units, the job issues an I/O
                      (the I/O takes ioTime units to complete)

        Job List:
          Job  0: startTime   0 - runTime  17 - ioFreq   0
          Job  1: startTime   0 - runTime   8 - ioFreq   0

        Compute the execution trace for the given workloads.
        If you would like, also compute the response and turnaround
        times for each of the jobs.

        Use the -c flag to get the exact results when you are finished.
        ```
        Es werden wieder zwei Jobs erstellt, welche zum selben Zeitpunkt im
        System eintreffen. Wie zuvor gibt es auch hier zwei Priority Queues.

        Job 0 wird als erstes ausgeführt, jedoch nur für 10ms, da danach die
        Quantum time abgelaufen ist und die Priorität des Jobs verringert wird.

        Anschließend wird Job 1 für 8ms ausgeführt und ist damit abgeschlossen.
        Daher wird nun wieder Job 1 ausgewählt, da in der Priority Queue mit der
        höchsten Priorität keine Jobs mehr vorhanden sind. Dieser läuft nun noch
        7 ms bis zum Abschluss.

        Die Response-Time von Job 0 beträgt hierbei 0ms, die Turnaround-Time
        hingegen 25ms.
        Job 1 besitzt eine Response-Time von 10ms und eine Turnaround-Time von
        18ms. Im Mittel ergibt sich hierbei eine Response-Time von 5ms und eine
        Turnaround-Time von 21.5ms.

2.  * **Example 1: A Single Long-Running-Job**  
      `$ ./mlfq.py -l 0,200,0 -n 3 -Q 10,10,10 -c`

    * **Example 2: Along Came A Short Job**  
      `$ ./mlfq.py -l 0,200,0:50,20,0 -n 3 -Q 10,10,10 -c`

    * **Example 3: What About I/O?**  
      `$ ./mlfq.py -l 0,220,0:20,200,1 -n 3 -Q 10,10,10 -c`

3.  Man muss die `-n` Flag auf 1 setzten. Dann existiert nämlich nur noch eine Queue
    und innerhalb der Queue wird mittels RR gescheduled.

4.  `$ ./mlfq.py -l 0,200,1:0,50,0 -n 3 -Q 2,3,4 10,10 -i 0 -S -c`    
    In der zeitspanne von `[ time 0 ]` bis `[ time 201 ]` läuft Job 0  für 200ms
    wohingegen Job 1 genau 2ms läuft.

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(202 / 200) * 100 = 99,01 %.

5.  Angenommen Job 0 (`startTime`: 0, `runTime`: 200ms) kommt ins System. Dann
    wird er sich für 10ms (da Quantumlänge: 10ms) in der höchsten Priority Queue
    befinden und anschließend wird seine Priorität verringert. Kommen nun immer
    wieder neue Jobs ins System, welche kürzer als 10ms sind, hat Job 0 keine
    Möglichkeit mehr die CPU zu verwenden und "verhungert".  
    Um dies zu verhindern soll ein Priority Boost eingesetzt werden, wodurch
    sichergestellt werden soll, dass ein Job mindestens 5% der CPU zur Verfügung
    gestellt bekommt.

    Daraus folgt:  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    (10ms / x) >= 0.05 &nbsp;&nbsp;| * x  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    => 10ms >= 0.05 * x &nbsp;&nbsp;&nbsp;&nbsp;| / 0.05  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    => (10ms / 0.05) >= x  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    => 200ms >= x

    Es ist also alle 200ms ein Priority Boost notwendig, damit jeder Job
    mindestens 5% der CPU zur Verfügung gestellt bekommt.

6.  ohne `-I` Flag:  
    ```
    $ ./mlfq.py -l 0,30,9:0,40,11 -n 3 -Q 10,10,10 -i 0 -S -c
    Here is the list of inputs:
    OPTIONS jobs 2
    OPTIONS queues 3
    OPTIONS allotments for queue  2 is   1
    OPTIONS quantum length for queue  2 is  10
    OPTIONS allotments for queue  1 is   1
    OPTIONS quantum length for queue  1 is  10
    OPTIONS allotments for queue  0 is   1
    OPTIONS quantum length for queue  0 is  10
    OPTIONS boost 0
    OPTIONS ioTime 0
    OPTIONS stayAfterIO True
    OPTIONS iobump False


    For each job, three defining characteristics are given:
      startTime : at what time does the job enter the system
      runTime   : the total CPU time needed by the job to finish
      ioFreq    : every ioFreq time units, the job issues an I/O
                  (the I/O takes ioTime units to complete)

    Job List:
      Job  0: startTime   0 - runTime  30 - ioFreq   9
      Job  1: startTime   0 - runTime  40 - ioFreq  11


    Execution Trace:

    [ time 0 ] JOB BEGINS by JOB 0
    [ time 0 ] JOB BEGINS by JOB 1
    [ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 29 (of 30) ]
    [ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 28 (of 30) ]
    [ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 27 (of 30) ]
    [ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 26 (of 30) ]
    [ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 25 (of 30) ]
    [ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 24 (of 30) ]
    [ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 23 (of 30) ]
    [ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 22 (of 30) ]
    [ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 21 (of 30) ]
    [ time 9 ] IO_START by JOB 0
    IO DONE
    [ time 9 ] IO_DONE by JOB 0
    [ time 9 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 39 (of 40) ]
    [ time 10 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 38 (of 40) ]
    [ time 11 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 37 (of 40) ]
    [ time 12 ] Run JOB 1 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 36 (of 40) ]
    [ time 13 ] Run JOB 1 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 35 (of 40) ]
    [ time 14 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 34 (of 40) ]
    [ time 15 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 33 (of 40) ]
    [ time 16 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 32 (of 40) ]
    [ time 17 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 31 (of 40) ]
    [ time 18 ] Run JOB 1 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 30 (of 40) ]
    [ time 19 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 20 (of 30) ]
    [ time 20 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 19 (of 30) ]
    [ time 21 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 18 (of 30) ]
    [ time 22 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 17 (of 30) ]
    [ time 23 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 16 (of 30) ]
    [ time 24 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 15 (of 30) ]
    [ time 25 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 14 (of 30) ]
    [ time 26 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 13 (of 30) ]
    [ time 27 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 12 (of 30) ]
    [ time 28 ] IO_START by JOB 0
    IO DONE
    [ time 28 ] IO_DONE by JOB 0
    [ time 28 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 11 (of 30) ]
    [ time 29 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 10 (of 30) ]
    [ time 30 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 9 (of 30) ]
    [ time 31 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 8 (of 30) ]
    [ time 32 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 7 (of 30) ]
    [ time 33 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 6 (of 30) ]
    [ time 34 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 5 (of 30) ]
    [ time 35 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 4 (of 30) ]
    [ time 36 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 3 (of 30) ]
    [ time 37 ] IO_START by JOB 0
    IO DONE
    [ time 37 ] IO_DONE by JOB 0
    [ time 37 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 2 (of 30) ]
    [ time 38 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 1 (of 30) ]
    [ time 39 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 0 (of 30) ]
    [ time 40 ] FINISHED JOB 0
    [ time 40 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 29 (of 40) ]
    [ time 41 ] IO_START by JOB 1
    IO DONE
    [ time 41 ] IO_DONE by JOB 1
    [ time 41 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 28 (of 40) ]
    [ time 42 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 27 (of 40) ]
    [ time 43 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 26 (of 40) ]
    [ time 44 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 25 (of 40) ]
    [ time 45 ] Run JOB 1 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 24 (of 40) ]
    [ time 46 ] Run JOB 1 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 23 (of 40) ]
    [ time 47 ] Run JOB 1 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 22 (of 40) ]
    [ time 48 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 21 (of 40) ]
    [ time 49 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 20 (of 40) ]
    [ time 50 ] Run JOB 1 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 19 (of 40) ]
    [ time 51 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 18 (of 40) ]
    [ time 52 ] IO_START by JOB 1
    IO DONE
    [ time 52 ] IO_DONE by JOB 1
    [ time 52 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 17 (of 40) ]
    [ time 53 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 16 (of 40) ]
    [ time 54 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 15 (of 40) ]
    [ time 55 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 14 (of 40) ]
    [ time 56 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 13 (of 40) ]
    [ time 57 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 12 (of 40) ]
    [ time 58 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 11 (of 40) ]
    [ time 59 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 10 (of 40) ]
    [ time 60 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 9 (of 40) ]
    [ time 61 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 8 (of 40) ]
    [ time 62 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 7 (of 40) ]
    [ time 63 ] IO_START by JOB 1
    IO DONE
    [ time 63 ] IO_DONE by JOB 1
    [ time 63 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 6 (of 40) ]
    [ time 64 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 5 (of 40) ]
    [ time 65 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 4 (of 40) ]
    [ time 66 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 3 (of 40) ]
    [ time 67 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 2 (of 40) ]
    [ time 68 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 1 (of 40) ]
    [ time 69 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 0 (of 40) ]
    [ time 70 ] FINISHED JOB 1

    Final statistics:
      Job  0: startTime   0 - response   0 - turnaround  40
      Job  1: startTime   0 - response   9 - turnaround  70

      Avg  1: startTime n/a - response 4.50 - turnaround 55.00
    ```

    mit `-I` Flag:
    ```
    ./mlfq.py -l 0,30,9:0,40,11 -n 3 -Q 10,10,10 -i 0 -S -I -c
    Here is the list of inputs:
    OPTIONS jobs 2
    OPTIONS queues 3
    OPTIONS allotments for queue  2 is   1
    OPTIONS quantum length for queue  2 is  10
    OPTIONS allotments for queue  1 is   1
    OPTIONS quantum length for queue  1 is  10
    OPTIONS allotments for queue  0 is   1
    OPTIONS quantum length for queue  0 is  10
    OPTIONS boost 0
    OPTIONS ioTime 0
    OPTIONS stayAfterIO True
    OPTIONS iobump True


    For each job, three defining characteristics are given:
      startTime : at what time does the job enter the system
      runTime   : the total CPU time needed by the job to finish
      ioFreq    : every ioFreq time units, the job issues an I/O
                  (the I/O takes ioTime units to complete)

    Job List:
      Job  0: startTime   0 - runTime  30 - ioFreq   9
      Job  1: startTime   0 - runTime  40 - ioFreq  11


    Execution Trace:

    [ time 0 ] JOB BEGINS by JOB 0
    [ time 0 ] JOB BEGINS by JOB 1
    [ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 29 (of 30) ]
    [ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 28 (of 30) ]
    [ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 27 (of 30) ]
    [ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 26 (of 30) ]
    [ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 25 (of 30) ]
    [ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 24 (of 30) ]
    [ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 23 (of 30) ]
    [ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 22 (of 30) ]
    [ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 21 (of 30) ]
    [ time 9 ] IO_START by JOB 0
    IO DONE
    [ time 9 ] IO_DONE by JOB 0
    [ time 9 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 20 (of 30) ]
    [ time 10 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 19 (of 30) ]
    [ time 11 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 18 (of 30) ]
    [ time 12 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 17 (of 30) ]
    [ time 13 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 16 (of 30) ]
    [ time 14 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 15 (of 30) ]
    [ time 15 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 14 (of 30) ]
    [ time 16 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 13 (of 30) ]
    [ time 17 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 12 (of 30) ]
    [ time 18 ] IO_START by JOB 0
    IO DONE
    [ time 18 ] IO_DONE by JOB 0
    [ time 18 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 11 (of 30) ]
    [ time 19 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 10 (of 30) ]
    [ time 20 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 9 (of 30) ]
    [ time 21 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 8 (of 30) ]
    [ time 22 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 7 (of 30) ]
    [ time 23 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 6 (of 30) ]
    [ time 24 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 5 (of 30) ]
    [ time 25 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 4 (of 30) ]
    [ time 26 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 3 (of 30) ]
    [ time 27 ] IO_START by JOB 0
    IO DONE
    [ time 27 ] IO_DONE by JOB 0
    [ time 27 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 2 (of 30) ]
    [ time 28 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 1 (of 30) ]
    [ time 29 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 0 (of 30) ]
    [ time 30 ] FINISHED JOB 0
    [ time 30 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 39 (of 40) ]
    [ time 31 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 38 (of 40) ]
    [ time 32 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 37 (of 40) ]
    [ time 33 ] Run JOB 1 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 36 (of 40) ]
    [ time 34 ] Run JOB 1 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 35 (of 40) ]
    [ time 35 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 34 (of 40) ]
    [ time 36 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 33 (of 40) ]
    [ time 37 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 32 (of 40) ]
    [ time 38 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 31 (of 40) ]
    [ time 39 ] Run JOB 1 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 30 (of 40) ]
    [ time 40 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 29 (of 40) ]
    [ time 41 ] IO_START by JOB 1
    IO DONE
    [ time 41 ] IO_DONE by JOB 1
    [ time 41 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 28 (of 40) ]
    [ time 42 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 27 (of 40) ]
    [ time 43 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 26 (of 40) ]
    [ time 44 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 25 (of 40) ]
    [ time 45 ] Run JOB 1 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 24 (of 40) ]
    [ time 46 ] Run JOB 1 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 23 (of 40) ]
    [ time 47 ] Run JOB 1 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 22 (of 40) ]
    [ time 48 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 21 (of 40) ]
    [ time 49 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 20 (of 40) ]
    [ time 50 ] Run JOB 1 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 19 (of 40) ]
    [ time 51 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 18 (of 40) ]
    [ time 52 ] IO_START by JOB 1
    IO DONE
    [ time 52 ] IO_DONE by JOB 1
    [ time 52 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 17 (of 40) ]
    [ time 53 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 16 (of 40) ]
    [ time 54 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 15 (of 40) ]
    [ time 55 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 14 (of 40) ]
    [ time 56 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 13 (of 40) ]
    [ time 57 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 12 (of 40) ]
    [ time 58 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 11 (of 40) ]
    [ time 59 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 10 (of 40) ]
    [ time 60 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 9 (of 40) ]
    [ time 61 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 8 (of 40) ]
    [ time 62 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 7 (of 40) ]
    [ time 63 ] IO_START by JOB 1
    IO DONE
    [ time 63 ] IO_DONE by JOB 1
    [ time 63 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 6 (of 40) ]
    [ time 64 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 5 (of 40) ]
    [ time 65 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 4 (of 40) ]
    [ time 66 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 3 (of 40) ]
    [ time 67 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 2 (of 40) ]
    [ time 68 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 1 (of 40) ]
    [ time 69 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 0 (of 40) ]
    [ time 70 ] FINISHED JOB 1

    Final statistics:
      Job  0: startTime   0 - response   0 - turnaround  30
      Job  1: startTime   0 - response  30 - turnaround  70

      Avg  1: startTime n/a - response 15.00 - turnaround 50.00
    ```

    Bei Angabe der `-I` Flag wird ein Job, der eine E/A-Anfrage aufgegeben hat
    und diese erfolgreich bearbeitet wurde, wieder an den Anfang der Queue
    gesetzt (Queue in der die E/A-Anfrage beendet wurde).
