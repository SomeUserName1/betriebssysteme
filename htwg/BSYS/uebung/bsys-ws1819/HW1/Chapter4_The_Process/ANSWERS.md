# Answers

1.  Die CPU wird in diesem Fall von beiden Prozessen zu 100% benutzt, da der
    Aufruf des Programms `process-run.py` mit den Flags `-l 5:100,5:100` zwei
    Prozesse mit fünf Instruktionen erstellt, welche die CPU zu 100% benutzen
    werden.  
    ```
    $ ./process-run.py -l 5:100,5:100 -c -p
      Time     PID: 0     PID: 1        CPU        IOs
        1     RUN:cpu      READY          1            
        2     RUN:cpu      READY          1            
        3     RUN:cpu      READY          1            
        4     RUN:cpu      READY          1            
        5     RUN:cpu      READY          1            
        6        DONE    RUN:cpu          1            
        7        DONE    RUN:cpu          1            
        8        DONE    RUN:cpu          1            
        9        DONE    RUN:cpu          1            
       10        DONE    RUN:cpu          1            

      Stats: Total Time 10
      Stats: CPU Busy 10 (100.00%)
      Stats: IO Busy  0 (0.00%)
    ```

2.  Der Programmaufruf `./process-run.py -l 4:100,1:0` erstellt zwei Prozesse:

    *  Der erste Prozess `[P0]` enthält vier Instruktionen, welche zu 100% auf
       der CPU ausgeführt werden. Dieser Prozess wird daher vier Zeiteinheiten
       (ZE) benötigen.

    *  Der zweite Prozess `[P1]` hingegen beinhaltet eine Instruktion, welche zu
       100% eine E/A-Anfrage sein wird. Da die `-L`-Flag beim Programmaufruf
       nicht spezifiziet wurde, wird für eine E/A-Anfrage der Standardwert von
       fünf ZE verwendet. Aufgrund dessen, dass die CPU nun fünf ZE auf
       Beendigung der E/A-Anfrage warten muss, kann die Anfrage erst nach der
       sechsten ZE als verarbeitet betrachtet werden.

    Somit werden insgesamt zehn ZE benötigt um beide Prozesse auszuführen.  
    ```
    $ ./process-run.py -l 4:100,1:0 -c -p
      Time     PID: 0     PID: 1        CPU        IOs
        1     RUN:cpu      READY          1            
        2     RUN:cpu      READY          1            
        3     RUN:cpu      READY          1            
        4     RUN:cpu      READY          1            
        5        DONE     RUN:io          1            
        6        DONE    WAITING                     1
        7        DONE    WAITING                     1
        8        DONE    WAITING                     1
        9        DONE    WAITING                     1
       10*       DONE       DONE                       

      Stats: Total Time 10
      Stats: CPU Busy 5 (50.00%)
      Stats: IO Busy  4 (40.00%)
    ```

3.  Ja die Reihenfolge der angegebenen Prozesse in der Prozessliste spielt eine
    Rolle, da nun zuerst der Prozess `[P1]` mit der E/A-Anfrage ausgeführt wird.
    Sobald `[P1]` den Status von `RUNNING` zu `BLOCKED` bzw. `WAITING` ändert,
    kann Prozess `[P0]` parallel die CPU benutzen.  
    ```
    $ ./process-run.py -l 1:0,4:100 -c -p
      Time     PID: 0     PID: 1        CPU        IOs
        1      RUN:io      READY          1            
        2     WAITING    RUN:cpu          1          1
        3     WAITING    RUN:cpu          1          1
        4     WAITING    RUN:cpu          1          1
        5     WAITING    RUN:cpu          1          1
        6*       DONE       DONE                       

      Stats: Total Time 6
      Stats: CPU Busy 5 (83.33%)
      Stats: IO Busy  4 (66.67%)
    ```

4.  Bei folgendem Programmaufruf `./process-run.py -l 1:0,4:100 -c -p -S
    SWITCH_ON_END`, wird erst zwischen den Prozessen gewechselt, wenn der zuvor
    gestartete Prozess beendet wurde (egal ob E/A-Anfrage oder CPU-Instruktion).
    Daher wird nun in Prozess `[P0]` auf die Beendigung der E/A-Anfrage gewartet,
    anstatt Prozess `[P1]` parallel die CPU zur verfügung zu stellen, obwohl
    diese momentan nichts zu tun hat und somit rechenbereit ist.
    ```
    $ ./process-run.py -l 1:0,4:100 -c -p -S SWITCH_ON_END
      Time     PID: 0     PID: 1        CPU        IOs
        1      RUN:io      READY          1            
        2     WAITING      READY                     1
        3     WAITING      READY                     1
        4     WAITING      READY                     1
        5     WAITING      READY                     1
        6*       DONE    RUN:cpu          1            
        7        DONE    RUN:cpu          1            
        8        DONE    RUN:cpu          1            
        9        DONE    RUN:cpu          1            

      Stats: Total Time 9
      Stats: CPU Busy 5 (55.56%)
      Stats: IO Busy  4 (44.44%)
    ```

5.  Bei folgendem Programmaufruf `./process-run.py -l 1:0,4:100 -c -p -S
    SWITCH_ON_IO`, wird zwischen den Prozessen gewechselt sobald eine
    E/A-Anfrage auftritt. Daher wird nun, sobald Prozess `[P0]` sich im Status
    `WAITING` befindet, parallel Prozess `[P1]` auf der CPU ausgeführt.

    Dies Ausgabe des Programms ist dabei die selbe wie bei 3.

6.  Der Programmaufruf `./process-run.py -l 3:0,5:100,5:100,5:100 -S
    SWITCH_ON_IO -I IO_RUN_LATER -c -p` erzeugt folgende Ausgabe:  
    ```
    $ ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
       Time     PID: 0     PID: 1     PID: 2     PID: 3        CPU        IOs
         1      RUN:io      READY      READY      READY          1            
         2     WAITING    RUN:cpu      READY      READY          1          1
         3     WAITING    RUN:cpu      READY      READY          1          1
         4     WAITING    RUN:cpu      READY      READY          1          1
         5     WAITING    RUN:cpu      READY      READY          1          1
         6*      READY    RUN:cpu      READY      READY          1            
         7       READY       DONE    RUN:cpu      READY          1            
         8       READY       DONE    RUN:cpu      READY          1            
         9       READY       DONE    RUN:cpu      READY          1            
        10       READY       DONE    RUN:cpu      READY          1            
        11       READY       DONE    RUN:cpu      READY          1            
        12       READY       DONE       DONE    RUN:cpu          1            
        13       READY       DONE       DONE    RUN:cpu          1            
        14       READY       DONE       DONE    RUN:cpu          1            
        15       READY       DONE       DONE    RUN:cpu          1            
        16       READY       DONE       DONE    RUN:cpu          1            
        17      RUN:io       DONE       DONE       DONE          1            
        18     WAITING       DONE       DONE       DONE                     1
        19     WAITING       DONE       DONE       DONE                     1
        20     WAITING       DONE       DONE       DONE                     1
        21     WAITING       DONE       DONE       DONE                     1
        22*     RUN:io       DONE       DONE       DONE          1            
        23     WAITING       DONE       DONE       DONE                     1
        24     WAITING       DONE       DONE       DONE                     1
        25     WAITING       DONE       DONE       DONE                     1
        26     WAITING       DONE       DONE       DONE                     1
        27*       DONE       DONE       DONE       DONE                       

       Stats: Total Time 27
       Stats: CPU Busy 18 (66.67%)
       Stats: IO Busy  12 (44.44%)
    ```

    Die Systemresourcen werden heirbei nicht optimal verwendet, da die
    letzten beiden E/A-Anfragen von Prozess `[P0]` parallel mit der Ausführung
    von CPU-Instruktionen der Prozesse `[P2]` und `[P3]` abgearbeitet werden
    könnten.

7.  Der Programmaufruf `./process-run.py -l 3:0,5:100,5:100,5:100 -S
    SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p` liefert folgende Ausgabe:  
    ```
    $ ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
        Time     PID: 0     PID: 1     PID: 2     PID: 3        CPU        IOs
         1      RUN:io      READY      READY      READY          1            
         2     WAITING    RUN:cpu      READY      READY          1          1
         3     WAITING    RUN:cpu      READY      READY          1          1
         4     WAITING    RUN:cpu      READY      READY          1          1
         5     WAITING    RUN:cpu      READY      READY          1          1
         6*     RUN:io      READY      READY      READY          1            
         7     WAITING    RUN:cpu      READY      READY          1          1
         8     WAITING       DONE    RUN:cpu      READY          1          1
         9     WAITING       DONE    RUN:cpu      READY          1          1
        10     WAITING       DONE    RUN:cpu      READY          1          1
        11*     RUN:io       DONE      READY      READY          1            
        12     WAITING       DONE    RUN:cpu      READY          1          1
        13     WAITING       DONE    RUN:cpu      READY          1          1
        14     WAITING       DONE       DONE    RUN:cpu          1          1
        15     WAITING       DONE       DONE    RUN:cpu          1          1
        16*       DONE       DONE       DONE    RUN:cpu          1            
        17        DONE       DONE       DONE    RUN:cpu          1            
        18        DONE       DONE       DONE    RUN:cpu          1  

       Stats: Total Time 18
       Stats: CPU Busy 18 (100.00%)
       Stats: IO Busy  12 (66.67%)
    ```
    Wenn nun ein Prozess eine E/A-Anfrage stellt (hier: `[P0]`), wird dieser
    Prozess direkt ausgeführt, damit wärend er sich im Status `WAITING`
    befindet, parallel andere Prozesse (mit CPU-Instruktionen) auf der CPU
    abgearbeitet werden können.

8.  *  Der Programmaufruf `./process-run.py -s 1 -l 3:50,3:50 -c -p` liefert
       folgende Ausgabe:  
       ```
       $ ./process-run.py -s 1 -l 3:50,3:50 -c -p
           Time     PID: 0     PID: 1        CPU        IOs
            1     RUN:cpu      READY          1            
            2      RUN:io      READY          1            
            3     WAITING    RUN:cpu          1          1
            4     WAITING    RUN:cpu          1          1
            5     WAITING    RUN:cpu          1          1
            6     WAITING       DONE                     1
            7*     RUN:io       DONE          1            
            8     WAITING       DONE                     1
            9     WAITING       DONE                     1
           10     WAITING       DONE                     1
           11     WAITING       DONE                     1
           12*       DONE       DONE                       

          Stats: Total Time 12
          Stats: CPU Busy 6 (50.00%)
          Stats: IO Busy  8 (66.67%)
       ```

    *  Wird der obrige Programmaufruf um eines der folgenden Flags erweitert:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`-I IO_RUN_IMMEDIATE`, `-I  
       IO_RUN_IMMEDIATE` oder `-S SWITCH_ON_IO`,

       ändert sich an der Ausgabe des Programm nichts.

    *  Wird der obrige Programmaufruf um das Flag `-S SWITCH_ON_END`
       erweitert, erhält man folgende Programmausgabe:
       ```
       $ ./process-run.py -s 1 -l 3:50,3:50 -S SWITCH_ON_END -c -p
           Time     PID: 0     PID: 1        CPU        IOs
            1     RUN:cpu      READY          1            
            2      RUN:io      READY          1            
            3     WAITING      READY                     1
            4     WAITING      READY                     1
            5     WAITING      READY                     1
            6     WAITING      READY                     1
            7*     RUN:io      READY          1            
            8     WAITING      READY                     1
            9     WAITING      READY                     1
           10     WAITING      READY                     1
           11     WAITING      READY                     1
           12*       DONE    RUN:cpu          1            
           13        DONE    RUN:cpu          1            
           14        DONE    RUN:cpu          1            

          Stats: Total Time 14
          Stats: CPU Busy 6 (42.86%)
          Stats: IO Busy  8 (57.14%)
       ```
       Hier werden jetzt alle Prozesse nacheinander ausgeführt, egal ob sie
       E/A-Anfragen oder CPU-Instruktionen enthalten.
