/*  GRR20190374 Tiago Henrique Conte
    Projeto de processamento de áudio
    Programa de ajuste de volume
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wav.h"
#include "linhaDeComando.h"

int main(int argc, char **argv){

    FILE *input = NULL, *output = NULL;
    float volume = 1;
    int i;
    // tratamento da linha de comando
    trataComandoIOLevel(argc, argv, &input, &output, &volume);
    // verifica se volume está dentro dos fator de ajuste
    if((volume < 0) || (volume > 10))
        fprintf(stderr, "Volume inválido!\n");
    // declaração da variável tipo cabeçalho wav
    wavFile_t wavFile;
    // leitura das informações do arquivo wav
    if(!readInfo(&wavFile, input)){
        fprintf(stderr, "Erro na leitura das informações do arquivo WAV!\n");
        exit(1);
    }

    // leitura de samples
    if(!readSamples(&wavFile, input)){
        fprintf(stderr, "Erro na leitura das samples do arquivo WAV!\n");
        exit(1);
    }

    // aumenta o volume
    for(i = 0; i < (wavFile.dataSize/wavFile.bytesPerSample); i++)
        wavFile.vetorSamples[i] *= volume;

    // escreve info no output
    if(!writeInfo(&wavFile, output)){
        fprintf(stderr, "Erro na escrita de info em arquivo WAV!\n");
        exit(1);
    }
    // escreve os samples no output
    if(!writeSamples(&wavFile, output)){
        fprintf(stderr, "Erro na escrita das samples em arquivo WAV!\n");
        exit(1);
    }

    free(wavFile.vetorSamples);
    fclose(input);
    fclose(output);

    return 0;
}