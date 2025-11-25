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

#ifndef ARQUIVO_C
#define ARQUIVO_C

#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"

/**
 * @brief Função -> leitura do arquivo de configuração
 * @param arquivo_config -> nome do arquivo de configuração
 * @param ConfigMemoria -> struct com as informações do arquivo de configuração
 */
ConfigMemoria arquivo_config(const char *config_1);

/**
 * @brief Função -> leitura do arquivo de acessos
 * @param arquivo_acessos -> nome do arquivo de acessos
 * @param Acessos -> struct com as informações do arquivo de acessos
 */
Acessos arquivo_acessos(const char *acessos_1);

#endif