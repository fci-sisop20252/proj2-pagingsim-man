#include <stdio.h>

#include "ram.h"

// gcc -Wall -Wextra -I./include src/*.c -o fifo
// -Wall - Wextra: Mostra possiveis erros
// -I./<pasta dos .h>: Para incluir os headers
int main() {
    /* config_1.txt:
        8
        10
        2
        0 50
        1 60
    */

    int num_frames  = 8;
    int tam_pag = 10;
    int num_processos = 2;

    int** processos = malloc(num_processos * sizeof(int*));
    for (int i = 0; i < num_processos; i++) processos[i] = malloc(2 * sizeof(int));
    processos[0][0] = 0;  processos[0][1] = 50;
    processos[1][0] = 1;  processos[1][1] = 60;

    RAM ram = criarRAM(num_frames, tam_pag, processos, num_processos);
    
    printf(
        "Frames disponiveis: %d\n"
        "Tamanho de cada pagina: %d\n"
        "Quantidade de processos: %d\n\n",
        ram.num_frames, ram.tam_pag, ram.num_processos
    );
    printFrames(ram);
    putchar('\n');
    printProcessos(ram);

    freeRAM(ram);

    return 0;
}

/* Formato:
// Acesso: PID <pid>, Endereço <addr> (Página <p>, Deslocamento <d>) -> HIT:          Página <p> (PID <pid>) já está no Frame <f>
// Acesso: PID <pid>, Endereço <addr> (Página <p>, Deslocamento <d>) -> PAGE FAULT -> Página <p> (PID <pid>) alocada no Frame livre <f>
// Acesso: PID <pid>, Endereço <addr> (Página <p>, Deslocamento <d>) -> PAGE FAULT -> Memória cheia. Página <p_antiga> (PID <pid_antigo>) (Frame <f>) será desalocada. -> Página <p> (PID <pid>) alocada no Frame <f>

// Acesso: PID 0, Endereço 25 (Página 2, Deslocamento 5) -> HIT:          Página 2 (PID 0) já está no Frame 2
// Acesso: PID 0, Endereço 25 (Página 2, Deslocamento 5) -> PAGE FAULT -> Página 2 (PID 0) alocada no Frame livre 2
// Acesso: PID 1, Endereço 55 (Página 5, Deslocamento 5) -> PAGE FAULT -> Memória cheia. Página 1 (PID 0) (Frame 0) será desalocada. -> Página 5 (PID 1) alocada no Frame 0
*/

/*========== NAOTO: ==========
#define MAX_PROCESSOS 50
#define MAX_ACCESS 100

typedef struct ConfigMemoria {
    int num_frames;
    unsigned int tamanho_pag;
    int num_processos;
    int pid[MAX_PROCESSOS];
    unsigned int tamanho_mem_virtual[MAX_ACCESS];
} ConfigMemoria;

typedef struct AlgFIFO {
    unsigned int pag_virtual;
} AlgFIFO;

void algFIFO(AlgFIFO lista[], unsigned int *size_atual, unsigned int new_pag, unsigned int TAM_MEMORIA){
    for(int k = 0; k < *size_atual; k++){
        if(lista[k].pag_virtual == new_pag){
            return; // Página já está na lista FIFO
        }
    }
    if(*size_atual == TAM_MEMORIA){
        for(int t = 0; t < *size_atual; t++){
            lista[t] = lista[t + 1];
        }
        lista[TAM_MEMORIA - 1].pag_virtual = new_pag;
    }
    else {
        lista[*size_atual].pag_virtual = new_pag;
        (*size_atual)++;
    }
}
*/