# Lösungen zum 11\. Übungsblatt

# Bamberger, Jannik und Klopfer, Fabian

## Gesamt:	17.5/20

## Aufgabe 1: Allgemein 		 6/7
- Welchen Unterschied zwischen den Dateiendungen (alles nach dem Punkt) gibt es klassischerweise zwischen den Betriebssystemen Windows und Linux? Denken Sie beispielsweise an die Erweiterung .exe. (1)

 Unter Linux hat die Dateiendung eher informativen Charakter, da der Punkt ein normales Zeichen ist. Linux bestimmt den Dateityp durch file (s. unten). Unter Windows ist der Punkt kein normales Zeichen, sondern wird vom Betriebssystem genutzt um den Dateityp fest zu stellen.

- Einige Dateien beginnen mit Magic Numbers. Warum? (1)

 Die Magic Numbers werden verwendet um den Dateityp anzugeben, der dann z.B. mit file() ausgelesen wird. Java hat beispielweise die Magic Number 0xCAFEBABE

- Was versteht man unter dem MIME−Typ einer Datei und wie erhält man diesen und welche Probleme können hierbei auftreten? (2)

 Multipurpose Internet Mail Extensions-Typ oder Content-Typ gibt die Art und den genauen Typ der Dateiinhalte an.
<<<<<<< HEAD
 Wird der MIME-Typ nicht angegeben, so wird versucht den Typ mit MIME-Sniffing zu finden. Hierfür wird zunächst geprüft, ob die Datei eine Magic Number enthält. Wenn nicht wird entsprechend des implementierten Algorithmuses geraten oder der Typ der Datei wird als unbekannt/Data gesetzt, wenn das Erraten fehlschlägt. **Potentielle Probleme fehlen. -1**
=======
 Wird der MIME-Typ nicht angegeben, so wird versucht den Typ mit MIME-Sniffing zu finden. Hierfür wird zunächst geprüft, ob die Datei eine Magic Number enthält. Wenn nicht wird entsprechend des implementierten Algorithmuses geraten oder der Typ der Datei wird als unbekannt/Data gesetzt, wenn das Erraten fehlschlägt.
 Anderen content type angeben als anghängt; content type mit versteckten dat. Gefährlich;
 Nicht klausurrelevant
>>>>>>> 41215f6f1f0229cee54377b65c6c29496cb1a137

- Welche Arten von Dateistrukturen kennen Sie? Worin unterscheiden sich diese? (Vor- und Nachteile) (3)
 - Byte Sequenz
   + maximale Flexibilität.
   - Das BS weiß nicht was die Datei enthält => Nur user-level Programme können Daten effektiv nutzen, sind dafür aber nicht eingeschränkt.
   - Keine kernelseitige Sicherheitsprüfung, was in Dateien geschrieben werden darf oder nicht.

 - Record Sequenz (records fester Größe)
   + read und write greifen jeweils recordweise zu => muss über weniger Elemente iteriert werden, als wenn byteweise addressiert wird.
   - weniger Flexibilität für user-level Programmierer.

 - Baum (mit Records variabler Größe als Knoten, aber einer fixen position für den Schlüssel) BS muss kenntnins über Daten haben;
   + ermöglicht sehr schnelles durchsuchen nach Schlüsslen in einer Datei.
   + Position beim einfügen wird vom BS bestimmt.
   - weniger Flexibilität für user-level Programmierer.

## Aufgabe 2: System Calls		 6/6
Einige, aber nicht alle, Betriebssysteme haben für das Umbenennen einer Datei einen separaten System Call.

-  Wie kann das Umbenennen einer Datei in Betriebssystemen durchgeführt werden, die einen solchen Call nicht unterstützen. (Ein schreibender Zugriff auf den Namen bestehender Dateien existiert daher nicht) (2)

  - Neu Verlinken mit gewünschtem Namen und unlinken der alten Referenz (funktioniert nur im gleichen fs bzw. unter dem gleichen Mount Point). **Nur in FS, die hardlinks unterstützen**
  - Neue Datei mit gewünschtem Namen erstellen, mit read und write aus der alten Datei einlesen und in die neue Datei speichern (unter unixoiden ist der Dateiname nicht Teil der Datei selbst**Im Fat System in dem Sinne ja auch nicht**). Danach alte Datei löschen.

-  Welche Vor- / Nachteile haben diese beiden Versionen des Umbenennens? (2)
  - Neu Verlinken: Geht nur unter dem selben Mount Point, effizient da nur Pointer geändert werden.
<<<<<<< HEAD
  - Neue Datei erstellen, Inhalt kopieren und alte Datei löschen: funktioniert immer **Solange genug Platz**; ineffizient, da alle Daten kopiert werden müssen.
=======
  - Neue Datei erstellen, Inhalt kopieren und alte Datei löschen: funktioniert immer; ineffizient, da alle Daten kopiert werden müssen; wenn nicht genug Platz nicht möglich; auf SSDs ist |Schreibop| limitiert (lebenszykl.)
>>>>>>> 41215f6f1f0229cee54377b65c6c29496cb1a137



- Im UNIX Dateisystem existiert ein System Call chroot, der die Verzeichniswurzel auf ein gegebenes Verzeichnis setzt. Welche Vorteile bringt dies mit sich? (2)  

 chroot setzt das root-Verzeichnis für einen Prozess auf das in den Parametern angegebene Verzeichnis. So kann zum Beispiel eine separate Testumgebung geschaffen werden mit anderen Attributen (z.B. verschiedene Library Versionen zum Testen von Abwärtskompabilität), als das primär laufende Betriebssystem. Ausserdem bietet es eine sehr limitierte Version von Sandboxing an, aus der aber schon nach Manpage Anleitung wieder "ausgebrochen" werden kann. Hilfreich ist das auch für "Wartungsarbeiten" um mittels Live Image Vollzugriff auf nicht-verschlüsselte und nicht BIOS/UEFI-Passwort geschützte Systeme zu erlangen.


<<<<<<< HEAD
## Aufgabe 3: Selbststudium: FAT16 		5.5/7
=======
## Aufgabe 3: Selbststudium: FAT16 		/7  Block-basiertes FS
>>>>>>> 41215f6f1f0229cee54377b65c6c29496cb1a137
-  **Wie ist das FAT16-Dateisystem aufgebaut? Gehen Sie auf Teilstrukturen ein und erläutern Sie deren Inhalte. (5)**

 Aus der FAT Spezifikation von Microsoft <http://read.pudn.com/downloads77/ebook/294884/FAT32%20Spec%20(SDA%20Contribution).pdf/>
 0 – Bootsector & BPB  
 1 - Reserved Region
 2 – FAT Region  // schreib op immer auf beiden; gegen hw defekte
 3 – Root Directory Region  
 4 – File and Directory Data Region  

 Max. Größe eines Laufwerks: 4GB  **Keine starre Größengrenze. Max Laufwerksgröße ist abhängig von der Clustergröße**
 Max. Größe einer Datei: 2GB
 Max. Länge des Dateinamen: 8 Chars . 3 Chars Dateiendung  

 0: Bootsector und Bios Parameter Block
	Bootsector: Existiert für jedes bootbare Medium. Der BPB ist im Bootsector. Er befindet sich nach dem Jump-Befehl zum Boot-Code und der OEM-Bezeichnung (ab Offset 11 bis 512 in Bytes). Attribute des BPB (die des Bootsectors weggelassen der Übersichtlichkeit halber):


| Attribut name		|  Offset 	|   Größe | Beschreibung  	|
|---	        	|---	    |---	  |---	            |
|  BPB_BytsPerSec  	|   11	|   2	|   Count of bytes per sector. This value may take on only the following values: 512, 1024, 2048 or 4096.	|
| BPB_SecPerClus 	|   13	|   1	|   Number of sectors per Cluster. This value must be a power of 2 that is greater than 0. The legal values are 1, 2, 4, 8, 16, 32, 64, and 128.	|
| BPB_NumFATs 		|   16	|   1	|   The count of file allocation tables (FATs) on the volume. A value of 2 is recommended although a value of 1 is acceptable. 	|
| BPB_TotSec16 		|   19	|   2	|   This field is the old 16-bit total count of sectors on the volume. This count includes the count of all sectors in all four regions of the volume.  This field can be 0; if it is 0, then BPB_TotSec32 must be non-zero. For FAT32 volumes, this field must be 0. For FAT12 and FAT16 volumes, this field contains the sector count, and BPB_TotSec32 is 0 if the total sector count “fits” (is less than 0x10000). 	|

 2: FAT Region: Hier wird die wirkliche file alloc. table gespeichert. Für FAT16 ist jeder Eintrag in der FAT 16 Bits lang. Ein Eintrag stellt den Zustand eines Clusters (also den Zustand einer festen Anzahl aufeinanderfolgender Sektoren) dar. Ist die FAT größer als die nötig um alle Sektoren abzubilden, werden die restlichen Einträge mit 0 gefüllt. Die Einträge in einer FAT16 sind folgendermaßen zu deuten:

| Wert 				| Beschreibung       |
|---   				|---                 |
| 0x0000			|	Cluster is free |
| 0x0002 to MAX*	| Cluster is allocated. Value of the entry is the cluster number of the next cluster following this corresponding cluster. MAX is the Maximum Valid Cluster Number |
| (MAX + 1) to 0xFFF6 | Reserved and must not be used.  |
| 0xFFF7 | Indicates a bad (defective) cluster. |
| 0xFFF8 to 0xFFFE | Reserved and should not be used. May be interpreted as an allocated cluster and the final cluster in the file (indicating end-of-file condition). |
| 0xFFFF | Cluster is allocated and is the final cluster for the file (indicates end-of-file). |

 \*MAX = Anzahl valider Cluster der Festplatte/... +1

  3: Root Directory Region:  
  "On FAT12 and FAT16 volumes, the root directory must immediately follow the last file allocation table. The location of the first sector of the root directory is computed as below:  
 FirstRootDirSecNum = BPB_ResvdSecCnt + (BPB_NumFATs * BPB_FATSz16)
 The size of the root directory on FAT12 and FAT16 volumes is computed using the contents of the BPB_RootEntCnt field."
  Wenn 0, dann Order;

 4: File and Directory Data Region  
 Ein FAT Verzeichnis ist ein eigener Dateityp.  Das FAT Verzeichnis dient als Container bzw. "Sammelbox" für weitere FAT Verzeichnisse oder Dateien. Jeder Verzeichniseintrag besteht aus 32 byte und repräsentiert meist entweder eine Datei oder ein Unterverzeichnis.
Hier die Felder eines Eintrags:

|   field name		|   Offset	|  Size	|  Description	|
|---				|---	|---	|---	|
|   DIR_Name		|   0	|   11	|  “Short” file name limited to 11 characters (8.3 format).  	|
|   DIR_CrtTime		|   14	|   2	|   Creation time. Granularity is 2 seconds.	|
|   DIR_CrtDate		|   16	|   2	|   Creation date. 	|
|   DIR_LstAccDate	| 18  	|   2	|   Last access date. Last access is defined as a read or write operation performed on the file/directory described by this entry. This field must be updated on file modification (write operation) and the date value must be equal to DIR_WrtDate. 	|
|   DIR_FstClusHI	|   20	|   2	|   High word of first data cluster number for file/directory described by this entry. Only valid for volumes formatted FAT32. Must be set to 0 on volumes formatted FAT12/FAT16. 	|
|   DIR_WrtTime		|   22	|   2	|   Last modification (write) time. Value must be equal to DIR_CrtTime at file creation.	|
|   DIR_WrtDate		|   24	|   2	|   Last modification (write) date. Value must be equal to DIR_CrtDate at file creation.	|
|   DIR_FstClusLO	|  26 	|   2	|   Low word of first data cluster number for file/directory described by this entry. 	|
|   DIR_FileSize	|   28	|   4	|   32-bit quantity containing size in bytes of file/directory described by this entry. 	|


**Hinweis: Das ist zwar schön und gut, aber ich habt das so sicherlich nicht alles im Kopf. Versucht immer eine kurze, eindeutige, Beschreibung abzugeben, die ihr euch auch ohne zusätzliche Quellen merken könnt**


**Beschreiben Sie alle Schritte, die ausgeführt werden müssen, um eine Datei im Ordner C:/Ordner/Unterordner/ zu lesen, die 5 Sektoren groß ist. (2)**

1. Verzeichniseintrag suchen: Starte bei Root, lese Anfangscluster, folge Chain und laden; Rauslesen wo /Ordner beginnt; Ordner Anfangscluster lesen, chain folgen und laden; Rauslesen wo Unterordner steht, anfangscluster lesen und chain folgen, dann laden
2. Anfangscluster aus Verzeichnis lesen und laden.
3. Anfangscluster in der FAT nachschauen und falls vorhanden Cluster laden das dort referenziert ist und dieses wieder in der FAT nachschauen und so weiter, bis kein weiteres Cluster mehr referenziert ist in der FAT
4. Fertig
**Sehr ungenau. Ziel war es, dass auch gezeigt wird, dass auch Ordner nur einfach in CLustern liegen und daher zum "Lesen" genau wie Dateien behandelt werden**
