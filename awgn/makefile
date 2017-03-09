CC = gcc
CFAGS = -W -Wall
TARGET = Test_exe
OBJECT = awgn.o main.o

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm *.o 
