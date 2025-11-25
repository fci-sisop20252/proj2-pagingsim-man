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

#ifndef SAIDA_H
#define SAIDA_H

#include <stdio.h>
#include "tipos.h"

void OUTPUT(TabelaPagina TP[], ConfigMemoria CM, FormatoSaida FS[], Acessos access, int idx_acesso, unsigned int pagina, unsigned int frame);

#endif