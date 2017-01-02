/**
 * \file bdd.c
 * \brief Fonctions de base de données
 */

#include "bdd.h"
#include "carte.h"
#include <stdlib.h>
#include <errno.h>

/**
 * \fn carte_cell* air_bdd_cell_creer(carte *c)
 * \brief Alloue et initialise une cellule
 * \param c La carte à encapsuler
 * \return NULL en cas d'erreur (voir errno), sinon la cellule nouvellement
 *          créée
 */
carte_cell* air_bdd_cell_creer(carte *c)
{
	if(c == NULL) {
		errno = EINVAL;
		return NULL;
	}

	carte_cell *cell = malloc(sizeof(carte_cell));

	if(cell == NULL) {
		return NULL;
	}

	air_bdd_cell_init(cell, c);
	return cell;
}

/**
 * \fn int air_bdd_cell_init(carte_cell *cell, carte *c);
 * \brief Initialise une cellule
 * \param cell La cellule à initialiser
 * \param c La carte à encapsuler
 * \return -1 en cas d'erreur (voir errno), 0 sinon
 */
int air_bdd_cell_init(carte_cell *cell, carte *c)
{
	if(cell == NULL || c == NULL) {
		errno = EINVAL;
		return -1;
	}

	cell->c = c;
	cell->suiv = NULL;
	return 0;
}

/**
 * \fn carte_liste* air_bdd_liste_creer()
 * \brief Alloue et initialise une liste de cellules
 * \return NULL en cas d'erreur (voir errno), sinon la liste nouvellement
 *         créée
 */
carte_liste* air_bdd_liste_creer()
{
	carte_liste *l = malloc(sizeof(carte_liste));
	if(l == NULL) {
		return NULL;
	}

	air_bdd_liste_init(l);
	return l;
}

/**
 * \fn int air_bdd_liste_init(carte_liste *l)
 * \brief Initialise une liste de cellules
 * \param l La liste à initialiser
 * \return -1 en cas d'erreur (voir errno), 0 sinon
 */
int air_bdd_liste_init(carte_liste *l)
{
	if(l == NULL) {
		errno = EINVAL;
		return -1;
	}

	l->premier = NULL;
	l->dernier = NULL;
	return 0;
}

/**
 * \fn void air_bdd_liste_free(carte_liste *l)
 * \brief Libère de la mémoire une liste de cellules
 * \param l La liste à libérer de la mémoire
 */
void air_bdd_liste_free(carte_liste *l)
{
	carte_cell *c = l->premier, *buf;
	while(c != NULL) {
		buf = c;
		c = buf->suiv;
		free(buf);
	}

	free(l);
}

/**
 * \fn int air_bdd_liste_ajouter(carte_liste *l, carte *c)
 * \brief Ajoute une carte à la liste
 * \param l La liste à manipuler
 * \param c La carte à ajouter
 * \return -1 en cas d'erreur (voir errno), 0 sinon
 */
int air_bdd_liste_ajouter(carte_liste *l, carte *c)
{
	if(l == NULL || c == NULL) {
		errno = EINVAL;
		return -1;
	}

	carte_cell *cell = air_bdd_cell_creer(c);
	if(cell == NULL) {
		return -1;
	}

	if(l->premier == NULL) {
		l->premier = cell;
	} else {
		l->dernier->suiv = cell;
	}

	l->dernier = cell;
	return 0;

}

/**
 * \fn int air_bdd_liste_retirer(carte_liste *l, carte *c)
 * \brief Reture une carte de la liste
 * \param l La liste à manipuler
 * \param c La carte à retirer
 * \return -1 en cas d'erreur (voir errno), 0 si l'élément a été retiré,
 *         1 si l'élément n'était pas dans la liste
 */
int air_bdd_liste_retirer(carte_liste *l, carte *c)
{
	carte_cell *cell = l->premier, *prec = NULL;
	while(cell != NULL) {
		if(cell->c == c) {
			break;
		}

		prec = cell;
		cell = prec->suiv;
	}

	if(cell == NULL) {
		return 1;
	}

	if(prec == NULL) {
		l->premier = cell->suiv;
	} else {
		prec->suiv = cell->suiv;
	}

	if(l->dernier == cell) {
		l->dernier = prec;
	}

	free(cell);

	return 0;
}

/**
 * \fn int air_bdd_liste_taille(carte_liste *l)
 * \brief Retourne la taille d'une liste de cartes
 * \param l La liste de cartes à manipuler
 * \return -1 en cas d'erreur (voir errno), sinon la taille de la liste
 */
int air_bdd_liste_taille(carte_liste *l)
{
	if(l == NULL) {
		errno = EINVAL;
		return -1;
	}

	carte_cell *c = l->premier;
	int i = 0;

	while(c != NULL) {
		i++;
		c = c->suiv;
	}

	return i;
}

/**
 * \fn carte_liste* air_bdd_liste_recherche_par_valeur(carte_liste *l, enum carte_valeur val)
 * \brief Retourne une liste des cartes ayant pour valeur `val`
 * \param l La liste sur laquelle exécuter la requête (allouée dynamiquement)
 * \param val La valeur à rechercher
 * \return NULL en cas d'erreur (voir errno), sinon retourne la liste résultat
 */
carte_liste* air_bdd_liste_recherche_par_valeur(carte_liste *l, enum carte_valeur val)
{
	if(l == NULL) {
		errno  = EINVAL;
		return NULL;
	}

	carte_liste *res = air_bdd_liste_creer();
	if(res == NULL) {
		return NULL;
	}

	carte_cell *cell = l->premier;
	while(cell != NULL) {
		if(air_carte_valeur_get(cell->c) == val) {
			air_bdd_liste_ajouter(res, cell->c);
		}

		cell = cell->suiv;
	}

	return res;
}

/**
 * \fn carte_liste* air_bdd_liste_recherche_par_enseigne(carte_liste *l, enum carte_enseigne enseigne)
 * \brief Retourne une liste des cartes ayant pour enseigne `enseigne`
 * \param l La liste sur laquelle exécuter la requête (allouée dynamiquement)
 * \param enseigne L'enseigne à rechercher
 * \return NULL en cas d'erreur (voir errno), sinon retourne la liste résultat
 */
carte_liste* air_bdd_liste_recherche_par_enseigne(carte_liste *l, enum carte_enseigne enseigne)
{
	if(l == NULL) {
		errno  = EINVAL;
		return NULL;
	}

	carte_liste *res = air_bdd_liste_creer();
	if(res == NULL) {
		return NULL;
	}

	carte_cell *cell = l->premier;
	while(cell != NULL) {
		if(air_carte_enseigne_get(cell->c) == enseigne) {
			air_bdd_liste_ajouter(res, cell->c);
		}

		cell = cell->suiv;
	}

	return res;
}


/**
 * \fn carte_liste* air_bdd_liste_recherche_attaquants(carte_liste *l, carte *c)
 * \brief Retourne la liste des cartes pouvant attaquer la carte `c`
 * \param l La liste sur laquelle effectuer la recherche
 * \param c La carte "attaquée"
 * \return NULL en cas d'erreur (voir errno), sinon retourne la liste résultat
 */
carte_liste* air_bdd_liste_recherche_attaquants(carte_liste *l, carte *c)
{
	if(l == NULL || c == NULL) {
		errno  = EINVAL;
		return NULL;
	}

	carte_liste *res = air_bdd_liste_creer();
	if(res == NULL) {
		return NULL;
	}

	carte_cell *cell = l->premier;
	while(cell != NULL) {
		if(air_carte_peut_battre(cell->c, c) == true) {
			air_bdd_liste_ajouter(res, cell->c);
		}

		cell = cell->suiv;
	}

	return res;
}
