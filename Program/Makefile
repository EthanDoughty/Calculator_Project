CC = g++
CFLAGS = -std=c++17
EXECUTABLE = calculator.exe

ifeq ($(OS),Windows_NT)
    RM = del /Q
else
    RM = rm -f
endif


all: $(EXECUTABLE)

$(EXECUTABLE): main.cpp
	$(CC) $(CFLAGS) -o $(EXECUTABLE) main.cpp

clean:
	$(RM) $(EXECUTABLE)
