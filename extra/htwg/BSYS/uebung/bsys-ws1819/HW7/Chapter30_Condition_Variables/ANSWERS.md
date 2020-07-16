# Answers

1.  ###### Our first question focuses on `main-two-cvs-while.c` (the working solution). First, study the code. Do you think you have an understanding of what should happen when you run the program?

    -  Das Programm `main-two-cvs-while.c` ist ein Beispiel für eine korrekte
       Producer/Consumer Synchronisation.  
       Ein Producer produziert eine gewisse Anzahl an Werten und schreibt diese
       in einen Buffer (falls die Buffergröße kleiner als die angegebenen Anzahl
       an Werten welche produziert werden sollen ist, muss der Buffer erst geleert
       werden - mittels Consumer - bevor der Producer weiterhin Werte produzieren
       kann), welche dann von Consumern konsumiert werden können.  
       Ist der Buffer voll, legt sich der Producer schlafen und ist der Buffer
       leer, so schlafen die Consumer.  
       Producer und Consumer wecken sich gegenseitig so lange, bis die gewünschte
       Anzahl an zu produzierenden Werten erzeugt sowie konsumiert wurde.

2.  ###### Run with one producer and one consumer, and have the producer produce a few values. Start with a buffer (size 1), and then increase it. How does the behavior of the code change with larger buffers? (or does it?)

    -  Sobald der Producer einen Wert produziert hat (unabhänig von der Buffergröße `-m`), konsumiert der Consumer diesen und legt sich wieder schalfen. Daraufhin wird der Producer wieder geweckt, welcher wieder einen Wert produziert.  
    Dies wiederholt sich solange, bis die gewünschte Anzahl von Werten produziert sowie konsumiert wurde.

    ###### What would you predict `num_full` to be with different buffer sizes (e.g., `-m 10`) and different numbers of produced items (e.g., `-l 100`), when you change the consumer sleep string from default (no sleep) to `-C 0,0,0,0,0,0,1`?

    -  Ein Consumer würde einen Wert konsumieren und sich danach schlafen legen. Danach wird der Producer geweckt, welcher nun genügend Zeit hat um den Buffer zu füllen. Anschließend legt sich der Producer schlafen und der Consumer ist wieder an der Reihe. Dies wiederholt sich nun so lange, bis die gewünschte Anzahl an Werten (hier: 100) produziert wurden.

    Der Buffer ist somit also die meiste Zeit über vollständig gefüllt, weswegen `num_full` sich im Bereich zwischen 0 und Buffergröße befindet.

3.  ###### If possible, run the code on different systems (e.g., a Mac and Linux). Do you see different behavior across these systems?

    -  Leider haben wir keinen Mac zur Verfügung, daher mussten wir leider auf
       Windows ausweichen...

    -  Der Programmaufruf `./main-two-cvs-while -p 1 -c 1 -m 5 -l 3 -v` liefert
       auf einem Linux Laptop (4 CPUs) folgende Ausgabe:

       ```
       ./main-two-cvs-while -p 1 -c 1 -m 5 -l 3 -v
       NF                            P0 C0
       0 [*---  ---  ---  ---  --- ] p0
       0 [*---  ---  ---  ---  --- ]    c0
       0 [*---  ---  ---  ---  --- ] p1
       1 [u  0 f---  ---  ---  --- ] p4
       1 [u  0 f---  ---  ---  --- ] p5
       1 [u  0 f---  ---  ---  --- ] p6
       1 [u  0 f---  ---  ---  --- ]    c1
       1 [u  0 f---  ---  ---  --- ] p0
       0 [ --- *---  ---  ---  --- ]    c4
       0 [ --- *---  ---  ---  --- ]    c5
       0 [ --- *---  ---  ---  --- ]    c6
       0 [ --- *---  ---  ---  --- ] p1
       0 [ --- *---  ---  ---  --- ]    c0
       1 [ --- u  1 f---  ---  --- ] p4
       1 [ --- u  1 f---  ---  --- ] p5
       1 [ --- u  1 f---  ---  --- ] p6
       1 [ --- u  1 f---  ---  --- ]    c1
       1 [ --- u  1 f---  ---  --- ] p0
       0 [ ---  --- *---  ---  --- ]    c4
       0 [ ---  --- *---  ---  --- ]    c5
       0 [ ---  --- *---  ---  --- ]    c6
       0 [ ---  --- *---  ---  --- ] p1
       0 [ ---  --- *---  ---  --- ]    c0
       1 [ ---  --- u  2 f---  --- ] p4
       1 [ ---  --- u  2 f---  --- ] p5
       1 [ ---  --- u  2 f---  --- ] p6
       1 [ ---  --- u  2 f---  --- ]    c1
       0 [ ---  ---  --- *---  --- ]    c4
       0 [ ---  ---  --- *---  --- ]    c5
       0 [ ---  ---  --- *--- f--- ]    c6
       1 [ ---  ---  --- uEOS f--- ] [main: added end-of-stream marker]
       1 [ ---  ---  --- uEOS f--- ]    c0
       1 [ ---  ---  --- uEOS f--- ]    c1
       0 [ ---  ---  ---  --- *--- ]    c4
       0 [ ---  ---  ---  --- *--- ]    c5
       0 [ ---  ---  ---  --- *--- ]    c6

       Consumer consumption:
         C0 -> 3
       ```

    -  Der Programmaufruf `./main-two-cvs-while -p 1 -c 1 -m 5 -l 3 -v` liefert
       auf einem Windows Rechner (8 CPUs) folgende Ausgabe:

       ```
       NF                            P0 C0
       0 [*---  ---  ---  ---  --- ] p0
       0 [*---  ---  ---  ---  --- ]    c0
       0 [*---  ---  ---  ---  --- ] p1
       1 [u  0 f---  ---  ---  --- ] p4
       1 [u  0 f---  ---  ---  --- ] p5
       1 [u  0 f---  ---  ---  --- ] p6
       1 [u  0 f---  ---  ---  --- ] p0
       1 [u  0 f---  ---  ---  --- ]    c1
       0 [ --- *---  ---  ---  --- ]    c4
       0 [ --- *---  ---  ---  --- ]    c5
       0 [ --- *---  ---  ---  --- ]    c6
       0 [ --- *---  ---  ---  --- ]    c0
       0 [ --- *---  ---  ---  --- ] p1
       1 [ --- u  1 f---  ---  --- ] p4
       1 [ --- u  1 f---  ---  --- ] p5
       1 [ --- u  1 f---  ---  --- ] p6
       1 [ --- u  1 f---  ---  --- ] p0
       1 [ --- u  1 f---  ---  --- ]    c1
       0 [ ---  --- *---  ---  --- ]    c4
       0 [ ---  --- *---  ---  --- ]    c5
       0 [ ---  --- *---  ---  --- ]    c6
       0 [ ---  --- *---  ---  --- ]    c0
       0 [ ---  --- *---  ---  --- ] p1
       1 [ ---  --- u  2 f---  --- ] p4
       1 [ ---  --- u  2 f---  --- ] p5
       1 [ ---  --- u  2 f---  --- ] p6
       1 [ ---  --- u  2 f---  --- ]    c1
       0 [ ---  ---  --- *---  --- ]    c4
       0 [ ---  ---  --- *---  --- ]    c5
       0 [ ---  ---  --- *---  --- ]    c6
       1 [ ---  ---  --- uEOS f--- ]    c0
       1 [ ---  ---  --- uEOS f--- ] [main: added end-of-stream marker]
       1 [ ---  ---  --- uEOS f--- ]    c1
       0 [ ---  ---  ---  --- *--- ]    c4
       0 [ ---  ---  ---  --- *--- ]    c5
       0 [ ---  ---  ---  --- *--- ]    c6

       Consumer consumption:
         C0 -> 3
       ```

       Die Ausführungsreihenfolge ist etwas anders, jedoch ist das Endresultat
       das selbe (war zu erwarten). 

4.  ###### Let’s look at some timings. How long do you think the following execution, with one producer, three consumers, a single-entry shared buffer, and each consumer pausing at point `c3` for a second, will take? `./main-two-cvs-while -p 1 -c 3 -m 1 -C 0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0 -l 10 -v -t`

    -  Da ein Producer existiert, welcher 10 Werte produziert und der Buffer
       eine Größe von 1 besitzt, werden die Consumer nach jedem einfügen eines
       Wertes geweckt. Da immer nur einer von den drei vorhandenen Consumern die
       Werte des Buffers konsumieren kann, werden die anderen beiden
       Cosumer-Threads schlafen gelegt und schlafen nun für eine Sekunde.

       ```
       -> ($l - 1) * 1s + $c * 1s
       -> 9 * 1s + 3 * 1s = 12s
         |______| |______|
            |        |
         Warten      Unlocken aller Consumer, nachdem der Producer
         der         alle Werte produziert  hat und diese bereits
         anderen 2   konsumiert wurden.
         Consumer.  
       ```

    -  Der Programmaufruf `./main-two-cvs-while -p 1 -c 3 -m 1 -C 0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0 -l 10 -v -t`
       benötigt ca. 12s zur vollständigen Ausführung.

5.  ###### Now change the size of the shared buffer to 3 (`-m 3`). Will this make any difference in the total time?

    -  Nein, das ändern der Buffergröße hat kaum Auswirkungen auf die
       Ausführungszeit, da nach jedem einfügen eines Wertes des Producers
       ein Cosumer den Wert konsumiert und die anderen beiden wieder für eine
       Sekunde schlafen gelegt werden.

6.  ###### Now change the location of the sleep to `c6` (this models a consumer taking something off the queue and then doing something with it), again using a single-entry buffer. What time do you predict in this case? `./main-two-cvs-while -p 1 -c 3 -m 1 -C 0,0,0,0,0,0,1:0,0,0,0,0,0,1:0,0,0,0,0,0,1 -l 10 -v -t`

    -  Hier wird ein Cosumer-Thread schlafen gelegt, sobald dieser den Lock wieder
       freigegeben hat (`c6`). Dadurch hat nun einer der anderen beiden
       Consumern die Gelegenheit Werte zu konsumieren (parallel zur Wartezeit).

       ```
       -> (($l - 1 - $c)) / $c * 1s + $c * 1s
       -> ((10 - 1 - 3) / 3) * 1s + 3 * 1s = 6 / 3 * 1s + 3s = 2s + 3s = 5s
       ```

    -  Der Programmaufruf `./main-two-cvs-while -p 1 -c 3 -m 1 -C 0,0,0,0,0,0,1:0,0,0,0,0,0,1:0,0,0,0,0,0,1 -l 10 -v -t`
       benötigt ca. 5s zur vollstädigen Ausführung.

7.  ###### Finally, change the buffer size to 3 again (`-m 3`). What time do you predict now?

    -  Der Producer wird nun schneller mit dem Produzieren der Werte fertig sein,
       jedoch benötigen die Consumer immer noch die gleiche Zeit um diese zu
       konsumieren. Daher wird sich an der Ausführungszeit nichts ändern.

    -  Der Programmaufruf `./main-two-cvs-while -p 1 -c 3 -m 3 -C 0,0,0,0,0,0,1:0,0,0,0,0,0,1:0,0,0,0,0,0,1 -l 10 -v -t`
       benötigt ca. 5s zur vollständigen Ausführung.

8.  ###### Now let’s look at `main-one-cv-while.c`. Can you configure a sleep string, assuming a single producer, one consumer, and a buffer of size 1, to cause a problem with this code?

    -  Nein, solange es nur einen Producer, sowie einen Consumer (2 Threads) gibt,
       sollten keine Probleme im Code auftreten, wenn nur eine Condition Variable
       verwendet wird. Zu Problemen kommt es erst, wenn es mehre mehre Producer
       bzw. Consumer gibt, da sich Consumer bzw. Producer dann gegenseitig wecken
       können (Consumer weckt Consumer, Producer weckt Producer). Daher verwendet
       man dann zwei Condition Variablen.

9.  ###### Now change the number of consumers to two. Can you construct sleep strings for the producer and the consumers so as to cause a problem in the code?

    -  Ja, indem einer der beiden Consumern den aderen Conumer weckt, wenn der
       Buffer leer ist. Dadurch tritt dann ein Deadlock auf.

    -  `./main-one-cv-while -p 1 -c 2 -m 1 -l 1 -P 0,0,0,0,0,0,1 -v`

10.  ###### Now examine `main-two-cvs-if.c`. Can you cause a problem to happen in this code? Again consider the case where there is only one consumer, and then the case where there is more than one.

     -  Wenn wieder nur ein Producer und ein Consumer existiern, funktioniert
        das Programm korrekt, obwohl hier ein `if` anstatt ein `while` zur
        Überprüfung verwendet wurde.

     -  Wenn zwei Consumer existieren, kann es zu einem `empty buffer error` kommen.
        Beispielsweiße liefert folgender Programmaufruf `./main-two-cvs-if -p 1 -c 2 -m 1 -l 2 -P 1 -C 1:0,0,0,1 -v`
        die folgende Ausgabe:

        ```
        ./main-two-cvs-if -p 1 -c 2 -m 1 -l 2 -P 1 -C 1:0,0,0,1 -v
        NF        P0 C0 C1
        0 [*--- ] p0
        0 [*--- ]    c0
        0 [*--- ]       c0
        0 [*--- ]       c1
        0 [*--- ]       c2
        0 [*--- ] p1
        1 [*  0 ] p4
        1 [*  0 ] p5
        1 [*  0 ] p6
        1 [*  0 ]    c1
        1 [*  0 ] p0
        0 [*--- ]    c4
        0 [*--- ]    c5
        0 [*--- ]    c6
        0 [*--- ]       c3
        0 [*--- ]    c0
        error: tried to get an empty buffer
        ```
        Dies liegt daran, dass `C1`, als erstes ausgeführt wird und dann schlafen
        gelegt wird, da der Buffer noch leer ist. Als nächstes ist `P0` an der
        Reihe, welcher einen Wert in den Buffer schreibt. Anschließen kommt `C0`
        an die Reihe und konsumiert den Wert im Buffer. Letztendlich ist nun `C1`
        wieder an der Reihe und versucht Werte zu konsumieren, jedoch ist der
        Buffer jetzt leer, was zu einem `empty buffer error` führt.

11.  ###### Finally, examine `main-two-cvs-while-extra-unlock.c`. What problem arises when you release the lock before doing a put or a get?

     -  Wenn der Lock vor `put` oder `get` bereits freigegeben wurde, kann es zu Race Conditions bei den globalen Ressourcen (`buffer`, `use_ptr`, `fill_ptr`, ...) kommen.

     ###### Can you reliably cause such a problem to happen, given the sleep strings?

     -  Mittels den Sleep Strings ist es uns nicht gelungen einen Data Race zu
        produzieren, da man einen Kontextwechsel in `put` oder `get` erzwingen
        müsste.

     ###### What bad thing can happen?

     -  Es könnten zwei Producer gleichzeitig in `put` bzw. zwei Consumer in `get`
        gelangen, wodurch sich ein undefiniertes Ergbnis in `buffer`, `use_ptr`,
        `fill_ptr` und `num_fill` ergeben könnte.
