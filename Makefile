prog: main.o executive.o game.o player.o ship.o
	g++ -std=c++17 -g -Wall main.o executive.o game.o player.o ship.o -o prog

main.o: main.cpp executive.h game.h player.h ship.h
	g++ -std=c++17 -g -Wall -c main.cpp

executive.o: executive.h executive.cpp
	g++ -std=c++17 -g -Wall -c executive.cpp

game.o: game.h game.cpp
	g++ -std=c++17 -g -Wall -c game.cpp

player.o: player.h player.cpp
	g++ -std=c++17 -g -Wall -c player.cpp

ship.o: ship.h ship.cpp
		g++ -std=c++17 -g -Wall -c ship.cpp

clean:
	rm *.o prog
