/*  GRR20190374 Tiago Henrique Conte
    Projeto de processamento de áudio
    Programa de estéreo ampliado
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wav.h"
#include "linhaDeComando.h"

#define PICO16BITS 32767

int main(int argc, char **argv){

    FILE *input = NULL, *output = NULL;
    float k = 1;
    int i;
    // tratamento da linha de comando
    trataComandoIOLevel(argc, argv, &input, &output, &k);
    // verifica se volume está dentro dos fator de ajuste
    if((k < 0) || (k > 10))
        fprintf(stderr, "Fator de ampliação inválido!\n");
    // declaração da variável tipo cabeçalho wav
    wavFile_t wavFile;
    // leitura das informações do arquivo wav
    if(!readInfo(&wavFile, input)){
        fprintf(stderr, "Erro na leitura das informações do arquivo WAV!\n");
        exit(1);
    }
    if(wavFile.numChannels != 2){
        fprintf(stderr, "O arquivo WAV possui número de canais incompatível com essa operação!\n");
        exit(1);
    }

    // leitura de samples
    if(!readSamples(&wavFile, input)){
        fprintf(stderr, "Erro na leitura das samples do arquivo WAV!\n");
        exit(1);
    }

    int16_t diff;
    // realiza a ampliação do estéreo
    for(i = 0; i <= (wavFile.dataSize/wavFile.bytesPerSample); i+=2){
        diff = wavFile.vetorSamples[i+1] - wavFile.vetorSamples[i];
        wavFile.vetorSamples[i+1] += (k * diff);
        wavFile.vetorSamples[i] -= (k * diff);
    }

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