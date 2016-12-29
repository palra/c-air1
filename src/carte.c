#include <stdlib.h>
#include "carte.h"

/**
 * Alloue dynamiquement une carte et l'initialise
 */
carte* air_carte_creer()
{
	carte *c = malloc(sizeof(carte));
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
 */
void air_carte_prop_init(carte_prop *p)
{
	p->suiv = NULL;
}

/**
 * Recherche la première propriété de type `type` dans la
 * chaîne des propriétés d'une carte donnée
 *
 * @param carte *c La carte à chercher
 * @param enum carte_prop_type type Le type à rechercher
 */
carte_prop* air_carte_prop_find_type(carte *c, enum carte_prop_type type)
{
	carte_prop *ptr = c->prop;
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
 */
void air_carte_prop_ajouter(carte *c, carte_prop *p)
{
	if(c->prop == NULL) {
		c->prop = p;
		return;
	}

	carte_prop *ptr = c->prop;
	while(ptr != NULL) {
		if(ptr->suiv == NULL)
			break;
		ptr = ptr->suiv;
	}

	ptr->suiv = p;
}

/**
 * Initialise la structure
 * @param carte *c L'instance de la structure à initialiser
 */
void air_carte_init(carte *c)
{
	c->prop = NULL;
}

enum carte_valeur air_carte_valeur_get(carte *c)
{
	carte_prop *ptr = air_carte_prop_find_type(c, cptValeur);

	if(ptr == NULL) {
		return cvNull;
	}

	return ptr->val.valeur;
}

/**
 * Affecte la valeur `valeur` à la carte
 * @param carte *c L'instance de la structure à modifier
 * @param enum carte_valeur valeur La valeur à affecter
 */
void air_carte_valeur_set(carte *c, enum carte_valeur valeur)
{
	carte_prop *prop = air_carte_prop_find_type(c, cptValeur);
	if(prop == NULL) { // Si aucune propriété précédente de même type n'existe
		prop = air_carte_prop_creer(); // On en crée une
		air_carte_prop_ajouter(c, prop); // Et on l'ajoute
	}
	
	prop->val.valeur = valeur; // On écrit la valeur
	prop->type = cptValeur; // Et le type
}
