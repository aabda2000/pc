#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "PoetryLibraryFileAdapter.h"
#include "PoetryLibraryFileAdapter.r"
#include "new.h"
#include "new.r"

static int count_lines(FILE *file);
static int random_number(int min_num, int max_num);

static void *PoetryLibraryFileAdapter_ctor(void *_self, va_list *app)
{
    struct PoetryLibraryFileAdapter *self = _self;

    const char *fname = va_arg(*app, const char *);
    FILE *fd = fopen(fname, "r+");
    self->fd = fd;
    assert(self->fd);
    return self;
}

static void *PoetryLibraryFileAdapter_dtor(void *_self)
{
    struct PoetryLibraryFileAdapter *self = _self;
    fclose(self->fd);
    return self;
}

static const struct Class _PoetryLibraryFileAdapter = {
    sizeof(struct PoetryLibraryFileAdapter),
    PoetryLibraryFileAdapter_ctor,
    PoetryLibraryFileAdapter_dtor};

const void *PoetryLibraryFileAdapter = &_PoetryLibraryFileAdapter;

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

#define BUF_SIZE 65536

static int count_lines(FILE *file_ptr)
{
    char buf[BUF_SIZE];
    int counter = 0;
    for (;;)
    {
        size_t res = fread(buf, 1, BUF_SIZE, file_ptr);
        if (ferror(file_ptr))
            return -1;

        int i;
        for (i = 0; i < res; i++)
            if (buf[i] == '\n')
                counter++;

        if (feof(file_ptr))
            break;
    }
    rewind(file_ptr);
    return counter;
}

void *GetMeAPoem(const void *_self)
{
    static char str[160];
    static int countLinesOK = -1;
    int rand_line;
    int number_of_lines;

    const struct PoetryLibraryFileAdapter *self = _self;
    if (countLinesOK == -1)
    {
        number_of_lines = count_lines(self->fd);
        countLinesOK = 1;
    }

    rand_line = random_number(0, number_of_lines);
    for (int i = 0; i < number_of_lines; i++)
    {
        /* Read next line */
        fgets(str, sizeof(str), self->fd);
        if (i == rand_line)
            break;
    }

    return str;
}
