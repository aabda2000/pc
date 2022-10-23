#include "ConsoleAdapter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define REP "../database/poems.txt"

void CONSOLE_ask()
{
    void *fileAdapter;
    void *poetryReader;
    MYSQL *conn;
    /* p = new (PoetryLibraryFileAdapter, "poems.txt");*/
    char *server = "localhost";
    char *user = "admin";
    char *password = "admin"; /*password */
    char *database = "rimbaud";
    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server,
                            user, password, database, 0, NULL, 0))
    {
        printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
    }

    fileAdapter = new (PoetryLibrarySQLAdapter, conn);
    poetryReader = new (PoetryReader, fileAdapter);

    char *poem = GiveMeSomePoetry(poetryReader);
    printf("%s\n", poem);
    delete (fileAdapter);
    delete (poetryReader);
}
