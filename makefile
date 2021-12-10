CC = g++

gamefile = main.cpp

ifdef OS
	   exe = flappybird.exe

	   comp = -Lwindows -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lsoil2 -o

	   inc = -Ilibraries/include
else
	   ifeq ($(shell uname), Linux)
		  exe = flappybird.exe 

		  comp = ./libraries/lib/glfw3.lib ./libraries/lib/soil2.lib -lGl -o
	   endif
endif

all:
	$(CC) $(gamefile) $(comp) $(exe) 

run: 
	./$(exe)

clean:
	rm -f flappybird.exe