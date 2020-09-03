# GRR20190374 Tiago Henrique Conte
# define as flags para compilação
CFLAGS = -Wall
CC = gcc
 
objs = wav.o
 
# regra default
all: wavinfo wavvol
 
# regras de ligacao
wavinfo: $(objs) wavinfo.o
wavvol: $(objs) wavvol.o
 
# regras de compilação
wavinfo.o: wavinfo.c wav.h
wavvol.o: wavvol.c wav.h	
wav.o: wav.c wav.h

# compila com flags de depuração
debug: CFLAGS += -DDEBUG -g
debug: all

# remove arquivos temporários
clean:
	-rm -f $(objs) wavinfo.o wavvol.o

# remove tudo o que não for o código-fonte
purge: clean
	-rm -f wavinfo wavvol