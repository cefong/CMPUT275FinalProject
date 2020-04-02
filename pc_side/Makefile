CC=g++
LFLAGS=
CFLAGS=-c -Wall -std=c++11 -O2
OBJS= galagamp.o serialport.o
EXE= galagamp

$(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LFLAGS)

galagamp.o: galagamp.cpp serialport.h
	$(CC) galagamp.cpp -o galagamp.o $(CFLAGS)
serialport.o: serialport.h serialport.cpp
	$(CC) serialport.cpp -o serialport.o $(CFLAGS)

clean:
	@rm $(OBJS) $(EXE)
