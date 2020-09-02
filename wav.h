/*	GRR20190374 Tiago Henrique Conte
	Projeto de processamento de áudio
	Biblioteca WAV 
*/
#include <stdint.h>

typedef struct wavType {
	// Informacoes do RIFF
	char riffID[4];
	uint32_t riffSize;
	char format[4];
	// Informacoes do fmt
	char fmtID[4];
	uint32_t fmtSize;
	uint16_t audioFormat;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;
	// Informacoes do data
	char dataID[4];
	uint32_t dataSize;
} wavType;

// Lê informações no arquivo WAV
int readInfo(wavType *wav, char *readFile);