CC=g++
CFLAGS= -Wall -Wextra -Werror -O2 -I include/

all: run

SRC=src/
BUILD=build/
main: $(BUILD)main.o
	$(CC) $(CFLAGS) -o $(BUILD)main $(BUILD)main.o

$(BUILD)main.o: 
	$(CC) $(CFLAGS) -c $(SRC)main.c++ -o $(BUILD)main.o
run: clean main
	./$(BUILD)main -c lang/test.anm -o lang/build/test.asm
	make build_script
debug: clean main
	./$(BUILD)main -c lang/test.anm -o lang/build/test.asm --debug
	make build_script

clean:
	rm -f $(BUILD)main.o $(BUILD)main lang/build/*.*
build_script:
	nasm -o lang/build/test.o lang/build/test.asm
	
	
.PHONY: all clean
