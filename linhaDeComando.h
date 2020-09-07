/*	GRR20190374 Tiago Henrique Conte
	Projeto de processamento de áudio
	Biblioteca para tratamento da linha de comando
*/
// comandos com input apenas
void trataComandoInput(int argc, char **argv, FILE **input);
// comandos com input e output
void trataComandoIO(int argc, char **argv, FILE **input, FILE **output);
// comandos com input, output e level
void trataComandoIOLevel(int argc, char **argv, FILE **input, FILE **output, float *level);