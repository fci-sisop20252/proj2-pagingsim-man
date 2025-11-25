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

#include "arquivo.h"

ConfigMemoria arquivo_config(const char *config_1) {
    ConfigMemoria ptr;
    
    FILE *config_file = fopen(config_1, "r");
    // Verificação:
    if (config_file == NULL) {
        perror("ERROR opening File <arquivo_config>");
        exit(1);
    }
    
    // Carrega as informacoes do arquivo para struct:
    fscanf(config_file, "%d", &ptr.num_frames);
    fscanf(config_file, "%u", &ptr.tamanho_pag);
    fscanf(config_file, "%d", &ptr.quant_processos);
    
    /* Para debugar:
    printf("\nQuant. frames: %d", ptr.num_frames);
    printf("\nTamanho da página: %u", ptr.tamanho_pag);
    printf("\nProcessos: %d\n", ptr.quant_processos);
    */

    for (int a = 0; a < ptr.quant_processos && a < MAX_PROCESSOS; a++) {
        if (fscanf(config_file, "%d %u", &ptr.pid[a], &ptr.tamanho_mem_virtual[a]) != 2) {
            printf("Erro ao ler processo %d\n", a);
            break;
        }
    }

    fclose(config_file);
    return ptr;
}

Acessos arquivo_acessos(const char *acessos_1) {
    Acessos ptr;
    ptr.quant_acessos = 0;
    
    FILE *file = fopen(acessos_1, "r");
    if (file == NULL) {
        perror("ERROR opening File <arquivo_acessos>");
        exit(1);
    }
    // Carrega as informacoes do arquivo para struct:
    while (ptr.quant_acessos < MAX_ACCESS && fscanf(file, "%d %u", &ptr.pid[ptr.quant_acessos], &ptr.end_mem_virtual[ptr.quant_acessos]) == 2) {
        ptr.quant_acessos++;
    }

    fclose(file);
    return ptr;
}