#ifndef __TYPVOISINS_H
#define __TYPVOISINS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	//
	// struct typVoisins
	typedef struct _typVoisins
	{
		int 			voisin;
		int				poid;
		struct      	_typVoisins* voisinSuivant;
	} typVoisins;

	typVoisins* 	createNewVoisin 		();
	
	void			ajouteVoisin			(typVoisins* pTypVoisins, int voisinState, int poid);
			
    void			supprimeTypVoisins		(typVoisins* pTypVoisins);
			
    typVoisins*		supprimerVoisin			(typVoisins* ptypVoisins, int VoisinState);
		
    int				nbElementtypVoisins		(typVoisins* pTypVoisins);
		
    void			affichetypVoisins		(typVoisins* pTypVoisins);
	
#endif // __TYPVOISINS_H
