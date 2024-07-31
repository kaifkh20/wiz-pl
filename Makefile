all:
	gcc -o main main.c debug.c chunk.c memory.c value.c
clean:
	rm main