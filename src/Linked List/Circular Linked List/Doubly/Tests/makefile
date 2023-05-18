CC = g++
CFLAGS = -I -Wall -Wextra -pedantic-errors
OBJFILES = CircularDoublyLinkedListTests.o
TARGET = structureTests

$(TARGET): $(OBJFILES) 
	$(CC) $(CFLAGS) $(OBJFILES) -o $(TARGET)

CircularDoublyLinkedListTests.o: CircularDoublyLinkedListTests.cpp 
	$(CC) $(CFLAGS) -c -g -fconcepts CircularDoublyLinkedListTests.cpp

clean:
	rm *.o $(TARGET)