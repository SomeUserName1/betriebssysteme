# Answers

1.  Der Kindsprozess beinhaltet den selben Wert der Variablen x wie der
    Elternprozess. Beide können unabhänig voneinander den Wert von x verändern
    ohne das dabei die Variable des anderen dabei überschrieben wird.

2.  Der Eltern- sowie Kindsprozess haben beide Zugriff auf den Dateideskriptor,
    welcher von `open()` zurückgeleifert wurde. Beide Prozesse haben somit die
    Möglichkeit in die geöffnete Datei zu schreiben. Versuchen jedoch beide
    Prozesse zeitgleich in die Datei zu schreiben, überschreibt der letztere
    Prozess der beiden, möglicherweiße den Wert des anderen.

3.  Man kann `wait()` auch durch `sleep()` ersetzen, jedoch ist damit nicht
    sicher gestellt, dass das gewünschte Verhalten (erst Kindsprozess ausführen,
    dann Elternprozess ausführen) auf einem beliebigen System auftritt,
    da es durch Performanceunterschiede auf einem System funktionieren kann, auf
    einem anderen jedoch nicht.

    Es wäre auch möglich `waitpid()` anstatt `wait()` zu verwenden.

4.  Weil es flexibler ist, als immer nur einen `exec()`-Aufruf zu verwenden.

5.  `wait()` gibt bei erfolgreicher Ausführung die `PID` des terminierten
    Kindsprozesses zurück, im Fehlerfall wird `-1` zurückgegeben.

    Wenn man im Kindsprozess `wait()` aufruft, so schlägt der Aufruf fehl und
    `wait()` liefert den Rückgabewert `-1` zurück.

6.  `wait()` wartet auf ein beliebiges Kind, wohingegen `waitpid()` auf einen
    bestimmten Prozess (spezifiziert mit der PID) wartet.

7. Wenn der Kindsprozess mittels `close(STDOUT_FILENO)` die Standardausgabe
   geschlossen hat und anschließend versucht wird mittels `printf(...)` etwas
   auszugeben, ist die spezifizierte Nachricht nicht in der Konsole zu sehen.
   Dies erscheint logisch, da zuvor die Standardausgabe geschlossen wurde.
