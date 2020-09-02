#include <stdio.h>
#include "wav.h"

// Lê informações no arquivo WAV
int readInfo(wavType *wav, char *readFile){
	FILE *arq;

	if(readFile == NULL)
		fread(wav, sizeof(wavType), 1, stdin);
	else{
		arq = fopen(readFile,"r");
		if(!arq)
			return 0;
		fread(wav, sizeof(wavType), 1, arq);
	}

	return 1;	
}