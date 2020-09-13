/*  GRR20190374 Tiago Henrique Conte
    Projeto de processamento de áudio
    Biblioteca para tratamento da linha de comando
*/

#ifndef __COMMANDLINE__
#define __COMMANDLINE__

#define VALOR_ALOC 5
#define MAX_INPUT 20

// comandos com input apenas
void trataComandoInput(int argc, char **argv, FILE **input);
// comandos com input e output
void trataComandoIO(int argc, char **argv, FILE **input, FILE **output);
// comandos com input, output e level
void trataComandoIOLevel(int argc, char **argv, FILE **input, FILE **output, float *level);
// comandos com input, output, level e time
void trataComandoIOLevelTime(int argc, char **argv, FILE **input, FILE **output, float *level, int *time);
// comandos com varios inputs e um output
void trataComandoVariosInputs(int argc, char **argv, int *inputFiles, FILE **output);

#endif