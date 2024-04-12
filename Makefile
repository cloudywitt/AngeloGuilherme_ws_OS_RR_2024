all: bin/paralelo bin/sequencial

bin/paralelo: src/solucao_multithread.c
	mkdir -p bin
	gcc -pthread -Wall -Wextra ./src/solucao_multithread.c -o bin/paralelo

bin/sequencial: src/solucao_singlethread.c
	gcc -pthread -Wall -Wextra ./src/solucao_singlethread.c -o bin/sequencial

clean:
	rm bin/*
