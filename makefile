kawaii: game.o main.o hud.o movement.o player.o world.o display.o texture.o textTexture.o tile.o camFocus.o collision.o collideBox.o
	g++ game.o main.o hud.o movement.o player.o world.o display.o texture.o textTexture.o tile.o camFocus.o collision.o collideBox.o -w -lSDL2 -lSDL2_image -lSDL2_ttf -o kawaii
main.o: main.cpp game.h
	g++ -c main.cpp
display.o: display.cpp display.h 
	g++ -c display.cpp
game.o: game.cpp game.h hud.h movement.h player.h display.h texture.h textTexture.h tile.h world.h camFocus.h collision.h
	g++ -c game.cpp
hud.o: hud.cpp hud.h
	g++ -c hud.cpp
movement.o: movement.cpp movement.h
	g++ -c movement.cpp
player.o: player.cpp player.h collision.h collideBox.h
	g++ -c player.cpp
world.o: world.cpp world.h tile.h
	g++ -c world.cpp
texture.o: texture.cpp texture.h display.h
	g++ -c texture.cpp
textTexture.o: textTexture.cpp textTexture.h display.h
	g++ -c textTexture.cpp
tile.o: tile.cpp tile.h display.h texture.h collideBox.h
	g++ -c tile.cpp
camFocus.o: camFocus.cpp camFocus.h player.h world.h
	g++ -c camFocus.cpp
collision.o: collision.cpp collision.h world.h player.h collideBox.h
	g++ -c collision.cpp
collideBox.o: collideBox.cpp collideBox.h
	g++ -c collideBox.cpp
clean:
	rm -f *.o
	rm kawaii
