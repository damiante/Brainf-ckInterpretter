#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//By convention, the tape is of length 30,000 cells
#define BUFFLEN 30000
#define CURRVER 0.1

/* Definitions of an instance structure to hold the information associated
 * with interpretting Brainfuck. Holds the information stored on the tape,
 * an integer representing the current position of the pointer on the tape,
 * and an integer representing the current size of the tape.
 */

typedef struct instance instance_t;
typedef instance_t* Instance;

struct instance {
	int Tape[BUFFLEN];
	int pos;
	int size;
};

Instance	newInstance();
void		printUsage(char**);
void		printWelcome();
void		interpretFile(FILE*);
void		interpretString(char*, Instance);
void		inc(Instance);
void		dec(Instance);
void		adv(Instance);
void		ret(Instance);
void		rea(Instance, int);
void		wri(Instance);
char*		findSubstring(char*);


int
main(int argv, char** argc){
	FILE * src;
	if (argv == 1){
		src = stdin;
		printWelcome();
	}
	else if (argv == 2){
		src = fopen(argc[1], "r");
	}
	else {
		fprintf(stderr, "Error: Incorrect number of arguments.\n");
		printUsage(argc);
		exit(EXIT_FAILURE);
	}
	interpretFile(src);
	return 0;
}

Instance
newInstance(){
	Instance i = calloc(1, sizeof(instance_t));
	i->size = BUFFLEN;
	return i;
}

void
printUsage(char** argc){
	fprintf(stderr, "Usage: %s (filename)\n", argc[1]);
	return;
}

void
printWelcome(){
	fprintf(stderr, "Damian's Brainfuck Interpretter.\n");
	fprintf(stderr, "Ver. %.1f\n", CURRVER);
	return;
}

void
interpretFile(FILE* fp){
	char curr, pair;
	char substr[BUFFLEN];
	int j, temp;
	Instance i = newInstance();
	while ((curr = fgetc(fp)) != EOF){
		switch (curr){
			case '+':
				inc(i);
				break;
			case '-':
				dec(i);
				break;
			case '>':
				adv(i);
				break;
			case '<':
				ret(i);
				break;
			case '.':
				wri(i);
				break;
			case ',':
				scanf("%d", &temp);
				rea(i, temp);
				break;
			case '[':
				pair = '[';
				j = 0;
				while (pair != ']'){
					if (pair == EOF) {
						substr[j] = '\0';
						interpretString(substr, i);
						return;
					}
					substr[j] = i->Tape[(i->pos)+j];
					j++;
				}
				substr[j] = '\0';
				while (i->Tape[i->pos] != 0){
					interpretString(substr, i);
				}
				break;
			default:
				break;
		}
	}
	return;
}

void
interpretString(char* str, Instance i){
	int j, temp;
	char* substr;
	for (j = 0; j < strlen(str); j++){
		switch (str[j]){
			case EOF:
				exit(EXIT_SUCCESS);
			case '+':
				inc(i);
				break;
			case '-':
				dec(i);
				break;
			case '>':
				adv(i);
				break;
			case '<':
				ret(i);
				break;
			case '.':
				wri(i);
				break;
			case ',':
				scanf("%d", &temp);
				rea(i, temp);
				break;
			case '[':
				substr = findSubstring(&str[j]);
				while (i->Tape[i->pos] != 0){
					interpretString(substr, i);
				}
				free(substr);
				break;
			default:
				break;
		}
	}
	return;
}

void
inc(Instance i){
	i->Tape[i->pos] += 1;
	return;
}

void
dec(Instance i){
	i->Tape[i->pos] += 1;
}

void
adv(Instance i){
	if ((i->pos)+1 == i->size){
		i->pos = 0;
	}
	else {
		i->pos++;
	}
	return;
}

void
ret(Instance i){
	if (i->pos == 0){
		i->pos = i->size;
	}
	else {
		i->pos--;
	}
	return;
}

void
rea(Instance i, int val){
	i->Tape[i->pos] = val;
	return;
}

void
wri(Instance i){
	putchar(i->Tape[i->pos]);
	return;
}

char* findSubstring(char* str){
	int i=0;
	char curr;
	char* substr = calloc(BUFFLEN, sizeof(char));
	while (curr != ']'){
		curr = str[i];
		substr[i] = str[i];
		i++;
	}
	substr[i] = '\0';
	return substr;
}
