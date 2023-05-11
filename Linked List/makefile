CC = g++
CFLAGS = -I -Wall -Wextra -pedantic-errors
TARGET = program 

$(TARGET): main.o 
	$(CC) $(CFLAGS) main.o  -o $(TARGET)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm *.o $(TARGET) 

leak_check:
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(TARGET)
