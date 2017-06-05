CC=gcc
CXX=g++
RM=rm -f
LDLIBS= -lglfw -lGLEW -lGL 

SRCS= $(wildcard *.cpp) $(wildcard loaders/*.cpp)
OBJS=$(subst .cc,.o,$(SRCS))

all: jogo

jogo: $(OBJS)
	$(CXX) -o jogo $(OBJS) $(LDLIBS)  

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) 
