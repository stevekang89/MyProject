CC = gcc
CFAGS = -W -Wall
TARGET = PRBS_exe
OBJECT = prbs.o main.o prbs_hs.o dec_to_bin.o

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o 
