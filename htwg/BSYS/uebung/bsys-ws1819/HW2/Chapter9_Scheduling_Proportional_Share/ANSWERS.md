# Answers

1.  *  Mit `-s 1`:  
       ```
       $ ./lottery.py -j 3 -s 1
       ARG jlist
       ARG jobs 3
       ARG maxlen 10
       ARG maxticket 100
       ARG quantum 1
       ARG seed 1

       Here is the job list, with the run time of each job:
        Job 0 ( length = 1, tickets = 84 )
        Job 1 ( length = 7, tickets = 25 )
        Job 2 ( length = 4, tickets = 44 )

       Here is the set of random numbers you will need (at most):
       Random 651593
       Random 788724
       Random 93859
       Random 28347
       Random 835765
       Random 432767
       Random 762280
       Random 2106
       Random 445387
       Random 721540
       Random 228762
       Random 945271
       ```
       Um harauszufinden welcher Job das Gewinnerticket **W** besitzt, muss man
       eine zufällig generierte Zahl **R** modulo der Gesamtanzahl der Tickets im
       System **T** rechnen. Die Gesamtzahl der Tickets ist die Summe der
       Tickets der einzelnen Jobs.

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![winningTicket](https://latex.codecogs.com/gif.latex?%5Ctextrm%7BW%7D%20%3D%20%5Ctextrm%7BR%7D%20%5C%20%5Ctextrm%7Bmod%7D%20%5C%20%5Ctextrm%7BT%7D)

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![amountOfTicketsInSystem](https://latex.codecogs.com/gif.latex?%5Ctextrm%7BT%7D%20%3D%20%5Ctextrm%7Bt%7D_%7B%5Ctextrm%7Bj0%7D%7D%20&plus;%20%5Ctextrm%7Bt%7D_%7B%5Ctextrm%7Bj1%7D%7D%20&plus;%20%5Cdots%20&plus;%20%5Ctextrm%7Bt%7D_%7B%5Ctextrm%7Bjn%7D%7D)

       Bei der Zahl 651593 würde das Gewinnerticket folgendermaßen bestimmt
       werden:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![example1T](https://latex.codecogs.com/gif.latex?%5Ctextrm%7BT%7D%20%3D%20%5Ctextrm%7Bt%7D_%7B%5Ctextrm%7Bj0%7D%7D%20&plus;%20%5Ctextrm%7Bt%7D_%7B%5Ctextrm%7Bj1%7D%7D%20&plus;%20%5Cdots%20&plus;%20%5Ctextrm%7Bt%7D_%7B%5Ctextrm%7Bjn%7D%7D%5C%5C%20%5Chphantom%7Ba%7D%5Cquad%20%5C%20%5C%20%3D%2084%20&plus;%2025%20&plus;%2044%5C%5C%20%5Chphantom%7Ba%7D%5Cquad%20%5C%20%5C%20%3D%20153)

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![example1W](https://latex.codecogs.com/gif.latex?%5Ctextrm%7BW%7D%20%3D%20%5Ctextrm%7BR%20mod%20T%7D%20%3D%20651593%20%5Ctextrm%7B%20mod%20%7D%20153%20%3D%20119)

       Der Job, welcher das Ticket 119 besitzt, hat somit gewonnen (Job 2) und
       wird daher ausgeführt.

       Anschließend beginnt der Prozess wieder von vorne, und es wird erneut
       ein Gewinnerticket "gezogen". Dies wird solange wiederholt, bis alle
       Prozesse erfolgreich ausgeführt wurden.

       Ausgabe des Programms mit zusätzlichem `-c` Flag:  
       ```
       $ ./lottery.py -j 3 -s 1 -c
       ARG jlist
       ARG jobs 3
       ARG maxlen 10
       ARG maxticket 100
       ARG quantum 1
       ARG seed 1

       Here is the job list, with the run time of each job:
        Job 0 ( length = 1, tickets = 84 )
        Job 1 ( length = 7, tickets = 25 )
        Job 2 ( length = 4, tickets = 44 )

       ** Solutions **

       Random 651593 -> Winning ticket 119 (of 153) -> Run 2
        Jobs:  (  job:0 timeleft:1 tix:84 )   (  job:1 timeleft:7 tix:25 )   (* job:2 timeleft:4 tix:44 )  
       Random 788724 -> Winning ticket 9 (of 153) -> Run 0
        Jobs:  (* job:0 timeleft:1 tix:84 )   (  job:1 timeleft:7 tix:25 )   (  job:2 timeleft:3 tix:44 )  
       --> JOB 0 DONE at time 2
       Random 93859 -> Winning ticket 19 (of 69) -> Run 1
        Jobs:  (  job:0 timeleft:0 tix:--- )   (* job:1 timeleft:7 tix:25 )   (  job:2 timeleft:3 tix:44 )  
       Random 28347 -> Winning ticket 57 (of 69) -> Run 2
        Jobs:  (  job:0 timeleft:0 tix:--- )   (  job:1 timeleft:6 tix:25 )   (* job:2 timeleft:3 tix:44 )  
       Random 835765 -> Winning ticket 37 (of 69) -> Run 2
        Jobs:  (  job:0 timeleft:0 tix:--- )   (  job:1 timeleft:6 tix:25 )   (* job:2 timeleft:2 tix:44 )  
       Random 432767 -> Winning ticket 68 (of 69) -> Run 2
        Jobs:  (  job:0 timeleft:0 tix:--- )   (  job:1 timeleft:6 tix:25 )   (* job:2 timeleft:1 tix:44 )  
       --> JOB 2 DONE at time 6
       Random 762280 -> Winning ticket 5 (of 25) -> Run 1
        Jobs:  (  job:0 timeleft:0 tix:--- )   (* job:1 timeleft:6 tix:25 )   (  job:2 timeleft:0 tix:--- )  
       Random 2106 -> Winning ticket 6 (of 25) -> Run 1
        Jobs:  (  job:0 timeleft:0 tix:--- )   (* job:1 timeleft:5 tix:25 )   (  job:2 timeleft:0 tix:--- )  
       Random 445387 -> Winning ticket 12 (of 25) -> Run 1
        Jobs:  (  job:0 timeleft:0 tix:--- )   (* job:1 timeleft:4 tix:25 )   (  job:2 timeleft:0 tix:--- )  
       Random 721540 -> Winning ticket 15 (of 25) -> Run 1
        Jobs:  (  job:0 timeleft:0 tix:--- )   (* job:1 timeleft:3 tix:25 )   (  job:2 timeleft:0 tix:--- )  
       Random 228762 -> Winning ticket 12 (of 25) -> Run 1
        Jobs:  (  job:0 timeleft:0 tix:--- )   (* job:1 timeleft:2 tix:25 )   (  job:2 timeleft:0 tix:--- )  
       Random 945271 -> Winning ticket 21 (of 25) -> Run 1
        Jobs:  (  job:0 timeleft:0 tix:--- )   (* job:1 timeleft:1 tix:25 )   (  job:2 timeleft:0 tix:--- )  
       --> JOB 1 DONE at time 12
       ```

    *  Mit `-s 2`:
       ```
       $ ./lottery.py -j 3 -s 2
       ```

       Analog zu oben.

    *  Mit `-s 3`:
       ```
       $ ./lottery.py -j 3 -s 3
       ```

       Analog zu oben.

2.  Wenn die Anzahl der Tickets so unbalanciert (Job 0: 1 Ticket, Job 1: 100
    Tickets) verteilt wurde, ist es sehr wahrscheinlich das Job 1 die CPU für
    sich beschlagnahmen wird und Job 0 erst dann an die Reihe kommt, wenn Job 1
    beendet wurde.

    Die Wahrscheinlichkeit **P**, dass Job 0 vor Job 1 ausgewählt wird, berechnet sich
    folgendermaßen:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![part1example2P](https://latex.codecogs.com/gif.latex?%5Ctextrm%7BP%7D_%7B%5Ctextrm%7Bjx%7D%7D%20%3D%20%5Cfrac%7B%5Ctextrm%7BT%7D%7D%7B%5Ctextrm%7Bt%7D_%7B%5Ctextrm%7Bjx%7D%7D%7D%20*100%20%5Cqquad%20%5Ctextrm%7Bmit%20x%20%3D%20%5C%23Job%7D)

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![part2example2P](https://latex.codecogs.com/gif.latex?%5Ctextrm%7BP%7D_%7B%5Ctextrm%7Bjx%7D%7D%20%3D%20%5Cfrac%7B101%7D%7B1%7D*100%20%3D%200.0099%20*%20100%20%3D%200.99%20%5C%25)

    Somit besteht eine rund 1%-ige Wahrscheinlichkeit, dass Job 0 anstatt Job 1
    ausgewählt wird. Es kann somit also auch immer noch passieren, dass Job 1
    teilweise ausgeführt wird, bevor Job 0 beendet wurde.

    Eine solch ungleiche Verteilung der Tickets, führt dazu, dass aus dem fairen
    Lotteryscheduler ein unfaires Schedulingverfahren wird. Es ist nämlich sehr
    wahrscheinlich, dass ein Job mit vielen Tickets die CPU solange belegt,
    bis er vollständig abgearbeitet wurde.

    Das Programm liefert folgende Ausgabe:  
    ```
    $ ./lottery.py -s 0 -l 10:1,10:100 -c
    ARG jlist 10:1,10:100
    ARG jobs 3
    ARG maxlen 10
    ARG maxticket 100
    ARG quantum 1
    ARG seed 0

    Here is the job list, with the run time of each job:
      Job 0 ( length = 10, tickets = 1 )
      Job 1 ( length = 10, tickets = 100 )


    ** Solutions **

    Random 844422 -> Winning ticket 62 (of 101) -> Run 1
      Jobs:  (  job:0 timeleft:10 tix:1 )   (* job:1 timeleft:10 tix:100 )  
    Random 757955 -> Winning ticket 51 (of 101) -> Run 1
      Jobs:  (  job:0 timeleft:10 tix:1 )   (* job:1 timeleft:9 tix:100 )  
    Random 420572 -> Winning ticket 8 (of 101) -> Run 1
      Jobs:  (  job:0 timeleft:10 tix:1 )   (* job:1 timeleft:8 tix:100 )  
    Random 258917 -> Winning ticket 54 (of 101) -> Run 1
      Jobs:  (  job:0 timeleft:10 tix:1 )   (* job:1 timeleft:7 tix:100 )  
    Random 511275 -> Winning ticket 13 (of 101) -> Run 1
      Jobs:  (  job:0 timeleft:10 tix:1 )   (* job:1 timeleft:6 tix:100 )  
    Random 404934 -> Winning ticket 25 (of 101) -> Run 1
      Jobs:  (  job:0 timeleft:10 tix:1 )   (* job:1 timeleft:5 tix:100 )  
    Random 783799 -> Winning ticket 39 (of 101) -> Run 1
      Jobs:  (  job:0 timeleft:10 tix:1 )   (* job:1 timeleft:4 tix:100 )  
    Random 303313 -> Winning ticket 10 (of 101) -> Run 1
      Jobs:  (  job:0 timeleft:10 tix:1 )   (* job:1 timeleft:3 tix:100 )  
    Random 476597 -> Winning ticket 79 (of 101) -> Run 1
      Jobs:  (  job:0 timeleft:10 tix:1 )   (* job:1 timeleft:2 tix:100 )  
    Random 583382 -> Winning ticket 6 (of 101) -> Run 1
      Jobs:  (  job:0 timeleft:10 tix:1 )   (* job:1 timeleft:1 tix:100 )  
    --> JOB 1 DONE at time 10
    Random 908113 -> Winning ticket 0 (of 1) -> Run 0
      Jobs:  (* job:0 timeleft:10 tix:1 )   (  job:1 timeleft:0 tix:--- )  
    Random 504687 -> Winning ticket 0 (of 1) -> Run 0
      Jobs:  (* job:0 timeleft:9 tix:1 )   (  job:1 timeleft:0 tix:--- )  
    Random 281838 -> Winning ticket 0 (of 1) -> Run 0
      Jobs:  (* job:0 timeleft:8 tix:1 )   (  job:1 timeleft:0 tix:--- )  
    Random 755804 -> Winning ticket 0 (of 1) -> Run 0
      Jobs:  (* job:0 timeleft:7 tix:1 )   (  job:1 timeleft:0 tix:--- )  
    Random 618369 -> Winning ticket 0 (of 1) -> Run 0
      Jobs:  (* job:0 timeleft:6 tix:1 )   (  job:1 timeleft:0 tix:--- )  
    Random 250506 -> Winning ticket 0 (of 1) -> Run 0
      Jobs:  (* job:0 timeleft:5 tix:1 )   (  job:1 timeleft:0 tix:--- )  
    Random 909747 -> Winning ticket 0 (of 1) -> Run 0
      Jobs:  (* job:0 timeleft:4 tix:1 )   (  job:1 timeleft:0 tix:--- )  
    Random 982786 -> Winning ticket 0 (of 1) -> Run 0
      Jobs:  (* job:0 timeleft:3 tix:1 )   (  job:1 timeleft:0 tix:--- )  
    Random 810218 -> Winning ticket 0 (of 1) -> Run 0
      Jobs:  (* job:0 timeleft:2 tix:1 )   (  job:1 timeleft:0 tix:--- )  
    Random 902166 -> Winning ticket 0 (of 1) -> Run 0
      Jobs:  (* job:0 timeleft:1 tix:1 )   (  job:1 timeleft:0 tix:--- )  
    --> JOB 0 DONE at time 20
    ```

3.  *  `$ ./lottery.py -l 100:100,100:100`:  
       Bei zwei Jobs der Länge 100 und beide bekommen 100 Tickets zugewießen,
       berechnet sich die Unfairness-Metrik **U** folgendermaßen:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![example1UnfairnessMetric](https://latex.codecogs.com/gif.latex?%5Ctextrm%7BU%7D%20%3D%20%5Cfrac%7B%5Ctextrm%7Bruntime%28j0%29%7D%7D%7B%5Ctextrm%7Bruntime%28j1%29%7D%7D%20%3D%20%5Cfrac%7B192%7D%7B200%7D%20%3D%200.96%20%5Cqquad%20%5Ctextrm%7Bmit%20runtime%28j0%29%7D%20%3C%20%5Ctextrm%7Bruntime%28j1%29%7D)

       Wenn die Unfairness-Metrik nahe bei 1 liegt, werden beide Jobs nahezu
       gleichzeitig fertig und das Schedulingverfahren lässt sich als fair
       bezeichnen. Anderenfalls ist das Schedulingverfahren unfair.

    * `$ ./lottery.py -s 1 -l 100:100,100:100`:

      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![example2UnfairnessMetric](https://latex.codecogs.com/gif.latex?%5Ctextrm%7BU%7D%20%3D%20%5Cfrac%7B%5Ctextrm%7Bruntime%28j1%29%7D%7D%7B%5Ctextrm%7Bruntime%28j0%29%7D%7D%20%3D%20%5Cfrac%7B196%7D%7B200%7D%20%3D%200.98)

    *  `./lottery.py -s 2 -l 100:100,100:100`:

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![example3UnfairnessMetric](https://latex.codecogs.com/gif.latex?%5Ctextrm%7BU%7D%20%3D%20%5Cfrac%7B%5Ctextrm%7Bruntime%28j1%29%7D%7D%7B%5Ctextrm%7Bruntime%28j0%29%7D%7D%20%3D%20%5Cfrac%7B190%7D%7B200%7D%20%3D%200.95)

4.  Folgende Unfairness-Metriken ergeben sich beim Programmaufruf
    `./lottery.py -l 100:100,100:100`, wenn die Quantumgröße (`-q`) größer wird:

    | Quantumgröße  | Unfairness-Metrik U |
    | ------------- | ------------------- |
    | 1             | 192 / 200 = 0.96    |
    | 2             | 188 / 200 = 0.94    |   
    | 3             | 201 / 204 = 0.9853  |
    | 4             | 176 / 200 = 0.88    |
    | 5             | 160 / 200 = 0.8     |
    | 10            | 150 / 200 = 0.75    |
    | 20            | 140 / 200 = 0.7     |
    | 50            | 150 / 200 = 0.75    |
    | 100           | 100 / 200 = 0.5     |
    | 200           | 200 / 400 = 0.5     |

    Man kann erkennen, dass mit steigender Quantumgröße die Unfairness steigt.

5.  Um den Graph im Kapitel zu generieren, berechnent man mehrere male (z.B. 30x)
    die Unfaireness-Metric einer gewissen Joblänge und bestimmt davon den
    durchschnittlichen Wert.  
    Dies wiederholt man nun für verschiedene Joblängen (1 - 100).  
    Die Unfairness-Metric wird dabei auf der y-Achse aufgetragen und die
    Job-Länge auf der x-Achse.

    Verwendet man hingegen das Stride-Verfahren, so ändert sich der Graph zu
    einer nahezu konstaten Line (parallel zur x-Achse).
