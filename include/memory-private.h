#ifndef MEMORY_PRIVATE_H_GUARD
#define MEMORY_PRIVATE_H_GUARD

#include "memory.h"

//estrutura que representa um buffer circular, completar pelos alunos
struct circular_buffer
{
    struct operation *buffer;
    int *in;
    int *out;
};

//estrutura que representa um buffer de acesso aleatório, completar pelos alunos
struct rnd_access_buffer
{
    struct operation *buffer;
    int *ptr;
};

#endif
