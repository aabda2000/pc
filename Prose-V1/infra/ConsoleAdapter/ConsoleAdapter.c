#include "ConsoleAdapter.h"
#include <stdio.h>
#include <string.h>
#define REP "../database/poems.txt"

void CONSOLE_ask()
{
    void *fileAdapter;
    void *poetryReader;
    /*
	p = new (PoetryLibraryFileAdapter, "poems.txt");*/
    fileAdapter = new (PoetryLibraryFileAdapter, REP);
    poetryReader = new (PoetryReader, fileAdapter);

    char *poem = GiveMeSomePoetry(poetryReader);
    printf("%s\n", poem);
}
