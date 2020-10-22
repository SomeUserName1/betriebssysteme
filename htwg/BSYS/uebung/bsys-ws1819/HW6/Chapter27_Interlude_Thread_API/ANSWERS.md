# Answers

1.  ###### First build `main-race.c`. Examine the code so you can see the (hopefully obvious) data race in the code. Now run `helgrind` (by typing `valgrind --tool=helgrind ./main-race`) to see how it reports the race. Does it point to the right lines of code? What other information does it give to you?

    -  Ruft man `valgrind --tool=helgrind ./main-race` auf, erhält man folgende
       Ausgabe:

       ```
       $ valgrind --tool=helgrind ./main-race           

       [...]
       ==10244== Command: ./main-race
       ==10244==
       ==10244== ---Thread-Announcement------------------------------------------
       ==10244==
       ==10244== Thread #1 is the program's root thread
       ==10244==
       ==10244== ---Thread-Announcement------------------------------------------
       ==10244==
       ==10244== Thread #2 was created
       ==10244==    at 0x518287E: clone (clone.S:71)
       ==10244==    by 0x4E49EC4: create_thread (createthread.c:100)
       ==10244==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
       ==10244==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==10244==    by 0x108C54: Pthread_create (mythreads.h:51)
       ==10244==    by 0x108D26: main (main-race.c:17)
       ==10244==
       ==10244== ----------------------------------------------------------------
       ==10244==
       ==10244== Possible data race during read of size 4 at 0x30A040 by thread #1
       ==10244== Locks held: none
       ==10244==    at 0x108D27: main (main-race.c:20)
       ==10244==
       ==10244== This conflicts with a previous write of size 4 by thread #2
       ==10244== Locks held: none
       ==10244==    at 0x108CDF: worker (main-race.c:10)
       ==10244==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==10244==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==10244==    by 0x518288E: clone (clone.S:95)
       ==10244==  Address 0x30a040 is 0 bytes inside data symbol "balance"
       ==10244==
       ==10244== ----------------------------------------------------------------
       ==10244==
       ==10244== Possible data race during write of size 4 at 0x30A040 by thread #1
       ==10244== Locks held: none
       ==10244==    at 0x108D30: main (main-race.c:20)
       ==10244==
       ==10244== This conflicts with a previous write of size 4 by thread #2
       ==10244== Locks held: none
       ==10244==    at 0x108CDF: worker (main-race.c:10)
       ==10244==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==10244==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==10244==    by 0x518288E: clone (clone.S:95)
       ==10244==  Address 0x30a040 is 0 bytes inside data symbol "balance"
       ==10244==
       [...]
       ==10244== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

       ```

    -  `helgrind` liefert einem Informationen über:

       *  Die Anzahl an erstellten Threads, sowie Informationen darüber,
          welcher Thread der "Root Thread" ist.

       *  Zeilen bzw. Zeilennummern, in denen mögliche "Data Races" auftreten
          können. Dabei wird einmal zwischen lesenden Zugriffen und schreibenden
          Zugriffen unterschieden, weswegen `helgrind` zweimal die betroffenen
          Zeilen ausgibt.

       *  Den Namen der Variablen, welche durch Locks geschützt werden sollte.

       *  Die Anzahl an verwendeten Locks, sowie deren Adressen (falls Locks
          verwendet wurden).

       *  Wie viele Fehler insgesamt gefunden wurden.

2.  ###### What happens when you remove one of the offending lines of code?

    -  `helgrind` kann keine Fehler mehr finden. Dies liegt daran, dass jetzt nur
       noch ein Thread auf `balance` zugreift und somit auch kein
       "Data Race" mehr auftreten kann.

    ###### Now add a lock around one of the updates to the shared variable, and then around both. What does helgrind report in each of these cases?

    -  Lock um nur einen der Updates von `balance`:

       *  Ausgabe von `helgrind`:

          ```
          $ valgrind --tool=helgrind ./main-race

          [...]
          ==5583== ---Thread-Announcement------------------------------------------
          ==5583==
          ==5583== Thread #1 is the program's root thread
          ==5583==
          ==5583== ---Thread-Announcement------------------------------------------
          ==5583==
          ==5583== Thread #2 was created
          ==5583==    at 0x518287E: clone (clone.S:71)
          ==5583==    by 0x4E49EC4: create_thread (createthread.c:100)
          ==5583==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
          ==5583==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
          ==5583==    by 0x108C54: Pthread_create (mythreads.h:51)
          ==5583==    by 0x108D26: main (main-race.c:15)
          ==5583==
          ==5583== ----------------------------------------------------------------
          ==5583==
          ==5583==  Lock at 0x30A060 was first observed
          ==5583==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
          ==5583==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
          ==5583==    by 0x108D32: main (main-race.c:16)
          ==5583==  Address 0x30a060 is 0 bytes inside data symbol "lock"
          ==5583==
          ==5583== Possible data race during read of size 4 at 0x30A040 by thread #1
          ==5583== Locks held: 1, at address 0x30A060
          ==5583==    at 0x108D33: main (main-race.c:17)
          ==5583==
          ==5583== This conflicts with a previous write of size 4 by thread #2
          ==5583== Locks held: none
          ==5583==    at 0x108CDF: worker (main-race.c:9)
          ==5583==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
          ==5583==    by 0x4E496DA: start_thread (pthread_create.c:463)
          ==5583==    by 0x518288E: clone (clone.S:95)
          ==5583==  Address 0x30a040 is 0 bytes inside data symbol "balance"
          ==5583==
          ==5583== ----------------------------------------------------------------
          [...]
          ==5583==
          ==5583== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
          ```

       *  `helgrind` liefert uns nun Informationen über:

          *  Einen vergessenen Lock. Da der kritische Bereich immer noch nicht
             vollständig durch Locks geschützt wurde.

          *  Verwendete Locks.

    -  Lock um beide Updates von `balance`.

       `helgrind` kann nun keine Fehler mehr erkennen, da nun der kritische
       Bereich geeignet durch Lockingmechanismen geschützt wurde und daher
       keine "Data Races" mehr auftreten können.

3.  ###### Now let’s look at `main-deadlock.c`. Examine the code. This code has a problem known as deadlock (which we discuss in much more depth in a forthcoming chapter). Can you see what problem it might have?

    -  Ein Deadlock beschreibt eine zyklische Wartesituation zwischen mehreren
       Threads. Sobald ein Deadlock in einem Programm aufgetreten ist,
       terminiert dieses nicht mehr, da die Threads, gegenseitig aufeinander
       warten. Daher muss das Programm manuell beendet werden.

    -  Bei `main-deadlock.c` tritt ein Deadlock auf, wenn:

       Wenn beispielsweiße Thread 1 den Lock auf `m1` anfordert und
       anschließend Thread 2 den Lock auf `m2` anfordert, kann keiner der
       Threads den zweiten Lock im if/else-Block anfordern, da die Threads nun
       gegenseitig darauf warten, dass der andere den Lock wieder frei gibt.
       Da dies nicht mehr eintreten kann, ist das Programm "gedeadlockt".

       &rarr; Wenn jeder Thread den ersten Lock im if/else-Block hält.

4.  ###### Now run `helgrind` on this code. What does `helgrind` report?

    -  `helgrind` liefert folgende Ausgabe für das Programm `main-deadlock`:

       ```
       $ valgrind --tool=helgrind ./main-deadlock

       [...]
       ==11245== ---Thread-Announcement------------------------------------------
       ==11245==
       ==11245== Thread #3 was created
       ==11245==    at 0x518287E: clone (clone.S:71)
       ==11245==    by 0x4E49EC4: create_thread (createthread.c:100)
       ==11245==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
       ==11245==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x108C54: Pthread_create (mythreads.h:51)
       ==11245==    by 0x108D89: main (main-deadlock.c:24)
       ==11245==
       ==11245== ----------------------------------------------------------------
       ==11245==
       ==11245== Thread #3: lock order "0x30A040 before 0x30A080" violated
       ==11245==
       ==11245== Observed (incorrect) order is: acquisition of lock at 0x30A080
       ==11245==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==11245==    by 0x108D06: worker (main-deadlock.c:13)
       ==11245==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==11245==    by 0x518288E: clone (clone.S:95)
       ==11245==
       ==11245==  followed by a later acquisition of lock at 0x30A040
       ==11245==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==11245==    by 0x108D12: worker (main-deadlock.c:14)
       ==11245==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==11245==    by 0x518288E: clone (clone.S:95)
       ==11245==
       ==11245== Required order was established by acquisition of lock at 0x30A040
       ==11245==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==11245==    by 0x108CEC: worker (main-deadlock.c:10)
       ==11245==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==11245==    by 0x518288E: clone (clone.S:95)
       ==11245==
       ==11245==  followed by a later acquisition of lock at 0x30A080
       ==11245==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==11245==    by 0x108CF8: worker (main-deadlock.c:11)
       ==11245==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==11245==    by 0x518288E: clone (clone.S:95)
       ==11245==
       ==11245==  Lock at 0x30A040 was first observed
       ==11245==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==11245==    by 0x108CEC: worker (main-deadlock.c:10)
       ==11245==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==11245==    by 0x518288E: clone (clone.S:95)
       ==11245==  Address 0x30a040 is 0 bytes inside data symbol "m1"
       ==11245==
       ==11245==  Lock at 0x30A080 was first observed
       ==11245==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==11245==    by 0x108CF8: worker (main-deadlock.c:11)
       ==11245==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==11245==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==11245==    by 0x518288E: clone (clone.S:95)
       ==11245==  Address 0x30a080 is 0 bytes inside data symbol "m2"
       ==11245==
       [...]
       ==11245== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)
       ```

    -  `helgrind` liefert Informationen über:

       Eine falsche Lockreihenfolge. Wenn die Locks der beiden Threads nämlich
       immer in der selben Reihenfolge ausgeführt werden würden, kann es zu
       keinem Deadlock kommen.

    -  Ausgabe von `helgrind` nachdem die Locks so platziert wurden, dass sie
       von beiden Threads in der selben Reihenfolge angefordert werden:

       ```
       $ valgrind --tool=helgrind ./main-deadlock

       ==11399== Helgrind, a thread error detector
       ==11399== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
       ==11399== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
       ==11399== Command: ./main-deadlock
       ==11399==
       ==11399==
       ==11399== For counts of detected and suppressed errors, rerun with: -v
       ==11399== Use --history-level=approx or =none to gain increased speed, at
       ==11399== the cost of reduced accuracy of conflicting-access information
       ==11399== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 11 from 11)
       ```

5.  ###### Now run `helgrind` on `main-deadlock-global.c`. Examine the code; does it have the same problem that `main-deadlock.c` has? Should `helgrind` be reporting the same error?

    -  `helgrind` liefert folgende Ausgabe für das Programm `main-deadlock-global`:

       ```
       $ valgrind --tool=helgrind ./main-deadlock-global

       [...]
       ==14133== ---Thread-Announcement------------------------------------------
       ==14133==
       ==14133== Thread #3 was created
       ==14133==    at 0x518287E: clone (clone.S:71)
       ==14133==    by 0x4E49EC4: create_thread (createthread.c:100)
       ==14133==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
       ==14133==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x108C54: Pthread_create (mythreads.h:51)
       ==14133==    by 0x108DA1: main (main-deadlock-global.c:27)
       ==14133==
       ==14133== ----------------------------------------------------------------
       ==14133==
       ==14133== Thread #3: lock order "0x30A080 before 0x30A0C0" violated
       ==14133==
       ==14133== Observed (incorrect) order is: acquisition of lock at 0x30A0C0
       ==14133==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==14133==    by 0x108D12: worker (main-deadlock-global.c:15)
       ==14133==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==14133==    by 0x518288E: clone (clone.S:95)
       ==14133==
       ==14133==  followed by a later acquisition of lock at 0x30A080
       ==14133==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==14133==    by 0x108D1E: worker (main-deadlock-global.c:16)
       ==14133==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==14133==    by 0x518288E: clone (clone.S:95)
       ==14133==
       ==14133== Required order was established by acquisition of lock at 0x30A080
       ==14133==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==14133==    by 0x108CF8: worker (main-deadlock-global.c:12)
       ==14133==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==14133==    by 0x518288E: clone (clone.S:95)
       ==14133==
       ==14133==  followed by a later acquisition of lock at 0x30A0C0
       ==14133==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==14133==    by 0x108D04: worker (main-deadlock-global.c:13)
       ==14133==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==14133==    by 0x518288E: clone (clone.S:95)
       ==14133==
       ==14133==  Lock at 0x30A080 was first observed
       ==14133==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==14133==    by 0x108CF8: worker (main-deadlock-global.c:12)
       ==14133==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==14133==    by 0x518288E: clone (clone.S:95)
       ==14133==  Address 0x30a080 is 0 bytes inside data symbol "m1"
       ==14133==
       ==14133==  Lock at 0x30A0C0 was first observed
       ==14133==    at 0x4C3403C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x108AD7: Pthread_mutex_lock (mythreads.h:23)
       ==14133==    by 0x108D04: worker (main-deadlock-global.c:13)
       ==14133==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==14133==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==14133==    by 0x518288E: clone (clone.S:95)
       ==14133==  Address 0x30a0c0 is 0 bytes inside data symbol "m2"
       ==14133==
       [...]
       ==14133== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)
       ```

    -  `helgrind` meldet den selben Fehler wie beim Programm `main-deadlock.c`.

       Durch den globalen Lock um die anderen Locks, kann nun kein Deadlock mehr
       auftreten. Jedoch ist meiner Meinung nach die Lösung mit der Reihenfolge
       übersichtlicher und eleganter (und wahrscheinlich auch ein klein wenig
       performanter).

    ###### What does this tell you about tools like `helgrind`?

    -  Tools wie `helgrind` können einem bei der Fehlersuche helfen, sind aber
       nur ein Hilfsmittel. Selbst wenn `helgrind` noch Fehler findet, kann es
       sein das der Code schon Threadsicher  ist. Findet `helgrind` jedoch keine
       Fehler mehr, kann man sich sicher sein, dass der Code korrekt funktioniert.

6.  ###### Let’s next look at `main-signal.c`. This code uses a variable (`done`) to signal that the child is done and that the parent can now continue. Why is this code inefficient? (what does the parent end up spending its time doing, particularly if the child thread takes a long time to complete?)

    -  Der Code ist ineffizient, da aktives Warten ("spin waiting") betrieben
       wird. Dabei werden CPU-Zyklen verschwendet, welche ein anderes Programm
       währendessen nutzen könnte. Des Weiteren ist aktives Warten auch noch
       sehr energieineffizient.

7.  ###### Now run `helgrind` on this program. What does it report?

    -  `helgrind` liefert folgende Ausgabe für das Programm `main-signal`:

       ```
       $ valgrind --tool=helgrind ./main-signal

       [...]
       this should print first
       ==15202== ---Thread-Announcement------------------------------------------
       ==15202==
       ==15202== Thread #1 is the program's root thread
       ==15202==
       ==15202== ---Thread-Announcement------------------------------------------
       ==15202==
       ==15202== Thread #2 was created
       ==15202==    at 0x518287E: clone (clone.S:71)
       ==15202==    by 0x4E49EC4: create_thread (createthread.c:100)
       ==15202==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
       ==15202==    by 0x4C36A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==15202==    by 0x108CA4: Pthread_create (mythreads.h:51)
       ==15202==    by 0x108D81: main (main-signal.c:15)
       ==15202==
       ==15202== ----------------------------------------------------------------
       ==15202==
       ==15202== Possible data race during read of size 4 at 0x30A014 by thread #1
       ==15202== Locks held: none
       ==15202==    at 0x108D83: main (main-signal.c:16)
       ==15202==
       ==15202== This conflicts with a previous write of size 4 by thread #2
       ==15202== Locks held: none
       ==15202==    at 0x108D36: worker (main-signal.c:9)
       ==15202==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==15202==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==15202==    by 0x518288E: clone (clone.S:95)
       ==15202==  Address 0x30a014 is 0 bytes inside data symbol "done"
       ==15202==
       ==15202== ----------------------------------------------------------------
       ==15202==
       ==15202== Possible data race during write of size 1 at 0x5C531A5 by thread #1
       ==15202== Locks held: none
       ==15202==    at 0x4C3C546: mempcpy (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==15202==    by 0x50EC993: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1258)
       ==15202==    by 0x50E1A8E: puts (ioputs.c:40)
       ==15202==    by 0x108D98: main (main-signal.c:18)
       ==15202==  Address 0x5c531a5 is 21 bytes inside a block of size 1,024 alloc'd
       ==15202==    at 0x4C30F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==15202==    by 0x50DF18B: _IO_file_doallocate (filedoalloc.c:101)
       ==15202==    by 0x50EF378: _IO_doallocbuf (genops.c:365)
       ==15202==    by 0x50EE497: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:759)
       ==15202==    by 0x50EC9EC: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1266)
       ==15202==    by 0x50E1A8E: puts (ioputs.c:40)
       ==15202==    by 0x108D35: worker (main-signal.c:8)
       ==15202==    by 0x4C36C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
       ==15202==    by 0x4E496DA: start_thread (pthread_create.c:463)
       ==15202==    by 0x518288E: clone (clone.S:95)
       ==15202==  Block was alloc'd by thread #2
       ==15202==
       this should print last
       ==15202==
       [...]
       ==15202== ERROR SUMMARY: 23 errors from 2 contexts (suppressed: 40 from 40)
       ```

    -  `helgrind` liefert folgende Informationen:

       *  Es könnte zu einem potentiellen "Data Race" in den Zeilen 16 und 9 kommen.

    ###### Is the code correct?

    -  In diesem Fall ist der Code tätsächlich korrekt. Dies liegt aber nur daran,
       das die Varable `done` mit dem Wert 0 initialisiert wird und nur ein Thread
       (hier Thread 2) schreibend auf die Variable zugreift. Daher kann Thread 1
       keinen falschen Wert in der `done` Variable lesen.

       Hierdurch wird gewährleistet, dass immer erst die Message von Thread 2
       "geprinted" wird und anschließend erst die Message von Thread 1.

8.  ###### Now look at a slightly modified version of the code, which is found in `main-signal-cv.c`. This version uses a condition variable to do the signaling (and associated lock). Why is this code preferred to the previous version?

    -  Da auf aktives Warten verzichtet wird.

    -  Da der kritische Bereich ordnungsgemäß durch Lockingmechanismen geschützt
       wurde.

    ###### Is it correctness, or performance, or both?

    -  Das Programm `main-signal-cv` ist einerseits korrekt und zusätzlich noch
       performanter als das Programm `main-signal`.

    -  Die Performance erhöt sich im Gegensatz zum `main-signal` Programm, da
       auf aktives Warten verzichtet wird.

9.  ###### Once again run `helgrind` on `main-signal-cv`. Does it report any errors?

    -  `helgrind` liefert folgende Ausgabe für das Programm `main-signal-cv`:

       ```
       $ valgrind --tool=helgrind ./main-signal-cv

       ==19594== Helgrind, a thread error detector
       ==19594== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
       ==19594== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
       ==19594== Command: ./main-signal-cv
       ==19594==
       this should print first
       this should print last
       ==19594==
       ==19594== For counts of detected and suppressed errors, rerun with: -v
       ==19594== Use --history-level=approx or =none to gain increased speed, at
       ==19594== the cost of reduced accuracy of conflicting-access information
       ==19594== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 13 from 13)
       ```

       Nein, `helgrind` kann keine Fehler im Programm `main-signal-cv` finden.
