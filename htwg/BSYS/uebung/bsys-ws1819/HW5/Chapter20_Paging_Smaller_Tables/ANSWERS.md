# Answers

1.  ###### With a linear page table, you need a single register to locate the page table, assuming that hardware does the lookup upon a TLB miss. How many registers do you need to locate a two-level page table? A three-level table?

    Für zwei Level werden `1 + N` viele Register benötigt, da ein Register die
    Adresse des Root Directorys enthält, und für jeden Eintrag (`N` viele) ein
    weiteres Register benötigt wird. Für 3 Level wären es dann `1 + N * M`
    (`N` Second Level Einträge, `M` Third Level Einträge) viele Register.

2.  ###### Use the simulator to perform translations given random seeds 0, 1, and 2, and check your answers using the -c flag. How many memory references are needed to perform each lookup?

    **Vorgehensweise:**

    1.  `VA` (Virtual Address) in Binärrepresentation umwandeln.
    2.  `VPN` (Virtual Page Number) sowie `Offset` bestimmen.
    3.  Von der `VPN` die `PDI` (Page Directory Index) sowie `PTI`
        (Page Table Index) bestimmen.
    4.  Mittels des PDBR (Page Directory Base Register) ermitteln, in welcher
        Page der benötigte Verweiß auf eine andere Page steht. In dieser Page
        interessiert uns der Inhalt an der Stelle `PDI`.
    5.  `PDE` (Page Directory Entry) bestimmen.
    6.  Ermitteln ob `PDE` valide ist, falls ja die `PTN` (Page Table Number)
        bestimmen.
    7.  Die Page in der Pagetable an der Stelle `PTN` begutachten und den Inhalt
        der Page an der Stelle `PTI` bestimmen.
    8.  `PFN` (Page Frame Number) bestimmen.
    9.  Ermitteln ob `PFN` valide ist, falls ja die `PFN` (Page Frame Number)
        bestimmen.
    10.  `VALUE` bestimmen. Dafür in die Page in der Pagetable an der Stelle `PFN`
         schauen und den Inhalt an der Stelle `Offset` ermitteln.
    11.  `PA` (Physical Address) bestimmen. Hierfür einfach `PFN` und `Offset` in
         der Binärrepresentation konkatenieren.

    *  Beispiel `./paging-multilevel-translate.py -s 0`:

       **Bsp. für valide VA 0x611c:**

       ```
       #Bits VA:     15
       #Bits VPN:    10
       #Bits Offset: 5

       PDBR:         108


       VA = (611c)_hex = (110 0001 0001 1100)_bin
                          |__________||____|    
                                |       |
                               VPN     Offset = 4 + 8 + 16 = 28

       VPN = (11 0000 1000)_bin
              |____||____|
                |      |
               PDI    PTI = 8
                =
            8 + 16 = 24

       page 108[24] = 0xa1

       --> PDE = (a1)_hex = (1010 0001)_bin
                             ^|______|
                         VALID    |
                                 PTN = 32 + 1 = 33

       page 33[8] = 0xb5

       --> PTE = (b5)_hex = (1011 0101)_bin
                             ^|______|
                         VALID    |
                                 PFN = 1 + 4 + 16 + 32 = 53

       page 53:[28] = 0x08 = VALUE

       PFN = (53)_dez = (11 0101)_bin
       Offset = (28)_dez = (1 1100)

       PA = PFN Offset = (110 1011 1100)_bin = (6bc)
       ```

       **Bsp. für invalide VA 0x3da8:**

       ```
       #Bits VA:     15
       #Bits VPN:    10
       #Bits Offset: 5

       PDBR:         108


       VA = (3da8)_hex = (011 1101 1010 1000)_bin
                          |__________||____|
                               |         |
                              VPN      Offset = 8

       VPN = (01 1110 1101)
              |____||____|
                |      |
               PDI    PTI = 1 + 4 + 8 = 13
                =
        1 + 2 + 4 + 8 = 15

       page 108[15] = 0xd6

       --> PDE = (d6)_hex = (1101 0110)_bin
                             ^|______|
                         VALID    |
                                 PTN = 2 + 4 + 16 + 64 = 86

       page 86[13] = 0x7f

       --> PTE = (7f)_hex = (0111 1111)_bin
                             ^
                          NOT VALID

       --> Fault (page table entry not valid)
       ```

    *  `./paging-multilevel-translate.py -s 0 -n 5 -c`

       ```
       $ ./paging-multilevel-translate.py -s 0 -n 5 -c
       ARG seed 0
       ARG allocated 64
       ARG num 5
       [...]
       PDBR: 108  (decimal) [This means the page directory is held in this page]

       Virtual Address 611c:
         --> pde index:0x18 [decimal 24] pde contents:0xa1 (valid 1, pfn 0x21 [decimal 33])
             --> pte index:0x8 [decimal 8] pte contents:0xb5 (valid 1, pfn 0x35 [decimal 53])
                 --> Translates to Physical Address 0x6bc --> Value: 08
       Virtual Address 3da8:
         --> pde index:0xf [decimal 15] pde contents:0xd6 (valid 1, pfn 0x56 [decimal 86])
             --> pte index:0xd [decimal 13] pte contents:0x7f (valid 0, pfn 0x7f [decimal 127])
                 --> Fault (page table entry not valid)
       Virtual Address 17f5:
         --> pde index:0x5 [decimal 5] pde contents:0xd4 (valid 1, pfn 0x54 [decimal 84])
             --> pte index:0x1f [decimal 31] pte contents:0xce (valid 1, pfn 0x4e [decimal 78])
                 --> Translates to Physical Address 0x9d5 --> Value: 1c
       Virtual Address 7f6c:
         --> pde index:0x1f [decimal 31] pde contents:0xff (valid 1, pfn 0x7f [decimal 127])
             --> pte index:0x1b [decimal 27] pte contents:0x7f (valid 0, pfn 0x7f [decimal 127])
                 --> Fault (page table entry not valid)
       Virtual Address 0bad:
         --> pde index:0x2 [decimal 2] pde contents:0xe0 (valid 1, pfn 0x60 [decimal 96])
             --> pte index:0x1d [decimal 29] pte contents:0x7f (valid 0, pfn 0x7f [decimal 127])
                 --> Fault (page table entry not valid)
       ```
    *  `./paging-multilevel-translate.py -s 1 -n 5 -c`:

       ```
       $ ./paging-multilevel-translate.py -s 1 -n 5 -c
       ARG seed 1
       ARG allocated 64
       ARG num 5
       [...]
       PDBR: 17  (decimal) [This means the page directory is held in this page]

       Virtual Address 6c74:
          --> pde index:0x1b [decimal 27] pde contents:0xa0 (valid 1, pfn 0x20 [decimal 32])
              --> pte index:0x3 [decimal 3] pte contents:0xe1 (valid 1, pfn 0x61 [decimal 97])
                  --> Translates to Physical Address 0xc34 --> Value: 06
       Virtual Address 6b22:
        --> pde index:0x1a [decimal 26] pde contents:0xd2 (valid 1, pfn 0x52 [decimal 82])
            --> pte index:0x19 [decimal 25] pte contents:0xc7 (valid 1, pfn 0x47 [decimal 71])
                --> Translates to Physical Address 0x8e2 --> Value: 1a
       Virtual Address 03df:
        --> pde index:0x0 [decimal 0] pde contents:0xda (valid 1, pfn 0x5a [decimal 90])
            --> pte index:0x1e [decimal 30] pte contents:0x85 (valid 1, pfn 0x05 [decimal 5])
                --> Translates to Physical Address 0x0bf --> Value: 0f
       Virtual Address 69dc:
        --> pde index:0x1a [decimal 26] pde contents:0xd2 (valid 1, pfn 0x52 [decimal 82])
          --> pte index:0xe [decimal 14] pte contents:0x7f (valid 0, pfn 0x7f [decimal 127])
              --> Fault (page table entry not valid)
       Virtual Address 317a:
        --> pde index:0xc [decimal 12] pde contents:0x98 (valid 1, pfn 0x18 [decimal 24])
            --> pte index:0xb [decimal 11] pte contents:0xb5 (valid 1, pfn 0x35 [decimal 53])
                --> Translates to Physical Address 0x6ba --> Value: 1e
       ```

    * `./paging-multilevel-translate.py -s 2 -n 5 -c`:

       ```
       $ ./paging-multilevel-translate.py -s 2 -n 5 -c
       ARG seed 2
       ARG allocated 64
       ARG num 5
       [...]
       PDBR: 122  (decimal) [This means the page directory is held in this page]

       Virtual Address 7570:
        --> pde index:0x1d [decimal 29] pde contents:0xb3 (valid 1, pfn 0x33 [decimal 51])
            --> pte index:0xb [decimal 11] pte contents:0x7f (valid 0, pfn 0x7f [decimal 127])
                --> Fault (page table entry not valid)
       Virtual Address 7268:
        --> pde index:0x1c [decimal 28] pde contents:0xde (valid 1, pfn 0x5e [decimal 94])
            --> pte index:0x13 [decimal 19] pte contents:0xe5 (valid 1, pfn 0x65 [decimal 101])
                --> Translates to Physical Address 0xca8 --> Value: 16
       Virtual Address 1f9f:
        --> pde index:0x7 [decimal 7] pde contents:0xaf (valid 1, pfn 0x2f [decimal 47])
            --> pte index:0x1c [decimal 28] pte contents:0x7f (valid 0, pfn 0x7f [decimal 127])
                --> Fault (page table entry not valid)
       Virtual Address 0325:
        --> pde index:0x0 [decimal 0] pde contents:0x82 (valid 1, pfn 0x02 [decimal 2])
            --> pte index:0x19 [decimal 25] pte contents:0xdd (valid 1, pfn 0x5d [decimal 93])
                --> Translates to Physical Address 0xba5 --> Value: 0b
       Virtual Address 64c4:
        --> pde index:0x19 [decimal 25] pde contents:0xb8 (valid 1, pfn 0x38 [decimal 56])
            --> pte index:0x6 [decimal 6] pte contents:0x7f (valid 0, pfn 0x7f [decimal 127])
                --> Fault (page table entry not valid)
       ```

    Es werden maximal **2** Speicherreferenzen benötigt um eine `VA` in eine
    `PA` umzuwandeln. Falls eine Referenz auf den Inhalt einer Page invalide ist,
    werden weniger Speicherreferenzen benötigt, da das Verfahren dann abgebrochen
    werden kann. Die Speicherreferenz beim 3. Durchgang wird nicht zur
    Adressübersetzung benötigt, sondern stellt das gesuchte Ergebnis dar.

3.  ###### Given your understanding of how cache memory works, how do you think memory references to the page table will behave in the cache? Will they lead to lots of cache hits (and thus fast accesses?) or lots of misses (and thus slow accesses)?

    Es kommt ganz auf die räumliche und tempörare Lokalität der erzeugten `VAs`
    an sowie auf die eingesetzte Replacement Policy. Da die Adressen zufällig
    erzeugt werden, kann es bei gewissen `seeds` vorkommen, das eine gewisse
    Lokalität existiert, jedoch wird dies nur sehr unwahrscheinlich einem Trace
    eines echten Programms entsprechen.

    Liegt so gut wie keine Lokalität vor, treten viele Cache-Misses auf
    (langsamer Zugriff).

    Anderenfalls treten weniger Misses auf, was jedoch wieder von der
    eingesetzten Replacement Policy abhängt (schneller Zugriff).
