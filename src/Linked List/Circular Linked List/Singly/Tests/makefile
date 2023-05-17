CC = g++
CFLAGS = -I -Wall -Wextra -pedantic-errors
OBJFILES = CircularSinglyLinkedListTests.o
TARGET = structureTests

$(TARGET): $(OBJFILES) 
	$(CC) $(CFLAGS) $(OBJFILES) -o $(TARGET)

CircularSinglyLinkedListTests.o: CircularSinglyLinkedListTests.cpp 
	$(CC) $(CFLAGS) -c -g -fconcepts CircularSinglyLinkedListTests.cpp

clean:
	rm *.o $(TARGET)

