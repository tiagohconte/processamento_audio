# GRR20190374 Tiago Henrique Conte
# define as flags para compilação
CFLAGS = -Wall
CC = gcc
 
objs = wav.o linhaDeComando.o
libs = wav.h linhaDeComando.h
 
# regra default
all: wavinfo wavvol wavnorm wavrev wavecho wavwide wavcat wavmix
 
# regras de ligacao
wavinfo: $(objs) wavinfo.o
wavvol: $(objs) wavvol.o
wavnorm: $(objs) wavnorm.o
wavrev: $(objs)	wavrev.o
wavecho: $(objs) wavecho.o
wavwide: $(objs) wavwide.o
wavcat: $(objs) wavcat.o
wavmix: $(objs) wavmix.o

# regras de compilação
wavinfo.o: wavinfo.c $(libs)
wavvol.o: wavvol.c $(libs)
wavnorm.o: wavnorm.c $(libs)
wavrev.o: wavrev.c $(libs)
wavecho.o: wavecho.c $(libs)
wavwide.o: wavwide.c $(libs)
wavcat.o: wavcat.c $(libs)
wavmix.o: wavmix.c $(libs)
wav.o: wav.c wav.h
linhaDeComando.o: linhaDeComando.c linhaDeComando.h

# compila com flags de depuração
debug: CFLAGS += -DDEBUG -g
debug: all

# remove arquivos temporários
clean:
	-rm -f $(objs) wavinfo.o wavvol.o wavnorm.o wavrev.o wavecho.o wavwide.o wavcat.o wavmix.o

# remove tudo o que não for o código-fonte
purge: clean
	-rm -f wavinfo wavvol wavnorm wavrev wavecho wavwide wavcat wavmix