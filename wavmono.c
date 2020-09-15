/*  GRR20190374 Tiago Henrique Conte
    Projeto de processamento de áudio
    Programa que gera dois audios mono a partir de um audio stereo
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wav.h"
#include "linhaDeComando.h"

int main(int argc, char **argv){

    FILE *input = NULL;
    // tratamento da linha de comando
    trataComandoInput(argc, argv, &input);
    // Declaração de variável do tipo WAV
    wavFile_t wav;
    uint32_t dataSize;

    // realiza a leitura das informações contidas nos arquivos
    if(!readInfo(&wav, input)){
        fprintf(stderr, "Erro na leitura das informações do arquivo WAV!\n");
        exit(1);
    }
    // verifica se o arquivo é stereo
    if(wav.numChannels != 2){
        fprintf(stderr, "O arquivo WAV não é stereo!\n");
        exit(1);
    }
    // leitura de samples
    if(!readSamples(&wav, input)){
        fprintf(stderr, "Erro na leitura das samples do arquivo WAV!\n");
        exit(1);
    }
    FILE *outputLeft, *outputRight;
    outputLeft = fopen("left.wav","w");
    if(!outputLeft){
        fprintf(stderr, "Erro na leitura do arquivo WAV!\n");
        exit(1);
    }
    outputRight = fopen("right.wav","w");
    if(!outputRight){
        fprintf(stderr, "Erro na leitura do arquivo WAV!\n");
        exit(1);
    }
    dataSize = wav.dataSize;
    wav.dataSize /= 2;
    wav.numChannels /= 2;
    // escreve info no output
    if(!writeInfo(&wav, outputLeft)){
        fprintf(stderr, "Erro na escrita de info em arquivo WAV!\n");
        exit(1);
    }
    if(!writeInfo(&wav, outputRight)){
        fprintf(stderr, "Erro na escrita de info em arquivo WAV!\n");
        exit(1);
    }
    for(int i = 0; i < (dataSize/wav.bytesPerSample); i+=2){
        fwrite(wav.vetorSamples+i, wav.bytesPerSample, 1, outputLeft);
        fwrite(wav.vetorSamples+i+1, wav.bytesPerSample, 1, outputRight);
    }

    return 0;
}