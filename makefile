EXECUTABLES := L10 L11
CXX := g++

all: compile

compile: 
	${CXX} -o L10 L10.cpp
	${CXX} -o L11 L11.cpp

clean:
	rm -f $(EXECUTABLES)