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

#include "saida.h"

void OUTPUT(TabelaPagina TP[], ConfigMemoria CM, FormatoSaida FS[], Acessos access, int idx_acesso, unsigned int pagina, unsigned int frame) {
    unsigned int endereco = access.end_mem_virtual[idx_acesso];
    unsigned int pid = access.pid[idx_acesso];
    unsigned int deslocamento = endereco % CM.tamanho_pag;
    if(FS[idx_acesso].hit){
        printf("Acesso: PID %u, Endereço %u (Página %u, Deslocamento %u) -> "
           "HIT: Página %u (PID %u) já está no Frame %u\n", pid, endereco, pagina, deslocamento, pagina, pid, frame);
    } else {
        printf("Acesso: PID %u, Endereço %u (Página %u, Deslocamento %u) -> "
           "PAGE FAULT -> Memória cheia. Página %d (PID %d) (Frame %d) será desalocada. -> Página %u alocada no Frame %u\n", pid, endereco, pagina, deslocamento, FS[idx_acesso].removed_pagina, FS[idx_acesso].removed_pid, FS[idx_acesso].removed_frame, pagina, FS[idx_acesso].frame);
    }
}