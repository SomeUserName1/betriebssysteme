# Answers

1.  *  `$ ./reallocation.py -s 1`:

       Das Programm `$ ./reallocation.py -s 1` liefert folgende Ausgabe:

       ```       
       ARG seed 1
       ARG address space size 1k
       ARG phys mem size 16k

       Base-and-Bounds register information:

          Base   : 0x0000363c (decimal 13884)
          Limit  : 290

       Virtual Address Trace
          VA  0: 0x0000030e (decimal:  782) --> PA or segmentation violation?
          VA  1: 0x00000105 (decimal:  261) --> PA or segmentation violation?
          VA  2: 0x000001fb (decimal:  507) --> PA or segmentation violation?
          VA  3: 0x000001cc (decimal:  460) --> PA or segmentation violation?
          VA  4: 0x0000029b (decimal:  667) --> PA or segmentation violation?

       For each virtual address, either write down the physical address it translates to
       OR write down that it is an out-of-bounds address (a segmentation violation). For
       this problem, you should assume a simple virtual address space of a given size.
       ```

       Um herauszufinden, ob eine virtuelle Adresse (VA) auf eine gültige
       physikalische Adresse (PA) zeigt, geht man folgendermaßen vor:

       1.  Als erstes überprüft man ob die VA kleiner als das gesetzte Limit ist:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;VA < Limit

           Falls dies zutrifft, kann eine gültige PA berechnet werden.
           Anderenfalls ist VA außerhalb der gültigen Adressen und führt dadurch
           zu einer SEGMENTATION VIOLATION.

       2.  Bestimme PA:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA

       Für das obrige Beispiel ergeben sich dabei folgende Adressen:

       Basis = 13884  
       Limit = 290  
       VALID falls: VA < LIMIT = TRUE  &nbsp;&nbsp;--> Berechene PA.  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
             anderenfalls:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                               = FALSE --> SEGMENTATION VIOLATION  
       PA = Basis + VA

       **VA 0: 0x0000030e (decimal:  782):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;782 > 290 (Limit) --> SEGMENTATION VIOLATION

       **VA  1: 0x00000105 (decimal:  261):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;261 < 290 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 13884 + 261 = 14145

       **VA 2: 0x000001fb (decimal:  507):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;507 > 290 --> SEGMENTATION VIOLATION

       **VA 3: 0x000001cc (decimal:  460):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;460 > 290 --> SEGMENTATION VIOLATION

       **VA 4: 0x0000029b (decimal:  667):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;667 > 290 --> SEGMENTATION VIOLATION

       Ruft man das Programm mit zusätzlichem `-c` Flag auf, ergibt sich
       folgende Ausgabe:
       ```
       $ ./relocation.py -s 1 -c

       ARG seed 1
       ARG address space size 1k
       ARG phys mem size 16k

       Base-and-Bounds register information:

          Base   : 0x0000363c (decimal 13884)
          Limit  : 290

       Virtual Address Trace
          VA  0: 0x0000030e (decimal:  782) --> SEGMENTATION VIOLATION
          VA  1: 0x00000105 (decimal:  261) --> VALID: 0x00003741 (decimal: 14145)
          VA  2: 0x000001fb (decimal:  507) --> SEGMENTATION VIOLATION
          VA  3: 0x000001cc (decimal:  460) --> SEGMENTATION VIOLATION
          VA  4: 0x0000029b (decimal:  667) --> SEGMENTATION VIOLATION
       ```
    *  `$ ./reallocation.py -s 2`:

       Basis = 15529  
       Limit = 500  
       VALID falls: VA < LIMIT = TRUE  &nbsp;&nbsp;--> Berechene PA.  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
             anderenfalls:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                               = FALSE --> SEGMENTATION VIOLATION   
       PA = Basis + VA  

       **VA 0: 0x00000039 (decimal:   57):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;57 < 500 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 15529 + 57 = 15586

       **VA  1: 0x00000056 (decimal:   86):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;86 < 500 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 15529 + 86 = 15615

       **VA  2: 0x00000357 (decimal:  855):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;855 > 500 --> SEGMENTATION VIOLATION

       **VA  3: 0x000002f1 (decimal:  753):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;753 > 500 --> SEGMENTATION VIOLATION

       **VA  4: 0x000002ad (decimal:  685):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;685 > 500 --> SEGMENTATION VIOLATION

       Ausgabe des Programms mit zusätzlichem `-c` Flag:

       ```
       $ ./relocation.py -s 2 -c

       ARG seed 2
       ARG address space size 1k
       ARG phys mem size 16k

       Base-and-Bounds register information:

          Base   : 0x00003ca9 (decimal 15529)
          Limit  : 500

       Virtual Address Trace
          VA  0: 0x00000039 (decimal:   57) --> VALID: 0x00003ce2 (decimal: 15586)
          VA  1: 0x00000056 (decimal:   86) --> VALID: 0x00003cff (decimal: 15615)
          VA  2: 0x00000357 (decimal:  855) --> SEGMENTATION VIOLATION
          VA  3: 0x000002f1 (decimal:  753) --> SEGMENTATION VIOLATION
          VA  4: 0x000002ad (decimal:  685) --> SEGMENTATION VIOLATION
       ```

    *  `$ ./reallocation.py -s 3`

       Lösung:

       Basis = 8916  
       Limit = 316  
       VALID falls: VA < LIMIT = TRUE  &nbsp;&nbsp;--> Berechene PA.  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
             anderenfalls:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                               = FALSE --> SEGMENTATION VIOLATION  
       PA = Basis + VA  

       **VA  0: 0x0000017a (decimal:  378):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;378 > 316 --> SEGMENTATION VIOLATION

       **VA  1: 0x0000026a (decimal:  618):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;618 > 316 SEGMENTATION VIOLATION

       **VA  2: 0x00000280 (decimal:  640):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;640 > 316 SEGMENTATION VIOLATION

       **VA  3: 0x00000043 (decimal:   67):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;67 < 316 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 8916 + 67 = 8983

       **VA  4: 0x0000000d (decimal:   13):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;13 < 316 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 8916 + 13 = 8929

       Ausgabe des Programms mit zusätzlichem `-c` Flag:

       ```
       $ ./relocation.py -s 3 -c

       ARG seed 3
       ARG address space size 1k
       ARG phys mem size 16k

       Base-and-Bounds register information:

          Base   : 0x000022d4 (decimal 8916)
          Limit  : 316

       Virtual Address Trace
          VA  0: 0x0000017a (decimal:  378) --> SEGMENTATION VIOLATION
          VA  1: 0x0000026a (decimal:  618) --> SEGMENTATION VIOLATION
          VA  2: 0x00000280 (decimal:  640) --> SEGMENTATION VIOLATION
          VA  3: 0x00000043 (decimal:   67) --> VALID: 0x00002317 (decimal: 8983)
          VA  4: 0x0000000d (decimal:   13) --> VALID: 0x000022e1 (decimal: 8929)
       ```

2.  Der Programmaufruf `$ ./relocation.py -s 0 -n 10` liefert folgende Ausgabe:
    ```
    $ ./relocation.py -s 0 -n 10

    ARG seed 0
    ARG address space size 1k
    ARG phys mem size 16k

    Base-and-Bounds register information:

      Base   : 0x00003082 (decimal 12418)
      Limit  : 472

    Virtual Address Trace
      VA  0: 0x000001ae (decimal:  430) --> PA or segmentation violation?
      VA  1: 0x00000109 (decimal:  265) --> PA or segmentation violation?
      VA  2: 0x0000020b (decimal:  523) --> PA or segmentation violation?
      VA  3: 0x0000019e (decimal:  414) --> PA or segmentation violation?
      VA  4: 0x00000322 (decimal:  802) --> PA or segmentation violation?
      VA  5: 0x00000136 (decimal:  310) --> PA or segmentation violation?
      VA  6: 0x000001e8 (decimal:  488) --> PA or segmentation violation?
      VA  7: 0x00000255 (decimal:  597) --> PA or segmentation violation?
      VA  8: 0x000003a1 (decimal:  929) --> PA or segmentation violation?
      VA  9: 0x00000204 (decimal:  516) --> PA or segmentation violation?

      For each virtual address, either write down the physical address it translates to
      OR write down that it is an out-of-bounds address (a segmentation violation). For
      this problem, you should assume a simple virtual address space of a given size.
    ```

    Das "bounds"-Register (Limit, `-l` Flag) muss hierbei auf den Wert der
    größten VA + 1 gesetzt werden, damit alle VAs auf gültige PAs verweißen
    (VA8 + 1 = 929 + 1 = 930). In diesem Fall wird `-l` auf 930 gesetzt.

3.  Der Programmaufruf `$ ./relocation.py -s 1 -n 10 -l 100` liefert folgende
    Ausgabe:

    ```
    $ ./relocation.py -s 1 -n 10 -l 100

    ARG seed 1
    ARG address space size 1k
    ARG phys mem size 16k

    Base-and-Bounds register information:

      Base   : 0x00000899 (decimal 2201)
      Limit  : 100

    Virtual Address Trace
      VA  0: 0x00000363 (decimal:  867) --> PA or segmentation violation?
      VA  1: 0x0000030e (decimal:  782) --> PA or segmentation violation?
      VA  2: 0x00000105 (decimal:  261) --> PA or segmentation violation?
      VA  3: 0x000001fb (decimal:  507) --> PA or segmentation violation?
      VA  4: 0x000001cc (decimal:  460) --> PA or segmentation violation?
      VA  5: 0x0000029b (decimal:  667) --> PA or segmentation violation?
      VA  6: 0x00000327 (decimal:  807) --> PA or segmentation violation?
      VA  7: 0x00000060 (decimal:   96) --> PA or segmentation violation?
      VA  8: 0x0000001d (decimal:   29) --> PA or segmentation violation?
      VA  9: 0x00000357 (decimal:  855) --> PA or segmentation violation?

    For each virtual address, either write down the physical address it translates to
    OR write down that it is an out-of-bounds address (a segmentation violation). For
    this problem, you should assume a simple virtual address space of a given size.
    ```
    Um den maximalen Wert für das "base"-Register (Basis, `-b` Flag) zu
    bestimmen, geht man folgendermaßen vor:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;maximale Basis = physikalische Speichergröße - LIMIT;

    Da das `-p` Flag nicht gesetzt wurde, wird der Standardwert für die
    physikalische Speichergröße von 16k (kibibyte) verwendet:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;physikalische Speichergröße = 16k = 16 * 1024b = 16384b;  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;maximale Basis = 16384 - 100 = 16284;

    Die Basis kann also maximal auf den Wert 16284 gesetzt werden, damit der
    Adressraum noch völlständig in den physikalischen Speicher passt.

4.  
    *  `$./reallocation.py -s 3 -a 128k -p 256k`:

       Ausgabe des Programmaufrufs `$./reallocation.py -s 3 -a 128k -p 256k`:

       ```
       $ ./relocation.py -s 3 -a 128k -p 256k

       ARG seed 3
       ARG address space size 128k
       ARG phys mem size 256k

       Base-and-Bounds register information:

         Base   : 0x00022d4a (decimal 142666)
         Limit  : 40565

       Virtual Address Trace
         VA  0: 0x0000bd6a (decimal: 48490) --> PA or segmentation violation?
         VA  1: 0x00013535 (decimal: 79157) --> PA or segmentation violation?
         VA  2: 0x0001405e (decimal: 82014) --> PA or segmentation violation?
         VA  3: 0x0000218c (decimal: 8588) --> PA or segmentation violation?
         VA  4: 0x000006bd (decimal: 1725) --> PA or segmentation violation?

       For each virtual address, either write down the physical address it translates to
       OR write down that it is an out-of-bounds address (a segmentation violation). For
       this problem, you should assume a simple virtual address space of a given size.
       ```

       Basis = 142666  
       Limit = 40565  
       VALID falls: VA < LIMIT = TRUE  &nbsp;&nbsp;--> Berechene PA.  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
             anderenfalls:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                               = FALSE --> SEGMENTATION VIOLATION  
       PA = Basis + VA

       **VA  0: 0x0000bd6a (decimal: 48490):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;48490 > 40565 --> SEGMENTATION VIOLATION

       **VA  1: 0x00013535 (decimal: 79157):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;79157 > 40565 --> SEGMENTATION VIOLATION

       **VA  2: 0x0001405e (decimal: 82014):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;82014 > 40565 --> SEGMENTATION VIOLATION

       **VA  3: 0x0000218c (decimal: 8588):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8588 < 40565 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 142666 + 8588 = 151254

       **VA  4: 0x000006bd (decimal: 1725):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1725 < 40565 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 142666 + 1725 = 144391

    *  `$ ./relocation.py -s0 -n 10 -a 10k -p 32k`:

       ```
       $ ./relocation.py -s0 -n 10 -a 10k -p 32k          

       ARG seed 0
       ARG address space size 10k
       ARG phys mem size 32k

       Base-and-Bounds register information:

         Base   : 0x00006104 (decimal 24836)
         Limit  : 4721

       Virtual Address Trace
         VA  0: 0x000010d2 (decimal: 4306) --> PA or segmentation violation?
         VA  1: 0x00000a5b (decimal: 2651) --> PA or segmentation violation?
         VA  2: 0x00001473 (decimal: 5235) --> PA or segmentation violation?
         VA  3: 0x00001032 (decimal: 4146) --> PA or segmentation violation?
         VA  4: 0x00001f5a (decimal: 8026) --> PA or segmentation violation?
         VA  5: 0x00000c21 (decimal: 3105) --> PA or segmentation violation?
         VA  6: 0x00001310 (decimal: 4880) --> PA or segmentation violation?
         VA  7: 0x00001755 (decimal: 5973) --> PA or segmentation violation?
         VA  8: 0x00002453 (decimal: 9299) --> PA or segmentation violation?
         VA  9: 0x0000142f (decimal: 5167) --> PA or segmentation violation?

       For each virtual address, either write down the physical address it translates to
       OR write down that it is an out-of-bounds address (a segmentation violation). For
       this problem, you should assume a simple virtual address space of a given size.
       ```

       Damit alle VAs gültig sind, muss das `-l` Flag ("bounds"-Register) auf den
       Wert der größten VA + 1 gesetzt werden. In diesem Fall hat VA 8 die größte
       VA und daher muss `-l` auf 9300 gesetzt werden (9299 + 1 = 9300).

       Daraus ergeben sich folgende PAs:

       BASE = 13781 (unterschiedlich zum Programmaufruf, da das Limit geändert wurde)  
       LIMIT = 9300  
       VALID falls: VA < LIMIT = TRUE  &nbsp;&nbsp;--> Berechene PA.  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
             anderenfalls:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                               = FALSE --> SEGMENTATION VIOLATION  
       PA = VA + BASE  

       **VA  0: 0x00000a5b (decimal: 2651):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2651 < 9300 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 13781 + 2651 = 16432

       **VA  1: 0x00001473 (decimal: 5235):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5235 < 9300 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 13781 + 5235 = 19016

       **VA  2: 0x00001032 (decimal: 4146):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4146 < 9300 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 13781 + 4146 = 17927

       **VA  3: 0x00001f5a (decimal: 8026):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8026 < 9300 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 13781 + 8026 = 21807

       **VA  4: 0x00000c21 (decimal: 3105):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3105 < 9300 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 13781 + 3105 = 16886

       **VA  5: 0x00001310 (decimal: 4880):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4880 < 9300 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 13781 + 4880 = 18661

       **VA  6: 0x00001755 (decimal: 5973):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5973 < 9300 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 13781 + 5973 = 19754

       **VA  7: 0x00002453 (decimal: 9299):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;9299 < 9300 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 13781 + 9299 = 23080

       **VA  8: 0x0000142f (decimal: 5167):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5167 < 9300 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 13781 + 5167 = 18948

       **VA  9: 0x00000b46 (decimal: 2886):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2886 < 9300 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + VA = 13781 + 2886 = 16667

    *  `$ ./relocation.py -s 1 -n 10 -l 100 -a 512k -p 1M -c`:  

       Die maximale Basis beträgt hierbei:

          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;physikalische Speichergröße = 1M = 1024 * 1024b = 1048576b

          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;maximale Basis = physikalische Specihergröße - Limit = 1048576 - 100 = 1048476b ≈ 1023k

5.  Kurzes Ausprobieren mit den `seeds` 0 - 4 liefert:

    `./relocation.py -s [0-4] -n 10000 -l [8000|4000|2000] -c | grep SEG | wc -l`  
    -> 0

    `./relocation.py -s [0-4] -n 10000 -l 1000 -c | grep SEG | wc -l`  
    -> 214, 240, 229, 262, 241

    `./relocation.py -s [0-4] -n 10000 -l 500 -c | grep SEG | wc -l`  
    -> 5152, 5079, 5075, 5047, 5070

    `./relocation.py -s [0-4] -n 10000 -l 250 -c | grep SEG | wc -l`  
    -> 7592, 7487, 7568, 7616, 7597

    Da der verwendete virtuelle Raum 1024 Adressen besitzt, wird schnell
    deutlich, dass der Anteil an  
    gültigen Adressen so groß ist wie die Größe des Limits geteilt durch die
    größe des virtuellen Raums.  
    (Anz.PAs(Speicher, Limit)=100(Limit/Speicher)[%])


    100% --- Anz. gültiger PAs  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;.&nbsp;&nbsp;&nbsp;&nbsp;f(x) = x  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;.  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;.  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;.   
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;.  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;.  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;.  
    0% |________________________  -> Limit  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0%&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;100% (Virt. Raum)
