#ifndef RAM_H
#define RAM_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @param frames Lista de frames, que guarda o ID do PID que está em cada frame. -1 se estiver vazio.
 * @param num_frames Quantidade de frames disponível.
 * @param ram_pag Tamanho de cada frame.
 *
 * @param processos Lista dos PIDs no seguinte formato: [<id pid>][<tamanho da memória nescessária>].
 * @param num_processos Quantidade de processos.
 */
typedef struct RAM {
    int* frames;
    int num_frames;
    int tam_pag;
    int** processos;
    int num_processos;
} RAM;

/**
 * @brief Cria nova estrutura de memória RAM e processos
 * 
 * @return @c RAM Estrutura RAM preenchida
 */
RAM criarRAM(int num_frames, int tam_pag, int** processos, int num_processos);

/**
 * @brief Exclui memória alocada de RAM
 * 
 * @param ram  @c RAM a ser desalocada
 */
void freeRAM(RAM ram);

/**
 * @brief Printa os PIDs de cada Frame
 * 
 * @param ram  @c RAM a ser printada
 */
void printFrames(RAM ram);

/**
 * @brief Printa os processos da RAM
 * 
 * @param ram  @c RAM a ser printada
 */
void printProcessos(RAM ram);

#endif // RAM_H