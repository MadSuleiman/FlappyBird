SOURCES := $(shell echo $(./)*.cpp)
DEPENDS = $(SOURCES:.h=.o)
OBJECTS = $(SOURCES:.cpp=.d),$(SOURCES:.c=.d)
OS = $(shell uname) # For Mac OS detection
PROGRAM = flappybird

OPTFLAGS = -g
CC=gcc
CFLAGS   = -w $(OPTFLAGS) -ISOIL/includes -std=c++11 -pthread

all: $(PROGRAM)

$(PROGRAM):$(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJECTS) $(DEPENDS)
	$(RM) $(PROGRAM)
	$(RM) *~


%.o: %.h
	$(CC) -c $(CFLAGS) $< -o $@

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< > $@