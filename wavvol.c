/*	GRR20190374 Tiago Henrique Conte
	Projeto de processamento de áudio
	Programa de ajuste de volume
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wav.h"
#include "linhaDeComando.h"

int main(int argc, char **argv){

	FILE *input = NULL, *output = NULL;
	float volume;
	int i;
	// tratamento da linha de comando
	trataComandoIOLevel(argc, argv, &input, &output, &volume);
	// declaração da variável tipo cabeçalho wav
	wavFile_t wavFile;
	// leitura das informações do arquivo wav
	if(!readInfo(&wavFile, input)){
		fprintf(stderr, "Erro na leitura das informações do arquivo WAV!\n");
		exit(1);
	}

	// leitura de samples
	if(!readSamples(&wavFile, input)){
		fprintf(stderr, "Erro na leitura das samples do arquivo WAV!\n");
		exit(1);
	}

	// aumenta o volume
	for(i = 0; i < (wavFile.dataSize/wavFile.bytesPerSample); i++)
		wavFile.vetorSamples[i] *= volume;

	// escreve os samples no output
	if(!writeWAV(&wavFile, output)){
		fprintf(stderr, "Erro na escrita das samples em arquivo WAV!\n");
		exit(1);
	}

	fclose(input);
	fclose(output);

	return 0;
}