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

#ifndef TIPOS_H
#define TIPOS_H

#define MAX_PROCESSOS 64
#define MAX_ACCESS 128
#define MAX_PAGES 1024

//Struct para config. da memória:
typedef struct{
    int num_frames;
    unsigned int tamanho_pag;
    int quant_processos;
    int pid[MAX_PROCESSOS];
    unsigned int tamanho_mem_virtual[MAX_ACCESS];
} ConfigMemoria;

//Struct para acessos:
typedef struct{
    unsigned int quant_acessos;
    int pid[MAX_ACCESS];
    unsigned int end_mem_virtual[MAX_ACCESS];
} Acessos;

//Struct para Tabela de Páginas:
typedef struct{
    unsigned int end_virtual;
    unsigned int num_frame;
    unsigned int valid_bit;
    unsigned int referenced_bit;
    unsigned int frame;
    int loaded_time;
    int pid;
} TabelaPagina;

typedef struct{
    unsigned int pagina;
    unsigned int frame;
    int hit;
    int removed_pagina;
    int removed_frame;
    int removed_pid;
} FormatoSaida;


// ===== Variaveis e estruturas não usadas: =====

// typedef struct{
//     bool ocupied;
//     int pagina_virtual;
// } Frame;

// // Esse tempo é usado para o -> FIFO <-
// int tempo_global_fifo = 0;

#endif