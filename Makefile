async-credis: src/main.o src/value.o
	cc src/main.o src/value.o -o bin/credis


src/main.o: src/main.c
	cc -c src/main.c -o src/main.o

src/value.o: src/value.c
	cc -c src/value.c -o src/value.o
