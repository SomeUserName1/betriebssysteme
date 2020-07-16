# Answers

1.  *  `$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0`:

       Der Programmaufruf `$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0` liefert folgende Ausgabe:

       ```
       $ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0

       ARG seed 0
       ARG address space size 128
       ARG phys mem size 512

       Segment register information:

         Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
         Segment 0 limit                  : 20

         Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
         Segment 1 limit                  : 20

       Virtual Address Trace
         VA  0: 0x0000006c (decimal:  108) --> PA or segmentation violation?
         VA  1: 0x00000061 (decimal:   97) --> PA or segmentation violation?
         VA  2: 0x00000035 (decimal:   53) --> PA or segmentation violation?
         VA  3: 0x00000021 (decimal:   33) --> PA or segmentation violation?
         VA  4: 0x00000041 (decimal:   65) --> PA or segmentation violation?

       For each virtual address, either write down the physical address it translates to
       OR write down that it is an out-of-bounds address (a segmentation violation). For
       this problem, you should assume a simple address space with two segments: the top
       bit of the virtual address can thus be used to check whether the virtual address
       is in segment 0 (topbit=0) or segment 1 (topbit=1). Note that the base/limit pairs
       given to you grow in different directions, depending on the segment, i.e., segment 0
       grows in the positive direction, whereas segment 1 in the negative.
       ```

       Um herauszufinden, ob eine virtuelle Addresse (VA) zu einer gültigen
       physikalischen Adresse übersetzt werden kann, geht man folgendermaßen
       vor:

       1.  VA in Binärrepresentation umwandeln

       2.  Top-Bit von VA bestimmen, um zu wissen in welchem Segment sie liegt:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Top-Bit = log_2(virtuelle Adressraumgröße)**

       3.  Falls VA in einem Segment liegt das negativ wächst (Hier: SEG 1):

           1.  Dezimalrepräsentation des Offsets von VA betimmen

           2.  Effektiven Offset berechnen:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**effektiver Offset = 2^(#Bits für Offset) - Offset von VA**

           3.  Prüfen, ob effektiver Offset valide ist:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**effektiver Offset <= Limit --> VALID**

           4.  Wenn effektiver Offset valide, bereche PA:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**PA = Basis - effektiver Offset**

       4.  Anderenfalls (HIER SEG 0):

           1.  Dezimalrepräsentation des Offsets von VA bestimmen

           2.  Prüfen ob Offset valide ist:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Offset von VA < Limit --> VALID**

           3.  Wenn Offset von VA valide, berechne PA:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**PA = Basis + Offset**

       **Lösung für das obrige Beispiel:**

       virtuelle Adressraumgröße = 128  
       physikalische Speichergröße = 512

       SEG 0 Basis = 0  
       SEG 0 Limit = 20  

       SEG 1 Basis = 512
       SEG 1 Limit = 20

       **VA  0: 0x0000006c (decimal:  108):**

       1.  Binärrepräsentation von VA bestimmen:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(108) dez = (1101100) bin  

       2.  Top-Bit bestimmen:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Adressraumgröße) = log_2(128) = 7 --> 7. Bit ist Top-Bit  
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1101100  
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;^  
           &nbsp;&nbsp;Top-Bit

           Da das Top-Bit = 1 ist, verweißt VA auf eine Adresse in SEG 1. Jedoch
           ist noch nicht sichergestellt, dass es sich dabei um eine gültige
           Adresse handelt.

       3.  VA 0 liegt in Seg 1, welches negativ wächst:

           1.  Dezimalrepräsentation des Offsets von VA bestimmen:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; (101100) bin = (44) dez

           2.  Effektiven Offset berechnen:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2^(#Bits für Offset) = 2^(6) = 64  
               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;effektiver Offset = 2^(#Bits für Offset) - Offset von VA = 2^(6) - 44 = 64 - 44 = 20

           3.  Prüfen ob effektiver Offset von VA valide ist:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;20 <= 20 --> VALID

           4.  Wenn effektiver Offset valide, berechne PA:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis - effektiver Offset = 512 - 20 = 492

       **VA  1: 0x00000061 (decimal:   97):**

       1.  Binärrepräsentation von VA bestimmen:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(97) dez = (1100001) bin

       2.  Top-Bit bestimmen:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Adressraumgröße) = log_2(128) = 7 --> 7. Bit ist Top-Bit  
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1100001  
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;^  
           &nbsp;&nbsp;Top-Bit

           Da das Top-Bit = 1 ist, verweißt VA auf eine Adresse in SEG 1. Jedoch
           ist noch nicht sichergestellt, dass es sich dabei um eine gültige
           Adresse handelt.

       3.  VA 1 liegt in SEG 1, welches negativ wächst:

           1.  Dezimalrepräsentation des Offsets von VA bestimmen:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(100001) bin = (33) dez

           2.  Effektiven Offset berechnen:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;effektiver Offset = 2^(#Bits für Offset) - Offset von VA = 2^6 - 33 = 64 - 33 = 31

           3.  Prüfen ob effektiver Offset von VA valide ist:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 31 > 20 --> SEGMENTATION VIOLATION (SEG 1)

       **VA  2: 0x00000035 (decimal:   53):**  

       1.  Binärrepräsentation von VA bestimmen:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(53) dez  = (110101) bin

       2.  Top-Bit bestimmen:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Adressraumgröße) = log_2(128) = 7 --> 7. Bit ist Top-Bit  
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0110101  
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;^  
           &nbsp;&nbsp;Top-Bit

           Da das Top-Bit = 1 ist, verweißt VA auf eine Adresse in SEG 1. Jedoch
           ist noch nicht sichergestellt, dass es sich dabei um eine gültige
           Adresse handelt.

       3. VA 2 liegt in SEG 0, welches Positiv wächst:

          1.  Dezimalrepräsentation des Offsets von VA bestimmen:

              &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(110101) bin = (53) bin

          2.  Prüfen ob Offset von VA valide ist:

              &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;53 > 20 --> SEGMENTATION VIOLATION (SEG 0)

       **VA  3: 0x00000021 (decimal:   33):**

       1.  Binärrepräsentation von VA bestimmen:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(33) dez = (100001) bin

       2.  Top-Bit bestimmen:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(128) = 7 --> 7. Bit ist Top-Bit  
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0100001  
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;^

       3.  VA 3 liegt in SEG 0, welches positiv wächst:

           1.  Dezimalrepräsentation des Offsets von VA bestimmen:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(100001) bin = (33) dez

           2.  Prüfen ob Offset von VA valide ist:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 33 > 20 --> SEGMENTATION VIOLATION (SEG 0)

       **VA  4: 0x00000041 (decimal:   65):**

       1.  Binärrepräsentation bestimmen:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(65) dez = (1000001) bin

       2.  Top-Bit bestimmen:

           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1000001
           &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;^
           &nbsp;&nbsp;Top-Bit

       3.  VA 4 liegt in SEG 1, das negativ wächst:

           1.  Dezimalrepräsentation des Offsets von VA bestimmen:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(000001) = 1

           2.  Effektiven Offset berechen:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;effektiver Offset = 2^(#Bits für Offset) - Offset von VA = 2^6 - 1 = 64 - 1 = 63

           3.  Prüfen ob effektiver Offset von VA valide ist:

               &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;63 > 20 --> SEGMENTATION VIOLATION (SEG 1)

    *  `$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1`:

       Der Programmaufruf `$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1`
       liefert folgende Ausgabe:

       ```
       `$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1`

       ARG seed 1
       ARG address space size 128
       ARG phys mem size 512

       Segment register information:

         Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
         Segment 0 limit                  : 20

         Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
         Segment 1 limit                  : 20

       Virtual Address Trace
         VA  0: 0x00000011 (decimal:   17) --> PA or segmentation violation?
         VA  1: 0x0000006c (decimal:  108) --> PA or segmentation violation?
         VA  2: 0x00000061 (decimal:   97) --> PA or segmentation violation?
         VA  3: 0x00000020 (decimal:   32) --> PA or segmentation violation?
         VA  4: 0x0000003f (decimal:   63) --> PA or segmentation violation?

       For each virtual address, either write down the physical address it translates to
       OR write down that it is an out-of-bounds address (a segmentation violation). For
       this problem, you should assume a simple address space with two segments: the top
       bit of the virtual address can thus be used to check whether the virtual address
       is in segment 0 (topbit=0) or segment 1 (topbit=1). Note that the base/limit pairs
       given to you grow in different directions, depending on the segment, i.e., segment 0
       grows in the positive direction, whereas segment 1 in the negative.
       ```

       **Lösung:**

       virtuelle Addressraumgröße = 128  
       physikalische Speichergröße = 512

       SEG 0 Basis = 0  
       SEG 0 Limit = 20   

       SEG 1 Basis = 512  
       SEG 1 Limit = 20

       **VA  0: 0x00000011 (decimal:   17):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(17) dez = (10001) bin  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Addressraumgröße) = log_2(128) = 7  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;=> Top-Bit = 0  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Offset von VA = 17  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;17 < 20 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + Offset = 0 + 17 = 17

       **VA  1: 0x0000006c (decimal:  108):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(108) dez = (1101100) bin  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Adressraumgröße) = log_2(128) = 7  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;=> Top-Bit = 1  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Offset von VA = (101100) bin = (44) dez  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;effektiver Offset = 2^(#Bits für Offset) - Offset von VA = 2^6 - 44 = 64 - 44 = 20  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;20 <= 20 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis - effektiver Offset = 512 - 20 = 492

       **VA  2: 0x00000061 (decimal:   97):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(97) dez = (1100001) bin  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Addressraumgröße) = log_2(128) = 7  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;=> Top-Bit = 1  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Offset von VA = (100001) bin = (33) dez  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;effektiver Offset = 2^(#Bits für Offset) - Offset von VA = 2^6 - 33 = 64 - 33 = 31  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;31 > 20 --> SEGMENTATION VIOLATION (SEG 1)

       **VA  3: 0x00000020 (decimal:   32):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(32) dez = (0100000) bin  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Adressraumgröße) = log_2(128) = 7  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;=> Top-Bit = 0  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Offset von VA = 32  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;32 > 20 --> SEGMENTATION VIOLATION (SEG 0)

       **VA  4: 0x0000003f (decimal:   63):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(63) dez = (0111111) bin  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Addressraumgröße) = log_2(128) = 7  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;=> Top-Bit = 0  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Offset von VA = 63  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;63 > 20 --> SEGMENTATION VIOLATION

    *  `$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2`:

       Der Programmaufruf `$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2`
       liefert folgende Ausgabe:

       ```
       $ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2

       ARG seed 2
       ARG address space size 128
       ARG phys mem size 512

       Segment register information:

         Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
         Segment 0 limit                  : 20

         Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
         Segment 1 limit                  : 20

       Virtual Address Trace
         VA  0: 0x0000007a (decimal:  122) --> PA or segmentation violation?
         VA  1: 0x00000079 (decimal:  121) --> PA or segmentation violation?
         VA  2: 0x00000007 (decimal:    7) --> PA or segmentation violation?
         VA  3: 0x0000000a (decimal:   10) --> PA or segmentation violation?
         VA  4: 0x0000006a (decimal:  106) --> PA or segmentation violation?

       For each virtual address, either write down the physical address it translates to
       OR write down that it is an out-of-bounds address (a segmentation violation). For
       this problem, you should assume a simple address space with two segments: the top
       bit of the virtual address can thus be used to check whether the virtual address
       is in segment 0 (topbit=0) or segment 1 (topbit=1). Note that the base/limit pairs
       given to you grow in different directions, depending on the segment, i.e., segment 0
       grows in the positive direction, whereas segment 1 in the negative.
       ```
       virtuelle Adressraumgröße = 128  
       physikalische Speichergröße = 512

       SEG 0 Basis = 0  
       SEG 0 Limit = 20

       SEG 1 Basis = 512  
       SEG 1 Limit = 20

       **VA  0: 0x0000007a (decimal:  122):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(122) dez = (1111010) bin  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Adressraumgröße) = log_2(128) = 7  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;=> Top-Bit = 1  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Offset von VA = (111010) bin = (58) dez  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;effektiver Offset = 2^(#Bits für Offset) - Offset von VA = 2^6 - 58 = 64 - 58 = 6  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;6 < 20 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis - effektiver Offset = 512 - 6 = 506

       **VA  1: 0x00000079 (decimal:  121):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(121) dez = (1111001) bin  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Addressraumgr) = log_2(128) = 7  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;=> Top-Bit = 1  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Offset von VA = (111001) bin = (57) dez  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;effektiver Offset = 2^(#Bits für Offset) - Offset von VA = 2^6 - 57 = 64 - 57 = 7  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7 < 20 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis - effektiver Offset = 512 - 7 = 505

       **VA  2: 0x00000007 (decimal:    7):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(7) dez = (111) bin  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Addressraumgröße) = log_2(128) = 7  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;=> Top-Bit = 0  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Offset von VA = 7   
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7 < 20 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + Offset von VA = 0 + 7 = 7

       **VA  3: 0x0000000a (decimal:   10):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(10) dez = (1010) bin  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Addressraumgröße) = log_2(128) = 7  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;=> Top-Bit = 0  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Offset von VA = 10
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10 < 20 --> VALID  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PA = Basis + Offset von VA = 0 + 10 = 10

       **VA  4: 0x0000006a (decimal:  106):**

       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(106) dez = (1101010) bin  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;log_2(virtuelle Addressraumgröße) = log_2(128) = 7  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;=> Top-Bit = 1  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Offset von VA = (101010) bin = (42) dez  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;effektiver Offset = 2^(#Bits für Offset) - Offset von VA = 2^6 - 42 = 64 - 42 = 22  
       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;22 > 20 --> SEGMENTATION VIOLATION (SEG 1)


2.  virtuelle Addressraumgröße = 128  
    physikalische Speichergröße = 512

    SEG 0 Basis = 0  
    SEG 0 Limit = 20  

    SEG 1 Basis = 512  
    SEG 1 Limit = 20

    Die kleinste gültige virtuelle Adresse bestimmt sich wie folgt:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;min valid VA in SEG 0 = Basis SEG 0 + Limit - 1 = 0 + 20 - 1 = 19

    Die größte gültige virtuelle Addresse bestimmt sich wie folgt:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;max valid VA in SEG 1 = virtuelle Adressraumgröße - Limit = 108

    Dir kleinste ungültige VA im gesamten Adressraum bestimmt sich folgendermaßen:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;min illegal VA in SEG 0 = min valid VA in SEG 0 + 1 = 19 + 1 = 20

    Die größte ungültige VA im gesamten Adressraum bestimmt sich folgendermaßen:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;min illegal VA in SEG 1 = max valid VA in SEG 1 - 1 = 108 - 1 = 107

    Zur Überprüfung:

    ```
    * kleinste gültige VA:

      $ ./segmentation.py -A 19 -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -c
      ARG seed 0
      ARG address space size 128
      ARG phys mem size 512

      Segment register information:

        Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
        Segment 0 limit                  : 20

        Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
        Segment 1 limit                  : 20

      Virtual Address Trace
        VA  0: 0x00000013 (decimal:   19) --> VALID in SEG0: 0x00000013 (decimal:   19)


    * kleinste ungültige VA:

      $ ./segmentation.py -A 20 -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -c

      ARG seed 0
      ARG address space size 128
      ARG phys mem size 512

      Segment register information:

        Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
        Segment 0 limit                  : 20

        Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
        Segment 1 limit                  : 20

      Virtual Address Trace
        VA  0: 0x00000014 (decimal:   20) --> SEGMENTATION VIOLATION (SEG0)


    * größte gültige VA:

      $ ./segmentation.py -A 108 -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -c

      ARG seed 0
      ARG address space size 128
      ARG phys mem size 512

      Segment register information:

        Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
        Segment 0 limit                  : 20

        Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
        Segment 1 limit                  : 20

      Virtual Address Trace
        VA  0: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal:  492)


    * größte ungültige VA:

      $ ./segmentation.py -A 107 -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -c

      ARG seed 0
      ARG address space size 128
      ARG phys mem size 512

      Segment register information:

        Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
        Segment 0 limit                  : 20

        Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
        Segment 1 limit                  : 20

      Virtual Address Trace
        VA  0: 0x0000006b (decimal:  107) --> SEGMENTATION VIOLATION (SEG1)
    ```

3.  Für die Basisregister kann ein beliebiger Wert eingesetzt werden, solange
    sich die beiden Segmente nicht überlappen (Bsp.: `--b0 0 --l0 2 --b1 3 --l1 2`).

    Die Limitregister werden beide auf 2 gesetzt, da in den einzelnen Segmenten
    jeweils 2 Adressen gültig sein sollen.

    Beispiel:

    ```
    $ ./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 0 --l0 2 --b1 4 --l1 2 -c

    ARG seed 0
    ARG address space size 16
    ARG phys mem size 128

    Segment register information:

      Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
      Segment 0 limit                  : 2

      Segment 1 base  (grows negative) : 0x00000004 (decimal 4)
      Segment 1 limit                  : 2

    Virtual Address Trace
      VA  0: 0x00000000 (decimal:    0) --> VALID in SEG0: 0x00000000 (decimal:    0)
      VA  1: 0x00000001 (decimal:    1) --> VALID in SEG0: 0x00000001 (decimal:    1)
      VA  2: 0x00000002 (decimal:    2) --> SEGMENTATION VIOLATION (SEG0)
      VA  3: 0x00000003 (decimal:    3) --> SEGMENTATION VIOLATION (SEG0)
      VA  4: 0x00000004 (decimal:    4) --> SEGMENTATION VIOLATION (SEG0)
      VA  5: 0x00000005 (decimal:    5) --> SEGMENTATION VIOLATION (SEG0)
      VA  6: 0x00000006 (decimal:    6) --> SEGMENTATION VIOLATION (SEG0)
      VA  7: 0x00000007 (decimal:    7) --> SEGMENTATION VIOLATION (SEG0)
      VA  8: 0x00000008 (decimal:    8) --> SEGMENTATION VIOLATION (SEG1)
      VA  9: 0x00000009 (decimal:    9) --> SEGMENTATION VIOLATION (SEG1)
      VA 10: 0x0000000a (decimal:   10) --> SEGMENTATION VIOLATION (SEG1)
      VA 11: 0x0000000b (decimal:   11) --> SEGMENTATION VIOLATION (SEG1)
      VA 12: 0x0000000c (decimal:   12) --> SEGMENTATION VIOLATION (SEG1)
      VA 13: 0x0000000d (decimal:   13) --> SEGMENTATION VIOLATION (SEG1)
      VA 14: 0x0000000e (decimal:   14) --> VALID in SEG1: 0x00000002 (decimal:    2)
      VA 15: 0x0000000f (decimal:   15) --> VALID in SEG1: 0x00000003 (decimal:    3)
    ```

4.  Damit ungefähr 90% der zufällig generierten VAs gültig sind, müssen die Limitregister
    von SEG 0 und SEG 1 so gewählt werden, dass 90% der VAs im gesamten
    Adressraum auf gültige PAs verweißen.

    Für den Programmaufruf `./segmentation.py -s 0 -a 32 -p 128` würden sich die
    beiden Limits folgendermaßen bestimmen:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;gesamte virtuelle Addressraumgröße = 32b  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;32b * 0.9 = 28.8 ≈ 29

    Da nun 14b auf zwei Segmente aufgeteilt werden, kann man die Limits zum
    Beispiel folgendermaßen wählen:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`--l0 13 --l1 16`

    ```
    $ ./segmentation.py -s 0 -n 10 -a 32 -p 128 --l0 13 --l1 16 -c

    ARG seed 0
    ARG address space size 32
    ARG phys mem size 128

    Segment register information:

      Segment 0 base  (grows positive) : 0x0000006c (decimal 108)
      Segment 0 limit                  : 13

      Segment 1 base  (grows negative) : 0x00000045 (decimal 69)
      Segment 1 limit                  : 16

    Virtual Address Trace
      VA  0: 0x00000008 (decimal:    8) --> VALID in SEG0: 0x00000074 (decimal:  116)
      VA  1: 0x00000010 (decimal:   16) --> VALID in SEG1: 0x00000035 (decimal:   53)
      VA  2: 0x0000000c (decimal:   12) --> VALID in SEG0: 0x00000078 (decimal:  120)
      VA  3: 0x00000019 (decimal:   25) --> VALID in SEG1: 0x0000003e (decimal:   62)
      VA  4: 0x00000009 (decimal:    9) --> VALID in SEG0: 0x00000075 (decimal:  117)
      VA  5: 0x0000000f (decimal:   15) --> SEGMENTATION VIOLATION (SEG0)
      VA  6: 0x00000012 (decimal:   18) --> VALID in SEG1: 0x00000037 (decimal:   55)
      VA  7: 0x0000001d (decimal:   29) --> VALID in SEG1: 0x00000042 (decimal:   66)
      VA  8: 0x00000010 (decimal:   16) --> VALID in SEG1: 0x00000035 (decimal:   53)
      VA  9: 0x00000009 (decimal:    9) --> VALID in SEG0: 0x00000075 (decimal:  117)
    ```

    Damit sind nun bei einer Stichprobe von 10 VAs, 9 von 10 VAs gültig.
    Das sind (9 / 10) * 100 = 90%.

5.  Damit alle VAs ungültig sind, muss man einfach beide Limitregister auf 0
    setzen:

    ```
    $ ./segmentation.py -s0 -a 128 -p 1k --b0 0 --l0 0 --b1 1023 --l1 0 -c

    ARG seed 0
    ARG address space size 128
    ARG phys mem size 1k

    Segment register information:

      Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
      Segment 0 limit                  : 0

      Segment 1 base  (grows negative) : 0x000003ff (decimal 1023)
      Segment 1 limit                  : 0

    Virtual Address Trace
      VA  0: 0x0000006c (decimal:  108) --> SEGMENTATION VIOLATION (SEG1)
      VA  1: 0x00000061 (decimal:   97) --> SEGMENTATION VIOLATION (SEG1)
      VA  2: 0x00000035 (decimal:   53) --> SEGMENTATION VIOLATION (SEG0)
      VA  3: 0x00000021 (decimal:   33) --> SEGMENTATION VIOLATION (SEG0)
      VA  4: 0x00000041 (decimal:   65) --> SEGMENTATION VIOLATION (SEG1)
    ```
