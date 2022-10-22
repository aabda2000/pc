#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "PoetryLibraryFileAdapter.h"
#include "PoetryLibraryFileAdapter.r"
#include "new.h"
#include "new.r"

static void *PoetryLibraryFileAdapter_ctor(void *_self, va_list *app)
{
    struct PoetryLibraryFileAdapter *self = _self;

    const char *fname = va_arg(*app, const char *);
    FILE *fd = fopen(fname, "r+");

    self->fd = fd;
    assert(self->fd);

    return self;
}

static const struct Class _PoetryLibraryFileAdapter = {
    sizeof(struct PoetryLibraryFileAdapter),
    PoetryLibraryFileAdapter_ctor,
    0,
};

const void *PoetryLibraryFileAdapter = &_PoetryLibraryFileAdapter;

void *GetMeAPoem(const void *_self)
{
    static char str[160];
    const struct PoetryLibraryFileAdapter *self = _self;
    fgets(str, 160, self->fd);
    return str;
}