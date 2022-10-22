
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "PoetryReader.h"
#include "PoetryReader.r"
#include "new.h"
#include "new.r"

static void *PoetryReader_ctor(void *_self, va_list *app)
{
    struct PoetryReader *self = _self;

    self->poetryLibrary = va_arg(*app, void *);
    assert(self->poetryLibrary);

    return self;
}

static void *PoetryReader_dtor(void *_self)
{
    struct PoetryReader *self = _self;

    free(self->poetryLibrary), self->poetryLibrary = 0;
    return self;
}

static const struct Class _PoetryReader = {
    sizeof(struct PoetryReader),
    PoetryReader_ctor, 0};

const void *PoetryReader = &_PoetryReader;

void *GiveMeSomePoetry(const void *_pReader)
{
    const struct PoetryReader *pReader = _pReader;

    struct PoetryLibrary *poetryLibrary = pReader->poetryLibrary;
    return GetMeAPoem(poetryLibrary);
}