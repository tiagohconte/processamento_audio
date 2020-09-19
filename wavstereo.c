/*  GRR20190374 Tiago Henrique Conte
    Projeto de processamento de áudio
    Programa que gera um audio stereo a partir de dois monos
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wav.h"
#include "linhaDeComando.h"

int main(int argc, char **argv){

    FILE *inputLeft = NULL, *inputRight = NULL, *output = NULL;
    int inputPos[MAX_INPUT+1];
    // tratamento da linha de comando
    trataComandoVariosInputs(argc, argv, inputPos, &output);
    // Declaração de variável do tipo WAV
    wavFile_t wavLeft, wavRight, wavOut;

    // Verifica se houveram 2 áudio na entrada
    if(inputPos[MAX_INPUT] > 2){
        fprintf(stderr, "São permitidos apenas 2 áudios nesta operação!\n");
        exit(1);
    }else if(inputPos[MAX_INPUT] < 2){
        fprintf(stderr, "São necessários 2 áudios para esta operação!\n");
        exit(1);
    }

    // Abre os arquivos para leitura
    inputLeft = fopen(argv[inputPos[0]],"r");
    if(!inputLeft){
        fprintf(stderr, "Erro na leitura do arquivo WAV!\n");
        exit(1);
    }
    inputRight = fopen(argv[inputPos[1]],"r");
    if(!inputRight){
        fprintf(stderr, "Erro na leitura do arquivo WAV!\n");
        exit(1);
    }
    // pega cabecalho para por na saída
    if(!readInfo(&wavOut, inputLeft)){
        fprintf(stderr, "Erro na leitura das informações do arquivo %s!\n", argv[inputPos[0]]);
        exit(1);
    }
    rewind(inputLeft);
    // realiza a leitura das informações contidas nos arquivos
    if(!readInfo(&wavLeft, inputLeft)){
        fprintf(stderr, "Erro na leitura das informações do arquivo %s!\n", argv[inputPos[0]]);
        exit(1);
    }
    if(!readInfo(&wavRight, inputRight)){
        fprintf(stderr, "Erro na leitura das informações do arquivo %s!\n", argv[inputPos[1]]);
        exit(1);
    }
    // verifica se os arquivos são mono
    if((wavLeft.numChannels != 1) || (wavRight.numChannels != 1)){
        fprintf(stderr, "Um dos arquivos de input não é mono!\n");
        exit(1);
    }
    // leitura de samples
    if(!readSamples(&wavLeft, inputLeft)){
        fprintf(stderr, "Erro na leitura das samples do arquivo %s!\n", argv[inputPos[0]]);
        exit(1);
    }
    if(!readSamples(&wavRight, inputRight)){
        fprintf(stderr, "Erro na leitura das samples do arquivo %s!\n", argv[inputPos[1]]);
        exit(1);
    }

    wavOut.dataSize = wavLeft.dataSize + wavRight.dataSize;
    wavOut.numChannels = 2;

    // escreve info no output
    if(!writeInfo(&wavOut, output)){
        fprintf(stderr, "Erro na escrita de info em arquivo WAV!\n");
        exit(1);
    }
    int dataSize;
    if(wavLeft.dataSize > wavRight.dataSize)
        dataSize = wavLeft.dataSize;
    else
        dataSize = wavRight.dataSize;

    for(int i = 0; i < (dataSize/wavOut.bytesPerSample); i++){
        if(i <= wavLeft.dataSize/wavLeft.bytesPerSample)
            fwrite(wavLeft.vetorSamples+i, wavLeft.bytesPerSample, 1, output);
        if(i <= wavRight.dataSize/wavRight.bytesPerSample)
            fwrite(wavRight.vetorSamples+i, wavRight.bytesPerSample, 1, output);
    }
    
    return 0;
}