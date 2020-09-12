/*  GRR20190374 Tiago Henrique Conte
    Projeto de processamento de áudio
    Biblioteca WAV 
*/

#include <stdio.h>
#include <stdlib.h>
#include "wav.h"

// Lê informações no arquivo WAV
int readInfo(wavFile_t *wav, FILE *readFile){
    if(!readFile)
        return 0;

    fread(wav, 44, 1, readFile);
    wav->bytesPerSample = wav->bitsPerSample/8;
    wav->samplesPerChannel = (wav->dataSize/wav->bytesPerSample)/wav->numChannels;

    return 1;   
}
// Lê samples do arquivo WAV e retorna numero de samples
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
// Escreve informacoes no arquivo WAV
int writeInfo(wavFile_t *wav, FILE *writeFile){
    if(!fwrite(wav, 44, 1, writeFile))
        return 0;

    return 1;
}
// Escreve samples em arquivo WAV
int writeSamples(wavFile_t *wav, FILE *writeFile){
    if(!fwrite(wav->vetorSamples, wav->bytesPerSample, wav->dataSize/wav->bytesPerSample, writeFile))
        return 0;

    return 1;
}