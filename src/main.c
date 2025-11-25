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

#include <stdio.h>

#include "algoritmos.h"
#include "arquivo.h"
#include "saida.h"
#include "tlb.h"

int main(int argc, char *argv[]){
    if (argc != 4) {
        printf("Uso correto: %s <algoritmo> <arquivo_config> <arquivo_acessos>\n", argv[0]);
        return 1;
    }

    const char *algoritmo = argv[1];         // "fifo" ou "clock"
    const char *config_file = argv[2];       // "tests/config_1.txt"
    const char *acessos_file = argv[3];      // "tests/acessos_1.txt
    
    ConfigMemoria CM = arquivo_config(config_file);
    Acessos AC = arquivo_acessos(acessos_file);
    TabelaPagina TP_FIFO[MAX_PAGES];
    TabelaPagina TP_CLOCK[MAX_PAGES];
    FormatoSaida FS_FIFO[MAX_ACCESS];
    FormatoSaida FS_CLOCK[MAX_ACCESS];

    int total_access_FIFO = 0;
    int total_pf_FIFO = 0;
    int total_access_CLOCK = 0;
    int total_pf_CLOCK = 0;

    // Para o caso de FIFO:
    if(strcmp(algoritmo, "fifo") == 0){
        tabela_pagina(TP_FIFO, AC, CM, FS_FIFO, &total_access_FIFO, &total_pf_FIFO, "fifo");

        for(int y = 0; y < AC.quant_acessos; y++){
            OUTPUT(TP_FIFO, CM, FS_FIFO, AC, y, FS_FIFO[y].pagina, FS_FIFO[y].frame);
        }
        printf("--- Simulação Finalizada (Algoritmo: <fifo>)\n");
        printf("Total de Acessos: %d\n", total_access_FIFO);
        printf("Total de Page Faults: %d\n", total_pf_FIFO);
    } else {
        tabela_pagina(TP_CLOCK, AC, CM, FS_CLOCK, &total_access_CLOCK, &total_pf_CLOCK, "clock");

        for(int t = 0; t < AC.quant_acessos; t++){
            OUTPUT(TP_CLOCK, CM, FS_CLOCK, AC, t, FS_CLOCK[t].pagina, FS_CLOCK[t].frame);
        }

        printf("--- Simulação Finalizada (Algoritmo: clock)\n");
        printf("Total de Acessos: %d\n", total_access_CLOCK);
        printf("Total de Page Faults: %d\n", total_pf_CLOCK);
    }
    return 0;
}
