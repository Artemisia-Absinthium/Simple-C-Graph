#ifndef __HEADER_H
#define __HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libCommon/common.h"
#include "libVoisins/typVoisins.h"
#include "libGraphe/typGraphe.h"
#include "libRechercheFlot/rechercheFlot.h"

//
//Choix du menu
#define 	CREATION 			1
#define 	LECTURE	 			2
#define 	INSERTIONSOMMET		3
#define 	INSERTIONARETE 		4
#define 	SUPPRESSIONSOMMET	5
#define 	SUPPRESSIONARET		6
#define 	AFFICHAGE			7
#define 	SAUVEGARDE			8
#define 	TROUVERFLOTMAXIMUM	9
#define 	QUITTER				0
#define 	ERROR				-1

#endif // __HEADER_H
