/*	GRR20190374 Tiago Henrique Conte
	Projeto de processamento de áudio
	Programa de ajsute de volume
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wav.h"

void comando(int argc, char **argv, FILE **input, FILE **output, float *volume){
	int option, flag_l = 0, flag_i = 0, flag_o = 0;
	char *value_l, *value_i, *value_o;
	// opcoes: -i arquivo
	while((option = getopt(argc, argv, "l:i:o:")) != -1)
		switch(option){
			case 'l':		//opcao -l selecionada
				flag_l = 1;
				value_l = optarg;
				break;
			case 'i':		//opcao -i selecionada
				flag_i = 1;
				value_i = optarg;
				break;
			case 'o':		//opcao -o selecionada
				flag_o = 1;
				value_o = optarg;
				break;
			default:
				fprintf(stderr, "Formato: wavvol -l V -i input -o output\n");
				exit(1);
		}
	// verifica se houve entrada com -o
	if(flag_l)
		*volume = atof(value_l);		
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

int main(int argc, char **argv){

	FILE *input = NULL, *output = NULL;
	float volume;
	// tratamento da linha de comando
	comando(argc, argv, &input, &output, &volume);
	// declaração da variável tipo cabeçalho wav
	wavHeader_t wavFile;
	// leitura das informações do arquivo wav
	if(!readInfo(&wavFile, input)){
		fprintf(stderr, "Erro na leitura das informações do arquivo WAV!\n");
		exit(1);
	}

	// declaração da variável tipo samples wav
	wavSamples_t samples;
	int i;
	// leitura de samples
	if(!readSamples(&wavFile, &samples, input)){
		fprintf(stderr, "Erro na leitura das samples do arquivo WAV!\n");
		exit(1);
	}

	// aumenta o volume
	fprintf(stderr, "%f\n", volume);
	for(i = 0; i < (wavFile.dataSize/wavFile.bytesPerSample); i++)
		samples.vetorSamples[i] *= volume;

	// escreve os samples no output
	if(!writeSamples(&wavFile, &samples, output)){
		fprintf(stderr, "Erro na escrita das samples em arquivo WAV!\n");
		exit(1);
	}

	fclose(input);
	fclose(output);

	return 0;
}