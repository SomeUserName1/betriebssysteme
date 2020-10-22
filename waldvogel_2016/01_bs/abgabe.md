# **Übungsblatt 01**

## Gesamt: 13/20
## Verständnisfragen 6/6

1. Zählen sie die 4 wichtigsten Bestandteile eines Computersystems auf und beschreiben diese kurz.

  - Prozessor (Kontrolliert Operationen und Datenverarbeitung)
  - Hauptspeicher (Speichert Daten und Programme während dem Betrieb)
  - I/O (Daten zwischen Computer und externen Umgebungen (Festplatte, Bidschirm, etc) verschieben)
  - System Bus (Kommunikation zwischen den oben genannten Komponenten)

2. Was sind die 2 Hauptfunktionen eines Betriebssystems?

  - Ressourcen Management (Verwaltet Speicher, plant/optimiert die Befehlsausführung,...)
  - Erweiterung der Maschiene um die Programmierung zu Vereinfachen (z.B. Anbindung des Monitors und graphische Ausgabe).

3. Welche Register sind generell für Benutzer sichtbar und welche nicht?<br>
  Sichtbar sollten alle Register sein, auch wenn nur aus Debugging Gründen (macht ja kein Sinn etwas zu Entwickeln, dass ich zur Fehlerbehebung nicht ansteuern kann). Jedoch lassen sich Memory Address , - Data - und - Buffer Register sowie das Instruction Register nicht erreichen, da diese für den fetch Prozess und somit die Funktion des Systems kritisch relevant sind.

4. Was sind die zwei Stufen eines minimalen Instruktionszykluses?<br>
  Fetch: Lädt den Befehl vom Hauptspeicher zunächst ins Data Memory Register und von dort ins Instruction Register<br>
  Execute: Befehl wird ausgeführt (Arith., JMP, Vgl., ...)

5. Was ist ein Interrupt und wozu wird er benötigt? Was ist der Unterschied zu einer Trap?<br>
  Ein Interrupt ist eine verrübergehende Unterbrechung des laufenden Programms. Der Interrupt dient u.a. zur Kommunikation verschiedener HW-Komponenten mit der CPU. Interrupts werden bei Programm-externen Ereignissen ausgelöst (asynchron, unvorhersagbar, nicht reproduzierbar). Traps sind synchron zum Programm, vorhersehbar und reproduzierbar (z.B. 0 Division), sind also Programm-abhängig.

6. Welche Speichertypen gibt es und wodurch unterscheiden sie sich?

  - Register: klein, geringe Kapazität, sehr schnell, sehr teuer
  - Caches: klein, geringe Kapazität, sehr schnell, sehr teuer
  - RAM/Hauptspeicher: moderate Größe, mittlere Kapazität, schnell, erschwinglich
  - Flash-Speicher: klein, große Kapazität, etwas langsamer, billig (je nach Kapazität)
  - Hard Drive Disks: groß, große Kapazität, langsam, sehr billig
  - Tape: sehr groß, sehr große Kapazität. sehr langsam, erschwinglich

## Cache 3/3

Wenn die effektive Zugriffszeit 10% größer ist als die Cache-Zugriffszeit ist, wie hoch ist dann die Trefferquote H?<br>
T_{cache} = 5ns; T_{mem} = 60ns

T<sub>avg</sub> = 1.1 * T<sub>cache</sub> = 1.1 * 5ns = 5.5ns

T<sub>avg</sub> = H * T<sub>cache</sub> + (1-H)(T<sub>cache</sub> + T<sub>mem</sub>)

5.5ns = H * 5 ns + (1 - H) (5 ns + 60 ns)<br>
= H * 5ns + (1-H) * 65ns<br>
= H _5ns + 65ns - H_ 65ns<br>
= 65ns - H * 60ns

59.5ns = H * 60ns<br>
H = 59.5ns / 60ns = 99.17%

## Speicher und Addressbus 1/7

32 Bit Mikroprozessor mit 32 Bit Befehlen: 8 Bit OpCode, 24 Bit Operanden/Operandenaddresse.

1. Wie groß ist die maximal addressierbare Speicherkapazität in Byte?

  Die Adressen haben 32 - 8 = 24 bit zur Verfügung. Damit können maximal 2^24 Speicherstellen addressiert werden.<br>
  2^24 = 16.777.216 bytes.

2. Beschreiben sie die Auswirkung auf die Systemgeschwindigkeit, wenn der Mikroprozessorbus

  - einen lokalen Addressbus von 32 Bit und einen lokalen Datenbus von 16 Bit hat<br>
    Durch mehr adressierbaren Hauptspeicher kann z.T. das Auslagern und Wiedereinlagern von Daten vom Hauptspeicher zur Festplatte oder andersrum vermieden werden und so Rechenzeit gespart. Da für die Caches nur Tags generiert werden, die das geladene Blockweise adressieren ist die Adressbusbreite nicht relevant für die Hit Ratio. **Warum mehr adressierbarer Hauptspeicher? Und der kleinere Datenbus hat keine Auswirkung? 0/2**

  - einen lokalen Addressbus von 16 Bit und einen lokalen Datenbus von 16 Bit hat<br>
    Langsamer durch mehr Lade und Speichervorgänge zw. Hauptspeicher und der HDD/SSD. **Warum langsamer, genauer. Hier kann zu viel interpretiert werden. 0/2**

3. Gibt es zwischen den genannten drei Fällen Unterschiede in der Leitungsnutzung?

  Wenn der Datenbus 32 Bit breit ist, ist die kleinste addressierbare einheit 4 Bytes, das heißt wenn nur ein Byte benötigt wird werden trotzdem 4 übertragen. Bei dem 16 bit Datenbus wird hingegen nur ein Byte unnötig übertragen. **Aber: Wir haben trotzdem ein 32 Bit System, somit müssen wir davon ausgehen, dass wir immer zwei Zyklen lang den Datenbus belegen für eine Übertragung. Andernfalls bräuchte es, wie bei seriellen Schnittstellen, Start- und Stopinformationen, die wieder zusätzlich Platz fressen würden. Damit: Kein Unterschied**

4. Wie viele Bits werden für den Programmzähler und das Befehlsregister benötigt?

  Genauso viele wie für die Adressen, da ja überall im Speicher Programmcode stehen kann oder der komplette Speicher durch ein einziges Programm belegt ist. In diesem Fall sind also 32 bit nötig.
**Welcher der beiden muss so groß sein wie die Adressen?**
**Der PC muss eine Adresse halten können, da er die Adresse der Instruktion hält. Diese sind aber, wie in Teil 1 gezeigt, nur 24 Bit groß.**
**Das Befehlsregister muss so groß sein, wie ein Befehl, also 32 Bit, bzw, wenn man nur den wirklichen Aufgabenteil des Befehls (Opcode) sieht, 8 Bit 0/1**

## Selbststudium 3/4

1. Ein Steuerregister ist ein Prozessorregister, das das Verhalten der CPU kontrolliert.

2. Steuerregister sind u.a. für Interrupts, Pageing und das Setzen oder nicht setzen von Modis zuständig (z.B. Debugging Ext, TimeStampDisable, etc) **Schön wären v.a. Beispiele (namentlich) gewesen. -1**
