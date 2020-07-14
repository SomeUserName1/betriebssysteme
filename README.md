#### Other OS courses:  
- [Stanford Spring '20](https://web.stanford.edu/~ouster/cgi-bin/cs140-spring20/index.php)  
- [MIT Fall '12](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-828-operating-system-engineering-fall-2012/index.htm)  
- [CalTech Fall '18](http://courses.cms.caltech.edu/cs124/lectures/)  
- [Berkley Summer '20](https://cs162.eecs.berkeley.edu/)  
- [Harvard 2020](https://read.seas.harvard.edu/cs161/2020/schedule/)  
- [Harvard Systems Prog. 2019](https://cs61.seas.harvard.edu/site/2019/)  
- [Tübingen WS '12/'13](https://uni-tuebingen.de/fakultaeten/mathematisch-naturwissenschaftliche-fakultaet/fachbereiche/informatik/lehrstuehle/symbolisches-rechnen/lehre/regelmaessige-veranstaltungen/betriebssysteme/)  
Viele europäische Top-Unis nutzen Moodle, ILIAS o.Ä., sodass man ohne Account der jeweiligen Uni keinen Zugriff hat...  
Geprüft wurden RWTH, TUM, KIT, ETH, EPFL, UCL  

#### Changelist:  
1. Extended Architektur/Struktur a bit  
2. Moved Synchronization to Processes & Threads  
3. Sloppy per unit annotation  
4. Info on previous knowledge of students is located in extra/besuchte\_kurse  
5. Altklausur from 2015 in extra/altklausuren  
6. Added brief ideas for exercise 1


## Einführung, Übersicht  [[Vorlesung 1]]
### Einführung  
    - Definition & Aufgaben  
    - Entwicklung & Geschichte  
### Überblick der Themen  
    - siehe Inhalt; jedes Thema kurz vorstellen (incl. Fragen & Probleme; priming)  
### Architekturen/Struktur  [[Vorlesung 2]]
    - Computerarchitektur & Hardware *Vieles sollte bekannt sein aus Rechnersysteme*  
        - Von Neumann Arch  
        - Modern CPU Arch (x86, arm): Multiprozessorsysteme, Hardware, Bus, Scheduling  
        - MoBo Überblick  
        - Bus Systeme & Controller Überblick  
    - Kernel Arch: monolithic, micro, exo, hybrid  
    - Betriebsarten: kernel space, user space, Protection Rings, System call interface  

### Einführung in die Programmierung in C [[Tutorium 1]]
    - Motivation (systemnah)
    - Grundlagen Widerholung (Bin/Hex, signed/unsigned, Bits/Bytes, IEEE754/Numerics, branchs & loops, funktionen) *sollte aus Konzepte der Informatik bekannt sein*  
    - libc vs. POSIX, Unixoid Kernel overview  
    - C Basics: chars & \0, bit ops (<<, ^, ~, ...), pointers, casts, printf & scanf, parts of stdio.h & stdlib.h  
    - (brief) C Datatypes: stdint.h, assert.h, complex.h, ctype.h, fenv.h, float.h, inttypes, stddef.h, stdbool.h, string.h, uchar.h, wchar.h, wctype.h ; POSIX: sys/types.h, monetary, strings.h  
    - (brief) C MISC: iso646.h, limits.h, locale.h, math.h, tgmath.h, stdarg.h, stdnoreturn ; POSIX Misc.: glob.h (globbing), iconv.h (codeset conversion), langinfo.h (locale), pwd.h (passwords), regex.h, search.h, stropts.h (streams), sys/utsname.h (uname), syslog.h, tar.h, trace.h, wordexp.h  
    - Compiler, Linker, IR, asm, obj, scopes, static vs shared lib, flags & sanitizers  
    - git *svn sollte aus Schlüsselqualifikation f. Informatiker bekannt sein*  
    - Shell (Befehle, Pipes, Sockets) *bash, sonst wie drüber*   
    - Blatt 1 Ausgabe: Wiederholungen & Basics
        1. Definition und Aufgaben Wdh.
        2. Geschichte: Unix == Linux?, Unix Philosopihie (one job at a time, everything is a file), POSIX standard  
        3. Fragen zur Control Unit & Bus System
        4. Kernel Arten Unterschiede
        5. Unterschied Kernel vs. Userspace
        6. Kleine C Aufgaben:
            - MergeSort in C with command line args, without pointers & call by value
            - Macros & pragmas
            - Structs, pointers, function pointers


## Virtualisation/Process Management Subsystem  
### Prozesse [[Vorlesung 3]]  
    - Definition Prozess  
    - Kontrollblöcke & Datenstrukturen 
    - Abstraktion & Isolation bei Prozessen
### Threads 
    - Definition,
    - Unterschied zu Prozessen, 
    - Kontrollblock & Datenstrukturen
    - Abstraktion & Isolation bei Threads

### Synchronisation & Kommunikation, Nebenläufigkeit [[Vorlesung 4]]
    - Race conditions
    - Mutual Exclusion (MutEx):
        - critical sections
        - Lock
        - Semaphore
        - Condition Variables
        - Monitor: combined semaphore + CV  
    - Theorie: readers-writers, dining philosophers
    - Starvation & Deadlocks: 
        - Prevention: preemption, pre-allocation, resolve mutEx, resolve circular wait  
        - Avoidance: wait/wound, wait/die
        - Recovery: process termination, preemption, rollback
        - Behebung, Starvation, Algorithmen, Modellierung mit Graphen;
    - Message passing
    - Hardwareunterstützung, Atomic Support

### Prozesse, Threads & Sync [[Tutorium 2]]
    - Blatt 1 Besprechung  
    - Call-by-Value vs. Call-by-Reference
    - Pointers revisited, Memory safety  
    - Compiler basics: flags, sanitizers, CMake/Makefiles, static vs shared lib revisited  
    - libc & POSIX overview, platform (independence) & calling conventions [dazu](https://stackoverflow.com/a/31865755/4801311)  
    - Processes: fork, join, wait, sleep, getXid/setXid, pipe, dup, exit, exec family (parts of C: errno.h, time.h, POSIX: unistd.h, sys/wait, sys/time.h, poll.h, spawn.h (RT), ulimit.h)  
    - Threads: pthread.h and some of the above & below  
    - Synchronization: C: stdatomic.h, threads.h, POSIX: sys/msg.h, fmtmsg.h, mqueue.h (RT), poll, semaphore.h, sys/ipc.h, sys/resource.h, sys/sem.h, sys/shm.h
    - Blatt 2:  
        1. Change MergeSort to use call-by-reference, pointers & to be memory safe  
        2. given code: split into smaller files, create modules, create Makefile & use CMake building a shared and a static library + questions on static vs shared  
        3. a) what mechanisms are there to achieve synchronization? whats the difference? b) Given code with race condition: Resolve RC  
        4. Create a child process 1.) printing hello world from the child, 2.) and use pipes to print the stdout from the parent after the child has died, 3.) experiment with how many processes you can create before your system crashes. is it useful to spawn so many processes, where does the limit come from? 4.) compute a sum in one process and using many processes and shared memory. What do you notice          
        5. Same as above using threads  
        6. How to prevent/avoid/recover from a deadlock


### Scheduling I [[Lecture 5]] 
    - CPU - E/A Burst cycles
    - Task Switching, Start, Terminierung
    - Interrupts & Signals

### Scheduling II [[Lecture 6]]
    - Ziele/Kriterien 
    - Algorithmen & Vergleich
    - MFQ & lottery scheduler 
    - [MuQSS](http://ck.kolivas.org/patches/muqss/sched-MuQSS.txt)

### Scheduling [[Tutorium 3]]
    - Interrupts & Signals
    - Algorithmen
    - 
    [//]: TODO


## Speicherverwaltung/ Memory Managament Subsystem
    - Hardware: Northbridge
    - Caching Policies
    - Allocation Algorithm & Fragmentation
    - Adressierung/Adressräume, virtual memory, 
    - Virtualisierung: logischer vs. physicher Speicher,
    - Segmentation
    - Paging: 
        - Page Table
        - Pages & Frames, 
        - Page Replacement Policy
        - Page fault
    - Swapping
    - Caches
    - Address Translation: Combined Paging + Segmentation

## I/O (Subsystem)
### Geräte & Treiber 
    - Hardware South bridge & PCIe + X d. North bridge
    - virtuelle Dateisysteme
    - Gerätemodelle
    - Schichten/Treiber
    - Schnittstellen
    - Struktur
    - Memory-Mapped I/O
    - Bus (I2C?)
    - Strom (ACPI?)
    - Timer
    - Optimierung/Performance (?) ??
    - Massenspeicher/Block Devices
        - Tape Drive
        - HDD
        - SSDs
        - RAID
        - Netzwerk- und Cloudspeicher ??
    - Character Devices
        - Keyboard
        - Mouse
        -

### File Systems  
    - Schnittstellen
    - Access control matrix
    - inodes 
    - Dateien
    - Verzeichnisse
    - SymLinks
    - Partitionen
    - Mounting
    - I/O Scheduling [Summary](https://www.thomas-krenn.com/de/wiki/Linux_I/O_Scheduler)  
    - Zuverlässigkeit & Journaling 
    - Formate (?)
    - Allokation (?)
    - Metadaten (?)
        - Character Devices
        - 

    - verteilte Dateisysteme ??
    - Backups ?? 
    - Sharing ??
    - Zugriffskontrolle -> Sicherheit ??
    - in-memory Dateisysteme ??
    - Netzwerkdateisysteme/NFS ??


### Terminals  
[//]: TODO   

### Networking & Sockets  
[//]: TODO  


## Vertiefungen
### Virtuelle Systeme (Zusammen mit Kryptographie als "Zusatz" für extra Punkte)
    - Container
    - Hypervisor
    - trap-and-emulate
    - Hardware Unterstützung
    - verteilte Systeme

### Grafik & Multimedia (??)
    - Grundlagen
    - Video
    - Audio
    - Formate
    - Echtzeit Scheduling
    - Zusammenhang Dateisysteme
    - graphische Benutzeroberflächen: Design, Struktur, Fenster bei Unix und Windows?

### Sicherheit
#### Grundlagen ("Auf dem weg" mit einbauen?)
    - Ziele
    - Identifikation
    - Ressourcenkontrolle
    - Zugriffskontrolle
    - Authentifizierung/Passwörter
    - Capabilities
    - Andere Ansätze
    - Security by Design
#### Kryptographie/Verschlüsselung (Zusammen mit Virtuellen Systemen als "zusatz Blatt")
    - symmetrische und asymmetrische Verschlüsselung
    - Hashfunktionen
    - PGP & S/MIME
    - Netzprotokolle TLS, SSH
    - Hardware
    - Zufall
    - Trusted Platform Module

#### Formale Ansätze ! more research necessary (??)
    - seL4 microkernel?   
#### Gefahren/Angriffsmöglichkeiten und Schutzmechanismen (Zusatz)
    - Sicherheitslücken
    - responsible disclose
    - Viren, Spyware, Rootkits
    - Speicherangriffe, side channel
    - social engineering, Zugriff vor Ort
    - Sandboxing
    - Stack Canaries
    - data execution preventio
    - address space randomization

Fallbeispiele, spezielle Anforderungen
    - Linux ("unterwegs" in den Übungen)
        - Geschichte
        - Shells
        - Kernels
        - Scheduling
        - Prozessmanagement
        - Speicher
        - E/A
        - Dateisysteme
        - Sicherheit
        - Bootprozess
        - Daemons
        - System Services]
    - Echtzeit BS, verteilte BS, eingebettete BS (mal erwähnen oder in vollem umfang?)  

Zusammenfassung & Ausblick
    - Wiederholung der Themen
    - Entwurf (Wiederholung sollte reichen??)
        - Schnittstellen
        - Implementierung
        - Performanz
        - Trends
        - Ziele
        - Herausforderungen
        - Trade-offs
        - Software Engineering


Notizen:
Einführung: Entwicklung & Geschichte: Zeitstrahl/Stammbaum (Marktanteile?)
Abstraktion: Speicherverwaltung: Caches: least-recently-used cache?
Abstraktion: Scheduling: Multi-level Feedback Queue, Lotterie Scheduling
Abstraktion: Virtualisierung: Multiprozessorsysteme: symmetric multi-processing
Sicherheit: Formale Modelle: http://www.ra.cs.uni-tuebingen.de/lehre/ss11/introsec/07-secmod.pdf
Sicherheit: Angriffe: Beispiele: heartbleed, rowhammer
Fallbeispiele: ggfs. Unterschiede zu Windows, MacOS, iOS, Android


! einsortieren (Übungen): E/A (wenn IO), Umgebungsvariablen (wenn platz ist), Speicher anfordern(speicher verwaltung) Speicherlayout, relocation, treiber schreiben
