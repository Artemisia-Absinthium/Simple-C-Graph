#ifndef __TYPGRAPHE_H
#define __TYPGRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libVoisins/typVoisins.h"
#include "../libCommon/common.h"

	//
	// struct TypGraphe
	typedef struct 
	{
		int 					estOriente;
		int 					nbMaxSommets;
		typVoisins**			listesAdjacences;
	} TypGraphe;
	
	void 		afficherGraphe			(TypGraphe* G);
		
	TypGraphe*	creatNewGraphe			();	
		
	TypGraphe*	initGraphe				(int nbrMaxSommets, int isOriented);
		
	void 		freeGraphe				(TypGraphe* G);
		
	void 		ajouteTransition 		(TypGraphe* G, int depart, int arrivee, float poid);
		
	void 		supprimerTransition		(TypGraphe* G, int depart, int arrivee);
	
	void 		insertionAreteCmd		(TypGraphe* G);
	
	void 		suppressionAreteCmd		(TypGraphe* G);
	
	void		insertionSommet			(TypGraphe* G);
		
	void 		suppressionSommet		(TypGraphe* G, int nSommet);
	
	void 		suppressionSommetCmd	(TypGraphe* G);

	TypGraphe*	chargerDepuisFichier	();
			
	void 		sauvegarderDansFichier	(TypGraphe* G);
	
	int			getValueGraphe			(TypGraphe* graphe, int source, int cible);
	
	TypGraphe* 	copierGraphe			(TypGraphe* G);
	
#endif // __TYPGRAPHE_H
