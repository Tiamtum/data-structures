CC = g++
CFLAGS = -I -Wall -Wextra -pedantic-errors
OBJFILES = SinglyLinkedListTests.o
TARGET = tests 

$(TARGET): $(OBJFILES) 
	$(CC) $(CFLAGS) $(OBJFILES) -o $(TARGET)

SinglyLinkedListTests.o: SinglyLinkedListTests.cpp 
	$(CC) $(CFLAGS) -c -g -fconcepts SinglyLinkedListTests.cpp

clean:
	rm *.o $(TARGET)

