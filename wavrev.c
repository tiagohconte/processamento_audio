/*	GRR20190374 Tiago Henrique Conte
	Projeto de processamento de áudio
	Programa de reversão WAV
*/
#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
#include "linhaDeComando.h"

int main(int argc, char **argv){

	FILE *input = NULL, *output = NULL;
	int i;
	// tratamento da linha de comando
	trataComandoIO(argc, argv, &input, &output);
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

	// escreve info no output
	if(!writeInfo(&wavFile, output)){
		fprintf(stderr, "Erro na escrita de info em arquivo WAV!\n");
		exit(1);
	}

	// escreve os samples no output ao contrário
	for(i = (wavFile.dataSize/wavFile.bytesPerSample); i >= -1; --i)
		fwrite(wavFile.vetorSamples+i, wavFile.bytesPerSample, 1, output);

	free(wavFile.vetorSamples);
	fclose(input);
	fclose(output);

	return 0;
}