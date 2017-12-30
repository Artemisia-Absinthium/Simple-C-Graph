Bibliothèque de graphes
Par Amélia Chavot - amelia@mysteriousfox.com
=======================

Structure des sources
---------------------
Avant compilation :
---code
 |
 |---src
 | |
 | |---libCommon
 | | | 
 | | |-common.c
 | | | 
 | | |-common.h
 | | 
 | |---libGraphe
 | | | 
 | | |-typGraphe.c
 | | | 
 | | |-typGraphe.h
 | | 
 | |---libRechercheFlot
 | | | 
 | | |-rechercheFlot.c
 | | | 
 | | |-rechercheFlot.h
 | | 
 | |---libVoisins
 | | | 
 | | |-typVoisins.c
 | | | 
 | | |-typVoisins.h
 | | 
 | |-header.h
 | |
 | |-main.c
 |
 |-Makefile
 |
 |-test
 
Après compilation :
---code
 |
 |---bin
 | |
 | |-GRAF_TP
 |
 |---lib
 | |
 | |-libcommon.a
 | |
 | |-libgraphe.a
 | |
 | |-libliste.a
 |
 |---obj
 | |
 | |-common.o
 | |
 | |-main.o
 | |
 | |-typGraphe.o
 | |
 | |-typVoisins.o
 |
 |---src
 | |
 | |---libCommon
 | | | 
 | | |-common.c
 | | | 
 | | |-common.h
 | | 
 | |---libGraphe
 | | | 
 | | |-typGraphe.c
 | | | 
 | | |-typGraphe.h
 | | 
 | |---libRechercheFlot
 | | | 
 | | |-rechercheFlot.c
 | | | 
 | | |-rechercheFlot.h
 | | 
 | |---libVoisins
 | | | 
 | | |-typVoisins.c
 | | | 
 | | |-typVoisins.h
 | | 
 | |-header.h
 | |
 | |-main.compiler
 |
 |-Makefile
 |
 |-test
 
Détails des sources
-------------------
Dans le dossier bin : "GRAF_TP" L'éxécutable du programme compilé.

Dans le dossier lib : Les fichiers de librairies statiques. 
	libcommon.a : Une librairie de fonction standard.
	libgraphe.a : La libraire d'utilisation des graphes.
	libRechercheFlot.a : La librairie de recherche de flot maximum.
	libliste.a : La libraire d'utilisation de listes de typVoisins.
	
Dans le dossier obj : Les fichiers compilés des sources du dossier src.

Dans le dossier src : Les fichiers .c et .h des sources du programme principal et des librairies.

Exécution du programme
----------------------
Pour compiler et éxécuter le programme

1 : Positionnez vous dans le dossier code depuis un terminal.
2 : "$ make" Pour compiler le code source.
3 : "$ ./bin/GRAF_TP" pour exécuter le code source.