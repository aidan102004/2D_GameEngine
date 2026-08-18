all:
	g++ -I src/include -L src/lib -o main src/main.cpp src/game.cpp src/texturemanager.cpp src/gameobject.cpp src/map.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image