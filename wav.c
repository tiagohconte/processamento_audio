/*	GRR20190374 Tiago Henrique Conte
	Projeto de processamento de áudio
	Biblioteca WAV 
*/

#include <stdio.h>
#include <stdlib.h>
#include "wav.h"

// Lê informações no arquivo WAV
int readInfo(wavHeader_t *wav, FILE *readFile){
	if(!readFile)
		return 0;

	fread(wav, sizeof(wavHeader_t)-8, 1, readFile);
	wav->bytesPerSample = wav->bitsPerSample/8;
	wav->samplesPerChannel = (wav->dataSize/wav->bytesPerSample)/wav->numChannels;

	return 1;	
}
// Lê samples do arquivo WAV
int readSamples(wavHeader_t *wav, wavSamples_t *samples, FILE *readFile){	
	samples->vetorSamples = malloc(wav->dataSize);
	if(!samples->vetorSamples){
		fprintf(stderr, "Erro ao alocar samples!");
		return 0;
	}
	while(!feof(readFile)){
		fread(samples->vetorSamples, wav->bytesPerSample, wav->dataSize/wav->bytesPerSample, readFile);
	}

	return 1;

}
// Escreve samples em arquivo WAV
int writeSamples(wavHeader_t *wav, wavSamples_t *samples, FILE *writeFile){
	fwrite(wav, sizeof(wavHeader_t)-8, 1, writeFile);
	fwrite(samples->vetorSamples, wav->bytesPerSample, wav->dataSize/wav->bytesPerSample, writeFile);

	return 1;
}