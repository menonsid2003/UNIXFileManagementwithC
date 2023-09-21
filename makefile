all: myls mysearch mystat mytail

myls: myls-Menon.c
	gcc -std=c99 -o myls myls-Menon.c

mysearch: mysearch-Menon.c
	gcc -std=c99 -o mysearch mysearch-Menon.c

mystat: mystat-Menon.c
	gcc -std=c99 -o mystat mystat-Menon.c

mytail: mytail-Menon.c
	gcc -std=c99 -o mytail mytail-Menon.c