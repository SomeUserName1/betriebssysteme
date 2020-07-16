# Answers

1.  Wenn man das Programm `null` ausführt, erhält man einen sogenannten
    "Segmentation fault" (Schutzverletzung), da die Adresse 0 nicht zum Programm
    gehört.

    Ausgabe des Programms `null`:
    ```
    $ ./null
    Address of main: 0x559b5cfe86aa
    [1]    5715 segmentation fault (core dumped)  ./null
    ```

2.  `gdb` liefert folgende Ausgabe für den Programmaufruf `$ gdb null`:

    ```
    $ gdb null

    [...]

    Address of main: 0x5555555546aa

    Program received signal SIGSEGV, Segmentation fault.
    0x00005555555546dc in main () at null.c:9
    9	  printf("i: %d\n", *i);

    [...]
    ```

    `gdb` zeigt einem die Zeile des Programms an, bei der die Schutzverletzung
    aufgetreten ist, sowie der Inhalt der Zeile.

    Des Weiteren erhält man noch Informationen darüber, in welcher Funktion
    die Schutzverletzung aufgetreten ist, sowie dessen Adresse.

    Ebenfalls erhält man noch die Adresse der Instruktion,
    bei der die Schutzverletzung aufgetreten ist (hier: `0x00005555555546dc`).

    Man erhält auch noch Informationen darüber, welches Signal das Programm
    vom Betriebsystem empfangen hat (hier: `SIGSEGV`).

3.  Wenn man `$ valgrind --leak-check=yes ./null` ausführt, versucht das Tool
    `valgrind` Speicherfehler (mittels `memcheck`) im Programm `null` zu finden:

    ```
    $ valgrind --leak-check=yes ./null
    ==6992== Memcheck, a memory error detector
    ==6992== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==6992== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==6992== Command: ./null
    ==6992==
    ==6992== Invalid read of size 4
    ==6992==    at 0x1086DC: main (null.c:9)
    ==6992==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
    ==6992==
    ==6992==
    ==6992== Process terminating with default action of signal 11 (SIGSEGV)
    ==6992==  Access not within mapped region at address 0x0
    ==6992==    at 0x1086DC: main (null.c:9)
    ==6992==  If you believe this happened as a result of a stack
    ==6992==  overflow in your program's main thread (unlikely but
    ==6992==  possible), you can try to increase the size of the
    ==6992==  main thread stack using the --main-stacksize= flag.
    ==6992==  The main thread stack size used in this run was 8388608.
    ==6992==
    ==6992== HEAP SUMMARY:
    ==6992==     in use at exit: 0 bytes in 0 blocks
    ==6992==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
    ==6992==
    ==6992== All heap blocks were freed -- no leaks are possible
    ==6992==
    ==6992== For counts of detected and suppressed errors, rerun with: -v
    ==6992== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
    [1]    6992 segmentation fault (core dumped)  valgrind --leak-check=yes ./null
    ```
    `valgrind` erkennt einen fehlerhaften `read`-Zugriff in Zeile 9 des Programms `null`:

    ```
    ==6992== Invalid read of size 4
    ==6992==    at 0x1086DC: main (null.c:9)
    ==6992==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
    ```

    Dies liegt daran, dass das Programm versucht auf Speicher zuzugreifen,
    welcher nicht allokiert wurde und somit nicht Teil des Programms ist.

    Man erhält Auskunft darüber, wie viele Bytes das Programm versucht hat zu
    lesen, wo der Fehler aufgetreten ist (inklusive Adresse der Instruktion
    sowie Funktionsname) sowie die Anfangsadresse des Speicherbereichs
    (hier: `0x0`).

4.  `gdb` kann im Programm `malloc` keine Fehler finden.  

    `valgrind` hingegen liefert folgende Ausgabe für das Programm `malloc`:

    ```
    $ valgrind --leak-check=yes ./malloc

    [...]

    ==8018== Command: ./malloc
    ==8018==
    ==8018==
    ==8018== HEAP SUMMARY:
    ==8018==     in use at exit: 40 bytes in 1 blocks
    ==8018==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
    ==8018==
    ==8018== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
    ==8018==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==8018==    by 0x10872B: main (malloc.c:5)
    ==8018==
    ==8018== LEAK SUMMARY:
    ==8018==    definitely lost: 40 bytes in 1 blocks
    ==8018==    indirectly lost: 0 bytes in 0 blocks
    ==8018==      possibly lost: 0 bytes in 0 blocks
    ==8018==    still reachable: 0 bytes in 0 blocks
    ==8018==         suppressed: 0 bytes in 0 blocks
    ==8018==
    ==8018== For counts of detected and suppressed errors, rerun with: -v
    ==8018== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
    ```

    `valgrind` erkennt, dass vergessen wurde allokierten Speicher wieder frei zu
    geben, bevor das Programm beendet wurde. Daher sind hier 40 Bytes verloren
    gegangen.

5.  Das Programm `array_of_integers` lässt sich "normal" ausführen, und es wird
    kein Fehler geworfen.

    Ruft man das Programm `array_of_integers` mit Hilfe von `valgrind` auf,
    erhält man folgende Ausgabe:

    ```
    $ valgrind --leak-check=yes ./array_of_integers

    [...]

    ==9046== Command: ./array_of_integers
    ==9046==
    ==9046== Invalid write of size 4
    ==9046==    at 0x10876B: main   (array_of_integers.c:12)
    ==9046==  Address 0x522d1d0 is 0 bytes after a block of size 400 alloc'd
    ==9046==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==9046==    by 0x10872B: main (array_of_integers.c:5)
    ==9046==
    ==9046==
    ==9046== HEAP SUMMARY:
    ==9046==     in use at exit: 400 bytes in 1 blocks
    ==9046==   total heap usage: 1 allocs, 0 frees, 400 bytes allocated
    ==9046==
    ==9046== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
    ==9046==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==9046==    by 0x10872B: main (array_of_integers.c:5)
    ==9046==
    ==9046== LEAK SUMMARY:
    ==9046==    definitely lost: 400 bytes in 1 blocks
    ==9046==    indirectly lost: 0 bytes in 0 blocks
    ==9046==      possibly lost: 0 bytes in 0 blocks
    ==9046==    still reachable: 0 bytes in 0 blocks
    ==9046==         suppressed: 0 bytes in 0 blocks
    ==9046==
    ==9046== For counts of detected and suppressed errors, rerun with: -v
    ==9046== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
    ```

    Das Programm ist nicht korrekt, da einerseits auf einen Speicherbereich im
    Heap zugegriffen wird, welcher nicht Teil des allokierten Speichers ist
    (`data[100] = 0`) und anderenseits wird der allokierte Speicher des
    Programms nicht mehr freigegeben, ohne das Programm zu beenden.

6.  Ja das Programm `array_of_integers_with_free` lässt sich ausführen und läuft.  

    `valgrind` liefert für das Programm `array_of_integers_with_free.c` folgende
    Ausgabe:

    ```
    $ valgrind --leak-check=yes ./array_of_integers_with_free

    [...]

    ==10475== Command: ./array_of_integers_with_free
    ==10475==
    ==10475== Invalid read of size 4
    ==10475==    at 0x108801: main (array_of_integers_with_free.c:15)
    ==10475==  Address 0x522d040 is 0 bytes inside a block of size 400 free'd
    ==10475==    at 0x4C30D3B: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==10475==    by 0x1087FC: main (array_of_integers_with_free.c:13)
    ==10475==  Block was alloc'd at
    ==10475==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==10475==    by 0x1087BB: main (array_of_integers_with_free.c:6)
    ==10475==
    data[0]: 0
    ==10475==
    ==10475== HEAP SUMMARY:
    ==10475==     in use at exit: 0 bytes in 0 blocks
    ==10475==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
    ==10475==
    ==10475== All heap blocks were freed -- no leaks are possible
    ==10475==
    ==10475== For counts of detected and suppressed errors, rerun with: -v
    ==10475== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
    ```

    `valgrind` bemerkt, dass auf einen Speicherbereich zugegriffen wurde, der
    bereits freigegeben wurde (invalid read).

7.  Führt man das Programm `funny_free` aus, stürzt es ab und man erhält man
    folgende Fehlermeldung:

    ```
    $ ./funny_free
    *** Error in `./funny_free': free(): invalid pointer: 0x000055be75e350d4 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x70bfb)[0x7fae58497bfb]

    [...]

    Aborted
    ```

    Man benötigt daher keine weitern Tools, um herauszufinden, dass free mit
    einem invaliden Pointer aufgrufen wurde. Will man jedoch allerdings wissen,
    in welcher Zeile des Programms der Fehler aufgetreten ist, gibt einem
    `valgrind` darüber Auskunft.

8.  `realloc()` vs. `linked list`:

    Eine Struktur mit `realloc` würde mit einer initial Kapazität erstellt werden
    und diese ab einem gewissen Grad automatisch vergrößern (meißt verdoppeln).
    Damit ist das hinzufügen von Elementen billig, da immer genug Platz für ein
    paar weitere Elemente ist.

    Eine `linked list` muss für jedes löschen/hinzufügen `free` bzw `malloc`
    benutzen, was bei vielen Elementen ein problematisch sein kann.

    Auf der anderen Seite ist bei einer `realloc`-Struktur der Platz
    zusammenhängend:

    Wenn z.B. schon 1mb in der Struktur sind, und diese um 10k erweitert wird,
    kann es sein, dass der ganze Bereich an eine andere Stelle im Speicher
    kopiert wird (kann unerwartet lange dauern). Dies kann noch zu weiteren
    Problemen führen, wenn vor dem Kopieren noch Referenzen auf diese Stelle
    existierten. Diese würden damit irgendwo in den Speicher zeigen, was
    unsicher ist.

    |                                            `realloc`                                         |              `linked list`             |
    |----------------------------------------------------------------------------------------------|----------------------------------------|
    | schnell bei vielen kleineren Elementen                                                       | eher langsam (malloc pro element)      |
    | unsicher (hinterlassen von Referenzen) + kompliziert (benutzt nach belieben malloc und free) | einfach / relativ sicher               |
    | bedingt portabel (def. in ansi)                                                              |                                        |
