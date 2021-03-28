/*
Gonçalo Cardoso - 54415
Marcio Moreira - 41972
Pedro Correia - 54570
*/
#include "memory.h"
#include "main.h"
#include "client.h"
#include "proxy.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Função que inicia um processo através da função fork do SO. O novo
* processo pode ser um cliente, proxy, ou servidor, consoante a variável
* process_code tem valor 0, 1, ou 2 respectivamente, e irá executar a função
* execute_* respetiva, fazendo exit do retorno. O processo pai devolve o pid
* do processo criado.
*/
int launch_process(int process_id, int process_code, struct communication_buffers *buffers, struct main_data *data, struct semaphores *sems)
{
    int pidfilho;
    {
        process_id = fork();

        if ((process_id) == -1)
        {
            perror(data);
            exit(1);
        }
        if (process_id == 0)
        {
            pidfilho = getpid();
            sem_post(sems);

            if (process_code == 0)
                execute_client(pidfilho, buffers, data, sems);

            if (process_code == 1)
                execute_proxy(pidfilho, buffers, data, sems);

            if (process_code == 2)
                execute_server(pidfilho, buffers, data, sems);
        }
        else
        {
            sem_wait(sems);
            return pidfilho;
        }
    }
}

/* Função que espera que um processo termine através da função waitpid. 
* Devolve o retorno do processo, se este tiver terminado normalmente.
*/
int wait_process(int process_id)
{
    int result;
    pid_t waitpid(pid_t process_id, int *status, int options);

    if (WIFEXITED(result))
        return 0;
    else
        return -1;
}
