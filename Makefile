#-----Macros--------------------------------- 
CC = gcc
CFLAGS = -std=c99 -Wall -c -g
LDFLAGS = -g
LIBFLAGS = -L./lib -lcommon -lliste -lgraphe -lrechercheflot -static

#-----Final PROGRAM----------------------
TARGET = bin/GRAF_TP
LIB = lib/libcommon.a lib/libliste.a lib/libgraphe.a lib/librechercheflot.a 

all: creatFolders $(LIB) $(TARGET)

creatFolders :
	mkdir -p bin
	mkdir -p lib
	mkdir -p obj
	mkdir -p src
	
#-----Main program----------------------
$(TARGET): obj/main.o
	${CC} ${LDFLAGS} -o ${TARGET} $^ ${LIBFLAGS}

obj/main.o: src/main.c src/header.h
	${CC} ${CFLAGS} -o $@ $<
	
#----Lib Common----------------------
lib/libcommon.a : obj/common.o
	ar rcs lib/libcommon.a obj/common.o
	ranlib lib/libcommon.a
obj/common.o :
	${CC} ${CFLAGS} src/libCommon/common.c -o obj/common.o

#----Lib liste----------------------
lib/libliste.a : obj/typVoisins.o
	ar rc lib/libliste.a obj/typVoisins.o
	ranlib lib/libliste.a
obj/typVoisins.o :
	${CC} ${CFLAGS} src/libVoisins/typVoisins.c -o obj/typVoisins.o
	
#----Lib Graphe---------------------
lib/libgraphe.a : obj/typGraphe.o \
				obj/typVoisins.o \
				obj/common.o
	ar rc lib/libgraphe.a obj/typGraphe.o obj/typVoisins.o obj/common.o
	ranlib lib/libgraphe.a
obj/typGraphe.o :
	${CC} ${CFLAGS} src/libGraphe/typGraphe.c -o obj/typGraphe.o

#----Lib Recherche de flots --------
lib/librechercheflot.a : obj/rechercheFlot.o \
						obj/typGraphe.o \
						obj/typVoisins.o \
						obj/common.o
	ar rc lib/librechercheflot.a obj/rechercheFlot.o obj/typGraphe.o obj/typVoisins.o obj/common.o
	ranlib lib/librechercheflot.a
	
obj/rechercheFlot.o :
	${CC} ${CFLAGS} src/libRechercheFlot/rechercheFlot.c -o obj/rechercheFlot.o
	
clean:
	rm -f obj/*.o
	rm -f lib/*.a
	rm -f $(TARGET)

mrproper: clean
	rmdir obj
	rmdir lib
	rmdir bin
