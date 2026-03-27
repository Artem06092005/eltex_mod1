CC = gcc
TARGET = res

OBJS = main.o calc.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -lm

main.o: main.c calc.h
calc.o: calc.c calc.h

clean:
	rm -f $(OBJS) $(TARGET)