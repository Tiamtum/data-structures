CC = g++
CFLAGS = -I -Wall -Wextra -pedantic-errors
OBJFILES = DoublyLinkedListTests.o
TARGET = structureTests

$(TARGET): $(OBJFILES) 
	$(CC) $(CFLAGS) $(OBJFILES) -o $(TARGET)

DoublyLinkedListTests.o: DoublyLinkedListTests.cpp 
	$(CC) $(CFLAGS) -c -g -fconcepts DoublyLinkedListTests.cpp

clean:
	rm *.o $(TARGET)
