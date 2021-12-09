CC = g++

gamefile = main.cpp

ifdef OS
	   exe = flappybird.exe

	   comp = -glfw3 -SOIL -opengl32 -o
else
	   ifeq ($(shell uname), Linux)
		  exe = flappybird.exe 

		  comp = ./libraries/lib/glfw3.lib ./libraries/lib/SOIL2.lib -lGl -o
	   endif
endif

all:
	$(CC) $(gamefile) $(comp) $(exe) 

run: 
	./$(exe)

clean:
	rm -f flappybird.exe