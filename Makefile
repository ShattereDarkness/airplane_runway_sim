a.exe:	1.o 2.o
			gcc 1.o 2.o
1.o:	main.c
			gcc -c main.c -o 1.o
2.o:	queue.c
			gcc -c queue.c	-o 2.o