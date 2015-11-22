kawaii: game.o main.o hud.o movement.o player.o world.o
	g++ game.o main.o hud.o movement.o player.o world.o -w -lSDL2 -o kawaii
main.o: main.cpp game.h
	g++ -c main.cpp
game.o: game.cpp game.h hud.h movement.h player.h
	g++ -c game.cpp
hud.o: hud.cpp hud.h
	g++ -c hud.cpp
movement.o: movement.cpp movement.h
	g++ -c movement.cpp
player.o: player.cpp player.h
	g++ -c player.cpp
world.o: world.cpp world.h
	g++ -c world.cpp
clean:
	rm -f *.o
	rm kawaii
