#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mysql/mysql.h>
#include <stdint.h>

#include "PoetryLibrarySQLAdapter.h"
#include "PoetryLibrarySQLAdapter.r"
#include "new.h"
#include "new.r"

static int count_lines(MYSQL *conn);
static int random_number(int min_num, int max_num);

static void *PoetryLibrarySQLAdapter_ctor(void *_self, va_list *app)
{
    struct PoetryLibrarySQLAdapter *self = _self;
    MYSQL *conn = va_arg(*app, MYSQL *);
    self->conn = conn;
    assert(self->conn);
    return self;
}

static void *PoetryLibrarySQLAdapter_dtor(void *_self)
{
    struct PoetryLibrarySQLAdapter *self = _self;
    mysql_close(self->conn);
    return self;
}

static const struct Class _PoetryLibrarySQLAdapter = {
    sizeof(struct PoetryLibrarySQLAdapter),
    PoetryLibrarySQLAdapter_ctor,
    PoetryLibrarySQLAdapter_dtor};

const void *PoetryLibrarySQLAdapter = &_PoetryLibrarySQLAdapter;

static int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    }
    else
    {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

static int count_lines(MYSQL *conn)
{

    uint64_t counter = 0;
    /* send SQL query */
    if (mysql_query(conn, "select * from poems"))
    {
        printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
        return -1;
    }

    counter = (int)mysql_num_rows(mysql_store_result(conn));

    return counter;
}

void *GetMeAPoem(const void *_self)
{
    static char str[160];
    static int countLinesOK = -1;
    int rand_line;
    int number_of_lines;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const struct PoetryLibrarySQLAdapter *self = _self;
    if (countLinesOK == -1)
    {
        number_of_lines = count_lines(self->conn);
        countLinesOK = 1;
    }

    rand_line = random_number(0, number_of_lines - 1);

    /* send SQL query */
    if (mysql_query(self->conn, "select strophe from poems"))
    {
        printf("Failed to execute quesry. Error: %s\n", mysql_error(self->conn));
        return NULL;
    }
    res = mysql_store_result(self->conn);
    if (res == NULL)
    {
        return NULL;
    }
    int i = 0;
    /* Read random line */
    while (row = mysql_fetch_row(res))
    {

        if (i == rand_line)
        {
            strcpy(str, row[0]);
            break;
        }
        i++;
    }
    mysql_free_result(res);
    return str;
}
