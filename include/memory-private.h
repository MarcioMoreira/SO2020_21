#ifndef MEMORY_PRIVATE_H_GUARD
#define MEMORY_PRIVATE_H_GUARD

//estrutura que representa um buffer circular, completar pelos alunos
struct circular_buffer
{
    void *buffer;
    void *buffer_end;
    size_t size;
    void *head;
    void *tail;
};

//estrutura que representa um buffer de acesso aleatório, completar pelos alunos
struct rnd_access_buffer
{
    void *buffer;
    void *buffer_end;
    size_t sz;
    void *head;
    void *tail;
};

#endif
