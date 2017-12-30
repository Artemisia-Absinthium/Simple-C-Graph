/** @file main.c
 *  @brief IHM pour la création, la modification et la visualisation de graphes.
 *
 *  @author Amélia Chavot (Artemisia)
 */
 
#include "header.h"
 
 //
 //Show the menu options
 int printMenu()
 {
	int choice = ERROR;
    do
    {
		printf("----------------------------------\n");
        printf("1 : creation d'un graphe initial\n");
        printf("2 : lecture depuis un fichier\n");
        printf("3 : insertion d'un sommet dans le graphe.\n");
        printf("4 : insertion d'une arête dans le graphe. \n");
        printf("5 : suppressio d'un sommet dans le graphe.\n");
	    printf("6 : suppressio d'une arête dans le graphe. \n");
        printf("7 : affichage du graphe\n");
        printf("8 : sauvegarde du graphe\n");
        printf("9 : Rechercher le flot maximum du graphe\n");
		
		printf("\nquitter 0\n\n> ");
		scanf ("%d",&choice);
        scanf("%*[^\n]s");
        getchar();
    } while((choice < 0) || (choice > 9)); 
	return choice;
 }

//
//Point d'entrée du programme.
int main()
{
	int	choice = ERROR;
	TypGraphe* testGraphe = NULL;
	
	while (choice != QUITTER)
    {
		choice = printMenu();
		switch (choice)
		{
			case CREATION :
				freeGraphe(testGraphe);
				testGraphe = creatNewGraphe();
			break;
			
			case LECTURE :
				freeGraphe(testGraphe);
				testGraphe = chargerDepuisFichier();
			break;
			
			case INSERTIONSOMMET :
				if (NULL != testGraphe)
				{
					insertionSommet(testGraphe);
				}
				else
				{
					printf("\nErreur, le graphe est nul, veuillez en initialiser un.\n\n");	
				}
			break;
			
			case INSERTIONARETE :
				if (NULL != testGraphe)
				{
					insertionAreteCmd(testGraphe);
				}
				else
				{
					printf("\nErreur, le graphe est nul, veuillez en initialiser un.\n\n");	
				}
			break;
			
			case SUPPRESSIONSOMMET :
				if (NULL != testGraphe)
				{
					suppressionSommetCmd(testGraphe);
				}
				else
				{
					printf("\nErreur, le graphe est nul, veuillez en initialiser un.\n\n");	
				}
			break;
			
			case SUPPRESSIONARET :
				if (NULL != testGraphe)
				{
					suppressionAreteCmd(testGraphe);
				}
				else
				{
					printf("\nErreur, le graphe est nul, veuillez en initialiser un.\n\n");	
				}
			break;
			
			case AFFICHAGE :
				afficherGraphe(testGraphe);
			break;
			
			case SAUVEGARDE :
				sauvegarderDansFichier(testGraphe);
			break;
			
			case TROUVERFLOTMAXIMUM :
				if (NULL != testGraphe)
				{
					int res = rechercherFlot(testGraphe);	
					printf("\n=================================");
					printf("\nLe flot maximum trouvé est : %d", res);
					printf("\n=================================\n\n");
				}
				else
				{
					printf("\nErreur, le graphe est nul, veuillez en initialiser un.\n\n");	
				}
			break;
			
			default :
			break;
		}
	}
	
	//
	//liberation de la memoire
	freeGraphe(testGraphe);
	
	printf("----------------------------------\n");
	printf("programme terminé\n");
	printf("----------------------------------\n");
    return 0;
}
