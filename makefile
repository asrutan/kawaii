kawaii: game.o main.o hud.o
	g++ game.o main.o hud.o -w -lSDL2 -o kawaii
main.o: main.cpp game.h
	g++ -c main.cp
game.o: game.cpp game.h hud.h
	g++ -c game.cpp
hud.o: hud.cpp hud.h
	g++ -c hud.cpp
clean:
	rm -f *.o
	rm kawaii
