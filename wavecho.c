/*  GRR20190374 Tiago Henrique Conte
    Projeto de processamento de áudio
    Programa de eco em WAV
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wav.h"
#include "linhaDeComando.h"

#define PICO16BITS 32767

int main(int argc, char **argv){

    FILE *input = NULL, *output = NULL;
    float level = 0.5;
    int i, delay = 1000;
    // tratamento da linha de comando
    trataComandoIOLevelTime(argc, argv, &input, &output, &level, &delay);
    if(delay < 0)
        fprintf(stderr, "Valor de delay inválido! (delay >= 0)\n");
    if((level < 0) || (level > 1))
        fprintf(stderr, "Valor de level inválido! (0.0 <= level <= 1.0)\n");
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

    // calcula o eco
    for(i = 0; i < (wavFile.dataSize/wavFile.bytesPerSample); i++)
        if(i > (wavFile.sampleRate/1000)*delay)
            wavFile.vetorSamples[i] += (level * wavFile.vetorSamples[i-(wavFile.sampleRate/1000)*delay]);

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