/** @file common.c
 *  @brief Fonctions de bases pour la création de programmes C.
 *
 *  @author Amélia Chavot (Artemisia)
 */

#include "common.h"

//
// Reimplemmentation of fgets to correct an issue with the buffer (USE THIS ONE)
void fgets2(char *chaine)
{
	fgets(chaine, sizeof chaine, stdin);
	cleanFgets(chaine);
}

void purger(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {}
}

//
// Clean the buffer for a proper use of fgets
void cleanFgets (char *chaine)
{
	char* p = strchr(chaine, '\n');
    
    if (p)
    {
        *p = 0;
    }
    else
    {
        purger();
    }
}

//
// Compute the maximum between two integer
int min(int nb1, int nb2) 
{
	if (nb1 < nb2)
	{
		return nb1;
	}
	else
	{
		return nb2;
	} 
}

//
// Compute the minimum between two integer
int max(int nb1, int nb2) 
{
	if (nb1 > nb2)
	{
		return nb1;
	}
	else
	{
		return nb2;
	} 
}