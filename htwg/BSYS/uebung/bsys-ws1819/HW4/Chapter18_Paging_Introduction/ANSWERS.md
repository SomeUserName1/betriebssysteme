# Answers

1.  Um zu bestimmen, wie sich die Größe der Seitentabelle ändert, wenn man
    **nur** die Adressraumgröße (`-a`-Flag) vergrößert, geht man folgendermaßen
    vor:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`linearPageTableSize = addressSpaceSize / pageSize`

    ---

    *  `paging-linear-translate.py -P 1k -a 1m -p 512m -v -n 0`:

       `linearPageTableSize = addressSpaceSize / pageSize = (1 * 1024 * 1024) / (1 * 1024) = 1024`

    *  `paging-linear-translate.py -P 1k -a 2m -p 512m -v -n 0`:

       `linearPageTableSize = addressSpaceSize / pageSize = (2 * 1024 * 1024) / (1 * 1024) = 2048`

    *  `paging-linear-translate.py -P 1k -a 4m -p 512m -v -n 0`:

       `linearPageTableSize = addressSpaceSize / pageSize = (4 * 1024 * 1024) / (1 * 1024) = 4096`

    Verdoppelt man die Adressraumgröße, verdoppelt sich auch die Größe der
    Seitentabelle.

    --> Die Seitentabelle vergrößert sich, wenn die Adressraumgröße wächst, da
    man nun mehr Seiten in der Seitentabelle
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;benötigt um den kompletten Adressraum
    abzudecken.

    ---

    Um herauszufinden, wie sich die Größe der Seitentabelle ändert, wenn man
    **nur** die Seitengröße (`-P`-Flag) vergrößert, geht man folgendermaßen vor:

    ---

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`linearPageTableSize = addressSpaceSize / pageSize`

    *  `paging-linear-translate.py -P 1k -a 1m -p 512m -v -n 0`:

       `linearPageTableSize = addressSpaceSize / pageSize = (1 * 1024 * 1024) / (1 * 1024) = 1024`

    *  `paging-linear-translate.py -P 2k -a 1m -p 512m -v -n 0`:

       `linearPageTableSize = addressSpaceSize / pageSize = (1 * 1024 * 1024) / (2 * 1024) = 512`

    *  `paging-linear-translate.py -P 4k -a 1m -p 512m -v -n 0`:

       `linearPageTableSize = addressSpaceSize / pageSize = (1 * 1024 *1024) / (4 * 1024) = 256`

    Verdoppelt man die Seitengröße, halbiert sich die Größe der Seitentabelle.

    --> Die Seitentabelle verkleinert sich, wenn die Seitengröße wächst, da man
    nun weniger Seiten braucht, um den  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;gesamten Adressraum abzudecken.

    ---

    --> Man sollte keine sehr großen Werte für die Seitengröße verwenden, da für
    kleine Speicheranfragen sehr viel Platz in  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;einer Seite verschwendet werden würde.

    ---

    **Beispiel für die Adressumsetzung:**

    Der Programmaufruf `./paging-linear-translate.py -P 1k -a 8k -p 16k -v -n 4`
    liefert folgende Ausgabe:

    ```
    $ ./paging-linear-translate.py -P 1k -a 8k -p 16k -v -n 4
    ARG seed 0
    ARG address space size 8k
    ARG phys mem size 16k
    ARG page size 1k
    ARG verbose True
    ARG addresses -1


    The format of the page table is simple:
    The high-order (left-most) bit is the VALID bit.
    If the bit is 1, the rest of the entry is the PFN.
    If the bit is 0, the page is not valid.
    Use verbose mode (-v) if you want to print the VPN # by
    each entry of the page table.

    Page Table (from entry 0 down to the max size)
      [       0]   0x8000000c
      [       1]   0x00000000
      [       2]   0x00000000
      [       3]   0x80000006
      [       4]   0x80000004
      [       5]   0x00000000
      [       6]   0x8000000e
      [       7]   0x80000009

    Virtual Address Trace
      VA 0x00000804 (decimal:     2052) --> PA or invalid address?
      VA 0x00001d1c (decimal:     7452) --> PA or invalid address?
      VA 0x00001f72 (decimal:     8050) --> PA or invalid address?
      VA 0x000019ed (decimal:     6637) --> PA or invalid address?

    For each virtual address, write down the physical address it translates to
    OR write down that it is an out-of-bounds address (e.g., segfault).
    ```

    Vorgehensweiße:

    1.  Anzahl an Bits für VA bestimmen (VPN + Offset):

        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`Gesamt #Bits = log_2(addressSpaceSize)`

    2.  Größe der Seitentabelle bestimmen:

        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`linearPageTableSize = addressSpaceSize / pageSize`

    3.  Anzahl an Bits für VPN von VA bestimmen:

        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`#Bits VPN = log_2(linearPageTableSize)`

    4.  VA in Binärrepräsentation umwandeln und VPN sowie Offset bestimmen.

    5.  In der Seitentabelle an der Stelle VPN die dazugehörige PFN bestimmen.

    6.  Überprüfen ob PFN gültig ist.

    7.  Falls PFN gültig, bestimme PA:

        Um die PA zu bestimmen, rechnen wir die PFN in die Binärrepräsentation
        um und ersetzten die VPN durch diese.

        Letztendlich müssen wir die erhaltene Binärzahl nur noch ins
        Dezimalsystem (bzw. Hexadezimalsystem) umrechnen und haben somit die
        PA bestimmt.

    **Lösung:**

    ```
    Page Table (from entry 0 down to the max size)
      [       0]   0x8000000c
      [       1]   0x00000000
      [       2]   0x00000000
      [       3]   0x80000006
      [       4]   0x80000004
      [       5]   0x00000000
      [       6]   0x8000000e
      [       7]   0x80000009

    Virtual Address Trace
    VA 0x00000804 (decimal:     2052) --> PA or invalid address?
    VA 0x00001d1c (decimal:     7452) --> PA or invalid address?
    VA 0x00001f72 (decimal:     8050) --> PA or invalid address?
    VA 0x000019ed (decimal:     6637) --> PA or invalid address?
    ```
    ---
    ```
    addressSpaceSize = 8k  
    physicalMemorySize = 16K  
    pageSize = 1k

    Gesamtanzahl Bits = log_2(addressSpaceSize) = log_2(8 * 1024) = 13
    linearPageTableSize = addressSpaceSize / pageSize = 8 * 1024 / (1 * 1024) = 8
    #Bits VPN = log_2(linearPageTableSize) = log_2(8) = 3
    ```

    *  `VA 0x00000804 (decimal:     2052)`:

       ```
       VA = (804)_hex = (0 1000 0000 0100)_bin = (2052)_dez
                         ^ ^^|__________|  
                         VPN      |
                         = 2    Offset

       linearPageTable[2] = (00000000)_hex
                             ^
                         NOT VALID

       VA 0x00000804 (decimal:     2052) --> Invalid (VPN 2 not valid)
       ```
    *  `VA 0x00001d1c (decimal:     7452)`:

       ```
       VA = (1d1c)_hex = (1 1101 0001 1100)_bin = (2052)_dez
                          ^ ^^|__________|
                          VPN      |
                          = 7    Offset

       linearPageTable[7] = (80000009)_hex
                             ^
                           VALID

       PFN = (9)_hex = (1001)_bin

       PA = (10 0101 0001 1100)_bin = (251c)_hex = (9500)_dez

       VA 0x00001d1c (decimal:     7452) --> 0000251c (decimal     9500) [VPN 7]
       ```

    *  `VA 0x00001f72 (decimal:     8050)`:

       ```
       VA = (1f72)_hex = (1 1111 0111 0010)_bin
                          ^ ^^|__________|
                          VPN      |
                          = 7    Offset

       linearPageTable[7] = (80000009)_hex
                             ^
                           VALID

       PFN = (9)_hex = (1001)_bin

       PA = (10 0111 0111 0010)_bin = (2772)_hex = (10098)_dez

       VA 0x00001f72 (decimal:     8050) --> 00002772 (decimal    10098) [VPN 7]
       ```

    *  `VA 0x000019ed (decimal:     6637) --> PA or invalid address?`:

       ```
       VA = (19ed)_hex = (1 1001 1110 1101)_bin
                          ^ ^^|__________|
                          VPN      |
                          = 6    Offset

       linearPageTable[6] = (8000000e)_hex
                             ^
                             VALID

       PFN = (e)_hex = (1110)_bin

       PA = (11 1001 1110 1101)_bin = (39ed)_hex = (14829)_dez

       VA 0x000019ed (decimal:     6637) --> 000039ed (decimal    14829) [VPN 6]
       ```

2.  *  `./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 0`:

       Da der prozentuale Anteil der verwendeten Addressraumgröße auf 0 gesetzt
       wurde (`-u 0`), sind alle Einträge in der Seitentabelle ungültig. Daher
       verweißen keine VAs auf gültige PAs und sind somit üngültig.

       Die Ausgabe des Programms mit zusätzlichem `-c`-Flag liefert:

       ```
       $ ./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 0 -c

       [...]

       Page Table (from entry 0 down to the max size)
         [       0]   0x00000000
         [       1]   0x00000000

         [...]

         [      15]   0x00000000

       Virtual Address Trace
         VA 0x00003a39 (decimal:    14905) -->  Invalid (VPN 14 not valid)
         VA 0x00003ee5 (decimal:    16101) -->  Invalid (VPN 15 not valid)
         VA 0x000033da (decimal:    13274) -->  Invalid (VPN 12 not valid)
         VA 0x000039bd (decimal:    14781) -->  Invalid (VPN 14 not valid)
         VA 0x000013d9 (decimal:     5081) -->  Invalid (VPN 4 not valid)
       ```

    ---

    *  `./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 25`:

       Der prozentuale Anteil der verwendeten Addressraumgröße beträgt hier 25%.
       Dadurch sind ungefähr 25% der Seiten in der Seitentabelle als gültig
       markiert. Hiermit verweißen auch ungefähr 25% der VAs auf gültige PAs.

       **Seitentabelle:**

       ```
       [       0]   0x80000018
       [       1]   0x00000000
       [       2]   0x00000000
       [       3]   0x00000000
       [       4]   0x00000000
       [       5]   0x80000009
       [       6]   0x00000000
       [       7]   0x00000000
       [       8]   0x80000010
       [       9]   0x00000000
       [      10]   0x80000013
       [      11]   0x00000000
       [      12]   0x8000001f
       [      13]   0x8000001c
       [      14]   0x00000000
       [      15]   0x00000000
       ```

       **Zu berechnende VAs:**
       ```
       VA 0x00003986 (decimal:    14726) --> PA or invalid address?
       VA 0x00002bc6 (decimal:    11206) --> PA or invalid address?
       VA 0x00001e37 (decimal:     7735) --> PA or invalid address?
       VA 0x00000671 (decimal:     1649) --> PA or invalid address?
       VA 0x00001bc9 (decimal:     7113) --> PA or invalid address?
       ```

       **Lösung:**

       ```
       addressSpaceSize = 16k
       pageSize = 1k
       physicalMemorySize = 32k

       Gesamt #Bits = log_2(addressSpaceSize) = log_2(16 * 1024) = 14
       linearPageTableSize = addressSpaceSize / pageSize = (16 * 1024) / (1 * 1024) = 16
       #Bits VPN = log_2(linearPageTableSize) = log_2(16) = 4
       ```

       *  `VA 0x00003986 (decimal:    14726)`:

          ```
          VA = (3986)_hex = (11 1001 1000 0110)_bin = (14726)_dez
                             ^^ ^^|__________|
                             VPN       |
                             =14     Offset

          linearPageTable[14] = 00000000
                                ^
                              NOT VALID

          VA 0x00003986 (decimal:    14726) -->  Invalid (VPN 14 not valid)
          ```

       *  `VA 0x00002bc6 (decimal:    11206)`:

          ```
          VA = (2bc6)_hex = (10 1011 1100 0110)_bin = (11206)_dez
                             ^^ ^^|__________|
                             VPN       |
                             =10     Offset

          linearPageTable[10] = (80000013)_hex
                                 ^
                               VALID

          PFN = (13)_hex = (0001 0011)_bin

          PA = (100 1111 1100 0110)_bin = (4fc6)_hex = (20422)_dez
          ```

       *  `VA 0x00001e37 (decimal:     7735)`:

          ```
          VA = (1e37)_hex = (01 1110 0011 0111)_bin = (7735)_dez
                             ^^ ^^|__________|
                             VPN       |
                             = 7     Offset

          linearPageTable[7] = (00000000)_hex
                                ^
                             NOT VALID

          VA 0x00001e37 (decimal:     7735) -->  Invalid (VPN 7 not valid)
          ```
       *  `VA 0x00000671 (decimal:     1649)`:

          ```
          VA = (671)_hex = (00 0110 0111 0001)_bin = (1649)_dez
                            ^^ ^^|__________|
                            VPN       |
                            = 1     Offset

          linearPageTable[1] = (00000000)_hex
                                ^
                             NOT VALID

          VA 0x00000671 (decimal:     1649) -->  Invalid (VPN 1 not valid)
          ```

       *  `VA 0x00001bc9 (decimal:     7113)`:

          ```
          VA = (1bc9)_hex = (01 1011 1100 1001)_bin = ()_dez
                             ^^ ^^|__________|
                             VPN       |
                             = 6     Offset

          linearPageTable[6] = (00000000)_hex
                                ^
                             NOT VALID
          ```

       Die Ausgabe des Programms mit zusätzlichem `-c`-Flag liefert:

       ```
       $ ./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 25 -c

       [...]

       Virtual Address Trace
         VA 0x00003986 (decimal:    14726) -->  Invalid (VPN 14 not valid)
         VA 0x00002bc6 (decimal:    11206) --> 00004fc6 (decimal    20422) [VPN 10]
         VA 0x00001e37 (decimal:     7735) -->  Invalid (VPN 7 not valid)
         VA 0x00000671 (decimal:     1649) -->  Invalid (VPN 1 not valid)
         VA 0x00001bc9 (decimal:     7113) -->  Invalid (VPN 6 not valid)
       ```

    ---

    * `paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 50`:

       Der prozentuale Anteil der verwendeten Addressraumgröße beträgt hier 25%.
       Dadurch sind ungefähr 50% der Seiten in der Seitentabelle als gültig
       markiert. Hiermit verweißen ebenfalls ungefähr 50% der VAs auf gültige PAs.

       **Lösung**

       Lösungsweg analog zu vorherigem Beispiel.

       Die Ausgabe des Programms mit zusätzlichem `-c`-Flag liefert:

       ```
       $ ./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 50 -c

       [...]

       Page Table (from entry 0 down to the max size)
         [       0]   0x80000018
         [       1]   0x00000000
         [       2]   0x00000000
         [       3]   0x8000000c
         [       4]   0x80000009
         [       5]   0x00000000
         [       6]   0x8000001d
         [       7]   0x80000013
         [       8]   0x00000000
         [       9]   0x8000001f
         [      10]   0x8000001c
         [      11]   0x00000000
         [      12]   0x8000000f
         [      13]   0x00000000
         [      14]   0x00000000
         [      15]   0x80000008

       Virtual Address Trace
         VA 0x00003385 (decimal:    13189) --> 00003f85 (decimal    16261) [VPN 12]
         VA 0x0000231d (decimal:     8989) -->  Invalid (VPN 8 not valid)
         VA 0x000000e6 (decimal:      230) --> 000060e6 (decimal    24806) [VPN 0]
         VA 0x00002e0f (decimal:    11791) -->  Invalid (VPN 11 not valid)
         VA 0x00001986 (decimal:     6534) --> 00007586 (decimal    30086) [VPN 6]
       ```

    ---

    *  `./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 75`:

       Der prozentuale Anteil der verwendeten Addressraumgröße beträgt hier 75%.
       Dadurch sind ungefähr 75% der Seiten in der Seitentabelle als gültig
       markiert. Hiermit verweißen ebenfalls ungefähr 75% der VAs auf gültige PAs.

       **Lösung**

       Lösungsweg analog zu vorherigem Beispiel.

       Die Ausgabe des Programms mit zusätzlichem `-c`-Flag liefert:

       ```
       $ ./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 75 -c     

       [...]

       Page Table (from entry 0 down to the max size)
         [       0]   0x80000018
         [       1]   0x80000008
         [       2]   0x8000000c
         [       3]   0x80000009
         [       4]   0x80000012
         [       5]   0x80000010
         [       6]   0x8000001f
         [       7]   0x8000001c
         [       8]   0x80000017
         [       9]   0x80000015
         [      10]   0x80000003
         [      11]   0x80000013
         [      12]   0x8000001e
         [      13]   0x8000001b
         [      14]   0x80000019
         [      15]   0x80000000

       Virtual Address Trace
         VA 0x00002e0f (decimal:    11791) --> 00004e0f (decimal    19983) [VPN 11]
         VA 0x00001986 (decimal:     6534) --> 00007d86 (decimal    32134) [VPN 6]
         VA 0x000034ca (decimal:    13514) --> 00006cca (decimal    27850) [VPN 13]
         VA 0x00002ac3 (decimal:    10947) --> 00000ec3 (decimal     3779) [VPN 10]
         VA 0x00000012 (decimal:       18) --> 00006012 (decimal    24594) [VPN 0]
       ```

    ---

    *  `./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 100`:

       Der prozentuale Anteil der verwendeten Addressraumgröße beträgt hier 75%.
       Dadurch sind 100% der Seiten in der Seitentabelle als gültig
       markiert. Hiermit verweißen ebenfalls 100% der VAs auf gültige PAs.

       **Lösung**

       Lösungsweg analog zu vorherigem Beispiel.

       Die Ausgabe des Programms mit zusätzlichem `-c`-Flag liefert:

       ```
       $ ./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 100 -c    

       [...]

       Page Table (from entry 0 down to the max size)
         [       0]   0x80000018
         [       1]   0x80000008
         [       2]   0x8000000c
         [       3]   0x80000009
         [       4]   0x80000012
         [       5]   0x80000010
         [       6]   0x8000001f
         [       7]   0x8000001c
         [       8]   0x80000017
         [       9]   0x80000015
         [      10]   0x80000003
         [      11]   0x80000013
         [      12]   0x8000001e
         [      13]   0x8000001b
         [      14]   0x80000019
         [      15]   0x80000000

       Virtual Address Trace
         VA 0x00002e0f (decimal:    11791) --> 00004e0f (decimal    19983) [VPN 11]
         VA 0x00001986 (decimal:     6534) --> 00007d86 (decimal    32134) [VPN 6]
         VA 0x000034ca (decimal:    13514) --> 00006cca (decimal    27850) [VPN 13]
         VA 0x00002ac3 (decimal:    10947) --> 00000ec3 (decimal     3779) [VPN 10]
         VA 0x00000012 (decimal:       18) --> 00006012 (decimal    24594) [VPN 0]
       ```

    ---

    **--> Erhöht man den prozentualen Anteil der verwedeten Adressraumgröße,
    erhöht sich dadurch die Anzahl an
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;validen Seiten in der Seitentabelle und
    somit auch die Anzahl an VAs die auf gültige PAs verweißen. Jedoch
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;nimmt hierduch die Anzahl an freien
    Speicherbereichen in der Seitentabelle ab.**

3.  *  `./paging-linear-translate.py -P 8 -a 32 -p 1024 -v -s 1`:

       Bei diesem Beispiel sind so gut wie alle Parameter unrealistisch, da die
       gewählten Werte sehr klein sind  
       (für `-P`, `-a` sowie `-p`). Dadurch wird auch die Seitentabelle sehr
       klein (hier: Größe 4), wodurch sehr viele VAs auf ungültige PAs verweißen.

       Ausgabe des Programms mit zusätzlichem `-c`-Flag:

       ```
       $ ./paging-linear-translate.py -P 8 -a 32 -p 1024 -v -s 1 -c

       [...]

       Page Table (from entry 0 down to the max size)
         [       0]   0x00000000
         [       1]   0x80000061
         [       2]   0x00000000
         [       3]   0x00000000

       Virtual Address Trace
         VA 0x0000000e (decimal:       14) --> 0000030e (decimal      782) [VPN 1]
         VA 0x00000014 (decimal:       20) -->  Invalid (VPN 2 not valid)
         VA 0x00000019 (decimal:       25) -->  Invalid (VPN 3 not valid)
         VA 0x00000003 (decimal:        3) -->  Invalid (VPN 0 not valid)
         VA 0x00000000 (decimal:        0) -->  Invalid (VPN 0 not valid)
       ```

    *  `./paging-linear-translate.py -P 8k -a 32k -p 1m -v -s 2`:

       Bei diesem Beispiel ist das Verhältnis von Adressraumgröße (`-a`-Flag)
       und Seitengröße (`-P`-Flag) sehr schlecht gewählt, da hierdurch die
       Seitentabelle wieder sehr klein wird (hier: Größe 4). Dadurch verweißen
       wieder sehr viele VAs auf ungültige PAs.

       Das Programm liefert mit zusätzlichem `-c`-Flag folgende Ausgabe:

       ```
       $ ./paging-linear-translate.py -P 8k -a 32k -p 1m -v -s 2 -c

       Page Table (from entry 0 down to the max size)
         [       0]   0x80000079
         [       1]   0x00000000
         [       2]   0x00000000
         [       3]   0x8000005e

       Virtual Address Trace
         VA 0x000055b9 (decimal:    21945) -->  Invalid (VPN 2 not valid)
         VA 0x00002771 (decimal:    10097) -->  Invalid (VPN 1 not valid)
         VA 0x00004d8f (decimal:    19855) -->  Invalid (VPN 2 not valid)
         VA 0x00004dab (decimal:    19883) -->  Invalid (VPN 2 not valid)
         VA 0x00004a64 (decimal:    19044) -->  Invalid (VPN 2 not valid)
       ```

    *  `./paging-linear-translate.py -P 1m -a 256m -p 512m -v -s 3`:

       Bei diesem Beispiel wurde eine sehr große Seitengröße (`-P`-Flag) gewählt,
       was zu sehr großer interner Fragmentierung führt, bei kleinen
       Speicheranfragen.

       Das Programm liefert mit zusätzlichem `-c`-Flag folgende Ausgabe:

       ```
       $ ./paging-linear-translate.py -P 1m -a 256m -p 512m -v -s 3 -c

       Page Table (from entry 0 down to the max size)
         [       0]   0x00000000
         [       1]   0x800000bd

         [...]

         [     254]   0x80000159
         [     255]   0x00000000

       Virtual Address Trace
         VA 0x0308b24d (decimal: 50901581) --> 1f68b24d (decimal 526955085) [VPN 48]
         VA 0x042351e6 (decimal: 69423590) -->  Invalid (VPN 66 not valid)
         VA 0x02feb67b (decimal: 50247291) --> 0a9eb67b (decimal 178173563) [VPN 47]
         VA 0x0b46977d (decimal: 189175677) -->  Invalid (VPN 180 not valid)
         VA 0x0dbcceb4 (decimal: 230477492) --> 1f2cceb4 (decimal 523030196) [VPN 219]
       ```

4.  Das Programm funktioniert nicht mehr, wenn:

    *  Die Addressraumgröße (`-a`-Flag) größer als die physikalische
       Speichergröße (`-p`-Flag) ist.

    *  Der Wert Addressraumgröße (`-a`-Flag) oder die Seitengröße (`-P`-Flag)
       keine Zweierpotenz ist.

    *  Die Seitengröße (`-P`-Flag) größer als die Addressraumgröße (`-a`-Flag)
       ist.

    *  Der Wert der Seitengröße (`-P`-Flag) kleiner gleich 0 ist.

    *  Der Wert der Addressraumgröße (`-a`-Flag) kleiner gleich 0 ist.

    *  Der Wert der physikalischen Speichergröße (`-p`-Flag) kleiner gleich 0 ist.
