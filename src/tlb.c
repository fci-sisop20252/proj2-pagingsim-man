/* Integrantes
    |=================== GRUPO ===================|
    |                                             |
    |               Nome              |     RA    |
    |---------------------------------|-----------|
    | Andre Doerner Duarte            | 10427938  |
    | Matheus Leonardo Cardoso Kroeff | 10426434  |
    | Naoto Ushizaki                  | 104374445 |
    |=============================================|
*/

#include "tlb.h"

Traducao traducao_endereco(unsigned int endereco, ConfigMemoria CM, TabelaPagina TP[]) {
    Traducao T;

    T.pagina = endereco / CM.tamanho_pag;
    T.deslocamento = endereco % CM.tamanho_pag;

    if(TP[T.pagina].valid_bit == 1){
        unsigned int frame = TP[T.pagina].num_frame;
        T.end_fisico = (frame * CM.tamanho_pag) + T.deslocamento;
    } else {
        T.end_fisico = (unsigned int)-1;
    }

    return T;
}

// Função que checa se página existe na memória física:
int checkHIT(TabelaPagina TP[], unsigned int pagina) {
    if(TP[pagina].valid_bit == 1){
        return TP[pagina].num_frame;
    } else {
        return -1;
    }
}

void PageFaultCorrection(TabelaPagina TP[], ConfigMemoria CM, int pag_virtual, int pid_atual, const char *algoritmo) { //int *removed_page, int *removed_frame, int *pid_removido){
    /*
    *removed_page = -1;
    *removed_frame = -1;
    *pid_removido = -1;*/
    int frame_free = -1; 

    // Cenário de procura por um frame livre primeiro:
    for(int d = 0; d < CM.num_frames; d++){
        int occupied = 0;
        // Caso de se tiver frame livre:
        for(int o = 0; o < MAX_PAGES; o++){
            if(TP[o].valid_bit && TP[o].num_frame == d){
                occupied = 1;
                break;
            }
        }
        if(!occupied){
            frame_free = d;
            break;
        }
        
    }

    if(frame_free != -1){
        TP[pag_virtual].loaded_time = clock(); // Comeca a contar o tempo para o FIFO
        TP[pag_virtual].end_virtual = pag_virtual;
        TP[pag_virtual].num_frame = frame_free;
        TP[pag_virtual].pid = pid_atual;
        TP[pag_virtual].valid_bit = 1;
        TP[pag_virtual].referenced_bit = 1;
        return;
    } else {
        int eliminate_page = -1;
        // Cenário 2: PAGE_FAULT -> Pagina não está na memória física:
        if (strcmp(algoritmo, "fifo") == 0) {
            eliminate_page = algFIFO(TP, CM.num_frames);
        } else if (strcmp(algoritmo, "clock") == 0) {
            eliminate_page = algCLOCK(TP, CM.num_frames);
        } else {
            printf("Algoritmo desconhecido: %s\n", algoritmo);
            exit(1);
        }

        int chosen_frame = TP[eliminate_page].num_frame;
        int pid_victim = TP[eliminate_page].pid;
        double maior_tempo_FIFO = (double)(clock() - TP[eliminate_page].loaded_time) / CLOCKS_PER_SEC;
        
        // Atualizando ponteiros:
        /*
        *removed_page = eliminate_page;
        *removed_frame = chosen_frame;
        *pid_removido = pid_victim;*/

        // Zerando os bits (retirada de páginas):
        TP[eliminate_page].valid_bit = 0;
        TP[eliminate_page].referenced_bit = 0;
        TP[eliminate_page].num_frame = -1;

        // Recolocando na table de paginas:
        TP[pag_virtual].loaded_time = clock();
        TP[pag_virtual].end_virtual = pag_virtual; // Atualizando pagina
        TP[pag_virtual].num_frame = chosen_frame;
        TP[pag_virtual].pid = pid_atual;
        TP[pag_virtual].valid_bit = 1;
        TP[pag_virtual].referenced_bit = 1;

    }
}

/**
 * @brief Função -> tabela de páginas
 * @param TP -> struct da tabela de páginas
 * @param num_pag -> número de páginas
 * @param pag_virtual -> página virtual
 * @return unsigned int -> número do frame correspondente
 */

void tabela_pagina(TabelaPagina TP[], Acessos AC, ConfigMemoria CM, FormatoSaida FS[], int *total_access, int *total_PAGEFAULTS, const char *algoritmo) {
    // Setando a tabela de páginas:
    for(int y = 0; y < MAX_PAGES; y++){
        TP[y].end_virtual = y;
        TP[y].num_frame = -1;
        TP[y].valid_bit = 0;
        TP[y].referenced_bit = 0;
        TP[y].loaded_time = 0;
    }

    *total_access = AC.quant_acessos;
    if(*total_access > MAX_ACCESS) *total_access = MAX_ACCESS;
    *total_PAGEFAULTS = 0;
    

    // Organizando end_virtual na tabela de páginas:
    for(int x = 0; x < *total_access; x++){
        Traducao T = traducao_endereco(AC.end_mem_virtual[x], CM, TP);
        unsigned int pag_virtual = T.pagina;
        int frame = checkHIT(TP, pag_virtual);

        // Cenário 1: HIT -> pagina está na memória física
        if(frame != -1){
            TP[pag_virtual].referenced_bit = 1;
            FS[x].hit = 1;
            FS[x].pagina = pag_virtual;
            FS[x].frame = TP[pag_virtual].num_frame;;
            FS[x].removed_frame = -1;
            FS[x].removed_pagina = -1;
            FS[x].removed_pid = -1;
        } else {
            // Cenário 2: página não está na memória física:
            (*total_PAGEFAULTS)++;
            //int removed_page, removed_frame, pid_removido;
            PageFaultCorrection(TP, CM, pag_virtual, AC.pid[x], algoritmo); //&removed_page, &removed_frame, &pid_removido);
            FS[x].hit = 0;
            FS[x].pagina = pag_virtual;
            FS[x].frame = TP[pag_virtual].num_frame;
            FS[x].removed_pagina = TP[pag_virtual].end_virtual;
            FS[x].removed_frame = TP[pag_virtual].num_frame;
            FS[x].removed_pid = TP[pag_virtual].pid;

        }
    }
}