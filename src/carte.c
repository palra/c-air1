#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "carte.h"

/**
 * Alloue dynamiquement une carte et l'initialise
 */
carte* air_carte_creer()
{
	carte *c = malloc(sizeof(carte));
	if(c == NULL) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(errno);
	}

	air_carte_init(c);
	return c;
}

/**
 * Libère de la mémoire une carte
 * @param carte *c La carte à libérer de la mémoire
 */
void air_carte_free(carte *c)
{
	carte_prop *ptr = c->prop, *buffer;
	while(ptr != NULL) {
		buffer = ptr;
		ptr = ptr->suiv;
		free(buffer);
	}

	free(c);
}

/**
 * Alloue la mémoire pour une carte_prop et l'initialise
 */
carte_prop* air_carte_prop_creer()
{
	carte_prop *prop = malloc(sizeof(carte_prop));
	air_carte_prop_init(prop);
	return prop;
}

/**
 * Initialise une carte_prop
 * @param carte_prop *p La propriété à initialiser
 * @return int 0 lorsqu'aucune erreur n'a eu lieu
 */
int air_carte_prop_init(carte_prop *p)
{
	p->suiv = NULL;
	return 0;
}

/**
 * Recherche la première propriété de type `type` dans la
 * chaîne des propriétés d'une carte donnée
 *
 * @param carte_prop *ptr La propriété à partir du quel effectuer la recherche
 * @param enum carte_prop_type type Le type à rechercher
 */
carte_prop* air_carte_prop_find_type(carte_prop *ptr, enum carte_prop_type type)
{
	while(ptr != NULL) {
		if(ptr->type == type)
			break;
		ptr = ptr->suiv;
	}

	return ptr;
}

/**
 * Ajoute une propriété à la carte
 * @param carte *c La carte à modifier
 * @param carte_prop *p La propriété à ajouter
 * @return int 0 lorsqu'aucune erreur n'a eu lieu
 */
int air_carte_prop_ajouter(carte *c, carte_prop *p)
{
	if(c->prop == NULL) {
		c->prop = p;
		return 0;
	}

	carte_prop *ptr = c->prop;
	while(ptr != NULL) {
		if(ptr->suiv == NULL)
			break;
		ptr = ptr->suiv;
	}

	ptr->suiv = p;

	return 0;
}

/**
 * Initialise la structure
 * @param carte *c L'instance de la structure à initialiser
 * @return int 0 lorsqu'aucune erreur n'a eu lieu
 */
int air_carte_init(carte *c)
{
	c->prop = NULL;
	return 0;
}

/**
 * Retourne la valeur d'une carte
 * @param carte *c La carte
 * @return enum carte_enseigne La valeur de la carte
 */
enum carte_valeur air_carte_valeur_get(carte *c)
{
	carte_prop *ptr = air_carte_prop_find_type(c->prop, cptValeur);

	if(ptr == NULL) {
		return cvNull;
	}

	return ptr->val.valeur;
}

/**
 * Affecte la valeur `valeur` à la carte
 * @param carte *c L'instance de la structure à modifier
 * @param enum carte_valeur valeur La valeur à affecter
 * @return int 0 lorsqu'aucune erreur n'a eu lieu
 */
int air_carte_valeur_set(carte *c, enum carte_valeur valeur)
{
	carte_prop *prop = air_carte_prop_find_type(c->prop, cptValeur);
	if(prop == NULL) { // Si aucune propriété précédente de même type n'existe
		prop = air_carte_prop_creer(); // On en crée une
		air_carte_prop_ajouter(c, prop); // Et on l'ajoute
	}
	
	prop->val.valeur = valeur; // On écrit la valeur
	prop->type = cptValeur; // Et le type

	return 0;
}

/**
 * Retourne l'enseigne d'une carte
 * @param carte *c La carte
 * @return enum carte_enseigne L'enseigne de la carte
 */
enum carte_enseigne air_carte_enseigne_get(carte *c)
{
	carte_prop *ptr = air_carte_prop_find_type(c->prop, cptEnseigne);

	if(ptr == NULL) {
		return ceNull;
	}

	return ptr->val.enseigne;
}

/**
 * Affecte l'enseigne `enseigne` à la carte
 * @param carte *c L'instance de la structure à modifier
 * @param enum carte_enseigne enseigne L'enseigne à affecter
 * @return int 0 lorsqu'aucune erreur n'a eu lieu
 */
int air_carte_enseigne_set(carte *c, enum carte_enseigne enseigne)
{
	carte_prop *prop = air_carte_prop_find_type(c->prop, cptEnseigne);
	
	if(prop == NULL) {
		prop = air_carte_prop_creer();
		air_carte_prop_ajouter(c, prop);
	}

	prop->val.enseigne = enseigne;
	prop->type = cptEnseigne;

	return 0;
}

/**
 * Vérifie si une carte peut en battre une autre
 * @param carte *c La carte "attaquante"
 * @param carte *peut_battre La carte "attaquée"
 * @return bool true si la carte attaquante peut la battre,
 *              false sinon
 */
bool air_carte_peut_battre(carte *c, carte *peut_battre)
{
	carte_prop *ptr = c->prop;
	while(ptr != NULL) {
		ptr = air_carte_prop_find_type(ptr, cptPeutBattre);
		if(ptr->val.peut_battre == peut_battre) {
			return true;
		}

		ptr = ptr->suiv;
	}

	return false;
}

/**
 * Affecte à une carte une référence vers une autre carte
 * @param carte *c L'instance de la structure à modifier
 * @param carte *peut_battre La carte battue
 * @return int 0 lorsqu'aucune erreur n'a eu lieu, -1 quand
 *         une erreur a eu lieu (peut_battre == NULL ou à c)
 */
int air_carte_bat_add(carte *c, carte *peut_battre)
{
	if(peut_battre == NULL || peut_battre == c) {
		errno = EINVAL;
		return -1;
	}

	carte_prop *prop = air_carte_prop_creer();
	air_carte_prop_ajouter(c, prop);

	prop->val.peut_battre = peut_battre;
	prop->type = cptPeutBattre;

	return 0;
}
