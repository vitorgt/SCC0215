all: arquivo.o
	gcc arquivo.o -o arquivo

run: arquivo
	./arquivo

arquivo.o: arquivo.c
	gcc -c arquivo.c -o arquivo.o

clean:
	rm -f saida.bin *.o arquivo
