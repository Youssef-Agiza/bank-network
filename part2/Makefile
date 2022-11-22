# makefie for the files in this directory:server.cpp and client.cpp

# The compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -std=c++11 -pthread

# the build target executable:
TARGET = server client



all: $(TARGET)
	


server: server.cpp
	$(CC) $(CFLAGS) -o server server.cpp

client: client.cpp
	$(CC) $(CFLAGS) -o client client.cpp

clean:
	$(RM) $(TARGET)
