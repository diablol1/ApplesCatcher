COMPILER = g++
LINKER = g++
COMPILER_PARAMS = -std=c++11
LINKER_PARAMS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

OBJS = obj/main.o obj/Apple.o obj/CurrentScoreLabel.o obj/Game.o obj/HighScoreLabel.o obj/Label.o obj/Player.o obj/SceneManager.o obj/TextureManager.o obj/Menu.o obj/SoundManager.o

all: ApplesCatcher

ApplesCatcher: $(OBJS)
	$(LINKER) -o $@ $^ $(LINKER_PARAMS)

obj/%.o: src/%.cpp
	$(COMPILER) -c -o $@ $< $(COMPILER_PARAMS)

setup:
	mkdir obj

run:
	./ApplesCatcher

clean:
	rm ApplesCatcher
	rm obj/*

