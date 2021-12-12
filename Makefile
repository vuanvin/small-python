CC = gcc -pthread
CXX = g++ -pthread
CXXFLAG = -g -Wall

SOURCE_FILES = src/*.cpp

all:
	$(CXX) $(CXXFLAG) $(SOURCE_FILES) -o python

clean:
	rm -rf src/*.o src/python