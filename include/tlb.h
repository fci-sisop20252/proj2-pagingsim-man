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

#ifndef TLB_H
#define TLB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tipos.h"
#include "algoritmos.h"

//Struct para tradução de endereços:
typedef struct{
    unsigned int pagina;
    unsigned int deslocamento;
    unsigned int end_fisico;
} Traducao;

/**
 * @brief Função -> tradução de endereços
 * @param T -> struct de tradução
 * @param endereco -> endereço virtual
 * @param frames -> número de frames
 * @param CM -> struct de configuração de memória
 */
Traducao traducao_endereco(unsigned int endereco, ConfigMemoria CM, TabelaPagina TP[]);

// Função que checa se página existe na memória física:
int checkHIT(TabelaPagina TP[], unsigned int pagina);

/**
 * @brief Função que trata o caso de PAGE FAULT
 * @param TP -> Struct de Tabela Página
 * @param CM -> Struct de Configuração de Memória
 * @param pag_virtual -> Recebe a página virtual para ser alocada em novo frame
 * 
 * @return Tabela atualizada com a página em novo frame
 */
void PageFaultCorrection(TabelaPagina TP[], ConfigMemoria CM, int pag_virtual, int pid_atual, const char *algoritmo);

/**
 * @brief Função -> tabela de páginas
 * @param TP -> struct da tabela de páginas
 * @param num_pag -> número de páginas
 * @param pag_virtual -> página virtual
 * @return unsigned int -> número do frame correspondente
 */

void tabela_pagina(TabelaPagina TP[], Acessos AC, ConfigMemoria CM, FormatoSaida FS[], int *total_access, int *total_PAGEFAULTS, const char *algoritmo);

#endif