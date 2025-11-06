#ifndef RAM_H
#define RAM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Processo {
    int pid;
    int tamanho_memoria_virtual;
    int num_paginas;
    PageTableEntry* tabela_paginas;
} Processo;

typedef struct RAM {
    Frame* frames;
    int num_frames;
    int tam_pag;

    Processo* processos;
    int num_processos;

    int clock_pointer;
    int next_fifo_index;

    int total_page_faults;
    int total_acessos;

} RAM;

typedef struct Frame {
    int pid;
    int pagina_virtual;
    int r_bit;

    int ordem_chegada;
} Frame;


RAM criarRAM(int num_frames, int tam_pag, int** processos, int num_processos);

void freeRAM(RAM ram);

void printFrames(RAM ram);

void printProcessos(RAM ram);

#endif // RAM_H