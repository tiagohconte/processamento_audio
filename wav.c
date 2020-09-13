/*  GRR20190374 Tiago Henrique Conte
    Projeto de processamento de áudio
    Biblioteca WAV 
*/

#include <stdio.h>
#include <stdlib.h>
#include "wav.h"

#define TAM_HEADER 44

// Lê informações no arquivo WAV
int readInfo(wavFile_t *wav, FILE *readFile){
    if(!readFile)
        return 0;

    fread(wav, TAM_HEADER, 1, readFile);
    wav->bytesPerSample = wav->bitsPerSample/8;
    wav->samplesPerChannel = (wav->dataSize/wav->bytesPerSample)/wav->numChannels;
    
    wav->vetorSamples = NULL;
    
    return 1;   
}
// Lê samples do arquivo WAV
int readSamples(wavFile_t *wav, FILE *readFile){    
    wav->vetorSamples = malloc(wav->dataSize*2);
    if(!wav->vetorSamples){
        fprintf(stderr, "Erro ao alocar samples!");
        return 0;
    }
    while(!feof(readFile)){
        fread(wav->vetorSamples, wav->bytesPerSample, wav->dataSize/wav->bytesPerSample, readFile);
    }

    return 1;

}
// Lê samples do arquivo WAV, adicionando ao final
int catSamples(wavFile_t *wav, wavFile_t *wavPROV, FILE *readFile){
    if(!wav->vetorSamples){
        fprintf(stderr, "Samples só podem ser concatenadas quando já houve uma leitura!\n");
        return 0;
    }
    uint32_t oldDataSize = wav->dataSize;
    wav->dataSize += wavPROV->dataSize;
    wav->samplesPerChannel = (wav->dataSize/wav->bytesPerSample)/wav->numChannels;
    wav->vetorSamples = realloc(wav->vetorSamples, wav->dataSize*2);
    printf("%d\n", oldDataSize);
    if(!wav->vetorSamples){
        fprintf(stderr, "Erro ao realocar samples!");
        return 0;
    }
    while(!feof(readFile)){
        fread(wav->vetorSamples+(oldDataSize/wav->bytesPerSample), wavPROV->bytesPerSample, wavPROV->dataSize/wavPROV->bytesPerSample, readFile);
    }

    return 1;

}
// Escreve informacoes no arquivo WAV
int writeInfo(wavFile_t *wav, FILE *writeFile){
    if(!fwrite(wav, TAM_HEADER, 1, writeFile))
        return 0;

    return 1;
}
// Escreve samples em arquivo WAV
int writeSamples(wavFile_t *wav, FILE *writeFile){
    if(!fwrite(wav->vetorSamples, wav->bytesPerSample, wav->dataSize/wav->bytesPerSample, writeFile))
        return 0;

    return 1;
}