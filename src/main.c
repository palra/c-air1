#include <stdio.h>
#include "carte.h"
#include "bdd.h"

#define EOL() printf("\n")

int main()
{
	printf("AIR 1 : Jeu de Cartes\n=====================\n\n");

	carte_liste *liste = air_bdd_liste_creer(), *res;

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

	air_bdd_liste_ajouter(liste, c1);
	air_bdd_liste_ajouter(liste, c2);
	air_bdd_liste_ajouter(liste, c3);

	printf("Liste initiale :\n%s\n",
		   "----------------");
	air_bdd_liste_printf(liste);

	printf("Cartes de trèfle :\n%s\n",
		   "------------------");
	res = air_bdd_liste_recherche_par_enseigne(liste, ceTrefle);
	air_bdd_liste_printf(res);

	printf("Cartes valant `3` :\n%s\n",
		   "-------------------");
	res = air_bdd_liste_recherche_par_valeur(liste, cv3);
	air_bdd_liste_printf(res);

	printf("Cartes pouvant battre le Roi de Coeur :\n%s\n",
		   "---------------------------------------");
	res = air_bdd_liste_recherche_attaquants(liste, c3);
	air_bdd_liste_printf(res);

	air_bdd_liste_free(liste);
	air_bdd_liste_free(res);

	air_carte_free(c1);
	air_carte_free(c2);
	air_carte_free(c3);

	return 0;
}
