CC = gcc
CFAGS = -W -Wall
TARGET = FIR_exe
OBJECT = filter.o

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o 
