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

#include "algoritmos.h"

int algFIFO(TabelaPagina TP[], unsigned int num_frames) {
    int older_page = -1;
    clock_t maior_tempo = (clock_t)~0;

    for(int idx = 0; idx < MAX_PAGES; idx++){
        if (TP[idx].valid_bit && TP[idx].num_frame >= 0 && TP[idx].num_frame < (int)num_frames) {
            if (TP[idx].loaded_time < maior_tempo){
                maior_tempo = TP[idx].loaded_time;
                older_page = idx;
            }
        }
    }
    return older_page;
}

unsigned int algCLOCK(TabelaPagina TP[], unsigned int num_frames) {
    static unsigned int ponteiro = 0; // ponteiro circular

    while (1) {
        // percorre todas as páginas para achar quem ocupa o frame atual
        for (unsigned int pag = 0; pag < MAX_PAGES; pag++) {
            if (TP[pag].valid_bit && TP[pag].num_frame == ponteiro) {
                // caso 1: bit de referência = 0 -> vítima encontrada
                if (TP[pag].referenced_bit == 0) {
                    unsigned int vitima = pag;
                    ponteiro = (ponteiro + 1) % num_frames; // avança ponteiro
                    return vitima;
                } else {
                    // caso 2: bit de referência = 1 -> segunda chance
                    TP[pag].referenced_bit = 0;
                }
            }
        }
        // avança ponteiro circularmente
        ponteiro = (ponteiro + 1) % num_frames;
    }
}