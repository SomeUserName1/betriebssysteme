# Lösungen zum 3. Übungsblatt
# Klopfer, Fabian und Bamberger, Jannik

## Aufgabe 2 (10/10)
```
/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 10
 */
```

Bei allen Programmen werden die folgenden syscalls ausgeführt (mit unterschiedlichen Adressen/Programmname etc.)
```
execve("./p1", ["./p1"], [/* 22 vars */]) = 0
brk(NULL)                               = 0x8756000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
mmap2(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb76f2000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat64(3, {st_mode=S_IFREG|0644, st_size=37709, ...}) = 0
mmap2(NULL, 37709, PROT_READ, MAP_PRIVATE, 3, 0) = 0xb76e8000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/i386-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\1\1\1\3\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0\320\207\1\0004\0\0\0"..., 512) = 512
fstat64(3, {st_mode=S_IFREG|0755, st_size=1786484, ...}) = 0
mmap2(NULL, 1792572, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xb7532000
mprotect(0xb76e1000, 4096, PROT_NONE)   = 0
mmap2(0xb76e2000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1af000) = 0xb76e2000
mmap2(0xb76e5000, 10812, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0xb76e5000
close(3)                                = 0
mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7719000
set_thread_area({entry_number:-1, base_addr:0xb7719940, limit:1048575, seg_32bit:1, contents:0, read_exec_only:0, limit_in_pages:1, seg_not_present:0, useable:1}) = 0 (entry_number:6)
mprotect(0xb76e2000, 8192, PROT_READ)   = 0
mprotect(0x8049000, 4096, PROT_READ)    = 0
mprotect(0xb771a000, 4096, PROT_READ)   = 0
munmap(0xb76e8000, 37709)               = 0
```

1.
Das Programm wartet 5 Sekunden und beendet sich dann.
```
nanosleep({5, 0}, 0xbfb17cb8)           = 0 //5s warten
exit_group(0)                           = ? //Alle Threads in der Threadgruppe des Prozesses beenden
+++ exited with 0 +++
```

2.
Das Programm p2 versucht die Datei "/foobar" zu öffnen. Dabei tritt ein Fehler auf (die Datei wird nicht gefunden) und deshalb beendet sich das Programm.
```
brk(NULL)                               = 0x8721000
brk(0x8742000)                          = 0x8742000
open("/foobar", O_RDONLY)               = -1 ENOENT (No such file or directory)
exit_group(1)                           = ?
+++ exited with 1 +++
```

3.
Das Programm öffnet die Datei `/tmp/myFile.txt` und schreibt dann `42 und mehr, die einwohnerreichste Insel ist Java (Indonesien) mit 131,193 Mio. Einwohnern.` hinein. Danach liest das Programm wieder die gleiche Datei. Zum Schluss wird `die einwohnerreichste Insel ist Java (Indonesien) mit 131,193 Mio. Einwohnern.` auf die Standardausgabe geschrieben.


```
brk(NULL)                               = 0x9105000
brk(0x9126000)                          = 0x9126000
open("/tmp/myFile.txt", O_RDWR|O_CREAT|O_TRUNC, 0666) = 3 //Datei /tmp/myFile.txt öffnen, ggf. erstellen. Die Datei hat den Filedescriptor 3
fstat64(3, {st_dev=makedev(252, 0), st_ino=1586634, st_mode=S_IFREG|0664, st_nlink=1, st_uid=1000, st_gid=1000, st_blksize=4096, st_blocks=0, st_size=0, st_atime=2016/11/16-17:07:32.245827529, st_mtime=2016/11/16-17:08:40.908141534, st_ctime=2016/11/16-17:08:40.908141534}) = 0 //Dateiinformationen abrufen
write(3, "42 und mehr, die einwohnerreichste Insel ist Java (Indonesien) mit 131,193 Mio. Einwohnern.", 91) = 91 // String in Datei 3 Schreiben
_llseek(3, 0, [0], SEEK_SET)            = 0 //Lesestelle auf 0 setzen, so dass von Beginn an gelesen wird.
read(3, "42 und mehr, die einwohnerreichste Insel ist Java (Indonesien) mit 131,193 Mio. Einwohnern.", 4096) = 91 // Datei 3 lesen
fstat64(1, {st_dev=makedev(0, 14), st_ino=3, st_mode=S_IFCHR|0620, st_nlink=1, st_uid=1000, st_gid=5, st_blksize=1024, st_blocks=0, st_rdev=makedev(136, 0), st_atime=2016/11/16-17:08:40.747301535, st_mtime=2016/11/16-17:08:40.747301535, st_ctime=2016/11/16-15:45:56.747301535}) = 0
read(3, "", 4096)                       = 0
close(3)                                = 0 //Datei 3 schließen
write(1, "die einwohnerreichste Insel ist Java (Indonesien) mit 131,193 Mio. Einwohnern.", 78die einwohnerreichste Insel ist Java (Indonesien) mit 131,193 Mio. Einwohnern.) = 78 //String nach Datei 1 (Standard out) schreiben
exit_group(0)                           = ?
+++ exited with 0 +++
```

4.
Es wird die Datei `/etc/localtime` geöffnet und die letzten 28 Zeichen daraus gelesen. Danach wird die Datei geschlossen und es wird das aktuelle Datum/die aktuelle Uhrzeit ausgegeben.

```
brk(NULL)                               = 0x964d000
brk(0x966e000)                          = 0x966e000
open("/etc/localtime", O_RDONLY|O_CLOEXEC) = 3
fstat64(3, {st_mode=S_IFREG|0644, st_size=2335, ...}) = 0 //Dateiinformationen anfordern
fstat64(3, {st_mode=S_IFREG|0644, st_size=2335, ...}) = 0 //Dateiinformationen anfordern
read(3, "TZif2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\t\0\0\0\t\0\0\0\0"..., 4096) = 2335
_llseek(3, -28, [2307], SEEK_CUR)       = 0 //Lesestelle um 28 zurückschieben
read(3, "\nCET-1CEST,M3.5.0,M10.5.0/3\n", 4096) = 28 // die letzten 28 zeichen lesen
close(3)                                = 0 //Datei schließen
fstat64(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
write(1, "Wed Nov 16 16:17:26 2016\n", 25Wed Nov 16 16:17:26 2016) = 25 // Zeit/Datum auf Standardausgabe schreiben
exit_group(0)                           = ?
+++ exited with 0 +++
```

5.
Das Programm erzeut mit clone einen Neuen Prozess, in dem eine shell läuft(pid1924). Diese hat die Anweisung ls auszuführen, und das Ergebins nach /dev/null umzuleiten.

Dazu Klont das Programm sich zuerst, so dass es einen Kindprozess gibt (pid 1924). Darin wird dann execve aufgerufen, um die shell zu starten. Diese speichert sich dann den Filedescriptor der Standardausgabe, und öffnet /dev/null. Dann wird der Filedescriptor 1 mit dem von /dev/null ersetzt. Daraufhin klont sich auch dieser Prozess (pid 1925) und führt in dem Kindprozess ls aus. Nachdem ls beendet ist wird von der shell wieder 1 als Standardausgabe gesetzt. Danach beendet sich auch dieser Prozess. Jetzt ist auch das komplette Programm beendet.

Vor dem Klonen legen die Prozesse jeweils fest, dass SIGINT und SIGQUIT ab jetzt ignoriert werden sollen. Nachdem das Kind fertig ist wird dies wieder geändert.

```
rt_sigaction(SIGINT, {SIG_IGN, [], 0}, {SIG_DFL, [], 0}, 8) = 0
rt_sigaction(SIGQUIT, {SIG_IGN, [], 0}, {SIG_DFL, [], 0}, 8) = 0
rt_sigprocmask(SIG_BLOCK, [CHLD], [], 8) = 0
clone(child_stack=0, flags=CLONE_PARENT_SETTID|SIGCHLD, parent_tidptr=0xbfd78d30) = 1924
waitpid(1924, strace: Process 1924 attached
 <unfinished ...>
[pid  1924] rt_sigaction(SIGINT, {SIG_DFL, [], 0}, NULL, 8) = 0
[pid  1924] rt_sigaction(SIGQUIT, {SIG_DFL, [], 0}, NULL, 8) = 0
[pid  1924] rt_sigprocmask(SIG_SETMASK, [], NULL, 8) = 0
[pid  1924] execve("/bin/sh", ["sh", "-c", "ls / > /dev/null"], [/* 22 vars */]) = 0
[pid  1924] brk(NULL)                   = 0x8016a000
[pid  1924] access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
[pid  1924] mmap2(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb76e8000
[pid  1924] access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
[pid  1924] open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
[pid  1924] fstat64(3, {st_mode=S_IFREG|0644, st_size=37709, ...}) = 0
[pid  1924] mmap2(NULL, 37709, PROT_READ, MAP_PRIVATE, 3, 0) = 0xb76de000
[pid  1924] close(3)                    = 0
[pid  1924] access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
[pid  1924] open("/lib/i386-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
[pid  1924] read(3, "\177ELF\1\1\1\3\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0\320\207\1\0004\0\0\0"..., 512) = 512
[pid  1924] fstat64(3, {st_mode=S_IFREG|0755, st_size=1786484, ...}) = 0
[pid  1924] mmap2(NULL, 1792572, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xb7528000
[pid  1924] mprotect(0xb76d7000, 4096, PROT_NONE) = 0
[pid  1924] mmap2(0xb76d8000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1af000) = 0xb76d8000
[pid  1924] mmap2(0xb76db000, 10812, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0xb76db000
[pid  1924] close(3)                    = 0
[pid  1924] mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb770f000
[pid  1924] set_thread_area({entry_number:-1, base_addr:0xb770f940, limit:1048575, seg_32bit:1, contents:0, read_exec_only:0, limit_in_pages:1, seg_not_present:0, useable:1}) = 0 (entry_number:6)
[pid  1924] mprotect(0xb76d8000, 8192, PROT_READ) = 0
[pid  1924] mprotect(0x800dc000, 4096, PROT_READ) = 0
[pid  1924] mprotect(0xb7710000, 4096, PROT_READ) = 0
[pid  1924] munmap(0xb76de000, 37709)   = 0
[pid  1924] getuid32()                  = 1000
[pid  1924] getgid32()                  = 1000
[pid  1924] getpid()                    = 1924
[pid  1924] rt_sigaction(SIGCHLD, {0x800cb7f0, ~[RTMIN RT_1], 0}, NULL, 8) = 0
[pid  1924] geteuid32()                 = 1000
[pid  1924] brk(NULL)                   = 0x8016a000
[pid  1924] brk(0x8018b000)             = 0x8018b000
[pid  1924] getppid()                   = 1923
[pid  1924] stat64("/home/jannik/bspk2016/03_pk", {st_mode=S_IFDIR|0775, st_size=4096, ...}) = 0
[pid  1924] stat64(".", {st_mode=S_IFDIR|0775, st_size=4096, ...}) = 0
[pid  1924] geteuid32()                 = 1000
[pid  1924] getegid32()                 = 1000
[pid  1924] rt_sigaction(SIGINT, NULL, {SIG_DFL, [], 0}, 8) = 0
[pid  1924] rt_sigaction(SIGINT, {0x800cb7f0, ~[RTMIN RT_1], 0}, NULL, 8) = 0
[pid  1924] rt_sigaction(SIGQUIT, NULL, {SIG_DFL, [], 0}, 8) = 0
[pid  1924] rt_sigaction(SIGQUIT, {SIG_DFL, ~[RTMIN RT_1], 0}, NULL, 8) = 0
[pid  1924] rt_sigaction(SIGTERM, NULL, {SIG_DFL, [], 0}, 8) = 0
[pid  1924] rt_sigaction(SIGTERM, {SIG_DFL, ~[RTMIN RT_1], 0}, NULL, 8) = 0
[pid  1924] open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC|O_LARGEFILE, 0666) = 3
[pid  1924] fcntl64(1, F_DUPFD, 10)     = 10 //stdout fd duplizieren
[pid  1924] close(1)                    = 0
[pid  1924] fcntl64(10, F_SETFD, FD_CLOEXEC) = 0
[pid  1924] dup2(3, 1)                  = 1 //umleiten der Ausgabe nach /dev/null
[pid  1924] close(3)                    = 0
[pid  1924] stat64("/usr/local/sbin/ls", 0xbfa1284c) = -1 ENOENT (No such file or directory)
[pid  1924] stat64("/usr/local/bin/ls", 0xbfa1284c) = -1 ENOENT (No such file or directory)
[pid  1924] stat64("/usr/sbin/ls", 0xbfa1284c) = -1 ENOENT (No such file or directory)
[pid  1924] stat64("/usr/bin/ls", 0xbfa1284c) = -1 ENOENT (No such file or directory)
[pid  1924] stat64("/sbin/ls", 0xbfa1284c) = -1 ENOENT (No such file or directory)
[pid  1924] stat64("/bin/ls", {st_mode=S_IFREG|0755, st_size=129280, ...}) = 0
[pid  1924] clone(child_stack=0, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0xb770f9a8) = 1925
[pid  1924] wait4(-1, strace: Process 1925 attached
 <unfinished ...>



[pid  1925] execve("/bin/ls", ["ls", "/"], [/* 22 vars */]) = 0
[pid  1925] brk(NULL)                   = 0x8525000
[pid  1925] access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
[pid  1925] mmap2(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7737000
[pid  1925] access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
[pid  1925] open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
[pid  1925] fstat64(3, {st_mode=S_IFREG|0644, st_size=37709, ...}) = 0
[pid  1925] mmap2(NULL, 37709, PROT_READ, MAP_PRIVATE, 3, 0) = 0xb772d000
[pid  1925] close(3)                    = 0
[pid  1925] access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
[pid  1925] open("/lib/i386-linux-gnu/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
[pid  1925] read(3, "\177ELF\1\1\1\0\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0\240F\0\0004\0\0\0"..., 512) = 512
[pid  1925] fstat64(3, {st_mode=S_IFREG|0644, st_size=145384, ...}) = 0
[pid  1925] mmap2(NULL, 154580, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xb7707000
[pid  1925] mprotect(0xb7729000, 4096, PROT_NONE) = 0
[pid  1925] mmap2(0xb772a000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x22000) = 0xb772a000
[pid  1925] mmap2(0xb772c000, 3028, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0xb772c000
[pid  1925] close(3)                    = 0
[pid  1925] access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
[pid  1925] open("/lib/i386-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
[pid  1925] read(3, "\177ELF\1\1\1\3\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0\320\207\1\0004\0\0\0"..., 512) = 512
[pid  1925] fstat64(3, {st_mode=S_IFREG|0755, st_size=1786484, ...}) = 0
[pid  1925] mmap2(NULL, 1792572, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xb7551000
[pid  1925] mprotect(0xb7700000, 4096, PROT_NONE) = 0
[pid  1925] mmap2(0xb7701000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1af000) = 0xb7701000
[pid  1925] mmap2(0xb7704000, 10812, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0xb7704000
[pid  1925] close(3)                    = 0
[pid  1925] access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
[pid  1925] open("/lib/i386-linux-gnu/libpcre.so.3", O_RDONLY|O_CLOEXEC) = 3
[pid  1925] read(3, "\177ELF\1\1\1\0\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0\220\16\0\0004\0\0\0"..., 512) = 512
[pid  1925] fstat64(3, {st_mode=S_IFREG|0644, st_size=472368, ...}) = 0
[pid  1925] mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb775e000
[pid  1925] mmap2(NULL, 475320, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xb74dc000
[pid  1925] mmap2(0xb754f000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x72000) = 0xb754f000
[pid  1925] close(3)                    = 0
[pid  1925] access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
[pid  1925] open("/lib/i386-linux-gnu/libdl.so.2", O_RDONLY|O_CLOEXEC) = 3
[pid  1925] read(3, "\177ELF\1\1\1\0\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0000\n\0\0004\0\0\0"..., 512) = 512
[pid  1925] fstat64(3, {st_mode=S_IFREG|0644, st_size=13828, ...}) = 0
[pid  1925] mmap2(NULL, 16488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xb74d7000
[pid  1925] mmap2(0xb74da000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0xb74da000
[pid  1925] close(3)                    = 0
[pid  1925] access("/etc/ld.so.nohwcap", F_OK) = -1 ENOENT (No such file or directory)
[pid  1925] open("/lib/i386-linux-gnu/libpthread.so.0", O_RDONLY|O_CLOEXEC) = 3
[pid  1925] read(3, "\177ELF\1\1\1\0\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0\320O\0\0004\0\0\0"..., 512) = 512
[pid  1925] fstat64(3, {st_mode=S_IFREG|0755, st_size=134904, ...}) = 0
[pid  1925] mmap2(NULL, 115264, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xb74ba000
[pid  1925] mmap2(0xb74d3000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x18000) = 0xb74d3000
[pid  1925] mmap2(0xb74d5000, 4672, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0xb74d5000
[pid  1925] close(3)                    = 0
[pid  1925] mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb74b9000
[pid  1925] mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb74b8000
[pid  1925] set_thread_area({entry_number:-1, base_addr:0xb74b9b00, limit:1048575, seg_32bit:1, contents:0, read_exec_only:0, limit_in_pages:1, seg_not_present:0, useable:1}) = 0 (entry_number:6)
[pid  1925] mprotect(0xb7701000, 8192, PROT_READ) = 0
[pid  1925] mprotect(0xb74d3000, 4096, PROT_READ) = 0
[pid  1925] mprotect(0xb74da000, 4096, PROT_READ) = 0
[pid  1925] mprotect(0xb754f000, 4096, PROT_READ) = 0
[pid  1925] mprotect(0xb772a000, 4096, PROT_READ) = 0
[pid  1925] mprotect(0x8067000, 4096, PROT_READ) = 0
[pid  1925] mprotect(0xb775f000, 4096, PROT_READ) = 0
[pid  1925] munmap(0xb772d000, 37709)   = 0
[pid  1925] set_tid_address(0xb74b9b68) = 1925
[pid  1925] set_robust_list(0xb74b9b70, 12) = 0
[pid  1925] rt_sigaction(SIGRTMIN, {0xb74be9e0, [], SA_SIGINFO}, NULL, 8) = 0
[pid  1925] rt_sigaction(SIGRT_1, {0xb74bea60, [], SA_RESTART|SA_SIGINFO}, NULL, 8) = 0
[pid  1925] rt_sigprocmask(SIG_UNBLOCK, [RTMIN RT_1], NULL, 8) = 0
[pid  1925] ugetrlimit(RLIMIT_STACK, {rlim_cur=8192*1024, rlim_max=RLIM_INFINITY}) = 0
[pid  1925] uname({sysname="Linux", nodename="jb-ltw550s", ...}) = 0
[pid  1925] statfs64("/sys/fs/selinux", 84, 0xbfa8c6f8) = -1 ENOENT (No such file or directory)
[pid  1925] statfs64("/selinux", 84, 0xbfa8c6f8) = -1 ENOENT (No such file or directory)
[pid  1925] brk(NULL)                   = 0x8525000
[pid  1925] brk(0x8546000)              = 0x8546000
[pid  1925] open("/proc/filesystems", O_RDONLY|O_LARGEFILE) = 3
[pid  1925] fstat64(3, {st_mode=S_IFREG|0444, st_size=0, ...}) = 0
[pid  1925] read(3, "nodev\tsysfs\nnodev\trootfs\nnodev\tr"..., 1024) = 364
[pid  1925] read(3, "", 1024)           = 0
[pid  1925] close(3)                    = 0
[pid  1925] open("/usr/lib/locale/locale-archive", O_RDONLY|O_LARGEFILE|O_CLOEXEC) = 3
[pid  1925] fstat64(3, {st_mode=S_IFREG|0644, st_size=4570528, ...}) = 0
[pid  1925] mmap2(NULL, 2097152, PROT_READ, MAP_PRIVATE, 3, 0) = 0xb72b8000
[pid  1925] mmap2(NULL, 323584, PROT_READ, MAP_PRIVATE, 3, 0x2cc000) = 0xb7269000
[pid  1925] mmap2(NULL, 4096, PROT_READ, MAP_PRIVATE, 3, 0x458000) = 0xb7736000
[pid  1925] close(3)                    = 0
[pid  1925] ioctl(1, TCGETS, 0xbfa8c37c) = -1 ENOTTY (Inappropriate ioctl for device)
[pid  1925] ioctl(1, TIOCGWINSZ, 0xbfa8c454) = -1 ENOTTY (Inappropriate ioctl for device)
[pid  1925] stat64("/", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
[pid  1925] open("/", O_RDONLY|O_NONBLOCK|O_LARGEFILE|O_DIRECTORY|O_CLOEXEC) = 3
[pid  1925] fstat64(3, {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
[pid  1925] getdents64(3, /* 26 entries */, 32768) = 680
[pid  1925] getdents64(3, /* 0 entries */, 32768) = 0
[pid  1925] close(3)                    = 0
[pid  1925] fstat64(1, {st_mode=S_IFCHR|0666, st_rdev=makedev(1, 3), ...}) = 0
[pid  1925] ioctl(1, TCGETS, 0xbfa89ebc) = -1 ENOTTY (Inappropriate ioctl for device)
[pid  1925] write(1, "bin\nboot\ndev\netc\nhome\ninitrd.img"..., 141) = 141
[pid  1925] close(1)                    = 0
[pid  1925] close(2)                    = 0
[pid  1925] exit_group(0)               = ?
[pid  1925] +++ exited with 0 +++
[pid  1924] <... wait4 resumed> [{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0, NULL) = 1925
[pid  1924] --- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=1925, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
[pid  1924] sigreturn({mask=[]})        = 1925
[pid  1924] dup2(10, 1)                 = 1
[pid  1924] close(10)                   = 0
[pid  1924] exit_group(0)               = ?
[pid  1924] +++ exited with 0 +++
<... waitpid resumed> [{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0) = 1924
rt_sigaction(SIGINT, {SIG_DFL, [], 0}, NULL, 8) = 0
rt_sigaction(SIGQUIT, {SIG_DFL, [], 0}, NULL, 8) = 0
rt_sigprocmask(SIG_SETMASK, [], NULL, 8) = 0
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=1924, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
exit_group(1)                           = ?
+++ exited with 1 +++
```
