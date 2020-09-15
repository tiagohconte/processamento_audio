/*  GRR20190374 Tiago Henrique Conte
    Projeto de processamento de áudio
    Programa de mixagem de arquivos WAV
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wav.h"
#include "linhaDeComando.h"

int main(int argc, char **argv){

    FILE *input = NULL, *output = NULL;
    int inputPos[MAX_INPUT+1], i;
    // tratamento da linha de comando
    trataComandoVariosInputs(argc, argv, inputPos, &output);
    // criacao variavel tipo wavFile para armazenar o mix
    wavFile_t wavMix;

    /* Lê todos os inputs e realiza a mixagem */
    int tamInput = inputPos[MAX_INPUT];
    for(i = 0; i < tamInput; i++){
        input = fopen(argv[inputPos[i]], "r");
        // lê o primeiro input antes para adquirir padrão
        if(i == 0){
            // leitura das informações do arquivo wav
            if(!readInfo(&wavMix, input)){
                fprintf(stderr, "Erro na leitura das informações do arquivo %s\n", argv[inputPos[i]]);
                exit(1);
            }
            rewind(input);
        }
        // mixagem de samples
        if(!mixSamples(&wavMix, tamInput, input)){
            fprintf(stderr, "Erro na leitura das samples do arquivo %s\n", argv[inputPos[i]]);
            exit(1);
        }

        fclose(input);
    }

    // escreve info no output
    if(!writeInfo(&wavMix, output)){
        fprintf(stderr, "Erro na escrita de info em arquivo WAV!\n");
        exit(1);
    }
    // escreve os samples no output
    if(!writeSamples(&wavMix, output)){
        fprintf(stderr, "Erro na escrita das samples em arquivo WAV!\n");
        exit(1);
    }

    free(wavMix.vetorSamples);
    fclose(output);

    return 0;
}