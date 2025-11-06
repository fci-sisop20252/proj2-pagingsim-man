#include "ram.h"

RAM criarRAM(int num_frames, int tam_pag, int** processos, int num_processos) {
    RAM nova_RAM;

    nova_RAM.frames = malloc(num_frames * sizeof(int));
    for (int i = 0; i < num_frames; i++) nova_RAM.frames[i] = -1;
    nova_RAM.num_frames = num_frames;
    nova_RAM.tam_pag = tam_pag;

    nova_RAM.processos = processos;
    nova_RAM.num_processos = num_processos;

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