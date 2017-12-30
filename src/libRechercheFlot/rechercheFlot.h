#ifndef __RECHERCHEFLOT_H
#define __RECHERCHEFLOT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "../libVoisins/typVoisins.h"
#include "../libCommon/common.h"
#include "../libGraphe/typGraphe.h"

	int 	rechercherFlot				(TypGraphe* G);
		
	int 	algoFordFulkerson			(int noeudSource, int noeudPuit, TypGraphe* G, int nbSommet, int* flotResiduel);//TypGraphe* grapheResiduel)
		
	int 	cheminAmeliorant			(TypGraphe* capacityGraphe, int source, int puit, int nbSommet, int* flotResiduel, int* cheminAmeliorantParent);
#endif // __RECHERCHEFLOT_H