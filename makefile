CC = g++

gamefile = flappybird.cpp

ifdef OS
	   exe = -o flappybird.exe

	   comp = -Lwindows -lsoil2-debug -lglfw3 -lglew32 -lopengl32 -lgdi32 -lglu32

	   inc = glad.c
else
	   ifeq ($(shell uname), Linux)
		  exe = flappybird.exe 

		  comp = ./libraries/lib/glfw3.lib ./libraries/lib/soil2.lib -lGl -o
	   endif
endif

all:
	$(CC) $(gamefile) $(exe) $(inc) $(comp)

run: 
	./$(exe)

clean:
	rm -f flappybird.exe