/** @file typVoisins.c
 *  @brief Gestion d'une liste de voisin pour la création de graphes.
 *
 *  @author Amélia Chavot (Artemisia)
 */

#include "typVoisins.h"

typVoisins* createNewVoisin ()
{
	typVoisins* newList = (typVoisins*) malloc(sizeof(typVoisins));
    newList->voisinSuivant = (typVoisins*) malloc(sizeof(typVoisins));

    if (newList == NULL || newList->voisinSuivant == NULL)
    {
        printf("/!\\ Erreur dans la création du typVoisins !!\n");
		return NULL;
    }

	newList->voisinSuivant = NULL;
	if(newList != NULL){
		newList->voisin = -1;
		newList->poid = 0;
	}

    return newList;
}

/** @brief Ajoute un voisin dans la liste
 *
 *  @param pTypVoisins 
 *  @param voisinState 
 *  @return Void.
 */
void ajouteVoisin(typVoisins* pTypVoisins, int voisinState, int poid)
{
	typVoisins* currentVoisin = pTypVoisins;
	
	//If there is no current voisin we creat it directly
	if(NULL == currentVoisin)
	{
		currentVoisin = createNewVoisin();
        currentVoisin->voisinSuivant = createNewVoisin();
		currentVoisin->voisin = voisinState;
		currentVoisin->poid = poid;
        pTypVoisins = currentVoisin;
        return;
	}
	
	//Else, we look for an existing voisin and update it
	while(-1 != currentVoisin->voisin)
    {
		if(voisinState == currentVoisin->voisin)
		{
			currentVoisin->poid = poid;
			return;
		}
        currentVoisin = currentVoisin->voisinSuivant;
    }

	//No voisin with this state where found, so we creat one;
	currentVoisin->voisin = voisinState;
	currentVoisin->poid = poid;
	currentVoisin->voisinSuivant = createNewVoisin();
	return;
}

/** @brief supprime une liste de voisin (Recursive)
 *
 *  @param l la lsite à supprimer
 *  @return Void.
 */
void supprimeTypVoisins(typVoisins* l)
{
    typVoisins* ptypVoisins;

    ptypVoisins = l;

    if(NULL != ptypVoisins){
        supprimeTypVoisins(ptypVoisins->voisinSuivant);
        free(ptypVoisins);
        ptypVoisins = NULL;
    }
}

/** @brief supprime un voisin de la liste
 *
 *  @param pTypVoisins la liste à modifier
 *  @param VoisinState le voisin à supprimer dans la liste
 *  @return Void.
 */
typVoisins* supprimerVoisin(typVoisins* ptypVoisins, int voisinState)
{
	typVoisins* ptypVoisinsTmp;
	typVoisins* ptypVoisinsprevious;
	
	//If there is no current voisin we creat it directly
	if(NULL == ptypVoisins || -1 == ptypVoisins->voisin)
	{
		printf("/!\\ Erreur aucune transition existante !!\n");
        return ptypVoisins;
	}
	
	ptypVoisinsprevious = ptypVoisins;

	if(voisinState == ptypVoisinsprevious->voisin)
	{
		ptypVoisins = ptypVoisinsprevious->voisinSuivant;
		free(ptypVoisinsprevious);
		printf("Transition supprimé\n");
		return ptypVoisins;
	}
	
	ptypVoisinsTmp = ptypVoisinsprevious->voisinSuivant;
	
	//Else, we look for an existing voisin and deletes it
	while(-1 != ptypVoisinsTmp->voisin && NULL != ptypVoisinsTmp)
    {
		if(voisinState == ptypVoisinsTmp->voisin)
		{
			ptypVoisinsprevious->voisinSuivant = ptypVoisinsTmp->voisinSuivant;
			free(ptypVoisinsTmp);
			printf("Transition (supprimé\n");
			return ptypVoisins;
		}
		ptypVoisinsprevious = ptypVoisinsTmp;
        ptypVoisinsTmp = ptypVoisinsTmp->voisinSuivant;
    }

	//No voisin with this state where found, so we quit;
	printf("/!\\ Erreur aucune transition existante !!\n");
	return ptypVoisins;
}

/** @brief Retourne le nombre d'élément de la liste
 *
 *  @param ptypVoisins la liste
 *  @return Void.
 */
int nbElementtypVoisins (typVoisins* ptypVoisins)
{
    int nbElement = 0;
    while(NULL != ptypVoisins)
    {
        ++nbElement;
        ptypVoisins = ptypVoisins->voisinSuivant;
    }
    return nbElement;
}

/** @brief affiche une liste sur une ligne (Format utilisé pour les graphes)
 *
 *  @param ptypVoisins la liste à afficher 
 *  @return Void.
 */
void affichetypVoisins(typVoisins* ptypVoisins)
{
	printf("TYPVOISIN : ");
    while(NULL != ptypVoisins)
    {
		if(-1 == ptypVoisins->voisin)
		{
			printf("-1 ");
		}
		else
		{
			printf("%d ",ptypVoisins->voisin + 1);
		}
        ptypVoisins = ptypVoisins->voisinSuivant;
    }
	printf(" FIN \n");
}
