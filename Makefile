OBJ = main.o lib1.o 
CFLAGS = -Wall -std=c99

all: main

main: $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o main

%.o : %.c
	gcc $(CFLAGS) -c $<

clean:
	rm main $(OBJ)
