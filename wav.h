/*	GRR20190374 Tiago Henrique Conte
	Projeto de processamento de áudio
	Cabeçalho Biblioteca WAV 
*/
#include <stdint.h>

// Struct para cabeçalho de arquivo WAV
typedef struct wavHeader_t {
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
} wavHeader_t;

typedef struct wavSamples_t {
	uint32_t *vetorSamples;
} wavSamples_t;


// Lê informações do arquivo WAV
int readInfo(wavHeader_t *wav, FILE *readFile);
// Lê samples do arquivo WAV
int readSamples(wavHeader_t *wav, wavSamples_t *samples, FILE *readFile);
// Escreve samples em arquivo WAV
int writeSamples(wavHeader_t *wav, wavSamples_t *samples, FILE *writeFile);