#include "ram.h"

Processo inicializarProcesso(int pid, int tamanho_virtual, int tam_pag) {
    Processo p;
    p.pid = pid;
    p.tamanho_memoria_virtual = tamanho_virtual;
    p.num_paginas = tamanho_virtual / tam_pag;

    p.tabela_paginas = malloc(p.num_paginas * sizeof(PageTableEntry));

    for (int i = 0; i < p.num_paginas; i++) {
        p.tabela_paginas[i].frame_id = -1;
        p.tabela_paginas[i].valid_bit = 0;
    }
    return p;
}

RAM criarRAM(int num_frames, int tam_pag, int num_processos, int** processos_config) {
    RAM nova_RAM;

    nova_RAM.num_frames = num_frames;
    nova_RAM.tam_pag = tam_pag;
    nova_RAM.num_processos = num_processos;
    
    nova_RAM.clock_pointer = 0;
    nova_RAM.next_fifo_index = 0;
    nova_RAM.total_page_faults = 0;
    nova_RAM.total_acessos = 0;

    nova_RAM.frames = malloc(num_frames * sizeof(Frame));
    for (int i = 0; i < num_frames; i++) {
        nova_RAM.frames[i].pid = -1;
        nova_RAM.frames[i].pagina_virtual = -1;
        nova_RAM.frames[i].r_bit = 0;
        nova_RAM.frames[i].ordem_chegada = -1;
    }

    nova_RAM.processos = malloc(num_processos * sizeof(Processo));
    for (int i = 0; i < num_processos; i++) {
        int pid = processos_config[i][0];
        int tamanho = processos_config[i][1];
        nova_RAM.processos[i] = inicializarProcesso(pid, tamanho, tam_pag);
    }
    
    for (int i = 0; i < num_processos; i++) free(processos_config[i]);
    free(processos_config);

    return nova_RAM;
}

void freeRAM(RAM ram) {
    free(ram.frames);
    ram.frames = NULL;

    for (int i = 0; i < ram.num_processos; i++)
        free(ram.processos[i]);
    free(ram.processos);
    ram.processos = NULL;

    ram.tam_pag = 0;
    ram.num_frames = 0;
    ram.num_processos = 0;
}

void printFrames(RAM ram) {
    printf("Frames: [\n");
    for (int i = 0; i < ram.num_frames; i++)
        printf("    Frame %d: PID %d\n", i+1, ram.frames[i]);

    printf("\n"
        "   (Nota: -1 = Nao utilizado)\n"
        "]\n"
    );
}

void printProcessos(RAM ram) {
    printf("Processos: [\n");
    for (int i = 0; i < ram.num_processos; i++) 
        printf("    Processo %d: Tamanho %d\n", ram.processos[i][0], ram.processos[i][1]);

    printf("]\n");
}