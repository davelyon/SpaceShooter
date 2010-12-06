all:
	g++ Parser/*.cpp *.cpp -o fly -lSDL -lGL -lGLU -lSDL_net -lSDL_image -lSDL_ttf -g
	g++ Actor.cpp Server/Enemy.cpp Parser/Parser.cpp Server/Server.cpp -o Server/run -lSDL_net -g -lGL -lSDL_image -lSDL -lGLU -lSDL_ttf
server:
	g++ Actor.cpp Server/Enemy.cpp Parser/Parser.cpp Server/Server.cpp -o Server/run -lSDL_net -lGL -lSDL_image -lSDL -lGLU -lSDL_ttf
