/*  GRR20190374 Tiago Henrique Conte
    Projeto de processamento de áudio
    Biblioteca para tratamento da linha de comando
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "linhaDeComando.h"

// comandos com input apenas
void trataComandoInput(int argc, char **argv, FILE **input){
    int option, flag_i = 0;
    char *value_i;

    // opcoes: -i entrada
    while((option = getopt(argc, argv, "i:")) != -1)
        switch(option){
            case 'i':       //opcao -i selecionada
                flag_i = 1;
                value_i = optarg;
                break;
            default:
                fprintf(stderr, "Formato: %s -i input\n", argv[0]);
                exit(1);
        }

    if(flag_i){
        *input = fopen(value_i,"r");
        if(!input){
            fprintf(stderr, "Erro na leitura do arquivo WAV!\n");
            exit(1);
        }
    }else
        *input = stdin;
}

// comandos com I/O
void trataComandoIO(int argc, char **argv, FILE **input, FILE **output){
    int option, flag_i = 0, flag_o = 0;
    char *value_i, *value_o;

    // opcoes: -i entrada -o saida
    while((option = getopt(argc, argv, "i:o:")) != -1)
        switch(option){
            case 'i':       //opcao -i selecionada
                flag_i = 1;
                value_i = optarg;
                break;
            case 'o':       //opcao -o selecionada
                flag_o = 1;
                value_o = optarg;
                break;
            default:
                fprintf(stderr, "Formato: %s -i input -o output\n", argv[0]);
                exit(1);
        }   
    // verifica se houve entrada com -i
    if(flag_i){
        *input = fopen(value_i,"r");
        if(!input){
            fprintf(stderr, "Erro na leitura do arquivo WAV!\n");
            exit(1);
        }
    }else
        *input = stdin;
    // verifica se houve entrada com -o
    if(flag_o)
        *output = fopen(value_o,"w");
    else
        *output = stdout;
}

// comandos com I/O e level
void trataComandoIOLevel(int argc, char **argv, FILE **input, FILE **output, float *level){
    int option, flag_i = 0, flag_o = 0, flag_l = 0;
    char *value_i, *value_o, *value_l;
    
    // opcoes: -l level -i entrada -o saida
    while((option = getopt(argc, argv, "l:i:o:")) != -1)
        switch(option){
            case 'l':       //opcao -l selecionada
                flag_l = 1;
                value_l = optarg;
                break;
            case 'i':       //opcao -i selecionada
                flag_i = 1;
                value_i = optarg;
                break;
            case 'o':       //opcao -o selecionada
                flag_o = 1;
                value_o = optarg;
                break;
            default:
                fprintf(stderr, "Formato: %s -l value -i input -o output\n", argv[0]);
                exit(1);
        }
    // verifica se houve entrada com -l
    if(flag_l)
        *level = atof(value_l);     
    // verifica se houve entrada com -i
    if(flag_i){
        *input = fopen(value_i,"r");
        if(!input){
            fprintf(stderr, "Erro na leitura do arquivo WAV!\n");
            exit(1);
        }
    }else
        *input = stdin;
    // verifica se houve entrada com -o
    if(flag_o)
        *output = fopen(value_o,"w");
    else
        *output = stdout;

    return;
}
// comandos com I/O, level e time
void trataComandoIOLevelTime(int argc, char **argv, FILE **input, FILE **output, float *level, int *time){
    int option, flag_i = 0, flag_o = 0, flag_l = 0, flag_t = 0;
    char *value_i, *value_o, *value_l, *value_t;
    
    // opcoes: -t time -l level -i entrada -o saida
    while((option = getopt(argc, argv, "t:l:i:o:")) != -1)
        switch(option){
            case 't':       //opcao -t selecionada
                flag_t = 1;
                value_t = optarg;
                break;
            case 'l':       //opcao -l selecionada
                flag_l = 1;
                value_l = optarg;
                break;
            case 'i':       //opcao -i selecionada
                flag_i = 1;
                value_i = optarg;
                break;
            case 'o':       //opcao -o selecionada
                flag_o = 1;
                value_o = optarg;
                break;
            default:
                fprintf(stderr, "Formato: %s -t value -l value -i input -o output\n", argv[0]);
                exit(1);
        }
    // verifica se houve entrada com -t
    if(flag_t){
        *time = atoi(value_t);
    }
    // verifica se houve entrada com -l
    if(flag_l)
        *level = atof(value_l);     
    // verifica se houve entrada com -i
    if(flag_i){
        *input = fopen(value_i,"r");
        if(!input){
            fprintf(stderr, "Erro na leitura do arquivo WAV!\n");
            exit(1);
        }
    }else
        *input = stdin;
    // verifica se houve entrada com -o
    if(flag_o)
        *output = fopen(value_o,"w");
    else
        *output = stdout;

    return;
}

// comandos com varios inputs e um output
void trataComandoVariosInputs(int argc, char **argv, int *inputFiles, FILE **output){
    int i = 1, flag_o = 0, contInput = 0;
    char *value_o;

    // opcoes: -o saida
    while(i < argc){
        if(!strcmp(argv[i], "-o")){    //opcao -o selecionada
            if(argv[i+1] != NULL){   // verifica se tem argumento para -o
                flag_o = 1;
                i++;
                value_o = argv[i];
            }else{
                fprintf(stderr, "Formato: %s ... -o outputFile\n", argv[0]);
                exit(1);
            }
        }else{
            /*  verifica se tem mais argumentos de
                input do que o definido por MAX_INPUT   */
            if(contInput > MAX_INPUT){
                fprintf(stderr, "Muitos argumentos! Limite de inputs: %d\n", MAX_INPUT);
                exit(1);
            }  
            // adiciona a posicao do arquivo input em argv
            inputFiles[contInput] = i;
            contInput++;
        }
        i++;        
    }
    // verifica se há mais de uma entrada
    if(contInput < 2){
        fprintf(stderr, "Poucos argumentos! %s espera ao menos 2 arquivos de input\n", argv[0]);
        exit(1);
    }
    // guarda o tamanho de input no último espaço do vetor
    inputFiles[MAX_INPUT] = contInput;
    // verifica se houve entrada com -o
    if(flag_o)
        *output = fopen(value_o,"w");
    else
        *output = stdout;
}