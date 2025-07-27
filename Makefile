CXX = g++
CXXFLAGS = -std=c++11 -I./raylib/include
LDFLAGS = -L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm

SAUCE = src/*.cpp
APP = -o platformer.exe

build: 
	$(CXX) $(SAUCE) $(CXXFLAGS) $(LDFLAGS) $(APP)

run: build
	./platformer.exe