all:
	g++ -std=c++11  Display.cpp Camera.cpp Split.cpp App.cpp main.cpp TextureManager.cpp `pkg-config --cflags --libs opencv` -lGL -lglut -lGLU -lfreeimage -o huesos.out