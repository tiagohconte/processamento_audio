/*	GRR20190374 Tiago Henrique Conte
	Projeto de processamento de áudio
	Programa de extração de informação WAV
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wav.h"

FILE * comando(int argc, char **argv){
	int option, flag_i = 0;
	char *value_i;
	// opcoes: -i arquivo
	while((option = getopt(argc, argv, "i:")) != -1)
		switch(option){
			case 'i':		//opcao -i selecionada
				flag_i = 1;
				value_i = optarg;
				break;
			default:
				fprintf(stderr, "Opção requer um argumento!\n");
				exit(1);
		}
	// verifica se houve entrada com -i
	if(flag_i)
		return fopen(value_i,"r");
	else
		return stdin;
}

int main(int argc, char **argv){
	FILE *input;	
	// tratamento da linha de comando
	input = comando(argc, argv);
	if(!input){
		fprintf(stderr, "Erro na leitura do arquivo WAV!\n");
		exit(1);
	}
	// Declaração de variável do tipo WAV
	wavHeader_t wav;
	// realiza a leitura das informações contidas nos arquivos
	if(!readInfo(&wav, input)){
		fprintf(stderr, "Erro na leitura das informações do arquivo WAV!\n");
		exit(1);
	}
	
	printf("riff ID			(%ld bytes): \"%.4s\"\n", sizeof(wav.riffID), wav.riffID);
	printf("riff Size		(%ld bytes): %d\n", sizeof(wav.riffSize), wav.riffSize);
	printf("format			(%ld bytes): \"%.4s\"\n", sizeof(wav.format), wav.format);
	printf("fmt ID			(%ld bytes): \"%.4s\"\n", sizeof(wav.fmtID), wav.fmtID);
	printf("fmt Size		(%ld bytes): %d\n", sizeof(wav.fmtSize), wav.fmtSize);
	printf("audio format		(%ld bytes): %d\n", sizeof(wav.audioFormat), wav.audioFormat);
	printf("number of channels	(%ld bytes): %d\n", sizeof(wav.numChannels), wav.numChannels);
	printf("sample rate		(%ld bytes): %d\n", sizeof(wav.sampleRate), wav.sampleRate);
	printf("byte rate		(%ld bytes): %d\n", sizeof(wav.byteRate), wav.byteRate);
	printf("block align		(%ld bytes): %d\n", sizeof(wav.blockAlign), wav.blockAlign);
	printf("bits per sample		(%ld bytes): %d\n", sizeof(wav.bitsPerSample), wav.bitsPerSample);
	printf("data ID			(%ld bytes): \"%.4s\"\n", sizeof(wav.dataID), wav.dataID);
	printf("data Size		(%ld bytes): %d\n", sizeof(wav.dataSize), wav.dataSize);
	printf("bytes per sample		 : %d\n", wav.bytesPerSample);
	printf("samples per channel		 : %d\n", wav.samplesPerChannel);

	fclose(input);
	return 0;
}