/*  GRR20190374 Tiago Henrique Conte
    Projeto de processamento de áudio
    Programa de concatenação de arquivos WAV
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "wav.h"
#include "linhaDeComando.h"

int main(int argc, char **argv){
    
    FILE *input = NULL, *output = NULL;
    int inputPos[MAX_INPUT+1], i;
    // tratamento da linha de comando
    trataComandoVariosInputs(argc, argv, inputPos, &output);
    // criacao variavel tipo wavFile, uma original e outra provisoria
    wavFile_t wavFile, wavFilePROV;

    /* Lê todas os inputs e realiza a concatenação */
    for(i = 0; i < inputPos[MAX_INPUT]; i++){
        input = fopen(argv[inputPos[i]], "r");

        if(i == 0){
            // leitura das informações do arquivo wav
            if(!readInfo(&wavFile, input)){
                fprintf(stderr, "Erro na leitura das informações do arquivo %s\n", argv[inputPos[i]]);
                exit(1);
            }
            // leitura de samples
            if(!readSamples(&wavFile, input)){
                fprintf(stderr, "Erro na leitura das samples do arquivo WAV!\n");
                exit(1);
            }
        }else{  
            // leitura das informações do arquivo wav
            if(!readInfo(&wavFilePROV, input)){
                fprintf(stderr, "Erro na leitura das informações do arquivo %s\n", argv[inputPos[i]]);
                exit(1);
            }      
            // verifica se possuem taxas de amostragem diferentes
            if(wavFile.sampleRate != wavFilePROV.sampleRate){
                fprintf(stderr, "Os arquivos possuem taxas de amostragem diferentes!\n");
                exit(1);
            }
            // leitura de samples
            if(!catSamples(&wavFile, &wavFilePROV, input)){
                fprintf(stderr, "Erro na leitura das samples do arquivo %s\n", argv[inputPos[i]]);
                exit(1);
            }
        }        

        fclose(input);

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
    fclose(output);

    return 0;
        
}