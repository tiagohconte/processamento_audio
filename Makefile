# GRR20190374 Tiago Henrique Conte
# define as flags para compilação
CFLAGS = -Wall
CC = gcc
 
objs = wav.o linhaDeComando.o
 
# regra default
all: wavinfo wavvol wavnorm wavrev
 
# regras de ligacao
wavinfo: $(objs) wavinfo.o
wavvol: $(objs) wavvol.o
wavnorm: $(objs) wavnorm.o
wavrev: $(objs)	wavrev.o
 
# regras de compilação
wavinfo.o: wavinfo.c wav.h linhaDeComando.h
wavvol.o: wavvol.c wav.h linhaDeComando.h
wavnorm.o: wavnorm.c wav.h linhaDeComando.h
wavrev.o: wavrev.c wav.h linhaDeComando.h
wav.o: wav.c wav.h
linhaDeComando.o: linhaDeComando.c linhaDeComando.h

# compila com flags de depuração
debug: CFLAGS += -DDEBUG -g
debug: all

# remove arquivos temporários
clean:
	-rm -f $(objs) wavinfo.o wavvol.o wavnorm.o wavrev.o

# remove tudo o que não for o código-fonte
purge: clean
	-rm -f wavinfo wavvol wavnorm wavrev