/** @file rechercheFlot.c
 *  @brief	Algorithme de Ford Fulkerson permettant de rechercher le flot maximum dans une structure typGraphe.
 *  Ces algorithmes n'utilisent pas de graphe résiduel. Les valeurs soont calculés avec le graphe initial et le flot résiduel.
 *
 *  @author Amélia Chavot (Artemisia)
 */

#include "rechercheFlot.h"

/** @brief Retourne le flot maximum dans une graphe entre deux points. Les points sont demandé à l'utilisateur.
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à analyser.
 *  @return int le flot maximum.
 */
int rechercherFlot (TypGraphe* G)
{
	//
	// Variables
	int source = -1, puit = -1, nbSommet = -1, res = 0;

	//
	// Nombre de sommet utilisé dans le graphe
    while (nbSommet < G->nbMaxSommets && NULL != G->listesAdjacences[nbSommet])
	{
		nbSommet++;
	}

	//
	// Demander le noeud source
	do
    {
		printf("----------------------------------\n");
        printf("Quel est le noeud source ? [1 - %d]\n", nbSommet);
		scanf ("%d",&source);
        scanf("%*[^\n]s");
        getchar();
    } while((source < 1) || (source > nbSommet));

	//
	// Demander le noeud puit
	do
    {
		printf("----------------------------------\n");
        printf("Quel est le noeud puit ? [1 - %d]\\%d\n", nbSommet, source);
		scanf ("%d",&puit);
        scanf("%*[^\n]s");
        getchar();
    } while((puit < 1) || (puit > nbSommet) || (source == puit));

	//
	// Créer le graphe de flot
	// Acces => int offset = source * nbSommet + destination
	int* flotResiduel = (int*) malloc (nbSommet * nbSommet * sizeof(int));

	
	//
	// Temps d'exécution DEBUT
	struct timeval start, end; 
	gettimeofday(&start, NULL); 

	//
	// Lancer l'algorithme
	res = algoFordFulkerson(source, puit, G, nbSommet, flotResiduel);//, grapheResiduel);

	//
	// Temps d'exécution FIN
	gettimeofday(&end, NULL);
	printf("\n============================================");
	printf("\nLe temps d'exécution est de %ld microseconds", ((end.tv_sec * 1000000 + end.tv_usec ) - (start.tv_sec * 1000000 + start.tv_usec)));
	printf("\n============================================\n");	
	//
	// Supprimer le graphe de flot
	free(flotResiduel);

	return res;
}
/** @brief Retourne le flot maximum dans une graphe entre deux points. Utilise l'algorithme de Ford-Fulkerson
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à analyser.
 *  @param int noeudSource le noeud de départ
 *  @param int noeudPuit le noeud d'arrivé
 *  @param int nbSommet le nombre de sommet de graphe
 *  @param int* flotResiduel une matrice représentant le flot résiduel.
 *  @return int le flot maximum.
 */
int algoFordFulkerson(int noeudSource, int noeudPuit, TypGraphe* G, int nbSommet, int* flotResiduel)
{
	//
	// Valeur de retour;
	int flowMaximum = 0;
	int* cheminAmeliorantParent = (int*) malloc (nbSommet * sizeof(int));
	for(int nSommet = 0; nSommet < nbSommet; ++nSommet)
	{
		cheminAmeliorantParent[nSommet] = -1;
	}

	//
	// Initialiser flot f à 0;
	int nbSommetMax = nbSommet * nbSommet;
	for(int nSommet = 0; nSommet < nbSommetMax; ++nSommet)
	{
		flotResiduel[nSommet] = 0;
	}
	//
	// tant que il existe un chemin p de s à t dans le graphe résiduel Gf faire
	while(1 == cheminAmeliorant(G, noeudSource, noeudPuit, nbSommet, flotResiduel, cheminAmeliorantParent))//,grapheResiduel))
	{
		//
		// residue est la valeur maximum pouvant être ajouter au chemin max
		int residue = 0;

		//
		// On remonte le chemin améliorant depuis le puit pour trouvé pour décider du flux minimum
		int nNoeud = noeudPuit - 1;
		residue = getValueGraphe(G, cheminAmeliorantParent[nNoeud] + 1, nNoeud + 1) - flotResiduel[cheminAmeliorantParent[nNoeud] * nbSommet + nNoeud];

		for (nNoeud = cheminAmeliorantParent[nNoeud]; cheminAmeliorantParent[nNoeud] != -1; nNoeud = cheminAmeliorantParent[nNoeud])
		{
			residue = min(residue, getValueGraphe(G, cheminAmeliorantParent[nNoeud] + 1, nNoeud + 1) - flotResiduel[cheminAmeliorantParent[nNoeud] * nbSommet + nNoeud]);
		}

		//
		// On modifie le flot résiduel et le graphe résiduel
		for (nNoeud = noeudPuit - 1; cheminAmeliorantParent[nNoeud] != -1; nNoeud = cheminAmeliorantParent[nNoeud])
		{
			//
			// flot résiduel
			flotResiduel[cheminAmeliorantParent[nNoeud] * nbSommet + nNoeud] += residue;
			flotResiduel[nNoeud * nbSommet + cheminAmeliorantParent[nNoeud]] -= residue;
		}

		flowMaximum += residue;

		//
		// mise à zero du chemin améliorant
		for(int nSommet = 0; nSommet < nbSommet; ++nSommet)
		{
			cheminAmeliorantParent[nSommet] = -1;
		}
	}

	return flowMaximum;
}
/** @brief Recherche un chemin améliorant dans un graphe en utilisant un flot résiduel.
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à analyser.
 *  @param int source le noeud de départ.
 *  @param int puit le noeud d'arrivé.
 *  @param int nbSommet le nombre de sommet de graphe.
 *  @param int* flotResiduel une matrice représentant le flot résiduel.
 *  @param int* cheminAmeliorantParent un tableau permettant d'enregistrer un chemin.
 *  @return int 1 si un chemin est trouvé, 0 sinon.
 */
int cheminAmeliorant(TypGraphe* capacityGraphe, int source, int puit, int nbSommet, int* flotResiduel, int* cheminAmeliorantParent)
{
	//
	// tableau visited utilisé pour marqué les noeuds visités
	int* visited = (int*) malloc (nbSommet * sizeof(int));
	for (int i = 0; i < nbSommet; ++i){
		visited[i] = 0;
	}

	int debutFile = 0, finFile = 0;
	int* file = (int*) malloc (nbSommet * sizeof(int));

	//
	// Push de la source
	file[finFile] = source - 1;
    ++finFile;
	visited[source - 1] = 1;

	//
	// Tant que la file n'est pas vide
	while (finFile != debutFile)
    {
		//
		// Pop de la file
		int currentSource = file[debutFile];
		debutFile++;

        for (int nNoeud = 0; nNoeud < nbSommet; ++nNoeud)
        {
            if (visited[nNoeud] == 0 && (getValueGraphe(capacityGraphe, currentSource + 1, nNoeud + 1) - flotResiduel[currentSource * nbSommet + nNoeud] > 0))
            {
				//
				// Push dans la file
				file[finFile] = nNoeud;
				++finFile;
				visited[nNoeud] = 1;
                cheminAmeliorantParent[nNoeud] = currentSource;
            }
        }
    }

	free(file);
	//
    // On retourne vrai si le puit est visité
    if (visited[puit - 1] == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}