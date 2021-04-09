/*
Gonçalo Cardoso - 54415
Marcio Moreira - 41972
Pedro Correia - 54570
*/

#include "memory.h"
#include "memory-private.h"
#include "synchronization.h"
#include <semaphore.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

/* Função que cria um novo semáforo com nome name e valor inicial igual a
* value. Pode concatenar o resultado da função getuid() a name, para tornar
* o nome único para o processo.
*/

sem_t *semaphore_create(char *name, int value)
{
	sem_t *sem;
	sem = sem_open(name, O_CREAT, 0xFFFFFFFF, value);
	if (sem == SEM_FAILED)
	{
		perror("sem");
		exit(6);
	}
}

/* Função que destroi o semáforo passado em argumento.
*/
void semaphore_destroy(char *name, sem_t *semaphore)
{
	int sem_close(sem_t * semaphore);
	int sem_unlink(const char *name);

	if (sem_close(semaphore) == -1)
	{
		perror(name);
	}
	if (sem_unlink(name) == -1)
	{
		perror(name);
	}
}
/* Função que inicia o processo de produzir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_begin(struct prodcons *pc)
{
	sem_wait(pc->empty);
	sem_wait(pc->mutex);
}
/* Função que termina o processo de produzir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_end(struct prodcons *pc)
{
	sem_post(pc->mutex);
	sem_post(pc->full);
}

/* Função que inicia o processo de consumir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_begin(struct prodcons *pc)
{
	sem_wait(pc->full);
	sem_wait(pc->mutex);
}

/* Função que termina o processo de consumir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_end(struct prodcons *pc)
{
	sem_wait(pc->mutex);
	sem_wait(pc->empty);
}

/* Função que faz wait a um semáforo.
*/
void semaphore_mutex_lock(sem_t *sem)
{
	sem_wait(sem);
}

/* Função que faz post a um semáforo.
*/
void semaphore_mutex_unlock(sem_t *sem)
{
	sem_post(sem);
}
