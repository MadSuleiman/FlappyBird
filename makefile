CC = g++

gamefile = flappybird.cpp

ifdef OS
	   exe = -o flappybird.exe

	   comp = -Lwindows -lsoil2-debug -lglfw3 -lglew32 -lopengl32 -lgdi32 -lglu32

	   inc = glad.c
else
	   ifeq ($(shell uname), Linux)
		  exe = -o flappybird.o 

		  comp = -Lwindows -lsoil2-debug -lglfw3 -lglew32 -lopengl32 -lgdi32 -lglu32

		  inc = glad.c
		else
			exe += -o flappybird.o

			comp += -Lmac -lsoil2-debug -framework Cocoa -framework IOKit -lglfw3arm -framework GLUT -framework OpenGL 
			
			inc += glad.c
		  
	   endif
	   
endif

all:
	$(CC) $(gamefile) $(exe) $(inc) $(comp)

run: 
	./$(exe)

clean:
	rm -f flappybird.exe
