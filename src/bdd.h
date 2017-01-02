/**
 * \file bdd.h
 * \brief Définitions des fonctions de la base de données
 * \author Loïc Payol <loicpayol@gmail.com>
 */

#pragma once
#include "carte.h"

/**
 * \struct carte_cell
 * \brief Définit une cellule d'une liste chaînée de cartes
 */
typedef struct carte_cell {
	carte *c; /*!< La carte à référencer */
	struct carte_cell *suiv; /*!< La cellule suivante */
} carte_cell;

/**
 * \struct carte_liste
 * \brief Définit une liste chaînée de cartes
 */
typedef struct carte_liste {
	carte_cell *premier; /*!< Le premier élément de la liste */
	carte_cell *dernier; /*!< Le dernier élément de la liste */
} carte_liste;


carte_cell* air_bdd_cell_creer(carte *c);
int air_bdd_cell_init(carte_cell *cell, carte *c);

carte_liste* air_bdd_liste_creer();
int air_bdd_liste_init(carte_liste *l);
void air_bdd_liste_free(carte_liste *l);
int air_bdd_liste_ajouter(carte_liste *l, carte *c);
int air_bdd_liste_retirer(carte_liste *l, carte *c);

int air_bdd_liste_taille(carte_liste *l);

carte_liste* air_bdd_liste_recherche_par_valeur(carte_liste *l, enum carte_valeur val);
carte_liste* air_bdd_liste_recherche_par_enseigne(carte_liste *l, enum carte_enseigne enseigne);
carte_liste* air_bdd_liste_recherche_attaquants(carte_liste *l, carte *c);

void air_bdd_liste_afficher(carte_liste *l);
