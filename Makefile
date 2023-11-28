CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

quiz.exe: quiz.o
	$(CC) $(CFLAGS) quiz.o -o quiz.exe

quiz.o: quiz.cpp
	$(CC) $(CFLAGS) quiz.cpp -c 

clean:
	rm -f *.o quiz *.exe
