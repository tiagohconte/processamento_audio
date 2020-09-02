# GRR20190374 Tiago Henrique Conte
# define as flags para compilação
CFLAGS = -Wall
CC = gcc
 
objs = wav.o wavinfo.o
 
# regra default
#all:
 
# regras de ligacao
wavinfo: $(objs)
 
# regras de compilação
wavinfo.o: wavinfo.c wav.h
wav.o: wav.c wav.h

# compila com flags de depuração
debug: CFLAGS += -DDEBUG -g
debug: all

# remove arquivos temporários
clean:
	-rm -f $(objs)

# remove tudo o que não for o código-fonte
purge: clean
	-rm -f wavinfo