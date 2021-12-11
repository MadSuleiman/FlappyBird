CC = g++

gamefile = main.cpp

ifdef OS
	   exe = flappybird.exe

	   comp = -Lwindows -lglfw3 -lsoil2 -lglew32 -lopengl32 -lglu32 -lgdi32 -o

	   inc = glad.c pipes.cpp bird.cpp ground.cpp shaderClass.cpp
else
	   ifeq ($(shell uname), Linux)
		  exe = flappybird.exe 

		  comp = ./libraries/lib/glfw3.lib ./libraries/lib/soil2.lib -lGl -o
	   endif
endif

all:
	$(CC) $(gamefile) $(comp) $(exe) $(inc)

run: 
	./$(exe)

clean:
	rm -f flappybird.exe