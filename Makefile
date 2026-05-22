CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = mysh
SRCS = src/shell.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)