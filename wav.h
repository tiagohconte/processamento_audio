/*	GRR20190374 Tiago Henrique Conte
	Projeto de processamento de áudio
	Cabeçalho Biblioteca WAV 
*/
#include <stdint.h>

// Struct para cabeçalho de arquivo WAV
typedef struct wavFile_t {
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
	uint16_t bytesPerSample;
	uint32_t samplesPerChannel;
	uint32_t *vetorSamples;
} wavFile_t;


// Lê informações do arquivo WAV
int readInfo(wavFile_t *wav, FILE *readFile);
// Lê samples do arquivo WAV
int readSamples(wavFile_t *wav, FILE *readFile);
// Escreve samples em arquivo WAV
int writeSamples(wavFile_t *wav, FILE *writeFile);