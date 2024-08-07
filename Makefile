all:
	gcc -o main main.c debug.c chunk.c memory.c value.c vm.c scanner.c compiler.c -Wall
clean:
	rm main
