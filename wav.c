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
    // aloca espaço em memória para as samples  
    wav->vetorSamples = malloc(wav->dataSize);
    if(!wav->vetorSamples){
        fprintf(stderr, "Erro ao alocar samples!");
        return 0;
    }
    // lê as samples do arquivo para dentro do vetor
    while(!feof(readFile)){
        fread(wav->vetorSamples, wav->bytesPerSample, wav->dataSize/wav->bytesPerSample, readFile);
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


// Lê samples do arquivo WAV, adicionando ao final
int catSamples(wavFile_t *wav, wavFile_t *wavPROV, FILE *readFile){
    if(!wav->vetorSamples){
        fprintf(stderr, "Samples só podem ser concatenadas quando já houve uma leitura!\n");
        return 0;
    }
    uint32_t oldDataSize = wav->dataSize;
    wav->dataSize += wavPROV->dataSize;
    wav->samplesPerChannel = (wav->dataSize/wav->bytesPerSample)/wav->numChannels;
    wav->vetorSamples = realloc(wav->vetorSamples, wav->dataSize);
    if(!wav->vetorSamples){
        fprintf(stderr, "Erro ao realocar samples!");
        return 0;
    }
    while(!feof(readFile)){
        fread(wav->vetorSamples+(oldDataSize/wav->bytesPerSample), wavPROV->bytesPerSample, wavPROV->dataSize/wavPROV->bytesPerSample, readFile);
    }

    return 1;

}

// Lê samples do arquivo WAV, mixando com as existentes
int mixSamples(wavFile_t *mix, int tamInput, FILE *readFile){
    wavFile_t wav;
    int i;
    
    // lê info do arquivo wav    
    if(!readInfo(&wav, readFile)){
        fprintf(stderr, "Erro na leitura das informações do arquivo\n");
        exit(1);
    }
    // verifica se o tamanho do arquivo mais recente é maior que o padrão do mix
    if(wav.dataSize > mix->dataSize){
        mix->dataSize = wav.dataSize;
        mix->vetorSamples = realloc(mix->vetorSamples, mix->dataSize);
        if(!mix->vetorSamples){
            fprintf(stderr, "Erro ao realocar samples!");
            return 0;
        }
    }
    if(!mix->vetorSamples){
        // aloca espaço em memória para as samples  
        mix->vetorSamples = malloc(mix->dataSize);
        if(!mix->vetorSamples){
            fprintf(stderr, "Erro ao alocar espaço para samples!");
            return 0;
        }
    }

    // leitura de samples
    if(!readSamples(&wav, readFile)){
        fprintf(stderr, "Erro na leitura das samples do arquivo WAV!\n");
        exit(1);
    }
    // realiza a mixagem
    for(i = 0; i < (wav.dataSize/wav.bytesPerSample); i++){
        mix->vetorSamples[i] += wav.vetorSamples[i]/tamInput;
    }

    free(wav.vetorSamples);

    return 1;
}