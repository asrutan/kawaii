kawaii: game.o main.o hud.o movement.o player.o world.o display.o texture.o textTexture.o
	g++ game.o main.o hud.o movement.o player.o world.o display.o texture.o textTexture.o -w -lSDL2 -lSDL2_image -lSDL2_ttf -o kawaii
main.o: main.cpp game.h
	g++ -c main.cpp
display.o: display.cpp display.h 
	g++ -c display.cpp
game.o: game.cpp game.h hud.h movement.h player.h display.h texture.h textTexture.h
	g++ -c game.cpp
hud.o: hud.cpp hud.h
	g++ -c hud.cpp
movement.o: movement.cpp movement.h
	g++ -c movement.cpp
player.o: player.cpp player.h
	g++ -c player.cpp
world.o: world.cpp world.h
	g++ -c world.cpp
texture.o: texture.cpp texture.h display.h
	g++ -c texture.cpp
textTexture.o: textTexture.cpp textTexture.h display.h
	g++ -c textTexture.cpp
clean:
	rm -f *.o
	rm kawaii
