Erläuterung zum Programm: 

Dieses Programm simuliert die Bewegung und das Zusammenstoßen von Billardkugel und
plottet, falls gewünscht, den Verlauf. 
Beim Testen des Programms habe ich meist folgende Einstellung benutzt:
Zeitschritt = 0.01 
Anzahl der Zeitschritte = 500

Die Abstoßungskräfte sind abhängig vom Abstand, treten jedoch erst auf bei echter 
Berührung der Kugeln mit anderen Kugel oder mit der Wand. 
Die Kraft ist dabei:
F_Kugeln = c*pow(2*radius/Abstand, 13);
F_Wand = c*pow(2*radius/(Abstand_zur_Wand+radius), 13);

Es wird der Verlet-Störmer und das Runge-Kutta Verfahren zur Berechnung verwendet.
Dazu eine Anmerkung:
Beim Verlet-Störmer wird die Reibungskraft in der calc_force Funktion subtrahiert.
Beim Runge-Kutta ist die Reibungskraft in der Differentialgleichung eingebettet: m*a = -D*v + F


Aufbau der Startdatei (Alle Werte können verändert werden):

Anzahl_der_Kugeln
Radius
Länge_x(Billardtisch)
Höhe_y(Billardtisch)
Masse Pos_x Pos_y Vel_x Vel_y
...

