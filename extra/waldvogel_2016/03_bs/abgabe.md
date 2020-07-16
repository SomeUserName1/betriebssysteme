# Lösungen zum 3. Übungsblatt
# Klopfer, Fabian und Bamberger, Jannik

## Gesamt: 19.5/20
## Aufgabe 1 6/6
1. **Was ist ein Prozesskontrollblock und welche drei Informationskategorien beinhaltet dieser?**
Der Prozesskontrollblock ist ein Datenbereich, der Informationen zu einem Prozess enthält. Es sind Informationen enthalten die das Betriebssystem benötigt um den Prozess auszuführen und hier wird der aktuelle Status eines Prozesses abgelegt, wenn gerade ein anderer Prozess ausgeführt wird.
  - Prozessidentifikation
  - Prozess Statusinformationen
  - Prozesskontrollinformationen

2. **Warum werden zwei Modi (Benutzermodus und Kernel-Modus) benötigt?**
Um Betriebssystemkomponenten und Datenstrukturen wie Prozesskontrollblöcke, Filetabellen etc. zu schützen werden normale Nutzerprogramme nicht im Kernel-Modus ausgeführt. Da ein normales Nutzerprogramm keine komplette Kontrolle über den Prozessor benötigt ist es aus Sicherheitsgründen sinnvoll, auch nicht alle Aktionen zuzulassen, also den 'user mode' zu verwenden.

3. **Was ist Swapping und welchen Sinn hat es?**
Beim Swapping wird ein geblockter Prozess auf die Festplatte geschreiben, um Platz im Hauptspeicher frei zu machen. In dem frei werdenden Speicher kann entweder ein neuer Prozess erstellt oder ein vorher ausgelagerter Prozess wieder geladen werden. Dadurch kann die CPU besser genutzt werden, denn wenn viele Prozesse auf IO-Operationen warten würde die CPU sonst nicht ausgelastet werden. Daher kann durch Swapping ein neuer Prozess in den Speicher geladen werden, der die CPU beschäftigt.

4. **Welche Schritte muss ein Betriebssystem beim Erzeugen eines neuen Prozesses ausführen?**
  1. Prozessidentifier vergeben und Eintrag in der primären Prozesstabelle erstellen
  2. Speicher für Stack, Daten, Programm und Prozesskontrollblock reservieren
  3. Prozesskontrollblock initialisieren
  4. Verlinkungen setzen, also zum Beispiel den Prozess beim Scheduler registrieren
  5. Sonstige Datenstrukturen erweitern oder erstellen, wie zum Beispiel Dateien zur Performanceanalyse des Systems

5. **Was ist der Unterschied zwischen einem Moduswechsel und einem Prozesswechsel (mode switch / process switch)?**
  Bei einem Moduswechsel wird der Status des aktuell laufenden Prozesses nicht verändert. Es muss also nur wenig Aufwand betrieben werden, um den Kontext zu speichern und wiederherzustellen. Bei einem Prozesswechsel hingegen wird der Status des aktuellen Prozesses verändert. Es muss also viel Arbeit betrieben werden, um den aktuellen Status des Prozesses zu speichern und dann die Kontrolle an einen anderen Prozess zu übergeben.

## Aufgabe 2 9/9
1. **Skizzieren Sie den 7-stufigen Prozesslebenszyklus. Benennen Sie auch die Übergänge.**
  - New (Übergänge nach Ready und Ready/Suspended)
  - Ready (Übergänge nach Running und Ready/Suspended)
  - Ready/Suspended (Übergang nach Ready)
  - Blocked (Übergänge nach Ready und Blocked/Suspended)
  - Blocked/Suspended (Übergänge nach Ready/Suspended und Blocked)
  - Running (Übergänge nach Ready, Exit, Blocked und Ready/Suspended)
  - Exit (Keine Übergänge möglich)

2.

| Zeitpunkt |               P1 |                P3 |                P5 |                P7 |                P8 |
| :-------- | :--------------- | :---------------- | :---------------- | :---------------- | :---------------- |
|       1-4 |          running |             ready |             ready |             ready |             ready |
|      5-14 |      blocked (3) |             ready |           running |             ready |             ready |
|     15-17 |      blocked (3) |             ready |             ready |           running |             ready |
|     18-19 |      blocked (3) |           running |             ready |       blocked (3) |             ready |
|     20-23 |      blocked (3) |       blocked (2) |           running |       blocked (3) |             ready |
|     24-27 |      blocked (3) |       blocked (2) |       blocked (3) |       blocked (3) |           running |
|     28-32 |      blocked (3) |       blocked (2) | blocked/susp. (3) |       blocked (3) |           running |
|     33-35 |      blocked (3) |             ready | blocked/susp. (3) |       blocked (3) |           running |
|     36-37 |            ready |             ready | blocked/susp. (3) |       blocked (3) |           running |
|     38-39 |            ready |           running | blocked/susp. (3) |       blocked (3) |              exit |
|     40-43 |            ready |           running |       ready/susp. |       blocked (3) |              exit |
|     44-47 |            ready |           running |             ready |       blocked (3) |              exit |
|        48 |            ready |           running |             ready |             ready |              exit |

## Aufgabe 3

1. **Was tut der Fork-Befehl?**
  Der Fork-Befehl erstellt eine exakte Kopie des aufrufenden Prozesses, und gibt an den Aufrufer die PID des neuen Prozesses, und an den neuen Prozess 0 zurück. Unter Linux werden die folgenden Schritte durchgeführt:
  1. Eintrag in der Prozesstabelle erstellen
  2. Eindeutige ID an den Kindprozess vergeben
  3. Eine Kopie des Elternprozesses anlegen
  4. Dateizähler für alle Dateien des Elternprozesses erhöhen, um den Kindprozess auch zu einem Besitzer zu machen
  5. Dem Kindprozess den ready Status geben
  6. Die ID des Kindprozesses an den Elternprozess geben und 0 an den Kindprozess

2. **Welche Rolle spielt fork bei der Erstellung von Prozessen in Linux? (Gehen sie auf die Beziehung zu init ein)**
  Bei einem Linux-System wird als erstes, wenn das System initialisiert wird der Init-Prozess gestartet. Dieser kümmert sich dann darum, all die anderen Prozesse zu starten, indem er wiederholt fork verwendet, um neue Prozesse zu erstellen. Wenn ein neuer Prozess verwendet werden soll muss fork verwendet werden, da exec keinen neuen Prozess erstellt, sondern den Inhalt des aufrufenden Prozesses durch einen neuen ersetzt.

3. **Erläutern Sie an einem selbst gewählten Codebeispiel, worum es sich bei einer Fork-Bombe handelt.**

  ```
  #include <unistd.h>

  int main(void){
      for(;;)
          fork();
      return 0;
  }
  ```
  Bei einer Fork-Bombe wird in einer Endlosschleife immer wieder Fork aufgerufen. Dadurch spaltet sich der Prozess immer wieder, und die neu entstehenden Prozesse ebenfalls etc. Damit wird versucht ein System lahm zu legen, indem es nurnoch damit beschäftigt ist, neue Prozesse zu erstellen und so einen kontinuirlich wachsenden Ressourcenverbrauch hat.

4. **Warum legt eine Fork-Bombe heutzutage nicht mehr das gesamte System lahm? Warum war dies früher der Fall?**
  Bei vielen heutigen Betriebssystemen ist es möglich, die Anzahl an Prozessen pro Nutzer zu beschränken. Dadurch wirkt sich der Aufruf einer Fork-Bombe nicht auf das komplette System aus, sondern nur auf den Nuter der die Bombe gestartet hat. **Warum war es früher der Fall? 0.5/1**
