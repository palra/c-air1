#include <stdio.h>
#include "carte.h"

#define EOL() printf("\n")

int main()
{
	printf("AIR 1 : Jeu de Cartes\n=====================\n\n");

	carte *c1 = air_carte_creer(),
		  *c2 = air_carte_creer(),
		  *c3 = air_carte_creer();

	air_carte_valeur_set(c1, cvAs);
	air_carte_valeur_set(c2, cv3);
	air_carte_valeur_set(c3, cvRoi);

	air_carte_bat_add(c1, c3);
	air_carte_bat_add(c2, c1);
	air_carte_bat_add(c2, c3);

	air_carte_enseigne_set(c1, ceTrefle);
	air_carte_enseigne_set(c2, cePique);
	air_carte_enseigne_set(c3, ceCoeur);


	printf("c1 : \n");
	air_carte_printf(c1); EOL();

	printf("c2 : \n");
	air_carte_printf(c2); EOL();

	printf("c3 : \n");
	air_carte_printf(c3); EOL();

	air_carte_free(c1);
	air_carte_free(c2);
	air_carte_free(c3);

	return 0;
}
