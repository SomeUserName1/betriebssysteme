# Answers

1. ./mem 1  
  An den cpu statisiken konnte man ablesen, dass die user-time von  ca 1% auf 13% ansteigt und die zeit im kernel-modus von 0% auf 1% steigt. Cpu idle war davor ca. 98%, danach knapp 86 %.
  Dies ist zu erwarten bei einem Mehrprozessorsystem. 13 % User-time bei 8 logischen kernen bedeutet, dass einer von den 8 ständig rechnet (100/8=12,5). Bei zwei Instanzen verdoppelt sich die Veränderung der Werte.
  Auf dem Container dagegen steigt die zeit im user mode von 13 - 15% auf ca 50% an, wobei die Zeit im kernel mode sich nicht merkbar veraendert. Mehrere Instanzen haben die statistiken kaum merkbar veraendert. User Zeit blieb bei ca 50% und kernel zeit bei 0 - 5%.

2. ./mem 1024  
  Bei einem Aufruf mit 1024 bleibt swpd unverändert bei 0. Free verkleinert sich um das erwartete 1 GB und kehrt nach dem beenden von mem zum ausgangswert zurück. Auf dem Container ergab sich ebenfalls nichts Ueberraschendes.

3. ./mem 7000  
  Um den swap zu benutzen muss der ganze ram des systems verbraucht sein, in meinem fall musste ich etwas weniger als 7 gb benutzen damit si/so != 0 sind. In der ersten loop wird der ganze restliche speicher alloziert (bis auf knapp 150 mb) und sobald dieser leer ist wird ausgeswaped, was sich in intervallen wiederholt. Eingeswaped wird unmittelbar danach, wobei in jeder loop eingeswaped wird, aber nur alle paar loops ausgelagert wird. Merkwürdiger weise sind das immer ein paar hundert bytes ausser wenn ausgelagert wird, dann sind es ein paar tausend bytes.
  Auf dem Container war gut zu beobachten dass erst nach der ersten loop eingelagert wird, davor wird eigentlich nur ausgelagert.

4.  Die cpu statistiken unterscheiden sich nur beim ein-/auslagern von denen, welche mit wenig allokation entstanden: es wird dann auf meinem system ca. 6% der zeit im kernel modus verbracht.
  Auf dem Container war ausserdem gut zu sehen, dass block out von io und swap out miteinander ansteigen.

5.  (Graph siehe src ordner)  
  Bei in den ram passenden mengen liegt die performace auf meinem system bei ca 5,5 gb/s. Sobald der speicher allerdings nicht mehr reicht (allokation von 8 gb bei 8 gb ram), sinkt die performance auf knapp 2 gb/s in der ersten loop, und dann auf 300 mb/s mit abnehmender tendenz. Auffaellig ist, dass die erste loop eine konstante performace liefert. Die unterschiede machen sich erst ab loop 1 bemerkbar.

6.  Es ist anscheinend nicht möglich mehr speicher zu allozieren, als ram da ist, da alle aufrufe mit mehr als 8 gb bei mir zu speicherzugriffsfehlern führten. Die Grenze lag auf meinem System bei etwa 8190 kB.

7.  Da wir weder ein RAID Array noch eine SSD zu viel hatten, haben wir einen usb-stick als swap genommen. Im Vergleich zum swap auf der internen SSD war dieser sehr viel langsamer (gerundet auf ganze mb/s):
  - usb swap:   loop 0: 25  mb/s; loop 1: 5 mb/s
  - intern ssd: loop 0: 500 mb/s; loop 1: 26 mb/s
