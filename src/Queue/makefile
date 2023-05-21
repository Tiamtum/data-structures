CC = g++
CFLAGS = -Wall -Wextra -pedantic-errors
OBJFILES = main.o
DEPS = Queue.hpp 
TARGET = program 

$(TARGET): $(OBJFILES) $(DEPS)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(TARGET)

main.o: main.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -g -fconcepts main.cpp

clean:
	rm *.o $(TARGET) cachegrind.out.*

leak_check:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

cachegrind:
	valgrind --tool=cachegrind --branch-sim=yes ./$(TARGET)
