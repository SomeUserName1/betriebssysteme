# Lösungen zum 12\. Übungsblatt

```
/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 */
 ```

## Aufgabe 2: Frage 1 (5/5)
- Wenn ``SIGALRM`` blockiert ist, wird  ``sleep1()`` nicht funktionieren, da das Alarmsignal einfach ignoriert wird.
- Wenn der Alarm vor ``pause()`` fertig wird (z.B. falls der Prozess keine Rechenzeit mehr hat), dann wird das Signal zwar behandlet, aber mit ``pause()`` wird dann auf ein weiteres Signal gewartet.
- falls bereits ein Alarmhandler installiert war, wird dieser nicht wiederhergestellt. Es gehen also alle weiteren ``SIGALRM`` verloren, da sie von dem neuen Alarmhandler einfach ignoriert werden.
