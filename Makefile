# GRR20190374 Tiago Henrique Conte
# define as flags para compilação
CFLAGS = -Wall
CC = gcc
 
objs = wav.o linhaDeComando.o
 
# regra default
all: wavinfo wavvol wavnorm
 
# regras de ligacao
wavinfo: $(objs) wavinfo.o
wavvol: $(objs) wavvol.o
wavnorm: $(objs) wavnorm.o
 
# regras de compilação
wavinfo.o: wavinfo.c wav.h
wavvol.o: wavvol.c wav.h
wavnorm.o: wavnorm.c wav.h
wav.o: wav.c wav.h
linhaDeComando.o: linhaDeComando.c linhaDeComando.h

# compila com flags de depuração
debug: CFLAGS += -DDEBUG -g
debug: all

# remove arquivos temporários
clean:
	-rm -f $(objs) wavinfo.o wavvol.o wavnorm.o

# remove tudo o que não for o código-fonte
purge: clean
	-rm -f wavinfo wavvol wavnorm