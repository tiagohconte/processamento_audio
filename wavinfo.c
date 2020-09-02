/*	GRR20190374 Tiago Henrique Conte
	Projeto de processamento de áudio
	Programa de extração de informação WAV
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wav.h"

int main(int argc, char **argv){
	int option;
	char *readFile = NULL;

	// opcoes: -i arquivo
	while((option = getopt(argc, argv, "i:")) != -1)
		switch(option){
			case 'i':		//opcao -i selecionada
				readFile = optarg;
				break;
			default:
				fprintf(stderr, "Opção requer um argumento!\n");
				exit(1);
		}

	wavType wav;

	if(!readInfo(&wav, readFile)){
		fprintf(stderr, "Erro na leitura do arquivo WAV!\n");
		exit(1);
	}
	
	printf("riff ID			(%ld bytes): \"%.4s\"\n", sizeof(wav.riffID), wav.riffID);
	printf("riff Size		(%ld bytes): %d\n", sizeof(wav.riffSize), wav.riffSize);
	printf("Format			(%ld bytes): \"%.4s\"\n", sizeof(wav.format), wav.format);
	printf("fmt ID			(%ld bytes): \"%.4s\"\n", sizeof(wav.fmtID), wav.fmtID);
	printf("fmt Size		(%ld bytes): %d\n", sizeof(wav.fmtSize), wav.fmtSize);
	printf("Audio format		(%ld bytes): %d\n", sizeof(wav.audioFormat), wav.audioFormat);
	printf("Number of Channels	(%ld bytes): %d\n", sizeof(wav.numChannels), wav.numChannels);
	printf("Sample rate		(%ld bytes): %d\n", sizeof(wav.sampleRate), wav.sampleRate);
	printf("Byte rate		(%ld bytes): %d\n", sizeof(wav.byteRate), wav.byteRate);
	printf("Block align		(%ld bytes): %d\n", sizeof(wav.blockAlign), wav.blockAlign);
	printf("Bits per sample		(%ld bytes): %d\n", sizeof(wav.bitsPerSample), wav.bitsPerSample);
	printf("data ID			(%ld bytes): \"%.4s\"\n", sizeof(wav.dataID), wav.dataID);
	printf("data Size		(%ld bytes): %d\n", sizeof(wav.dataSize), wav.dataSize);
	printf("Bytes per sample		 : %d\n", wav.bitsPerSample/8);
	printf("samples per channel		 : %d\n", (wav.dataSize/(wav.bitsPerSample/8))/wav.numChannels);

	return 0;
}