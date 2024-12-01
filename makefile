# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
all: clean bin compile link run

clean: 
	rm -f bin/*.o bin/test

bin:
	mkdir -p bin

compile:
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Actions.o src/Action.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Simulation.o src/Simulation.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/SelectionPolicy.o src/SelectionPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Facility.o src/Facility.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Settlement.o src/Settlement.cpp

link:
	g++ -o bin/main bin/main.o bin/Action.o bin/Simulation.o bin/SelectionPolicy.o bin/Facility.o bin/Settlement.o

run:
	./bin/main