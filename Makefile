all:
	gcc -Wall  -g3 main.c Funcionalidades.c lista.c Funcionalidade1.c Funcionalidade2.c Funcionalidade3.c Funcionalidade4.c  Funcionalidade6.c  -o programaTrab

run:
	./programaTrab

test:
	gcc -Wall  -g3 main.c Funcionalidades.c lista.c Funcionalidade1.c Funcionalidade2.c Funcionalidade3.c Funcionalidade4.c  Funcionalidade6.c  -o programaTrab
	./programaTrab