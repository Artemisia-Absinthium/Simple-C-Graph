/** @file typGraphe.c
 *  @brief Gestion de graphes utilisant des structures typVoisins an valeurs.
 *
 *  @author Amélia Chavot (Artemisia)
 */
 
#include "typGraphe.h"

/** @brief  Affiche un graphe selont le format des fichiers de graphes.
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à afficher.
 *  @return Void.
 */
void afficherGraphe(TypGraphe* G)
{
	if(NULL == G)
	{
		printf("\nErreur, graphe à aficher == NULL\n");	
		return;
	}
	typVoisins* 		pTypVoisins;

	printf("\n----------GRAPHE-----------\n");
	printf("# nombre maximum de sommets\n");
	printf("%d\n", G->nbMaxSommets);
	printf("# oriente\n");
	0 == G->estOriente ? printf("Non\n") : printf("Oui\n"); 
	
	printf("# sommets : voisins\n");
	int nEtat = 0;
	while(nEtat < G->nbMaxSommets && NULL != G->listesAdjacences[nEtat])
	{
		printf("%d : ", nEtat + 1);
		pTypVoisins = G->listesAdjacences[nEtat];
		if( NULL != pTypVoisins)
		{
					while(NULL != pTypVoisins && (-1 != pTypVoisins->voisin))
		{
			printf("(%d/%d) ", pTypVoisins->voisin + 1, pTypVoisins->poid);
			pTypVoisins = pTypVoisins->voisinSuivant;
		}
		}
		while(NULL != pTypVoisins && (-1 != pTypVoisins->voisin))
		{
			printf("(%d/%d) ", pTypVoisins->voisin + 1, pTypVoisins->poid);
			pTypVoisins = pTypVoisins->voisinSuivant;
		}
		printf("\n");
		++nEtat;
	}
}

/** @brief Demande les informations pour initialiser un nouveau graphe
 *
 *  @return TypGraphe* Un pointeur sur le graphe nouvellement initialisé.
 */
TypGraphe* creatNewGraphe ()
{
	int orientedChoice;
	int nbSommetChoice;

	//
	//Demander si le graphe est orienté.
	do
    {
		printf("----------------------------------\n");
        printf("creation d'un nouveau graphe\n");
        printf("Graphe orienté : 1\nGraphe non orienté : 2\n");
		
		printf("\nquitter 0\n\n> ");
		scanf ("%d",&orientedChoice);
        scanf("%*[^\n]s");
        getchar();
    } while((orientedChoice < 0) || (orientedChoice > 2)); 
	
	if (0 == orientedChoice)
	{
		return NULL;
	}
	else if (2 == orientedChoice)
	{
		orientedChoice = 0;
	}
	
	//
	//Demander le nombre max de sommets.
	do
    {
		printf("----------------------------------\n");
        printf("creation d'un nouveau graphe\n");
        printf("Quel est le nombre max de sommets ? [0 - 200])\n");
		
		printf("\nquitter 0\n\n> ");
		scanf ("%d",&nbSommetChoice);
        scanf("%*[^\n]s");
        getchar();
    } while((nbSommetChoice < 0) || (nbSommetChoice > 200));
	if (0 == nbSommetChoice)
	{
		return NULL;
	}
	
	//
	//creation du graphe avec les informations.
	return(initGraphe(nbSommetChoice, orientedChoice));
}

/** @brief  Initialise ou reinitialise un graphe.
 *
 *  @param nbrMaxSommets Le nombre de sommet maximum du graphe.
 *  @param  isOriented Un booleen indiquant si le graphe est orienté ou non.
 *  @return TypGraphe* Un pointeur sur le graphe nouvellement initialisé.
 */
TypGraphe* initGraphe(int nbrMaxSommets, int isOriented)
{
	TypGraphe* res = (TypGraphe*)malloc(sizeof(TypGraphe));	
	if (NULL == res)
	{
		fprintf(stderr,"Allocation Impossible, erreur inconnue");
		exit(EXIT_FAILURE);
	}
	res->estOriente 		= isOriented;
	res->nbMaxSommets	 	= nbrMaxSommets;
	res->listesAdjacences	= (typVoisins**) calloc(nbrMaxSommets, sizeof(typVoisins*));

	if (NULL == res->listesAdjacences)
	{
		fprintf(stderr,"Allocation Impossible");
		exit(EXIT_FAILURE);
	}
	return res;
}

/** @brief  Desaloue la memoire allouee au graphe.
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à Desalouer. 
 *  @return Void.
 */
void freeGraphe(TypGraphe* G)
{
	if(NULL != G)
	{
		if(NULL != G->listesAdjacences)
		{
			for(int nVoisin = 0; nVoisin < G->nbMaxSommets; ++nVoisin)
			{
				if(NULL != G->listesAdjacences[nVoisin])
				{
					supprimeTypVoisins(G->listesAdjacences[nVoisin]);
					G->listesAdjacences[nVoisin] = NULL;
				}
			}
			free(G->listesAdjacences);
			G->listesAdjacences = NULL;
		}
		free(G);
	}
}

/** @brief Ajoute une transition au Graphe
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à modifier.
 *  @param int depart le sommet de départ.
 *  @param int arrivee le sommet d'arrivé.
 *	@param int poid le poid de la transition
 *  @return Void.
 */
void ajouteTransition(TypGraphe* G, int depart, int arrivee, float poid)
{
	int nSommet = 0;
	while (NULL != G->listesAdjacences[nSommet])
	{
		nSommet++;
	}
	
	if(depart > nSommet || arrivee > nSommet)
	{
        printf("/!\\ Erreur dans la création de la transition !!\n");
		return;
	}
	else
	{
		ajouteVoisin(G->listesAdjacences[depart-1], arrivee-1, poid);
		if(0 == G->estOriente)
		{
			ajouteVoisin(G->listesAdjacences[arrivee-1], depart-1, poid);
		}
	}
}

/** @brief Supprime une transition du Graphe
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à modifier.
 *  @param int depart le sommet de départ.
 *  @param int arrivee le sommet d'arrivé.
 *  @return Void.
 */
void supprimerTransition(TypGraphe* G, int depart, int arrivee)
{
	if(depart > G->nbMaxSommets || arrivee > G->nbMaxSommets || depart < 0 || arrivee < 0)
	{
		printf("/!\\ Erreur dans les valeurs utilisés !!\n");
		return;
	}
	G->listesAdjacences[depart-1] = supprimerVoisin(G->listesAdjacences[depart-1], arrivee-1);
}

/** @brief insertion d'une nouvelle arête dans le graphe, les valeur sont demandées à l'utilisateur.
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à modifier.
 *  @return Void.
 */
void insertionAreteCmd(TypGraphe* G)
{
	int nSommet = 0;
	while (NULL != G->listesAdjacences[nSommet])
	{
		nSommet++;
	}
	
	if(0 != nSommet)
	{
		int depart;
		int arrivee;
		int poid;
		
		//
		//Demander le sommet de départ
		do
		{
			printf("----------------------------------\n");
			printf("Insertion d'une nouvelle arête\n");
			printf("Sommet de départ [1 - %d]", nSommet);
			
			printf("\nquitter 0\n\n> ");
			scanf ("%d",&depart);
			scanf("%*[^\n]s");
			getchar();
		} while((depart < 0) || (depart >nSommet)); 
		
		if (0 == depart)
		{
			return;
		}	
		
		//
		//Demander le sommet d'arrivée
		do
		{
			printf("----------------------------------\n");
			printf("Insertion d'une nouvelle arête\n");
			printf("Sommet d'arrivée [1 - %d]", nSommet);
			
			printf("\nquitter 0\n\n> ");
			scanf ("%d",&arrivee);
			scanf("%*[^\n]s");
			getchar();
		} while((arrivee < 0) || (arrivee > nSommet)); 
		
		if (0 == arrivee)
		{
			return;
		}
		
		//
		//Demander le poid
		do
		{
			printf("----------------------------------\n");
			printf("Insertion d'une nouvelle arête\n");
			printf("poid de l'arête (min 0)");
			
			printf("\nquitter -1\n\n> ");
			scanf ("%d",&poid);
			scanf("%*[^\n]s");
			getchar();
		} while((poid < -1)); 
		
		if (-1 == poid)
		{
			return;
		}
		
		//Si le graphe est orienté, on demande si l'arrête est symetrique.
		//Si il n'est pas orienté, elle l'est automatiquement,
		if(G->estOriente)
		{			
			int orientedChoice = 0;
			
			//
			//Demander si l'arrête est symetrique.
			do
			{
				printf("----------------------------------\n");
				printf("Insertion d'une nouvelle arête\n");
				printf("Arrête non symetrique : 1\nArrête symetrique : 2\n");
				
				printf("\nquitter 0\n\n> ");
				scanf ("%d",&orientedChoice);
				scanf("%*[^\n]s");
				getchar();
			} while((orientedChoice < 0) || (orientedChoice > 2)); 
			
			if (0 == orientedChoice)
			{
				return;
			}
			ajouteTransition(G, depart, arrivee, poid);
			if(2 == orientedChoice)
			{
				ajouteTransition(G, arrivee, depart, poid);		
			}
		}
		else
		{
			ajouteTransition(G, depart, arrivee, poid);
		}
		printf("----------------------------------\n");
		printf("Insertion d'une nouvelle arête\n");
		printf("Ajout OK");
	}
	else{
		printf("----------------------------------\n");
		printf("Pas de sommet disponible pour ajouter une arête\n");
	}
		printf("\ncontinuer : ENTER\n\n> ");
		scanf("%*[^\n]s");
		getchar();
}

/** @brief suppresion d'une arête dans le graphe, les valeur sont demandées à l'utilisateur.
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à modifier.
 *  @return Void.
 */
void suppressionAreteCmd (TypGraphe* G)
{
	int nSommet = 0;
	while (NULL != G->listesAdjacences[nSommet])
	{
		nSommet++;
	}
	
	if(0 != nSommet)
	{
		int depart;
		int arrivee;
		
		//
		//Demander le sommet de départ
		do
		{
			printf("----------------------------------\n");
			printf("Suppresion d'une arête\n");
			printf("Sommet de départ [1 - %d]", nSommet);
			
			printf("\nquitter 0\n\n> ");
			scanf ("%d",&depart);
			scanf("%*[^\n]s");
			getchar();
		} while((depart < 0) || (depart >nSommet)); 
		
		if (0 == depart)
		{
			return;
		}	
		
		//
		//Demander le sommet d'arrivée
		do
		{
			printf("----------------------------------\n");
			printf("Suppresion d'une arête\n");
			printf("Sommet d'arrivée [1 - %d]", nSommet);
			
			printf("\nquitter 0\n\n> ");
			scanf ("%d",&arrivee);
			scanf("%*[^\n]s");
			getchar();
		} while((arrivee < 0) || (arrivee > nSommet)); 
		
		if (0 == arrivee)
		{
			return;
		}
		printf("----------------------------------\n");
		printf("Suppresion de l'arête\n");
		supprimerTransition(G, depart, arrivee);

		if(!G->estOriente)
		{			
			printf("----------------------------------\n");
			printf("Suppresion de l'arête symétrique\n");
			supprimerTransition(G, arrivee, depart);
		}
	}
	else{
		printf("----------------------------------\n");
		printf("Pas de sommet disponible. Donc pas d'arêtes\n");
	}
		printf("\ncontinuer : ENTER\n\n> ");
		scanf("%*[^\n]s");
		getchar();
}

/** @brief Ajoute un sommet dans le graphe. (Sans dépasser le nombre de sommet max)
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à modifier.
 *  @return Void.
 */
void insertionSommet(TypGraphe* G)
{
    int nSommet = 0;
    while (NULL != G->listesAdjacences[nSommet])
	{
		nSommet++;
	}

    if (nSommet >= G->nbMaxSommets)
    {
        printf("Erreur, le nombre de sommet dépasse la limite\n");
		return;
    }

	G->listesAdjacences[nSommet] = createNewVoisin();
	
	printf("Sommet %d ajouté\n", nSommet + 1);
}	

/** @brief Supprime un sommet du graphe.
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à modifier.
 *  @param nSommet numéro du sommet à supprimer.
 *  @return Void.
 */
void suppressionSommet (TypGraphe* G, int nSommet)
{
	//
	// Pour chaque listes
	int nEtat = 0;
	while(nEtat < G->nbMaxSommets && NULL != G->listesAdjacences[nEtat])
	{
		//
		// Parcours de la liste
		typVoisins* pTypVoisins = G->listesAdjacences[nEtat];
		while(NULL != pTypVoisins && (-1 != pTypVoisins->voisin) && (nSommet-1 != nEtat))
		{
			//
			// sinon si voisin == sommet, supprimer transition
			if(nSommet-1 == pTypVoisins->voisin)
			{
				G->listesAdjacences[nEtat] = supprimerVoisin(G->listesAdjacences[nEtat], nSommet-1);
				pTypVoisins = G->listesAdjacences[nEtat];
			}
			else{
				pTypVoisins = pTypVoisins->voisinSuivant;
			}
		}
		pTypVoisins = G->listesAdjacences[nEtat];
		while(NULL != pTypVoisins && (-1 != pTypVoisins->voisin) && (nSommet-1 != nEtat))
		{
			//
			// Si voisin > nSommet alors --voisin
			if(nSommet-1 < pTypVoisins->voisin)
			{
				pTypVoisins->voisin -= 1;
			}
			pTypVoisins = pTypVoisins->voisinSuivant;	
		}
		++nEtat;
	}

	
	//
	// supprimer liste à nSommet
	supprimeTypVoisins(G->listesAdjacences[nSommet-1]);

	int nbSommet = 0;
	while(nbSommet < G->nbMaxSommets && NULL != G->listesAdjacences[nbSommet])
	{
		nbSommet++;
	}

	for(; nSommet - 1 < nbSommet - 1; ++nSommet)
	{
		G->listesAdjacences[nSommet-1] = G->listesAdjacences[nSommet];
	}
			
	G->listesAdjacences[nbSommet-1] = NULL;
}

/** @brief Supprime un sommet du graphe en demandant le numéro du sommet.
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à modifier. 
 *  @return Void.
 */
void suppressionSommetCmd (TypGraphe* G)
{
	int nSommet = 0;
	while(nSommet < G->nbMaxSommets && NULL != G->listesAdjacences[nSommet])
	{
		nSommet++;
	}
	int sommet = 0;
	if(0 != nSommet)
	{
		//
		//Demander le sommet à supprimer
		do
		{
			printf("----------------------------------\n");
			printf("Suppresion d'un sommet\n");
			printf("Sommet à supprimer [1 - %d]", nSommet);
			
			printf("\nquitter 0\n\n> ");
			scanf ("%d",&sommet);
			scanf("%*[^\n]s");
			getchar();
		} while((sommet < 0) || (sommet >nSommet)); 
		
		if (0 == sommet)
		{
			return;
		}
		suppressionSommet(G, sommet);
	}
	else
	{
		printf("/!\\ Erreur, il n'y à pas de sommets à supprimer\n");
	}
}

/** @brief Charge un graphe depuis un fichier (fichier demandé à l'utilisateur).
 *
 *  @return TypGraphe* Un pointeur sur le graphe chargé. 
 */
TypGraphe* chargerDepuisFichier ()
{
    printf("----------------------\n");
    printf("Chargement\n");
    printf("\n");
    char path[512];
    printf("Entrer le nom du fichier de chargement : \n> ");
	fgets2(path);
	
    char* nbSommet = malloc(4*sizeof(char));
    int compteur = 0;
    int nbLigne = 0;
    FILE* fichier = NULL;
    int maxSommet = -1;
    int oriente = -1;
    char* arrivee = malloc(10*sizeof(char));
	char* poid = malloc(10*sizeof(char));
    char c ='\0';
	int nbMaxSommet;
	
	TypGraphe* res = NULL;
	
	fichier = fopen(path, "r");
    if (NULL != fichier)
    {
        while ((c = fgetc(fichier)) != EOF)
        {
            if('\n' == c)
			{
                nbLigne++;
            }

            if(nbLigne == 1)
            {
                if('\n' != c)
                {
                    nbSommet[compteur] = c;
                    compteur++;
                }       
            }
			
            if(nbLigne == 2){
                if(c == '\n'){
                    maxSommet = atoi(nbSommet);
                }
            }
            if(oriente == -1 && nbLigne == 3 && '\n' != c && ' ' != c)
            {
				if(c == 'o'){
					oriente = 1;
				}
				else{
					oriente = 0;
				}
				if(-1 != oriente && 0 < maxSommet)
				{
					res = initGraphe(maxSommet, oriente);
					for(int nSommet = 0; nSommet < maxSommet; ++ nSommet)
					{
						insertionSommet(res);
					}
				}
				else
				{
					printf("/!\\ Erreur dans les valeurs du fichier (0 > %d)", maxSommet);
					return NULL;
				}
            }
			
            if(nbLigne >= 5)
            {
                if('(' == c && '\n' != c)
                {
					compteur = 0;
					while ((c = fgetc(fichier)) != '/')
					{
						arrivee[compteur] = c;
						compteur++;
					}
					arrivee[compteur] = '\0';
					compteur = 0;
					while ((c = fgetc(fichier)) != ')')
					{
						poid[compteur] = c;
						compteur++;	
					}
					poid[compteur] = '\0';
					ajouteTransition(res, nbLigne - 4, atoi(arrivee), atoi(poid));
					
					nbMaxSommet = max(nbLigne - 4, max(nbMaxSommet,atoi(arrivee)));
				}
				else if(':' == c)
				{
					nbMaxSommet = max(nbLigne - 4, nbMaxSommet);
				}
            }
        }
        fclose(fichier);
		while(nbMaxSommet < maxSommet)
		{
			suppressionSommet(res, maxSommet);
			--maxSommet;
		}
    }
    else
    {
		printf("/!\\ Erreur d'ouverture du fichier : %s\n", path);
    }
    free(nbSommet);
	free(arrivee);
	free(poid);
	
	return res;
}

/** @brief Sauvegarde un graphe dans un fichier (Nom du fichier demandé à l'utilisateur).
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à sauvegarder. 
 *  @return Void.
 */
 void sauvegarderDansFichier (TypGraphe* G)
{
    printf("----------------------\n");
    printf("Sauvegarde \n");
    printf("\n");
    if(NULL != G){
        char path[512];
        printf("Entrer le nom du fichier de sauvegarde : \n> ");
        fgets2(path);
        printf("\n");
		
        FILE* fichier = NULL;
        fichier = fopen(path, "w+");
		
        if (fichier != NULL)
        {
            fprintf(fichier, "# nombre maximum de sommets \n");
            fprintf(fichier, "%d \n",G->nbMaxSommets);
            fprintf(fichier, "# oriente \n");
			if(1 == G->estOriente)
			{
				fprintf(fichier, "o \n");
			}
			else
			{
				fprintf(fichier, "n \n");
			}
            fprintf(fichier, "# sommets : voisins \n");

			typVoisins* pTypVoisins;
			int nEtat = 0;
			while(nEtat < G->nbMaxSommets && NULL != G->listesAdjacences[nEtat])
			{
				fprintf(fichier, "%d : ", nEtat + 1);
				pTypVoisins = G->listesAdjacences[nEtat];
				while(NULL != pTypVoisins && (-1 != pTypVoisins->voisin))
				{
					fprintf(fichier, "(%d/%d) ", pTypVoisins->voisin + 1, pTypVoisins->poid);
					pTypVoisins = pTypVoisins->voisinSuivant;
				}
				fprintf(fichier, "\n");
				++nEtat;
			}
        }
        else
        {
            printf("/!\\ Erreur d'ouverture du fichier : %s\n", path);
        }

        fclose(fichier);
    }
    else{
		printf("/!\\ Erreur aucun graphe initialisé (1 dans le menu)\n");
    }
    
}

/** @brief Récupere le poid du graphe entre deux noeuds. (-1 si aucune valeur TODO changer ceci)
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à analyser. 
 *  @param int source
 *  @param int cible
 *  @return int la valeur trouvé entre la source et la cible.
 */
int getValueGraphe(TypGraphe* graphe, int source, int cible)
{
	int res = -1;
	
	typVoisins* current = graphe->listesAdjacences[source - 1];
	while(NULL != current && res == -1)
	{
		if (current->voisin == cible - 1)
		{
			res = current->poid;
		}
		current = current->voisinSuivant;
	}
	
	return res;
}

/** @brief Copie un graphe.
 *
 *  @param TypGraphe* G Un pointeur sur le graphe à copier. 
 *  @return Une copie du graphe.
 */
TypGraphe* copierGraphe(TypGraphe* G)
{
	TypGraphe* res = NULL;
	
	res = initGraphe(G->nbMaxSommets, G->estOriente);
	int nbSommet = 0;
	while (NULL != G->listesAdjacences[nbSommet])
	{
		insertionSommet(res);
		++nbSommet;
	}
	
	nbSommet = 0;
	while (NULL != G->listesAdjacences[nbSommet])
	{
		typVoisins* ptypVoisins = G->listesAdjacences[nbSommet];
		while(NULL != ptypVoisins)
		{
			if(-1 != ptypVoisins->voisin)
			{
				printf("%d ",ptypVoisins->voisin + 1);
				ajouteTransition (res, nbSommet+1, ptypVoisins->voisin + 1, ptypVoisins->poid);
			}
			ptypVoisins = ptypVoisins->voisinSuivant;
		}
		++nbSommet;
	}
	return res;
}