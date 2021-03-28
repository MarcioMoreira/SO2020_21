/*
Gonçalo Cardoso - 54415
Marcio Moreira - 41972
Pedro Correia - 54570
*/
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "memory.h"
#include "memory-private.h"

/* Função que reserva uma zona de memória partilhada com tamanho indicado
* por size e nome name, preenche essa zona de memória com o valor 0, e 
* retorna um apontador para a mesma. Pode concatenar o resultado da função
* getuid() a name, para tornar o nome único para o processo.
*/
void *create_shared_memory(char *name, int size)
{
	void *ptr;
	int ret;
	int fd = shm_open(name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror(name);
		exit(1);
	}
	ret = ftruncate(fd, size);
	if (ret == -1)
	{
		perror(name);
		exit(2);
	}
	ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED)
	{
		perror(name);
		exit(3);
	}
	return ptr;
}

/* Função que reserva uma zona de memória dinâmica com tamanho indicado
* por size, preenche essa zona de memória com o valor 0, e retorna um 
* apontador para a mesma.
*/
void *create_dynamic_memory(int size)
{
	int *dynamicmem = (int *)malloc(size);
	for (int i = 0; i < size; i++)
	{
		dynamicmem[i] = 0;
	}
	return (void *)dynamicmem;
}

/* Função que liberta uma zona de memória dinâmica previamente reservada.
*/
void destroy_shared_memory(char *name, void *ptr, int size)
{
	size = munmap(ptr, size);
	if (size == -1)
	{
		perror(name);
		exit(7);
	}
	size = shm_unlink(name);
	if (size == -1)
	{
		perror(name);
		exit(8);
	}
	exit(0);
}

/* Função que liberta uma zona de memória partilhada previamente reservada.
*/
void destroy_dynamic_memory(void *ptr)
{
	free(ptr);
}

/* Função que escreve uma operação num buffer de acesso aleatório. A
* operação deve ser escrita numa posição livre do buffer, segundo as
* regras de escrita em buffers de acesso aleatório. Se não houver nenhuma
* posição livre, não escreve nada.
*/
void write_rnd_access_buffer(struct rnd_access_buffer *buffer, int buffer_size, struct operation *op)
{
	for (int n = 0; n < buffer_size; n++)
	{
		if (buffer->ptr[n] == 0)
		{
			buffer->buffer[n] = *op;
			buffer->ptr[n] = 1;
			break;
		}
	}
}

/* Função que escreve uma operação num buffer circular. A operação deve 
* ser escrita numa posição livre do buffer, segundo as regras de escrita
* em buffers circulares. Se não houver nenhuma posição livre, não escreve
* nada.
*/
void write_circular_buffer(struct circular_buffer *buffer, int buffer_size, struct operation *op)
{
	while (((*(buffer->in) + 1) % buffer_size) == buffer->out)
		;
	buffer->buffer[*(buffer->in)] = *op;
	buffer->in = (*(buffer->in) + 1) % buffer_size;
}

/* Função que lê uma operação de um buffer de acesso aleatório, se houver
* alguma disponível para ler. A leitura deve ser feita segundo as regras
* de leitura em buffers acesso aleatório. Se não houver nenhuma operação
* disponível, afeta op com o valor -1.
*/
void read_rnd_access_buffer(struct rnd_access_buffer *buffer, int buffer_size, struct operation *op)
{
	for (int n = 0; n < buffer_size; n++)
	{
		if (buffer->ptr[n] == 1)
		{
			*op = buffer->buffer[n];
			buffer->ptr[n] = 0;
			break;
		}
	}
}
/* Função que lê uma operação de um buffer circular, se houver alguma 
* disponível para ler. A leitura deve ser feita segundo as regras de
* leitura em buffers circular. Se não houver nenhuma operação disponível,
* afeta op->id com o valor -1.
*/
void read_circular_buffer(struct circular_buffer *buffer, int buffer_size, struct operation *op)
{
	while (buffer->in == buffer->out)
		;
	*op = buffer->buffer[*(buffer->out)];
	buffer->out = (*(buffer->out) + 1) % buffer_size;
}
