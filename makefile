.PHONY: all

all: Billard

Billard: main.o verlet.o runge_kutta.o
	g++ $^ -o $@

main.o: main.cpp particle.h verlet.h runge_kutta.h
	g++ -c $< -o $@

verlet.o: verlet.cpp verlet.h particle.h
	g++ -c $< -o $@

runge_kutta.o: runge_kutta.cpp runge_kutta.h particle.h
	g++ -c $< -o $@

.PHONY: run

run: 
	make all
	./Billard

.PHONY: clean
clean:
	rm -f *.o *Pos* *~ Ergebnis* Billard
