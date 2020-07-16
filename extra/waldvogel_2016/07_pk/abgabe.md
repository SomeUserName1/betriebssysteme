# Lösungen zum 7\. Übungsblatt

# Bamberger, Jannik und Klopfer, Fabian

```
/**
 * @author Jannik Bamberger
 * @author Fabian Klopfer
 * @credits 9.5
 */
```

## Aufgabe 2: Immer wieder Pointer

1. Es wird ein Array "string" der länge 7 mit dem String ``Foobar\0`` initialisiert.
2. Es wird ein konstanter **Der Pointer ist nicht const (-.5)** char Pointer "string" initialisiert, der auf den konstanten String ``Foobar\0`` zeigt.
3. Wenn der String verändert werden soll, dann muss die erste Variante verwendet werden. Dabei wird eine Kopie des Strings im Speicher des Programms abgelegt. Daher ist es besser den konstanten Pointer zu verwenden wenn die Werte sowieso nicht verändert werden. Somit wird Speicher gespart.
4. Die Zeile ist valide, aber es ist in string kein valider String enthalten, da das Nullzeichen fehlt.
5. Bei 5. wird eine Kopie im beschreibbaren Speicher des Programms abgelegt. Da der Pointer aber konstant **Siehe oben** ist kann dieser Speicher trotzdem nicht direkt beschrieben werden. 1. und 5. sind valide Strings. Bei 5. wird bis es 20 Zeichen sind mit ``\0`` aufgefüllt. Bei 4. Fehlt das Nullzeichen, somit ist es kein valider String.
6. Bei 6. steht ``Foobat`` in dem Array und die Initialisirung ist valide. Bei 6. fehlt das Nullzeichen, bei 5. nicht. Es kann auf beide gleich zugegriffen werden. Stringverarbeitende Funktionen funktionieren auf 6. nicht.

> Schaut euch den Unterschied zwischen const char *c und char * const c an
