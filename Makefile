# Damian Testa, https://github.com/damiante/
# Makefile for Brainf*ck Interpretter

main: bfint.c
	gcc -o bf bfint.c

clean:
	rm -f bf
