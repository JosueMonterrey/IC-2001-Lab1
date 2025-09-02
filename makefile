EXECUTABLES := L10 L11_SLL L11_SKP
CXX := g++

all: compile

compile: 
	${CXX} -o L10 L10.cpp
	${CXX} -o L11_SLL L11_LinkedList.cpp
	${CXX} -o L11_SKP L11_SkippedList.cpp

clean:
	rm -f $(EXECUTABLES)