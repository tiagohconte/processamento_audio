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
    // tratamento da linha de comando
    trataComandoOutput(argc, argv, &output);

    

    return 0;
}