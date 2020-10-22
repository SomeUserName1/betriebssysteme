# Lösungen zum 10\. Übungsblatt

# Bamberger, Jannik und Klopfer, Fabian

## Aufgabe 1: ???

```
/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 10
 */
```

``seq`` erzeugt als Ausgabe eine aufsteigende Sequenz von Zahlen, jeweils getrennt duch ein Newline Zeichen (etwa ``seq 5 -> "1\n2\n3\n4\n5\n"``). Diese Eingabe wird in das Shellskript gepipt, daher ist es die Standardeingabe für dieses. Jeztz liest das erste Kommando (``head >/dev/null``) 8192 Zeichen von der Eingabe (In strace ``read(0, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14"..., 8192) = 8192``). Davon nimmt head die ersten 10 Zeilen (Standard ohne Parameter), also 21 Bytes/Zeichen und schreibt diese nach /dev/null. Jetzt versucht head, die zu viel gelesen Zeichen wieder "zurückzugeben", indem lseek benutzt wird um die Schreib/Leseposition um 8192-21 = 8171 nach links zu verschieben (``lseek(0, -8171, SEEK_CUR)   = -1 ESPIPE (Illegal seek)``). Dies schlägt aber fehl, da aus der Pipe nur einmal gelesen werden kann. Es bleibt also in der Pipe ``"\n1861\n1862\n..."`` (Anstatt den Punkten die Zahlen bis 100000) stehen. Das liegt daran, dass 8192 Zeichen genau die Zahlen bis 1860 sind (Es werden immer die Ziffern und ein Newline pro Zahl benötigt. 0-9 brauchen je 2 Zeichen, 10 - 99 je 3, 100 - 999 je 4 und 1000 - 9999 je 5). Es werden also die ersten Zahlen (1-9) gelesen, was 18 Zeichen verbraucht. Dann werden die nächsten 90 Zahlen gelesen (10 - 99) was 270 Zeichen verbraucht. Die nächsten 900 (100-999) brauchen 3600 Zeichen. Es werden jetzt noch 8192-(18+270+3600) = 4304 weitere Zeichen gelesen. Bisher wurden alle Zahlen bis einschließlich 999 gelesen. Alle weiteren Zahlen die gelesen Werden sind 5 Zeichen lang. Damit werden 4304 / 5 = 860 Rest 4 Weitere Zahlen gelesen und es bleiben noch 4 Zeichen übrig. Somit sind jetzt alle Zahlen bis einschließlich 1859 gelesen. Die übrigen 4 Zeichen sind genau die Ziffern der 1860. Das letzte Newline-Zeichen bleibt also stehen. Jetzt ist das erste Kommando fertig, und head wird mit der übrigen pipe aufgerufen. Dieses liest wieder 8192 Bytes und schreibt die ersten zehn Zeilen. Das sind das übrige Newline und die Zahlen die nach 1860 kommen, also 1861, 1862, ... , 1869.
