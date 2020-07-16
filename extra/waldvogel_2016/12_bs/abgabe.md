# Lösungen zum 12\. Übungsblatt

# Bamberger, Jannik und Klopfer, Fabian

## Gesamt:	/20

## Aufgabe 1: Das Ext2 Dateisystem			 /9

**Wie ist das Ext2-Dateisystem aufgebaut? Erläutern Sie u.a. Blöcke, Blockgruppen, Superblocks und Inodes (/4)**  
[Ref0](http://www.science.unitn.it/~fiorella/guidelinux/tlk/node95.html#SECTION001110000000000000000)
[Ref1](http://de.linwiki.org/wiki/Linuxfibel_-_System-Administration_-_Dateisysteme#Das_Extended_File_System_Version_2_.28ext2.29)  [Ref2](http://www.nongnu.org/ext2-doc/ext2.html#INODE-TABLE)  
 Man kann Geräte im Dateisystem grob in 3 Kategorien Unterteilen: Character, Network und Block Devices. Block devices sind solche, die Daten blockweise speichern können. Die Blockgröße ist bei der Partitionierung variabel (meistens 1024, 2048 oder 4096 KiB). Die Daten einer Datei sind in ext2 in einem oder mehreren Blöcken gespeichert. Diese werden aus effizienzgründen zu Gruppen zusammengefasst. Jede Gruppe enthält alle der unten genannten Felder als Header. Falls ein Block oder mehrere Blöcke beschädigt werden kann man sie wiederherstellen.
 Man kann es sich also als eine Aneinanderreihung von Gruppen mit Kopien von Dateisystem-relevanten Daten und Nutzer-Daten


 | Bootsektor | Gruppe 1 | Gruppe ... | Gruppe N |

Wieso gibt es Blockgruppen? Gegen Fragmentierung & damit Bitmaps nur 1 Block weit

 Eine Einzelne Gruppe ist folgendermaßen aufgeteilt:



 |   Super Block | Group Descriptor Table |  Block Bitmap | Inode Bitmap | Inode List | Data Blocks  |



 0.) Super Block   
 	enthält Metadaten/mount- & Allokationsinfos; immer and er gleichen Stelle

 - _Magic Number:_  
 	Dadurch identifizieren z.B. Unix Systeme & der Linux kernel den Dateityp.
  	"For the current version of EXT2 this is 0xEF53."  

 - _Revision Level:_  
	Versionsinformation, die von mount genutzt wird um zu bestimmen welche Funktionen verfügbar sind.  

 - _Mount Count and Maximum Mount Count:_  
	Bei jedem mount wird der Mount Counter um Eins erhöht, bis Max Mount Count erreicht ist, dann wird eine Warnung ausgegeben das e2fsck ausgeführt werden sollte.  

 - _Block Group Number:_  
	Block Nummer der Superblock-Sicherheitskopie

 - _Block Size:_  
	Die Blockgröße (fix für diese Instanz des ext2FS).  

 - _Blocks per Group:_  
	Anzahl der Blocks pro Gruppe (fix für diese Instanz des ext2FS). Begrenzt auf 8 &middot; Block Size (,da jede Bitmap nur einen Block belegen kann; s.u.)

 - _Free Blocks:_  
	Anzahl der unbelegten Blocks im FS; Wird gespeichert um beim Anfordern von neuem Speicher nicht durch die ganze Liste iterieren muss; ausserdem gibt das ext2fs den Speicher nicht sofort wenn möglich sondern in größeren Gruppen frei, um möglichst viele aneinanderhängende Blöcke reservieren zu können. Gleiches gilt für Free Inodes

 - _Free Inodes:_  
	Anzahl der unbelegten Inodes im FS,

 - _First Inode:_  
	Die Inode für das Wurzelverzeichnis /


 1.) Group Descriptors:  
 Relative Position der Bitmaps und Inode Table, Freie Blöcke/Inodes in jeder Gruppe.

 2.) Block Bitmap  
 	Codiert freie und belegte Blöcke in einer Bitmap, die benutzt wird um zusammenhängend zu allozieren (0 frei, 1 verwendet).

 3.) Inode Bitmap  
 	wie darüber.

 4.) Inode-Liste  
 Inode linked list für die Gruppe


Datenstruktur der Inode:
 - mode  
	16bit vector used to indicate the format of the described file and the access rights. Here are the possible values, which can be combined in various ways:


| Constant			|	Value	| Description			|
|---				|---		|---					|
| **file format**	|			|						|
| EXT2_S_IFSOCK		| 0xC000 	| socket 				|
| EXT2_S_IFLNK		| 0xA000 	| symbolic link 		|
| EXT2_S_IFREG		| 0x8000 	| regular file 			|
| EXT2_S_IFBLK		| 0x6000 	| block device 			|
| EXT2_S_IFDIR		| 0x4000 	| directory 			|
| EXT2_S_IFCHR		| 0x2000 	| character device		|
| EXT2_S_IFIFO		| 0x1000 	|	fifo 				|
| **process execution user/group override**	|	|		|
| EXT2_S_ISUID		| 0x0800 	|	Set process User ID	|
| EXT2_S_ISGID		| 0x0400 	| Set process Group ID	|
| EXT2_S_ISVTX		| 0x0200 	|	sticky bit			|
| **access rights**	|			|						|
| EXT2_S_IRUSR		| 0x0100 	|	user read 			|
| EXT2_S_IWUSR		| 0x0080 	|	user write 			|
| EXT2_S_IXUSR		| 0x0040 	|	user execute 		|
| EXT2_S_IRGRP		| 0x0020 	|	group read 			|
| EXT2_S_IWGRP		| 0x0010 	|	group write 		|
| EXT2_S_IXGRP		| 0x0008 	|	group execute 		|
| EXT2_S_IROTH		| 0x0004 	|	others read 		|
| EXT2_S_IWOTH		| 0x0002 	| 	others write 		|
| EXT2_S_IXOTH		| 0x0001 	|	others execute 		|

 - uid  
	16bit user id associated with the file.

 - size  
	In revision 0, (signed) 32bit value indicating the size of the file in bytes. In revision 1 and later revisions, and only for regular files, this represents the lower 32-bit of the file size; the upper 32-bit is located in the i_dir_acl.

 - access time  
	32bit value representing the number of seconds since january 1st 1970 of the last time this inode was accessed.

 - creation time  
	32bit value representing the number of seconds since january 1st 1970, of when the inode was created.

 - modification time  
	32bit value representing the number of seconds since january 1st 1970, of the last time this inode was modified.

 - deletion time  
	32bit value representing the number of seconds since january 1st 1970, of when the inode was deleted.

 - group id  
	16bit value of the POSIX group having access to this file.

 - links count  
	16bit value indicating how many times this particular inode is linked (referred to). Most files will have a link count of 1. Files with hard links pointing to them will have an additional count for each hard link.  
	Symbolic links do not affect the link count of an inode. When the link count reaches 0 the inode and all its associated blocks are freed.

 - flags
	32bit value indicating how the ext2 implementation should behave when accessing the data for this inode.

 - block
	12 x 32bit block numbers pointing to the blocks containing the data for this inode.  
	1x singular indirect block (13th filed in the block array), which is a block containing an array of blocks containing the data. Such a singular indirect block may contain up to (block size << log(sizeof(address))) = maxRefAmount references to other blocks.  
	1x doubly-indirect block; which is a block containing an array of indirect block IDs, with each of those indirect blocks containing an array of blocks containing the data. maxRefAmount &middot; maxRefAmount.  
	1x triply-indirect block; which is a block containing an array of doubly-indrect block IDs, with each of those doubly-indrect block containing an array of indrect block, and each of those indirect block containing an array of direct block. maxRefAmount &middot; maxRefAmount &middot; maxRefAmount.  
	A value of 0 in this array effectively terminates it with no further block being defined.	All the remaining entries of the array should still be set to 0. => 0 in the block array determines EOF

- generation
	32bit value used to indicate the file version (used by NFS).


5.) Data block  
 	Blöcke, die die Daten enthalten.



Inode nur mit daten: immediate File: Wenn Datei weniger als 60 Byte hat z.B. SymLinks (Enthält nur Dateipfad)



**Ext2 kann deutlich größere Dateien beinhalten als FAT16. Wieso? Wie werden Datein abgelegt? (/2)**

Die Größe einer Inode ist konstant 128 Byte, die Datenblockgröße kann jedoch bei der Erstellung frei gewählt werden.  
Mit einem dreifach indiretem Block und 4 KiB Blockgröße könnte ein Zeiger 2^12 Byte &middot; (2^12 Byte / (sizeof((void)\*)))^3 (für 32-Bit System 2^2 Byte) Zeiger = 2^12 &middot;  2^10  &middot;  2^10 = 2^32 Byte fassen.


| Blockgröße (KiB)	| Maximale Dateigröße (GiB)	|
|--- 				|---						|
| 1					| 1 						|
| 2 				| 2 						|
| 4 				| 4 						|

Insgesamt ergibt sich:
12 &midddot; block size + (block size << log(sizeof(address))) &middot; block size + (block size << log(sizeof(address))) &middot; (block size << log(sizeof(address))) &middot; block size + (block size << log(sizeof(address))) &middot; (block size << log(sizeof(address))) &middot; (block size << log(sizeof(address))) &middot; block size  

**Was versteht man unter Symbolic Links und Hard Links? (/2)**
	Ein Hard Link ist eine Referenz auf die erste Inode einer Datei. Ein Soft/Sym Link ist eine Referenz auf ein Verzeichnis oder eine im Verzeichnis befindlichen Hard Link (Referenz als Pfad, KEIN POINTER), versehen mit einer Markierung, die den Soft/Sym Link als solchen markiert. Da Verzeichnisse auch nur Dateien sind, gilt allgemein:  
	Hard Link: Inode <=> Datei  
	Soft/Sym Link: Datei <=> Datei  


## Aufgabe 2: Backups		 	/4
Nehmen Sie an, Sie müssen einen Fileserver einrichten und bekommen hierfür drei Festplatten zur Verfügung gestellt.
- **Wie würden Sie den Server einrichten? Begründen Sie.**
RAID 01 Konfiguration: Effizient für viele kleinere Schreibzugriffe, da hier zwei Platten parallel arbeiten können und jeder strip einmal gespiegelt vorhanden ist. Somit sind schnelle Zugriffszeiten möglich und eine geringe Redundanz. Im besten Fall besitzt man einen Gönner der einem ein Satz Lochkarten/eine Rolle Tape als Disaster Backup spendiert oder man druckt alles aus.

- **Wogegen schützt ihre Version und wogegen nicht?**
Nicht gegen Malware, Stromausfall, Netzüberspannung, Adminfehler, wenn 2 Disks ausfallen, Nutzerfehler, BSOD, DDOS Attacken, MITM Attacken, Java Sicherheitslücken, OS spezifische Sicherheitslücken, ...

## Aufgabe 3: Selbststudium: RAID 			/7

- **Wofür steht die Abkürzung RAID und was ist damit gemeint? (1)**
Redundant Array of Inexpensive Disk oder Redundant Array of Idependend Disk; die Zusammenfassung mehrerer physischer Festplatten zu einer logischen um den Datensurchsatz zu erhöhen und abgesehen von RAID 0 auch um Daten sicherer zu speichern, damit im Falle einer Inkonsistenz der korrekte Zustand wieder hergestellt werden kann.
- **Erklären Sie kurz die RAID-Level 0, 1, 4, 5, 6 und 10. (3)**

| RAID level	| Beschreinung	|
|---			|---			|
| 0 			| Alle vefügbaren Disks werden zunächst in sog. strips aufgeteilt und dann zu einer großen logischen Disk aus strips zusammengefügt (Stripping). Hierbei werden die Blocks nach dem Reissverschluss-Prinzip angeordnet, sodass parallel zugegriffen werden kann. Führt zu sehr hohen Übertragungsgeschwindigkeiten und vielen I/O Op/s, auf Kosten möglicher Sicherheiten. Ab 2 sinnvoll Disks möglich. |  
| 1 			| Zu jeder Festplatte gibt es eine Kopie/Spiegelung (Mirroring), die synchronisiert wird und nur zum Lesen benutzt wird. Somit kann die Transfergeschwindigkeit erhöht werden und Redundanz zur Fehlerkorrekur wird geschaffen. Ab 2 Disks sinnvoll möglich. OBACHT: nicht mischen mit 10/01; Daten werden gleichzeitig geschrieben ausser es gibt BUS-Begrenzungen |  
| 4 			| Stript die einzelnen Festplatten, berechnet Paritätsdaten und speichert diese auf einer dedizierten Platte, die restlichen Platten erhalten Nutzerdaten. Paritäten werden immer stripe-gruppenweise berechnet (z.B. bei 5 Disks ist 1 die Paritätsdatendisk und 4 Nutzerdatendisks. Je ein Strip von den Nutzerdisks kann eine Paritätsgruppe bilden, d.h. Nutzerstrip x Nutzerstrip x Nutzerstrip x Nutzerstrip -> Paritätsstrip). Bei Systemen mit vielen kleineren I/O Op verliert RAID 4 (sowie 5 und 6) deutlich an Geschwindigkeit, wegen des 2-phasigen Schreibvorgangs. Fällt die Paritätsplatte aus, so kann nichts mehr wiederhergstellt werden. Ab 3 Disks sinnvoll möglich. Schreiben braucht bzgl. der Paritätsplatte immer länger, da diese zuvor berechnet werden müssen |
| 5 			| Wie 4, nur, dass die Paritätsdaten auf allen Festplatten verteilt werden. So wird die Paritätsplatte nicht bei jedem Zugriff beansprucht und verschleißt. Ausserdem hängt die Geschwindigkeit des RAID Systems nicht nur von der Leistung der Partitätsplatte ab und diese kann nicht ausfallen, sondern nur eine der anderen Disks (bei mehr als einem Ausfall => Systemausfall). Ab 3 Disks sinvoll möglich. Vorteil zu 4: Paritätsschreiben wird verteilt => Lastenverteilung |
| 6 			| Wie 5, nur, dass es jeder Paritätsstrip zweimal gespeichert wird auf verschiedenen Platten, sodass auch der Ausfall von 2 Platten kompensiert werden kann. Ab 3 Disks sinvoll möglich. |
| 10 			| Zwei RAID Level: Top Level RAID 0, also min. 2 logische Festplatten werden zu einer logischen Festplatte zusammengefügt mittels Reissverschluss-Prinzip. Bottom level: RAID 1 Spiegelung. Also besteht ein RAID 10 System aus Festplatten und Spiegel zur Integritätssicherung, die zusammengefügt wurden zu einer logischen Festplatte. Hierbei besitzt die größere Festplatte keine direkte Spiegelung, sondern erst die jeweiligen physischen Festplatten auf der Stripebene (Abgrenzung RAID 01). Ab 4 Disks sinvol möglich. |  

- **Wenn vier Festplatten zu je 4 GiB verwendet werden können, wie hoch ist die Gesamtkapazität bei den RAID-Leveln aus Aufgabenteil b?. (2)**  


| RAID level	| Gesamtkapazität	|
|--- 			|---				|
| 0 			| 16 				|
| 1 			| 8 				|
| 4 			| 12 				|
| 5 			| 12 				|
| 6 			| 8 				|
| 10 			| 8 				|

- **Gibt es einen relevanten Unterschied zwischen RAID-Level 10 und 01 bezüglich der Fehlertoleranz? (1)**
RAID 10 ist in der Fehlererkennung besser: Es ist aus der Top-level RAID 0 einfach zu erkennen wo der Block lag, und je nach dem wird vom jeweiligen Spiegel wieder hergestellt.
Bei RAID 01 muss zunächst geprüft werden in welchem Strip die Datei lag, auf welcher Platte der Strip lag und auf welcher Platte der SpiegelStrip liegt um dann entsprechend wieder herzustellen.
