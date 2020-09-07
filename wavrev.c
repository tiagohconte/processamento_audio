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
	float volume;
	int i;
	// tratamento da linha de comando
	trataComando(argc, argv, &input, &output);
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

	// encontra o valor do pico
	int16_t valorSample, pico = 0;
	for(i = 0; i < (wavFile.dataSize/wavFile.bytesPerSample); i++){
		valorSample = wavFile.vetorSamples[i];
		// verifica que a sample tem valor negativo
		if(valorSample < 0){
			if((-valorSample) > pico)
				pico = (-valorSample);
		}
		else
			if(valorSample > pico)
				pico = valorSample;
	}
	#ifdef DEBUG
	printf("pico: %d\n", pico);
	#endif
	// calcula volume para as samples
	volume = (float) PICO16BITS/pico;
	fprintf(stderr, "Volume automático: %.3f\n", volume);

	// normaliza o volume
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