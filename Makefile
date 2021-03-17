CFLAGS = -ansi -Wall -Wextra -Wpedantic

rpn : rpn.o sllstack.o
	gcc -o rpn rpn.o sllstack.o
rpn.o : rpn.c sllstack.h
	gcc -c $(CFLAGS) rpn.c
sllstack.o : sllstack.c sllstack.h
	gcc -c $(CFLAGS) sllstack.c
clean :
	rm rpn.exe rpn.o sllstack.o
