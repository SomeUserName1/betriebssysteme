# Übungsblatt 5
# Fabian Klopfer & Jannik Bamberger


## Aufgabe 1: Finde den Fehler

fehler-1.c:
 + **Korrekt?** Nein, es hatte keinen Platz für '\0' am Ende. Deshalb kann printf über die Arraygrenze hinauslaufen, da ein '\0' erwartet wird. **Lesbar?** Da es nur 3 Zeilen sind, ja; sehr weit eingerückt und checkpatch Konventionen nicht beachtet (Details siehe Kommentare).
 + Was ist die erwartete Ausgabe? ```Network```  

fehler-2.c:
 + **Korrekt?** Nein, die Stringgröße war falsch (11 statt 25) (=> gibt Compilerwarnung und es fehlt '\0') **Lesbar?** Gleiche Fehler wie in fehler-1.c.
 + Was ist die erwartete Ausgabe? ```Ich liebe Zeichenketten!```

fehler-3.c:
 + **Korrekt?** Nein, der Pointer ptr sollte const sein, da Stringliterale nicht modifiziert werden können. In printf sollte vermutlich %c stehen damit ein einzelner Buchstabe anstatt dessen dezimaler Wert ausgegeben wird. **Lesbar?** Wie bei fehler-1.c, Zugirff auf den Pointer nicht intuitiv. Es ist besser ptr[3] anstatt 3[ptr] zu schreiben.
 + Was ist die erwartete Ausgabe?  ```X ```

fehler-4.c:
 + **Korrekt?** Nein, durch das Vorkommen von nul im String wird alles nach nul nicht mehr ausgegeben. **Lesbar?** wie bei fehler-1.c
 + Was ist die erwartete Ausgabe?  
 ```
 Uni Konstanz i
 Uni Konstanz i
 13 8
 ```

fehler-5.c:
 + **Korrekt?** Ja. **Lesbar?** Undeutlich, was bei der Pointerarithmentik passiert. Es ist deutlich einfacher möglich, das Gleiche zu erreichen. Code-Style hat die gleichen Fehler wie fehler-1.c.
 + Was ist die erwartete Ausgabe? Zweites und letztes Element von a: ```2 5```

fehler-6.c:
 + **Korrekt?** Arraylänge ist zu groß gewählt. Es werden nur 8 Plätze für die angegebenen Werte benötigt. Der Rest wird mit 0 gefüllt. **Lesbar?** Arrayzugriff sehr umständlich ausgedrückt.
 + Was ist die erwartete Ausgabe? Siebtes Element des Arrays: ```9```

fehler-7.c:
 + **Korrekt?** Ja, falls die Größe eines ints entsprechend klein ist. Falls diese zu groß ist, ist das Verhalten undefiniert. **Lesbar?** Wie fehler-1.c und die Zuweisung von t kann übersichtlicher gestaltet werden.
 + Was ist die erwartete Ausgabe? Der sizeof(int)te String wird ausgegeben. ```gh```  


## Aufgabe 2: Schwupp?
1. In den Kommentaren beantwortet.
2. Es muss in der Schleife geprüft werden, ob das Ende des Strings erreicht ist. Ansonsten wird auch der Datenbereich hinter dem Array modifiziert.
