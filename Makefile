# GRR20190374 Tiago Henrique Conte
# define as flags para compilação
CFLAGS = -Wall
CC = gcc

BINARIES = wavinfo wavvol wavnorm wavrev wavecho wavwide wavcat wavmix wavmono wavstereo
 
objs = wav.o linhaDeComando.o
libs = wav.h linhaDeComando.h
 
# regra default
all: $(BINARIES)
 
# regras de ligacao
wavinfo: $(objs) wavinfo.o
wavvol: $(objs) wavvol.o
wavnorm: $(objs) wavnorm.o
wavrev: $(objs)	wavrev.o
wavecho: $(objs) wavecho.o
wavwide: $(objs) wavwide.o
wavcat: $(objs) wavcat.o
wavmix: $(objs) wavmix.o
wavmono: $(objs) wavmono.o
wavstereo: $(objs) wavstereo.o

# regras de compilação
wav.o: wav.c wav.h
linhaDeComando.o: linhaDeComando.c linhaDeComando.h

# compila com flags de depuração
debug: CFLAGS += -DDEBUG -g
debug: all

# remove arquivos temporários
clean:
	-rm -f *.o

# remove tudo o que não for o código-fonte
purge: clean
	-rm -f $(BINARIES)