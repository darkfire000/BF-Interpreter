#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bf.h"
#include "commands.c"

CallLater callLater[COMMAND_COUNT];
CallLater *clpt = callLater;
int size = 0;
CallLater *clLoopStack[LOOP_STACK_SIZE];
int clLoopIndex = 0;

void parseFile(FILE *file)
{
	int c;
	while ((c = getc(file)) != EOF)
	{
		switch((char)c)
		{
		case '>':
			clpt->Function = (function) &incpt;
			break;
		case '<':
			clpt->Function = (function) &decpt;
			break;
		case '+':
			clpt->Function = (function) &inc;
			break;
		case '-':
			clpt->Function = (function) &dec;
			break;
		case '.':
			clpt->Function = (function) &prnt;
			break;
		case ':':
			clpt->Function = (function) &prntv;
			break;
		case '[':
			clpt->Function = (function) &skip;
			clLoopStack[clLoopIndex++] = clpt;
			break;
		case ']':
			clpt->Function = (function) &loop;
			clpt->fail = clLoopStack[--clLoopIndex];
			break;
		default:
			size--;
			clpt--;
			break;
		}
		size++;
		clpt++;
	}
}

int main (int argc, char **argv)
{
	// Init cell table
	CellTable ct;
	ct.pointer = ct.cells;
	int i = 0;
	for(; i < CELL_COUNT; i++) ct.cells[i] = 0;
	
	// Exit if too view args
	if (argc < 2) {
		printf("%s\n", "Please specify input file");
		return 1;
	}
	
	FILE *file;
	file = fopen(argv[1], "r");
	
	// Exit if fopen fails
	if (!file) {
		printf("%s\n", "Input file could not be read!");
		return 1;
	}
	
	parseFile(file);
	
	fclose(file);

	// Exit if there are bracket mismatches
	if (clLoopIndex > 0) {
		printf("Can't execute code. %d unclosed loops\n", clLoopIndex);
		return 1;
	} else if (clLoopIndex < 0) {
		printf("Can't execute code. %d loops closed too much\n", clLoopIndex*-1);
		return 1;
	}
	
	// Set end function for last element
	clpt->Function = (function) &end;

	// Go backwards through all elements and concate with the fitting next
	i = 0;
	for (; i < size; i++) {
		CallLater *tmp = clpt-1;
		tmp->next = clpt;
		clpt--;
	}

	// Loop through all elements until the end function in the last element returns NULL
	while ((clpt = (*(clpt->Function))(clpt, &ct)) != NULL);

	return 0;
}