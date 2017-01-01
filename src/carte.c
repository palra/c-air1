/**
 * \file carte.c
 * \brief Fonctions de manipulation de l'entité "carte"
 * \author Loïc Payol <loicpayol@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "carte.h"

/**
 * \fn carte* air_carte_creer()
 * \brief Alloue dynamiquement une carte et l'initialise
 * \return La carte nouvellement crée
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
 * \fn void air_carte_free(carte *c)
 * \brief Libère de la mémoire une carte
 * \param c La carte à libérer de la mémoire
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
 * \fn carte_prop* air_carte_prop_creer()
 * \brief Alloue la mémoire pour une carte_prop et l'initialise
 * \return la prorpiété nouvellement crée
 */
carte_prop* air_carte_prop_creer()
{
	carte_prop *prop = malloc(sizeof(carte_prop));
	if(prop == NULL) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(errno);
	}

	air_carte_prop_init(prop);
	return prop;
}

/**
 * \fn int air_carte_prop_init(carte_prop *p)
 * \brief Initialise une carte_prop
 * \param p La propriété à initialiser
 * \return 0 lorsqu'aucune erreur n'a eu lieu
 */
int air_carte_prop_init(carte_prop *p)
{
	p->suiv = NULL;
	return 0;
}

/**
 * \fn carte_prop* air_carte_prop_find_type(carte_prop *ptr, enum carte_prop_type type)
 * \brief Recherche la première propriété de type `type` dans la chaîne des
 *        propriétés d'une carte donnée
 *
 * \param ptr La propriété à partir de laquelle effectuer la recherche
 * \param type Le type à rechercher
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
 * \fn int air_carte_prop_ajouter(carte *c, carte_prop *p)
 * \brief Ajoute une propriété à la carte
 * \param c La carte à modifier
 * \param p La propriété à ajouter
 * \return 0 lorsqu'aucune erreur n'a eu lieu
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
 * \fn int air_carte_init(carte *c)
 * \brief Initialise la structure
 * \param c L'instance de la structure à initialiser
 * \return 0 lorsqu'aucune erreur n'a eu lieu
 */
int air_carte_init(carte *c)
{
	c->prop = NULL;
	return 0;
}

/**
 * \fn enum carte_valeur air_carte_valeur_get(carte *c)
 * \brief Retourne la valeur d'une carte
 * \param c La carte
 * \return La valeur de la carte
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
 * \fn int air_carte_valeur_set(carte *c, enum carte_valeur valeur)
 * \brief Affecte la valeur `valeur` à la carte
 * \param c L'instance de la structure à modifier
 * \param valeur La valeur à affecter
 * \return 0 lorsqu'aucune erreur n'a eu lieu
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
 * \fn enum carte_enseigne air_carte_enseigne_get(carte *c)
 * \brief Retourne l'enseigne d'une carte
 * \param c La carte
 * \return L'enseigne de la carte
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
 * \fn int air_carte_enseigne_set(carte *c, enum carte_enseigne enseigne)
 * \brief Affecte l'enseigne `enseigne` à la carte
 * \param c L'instance de la structure à modifier
 * \param enseigne L'enseigne à affecter
 * \return 0 lorsqu'aucune erreur n'a eu lieu
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
 * \fn bool air_carte_peut_battre(carte *c, carte *peut_battre)
 * \brief Vérifie si une carte peut en battre une autre
 * \param c La carte "attaquante"
 * \param peut_battre La carte "attaquée"
 * \return true si la carte attaquante peut la battre, false sinon
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
 * \fn int air_carte_bat_add(carte *c, carte *peut_battre)
 * \brief Affecte à une carte une référence vers une autre carte
 * \param c L'instance de la structure à modifier
 * \param peut_battre La carte battue
 * \return 0 lorsqu'aucune erreur n'a eu lieu, -1 quand
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

/**
 * \fn void air_carte_printf(carte *c)
 * \brief Affiche les propriétés d'une carte sur la sortie standard
 * \param c La carte à afficher
 */
void air_carte_printf(carte *c)
{
	carte_prop *ptr = c->prop;
	if(ptr == NULL) {
		printf("Aucune propriété\n");
	}

	int i = 1;
	while(ptr != NULL) {
		printf("[%d] ", i);
		switch(ptr->type) {
			case cptValeur:
				printf("Valeur = ");
				air_carte_affiche_valeur(ptr->val.valeur);
				break;
			case cptEnseigne:
				printf("Enseigne = ");
				air_carte_affiche_enseigne(ptr->val.enseigne);
				break;
			case cptPeutBattre:
				printf("Peut battre = ");
				carte *peut_battre = ptr->val.peut_battre;
				if(peut_battre == NULL) {
					printf("Non défini");
				}

				air_carte_affiche_valeur(
					air_carte_valeur_get(peut_battre)
				);
				printf(" de ");
				air_carte_affiche_enseigne(
					air_carte_enseigne_get(peut_battre)
				);
				break;
			default:
				printf("Propriété de type inconnu");
				break;
		}
		
		printf("\n");

		ptr = ptr->suiv;
		i++;
	}
}

/**
 * \fn void air_carte_affiche_valeur(enum carte_valeur valeur)
 * \brief Affiche la valeur passée en paramètre dans la sortie standard
 * \param valeur La valeur à afficher
 */
void air_carte_affiche_valeur(enum carte_valeur valeur)
{
	switch(valeur) {
		case cvAs:
			printf("As");
			break;
		case cv2:
			printf("2");
			break;
		case cv3:
			printf("3");
			break;
		case cv4:
			printf("4");
			break;
		case cv5:
			printf("5");
			break;
		case cv6:
			printf("6");
			break;
		case cv7:
			printf("7");
			break;
		case cv8:
			printf("8");
			break;
		case cv9:
			printf("9");
			break;
		case cv10:
			printf("10");
			break;
		case cvValet:
			printf("Valet");
			break;
		case cvDame:
			printf("Dame");
			break;
		case cvRoi:
			printf("Roi");
			break;
		default:
			printf("Non défini");
			break;
	}
}

/**
 * \fn void air_carte_affiche_enseigne(enum carte_enseigne enseigne)
 * \brief Affiche l'enseigne passée en paramètre dans la sortie standard
 * \param valeur L'enseigne à afficher
 */
void air_carte_affiche_enseigne(enum carte_enseigne enseigne)
{
	switch(enseigne) {
		case cePique:
			printf("Pique");
			break;
		case ceCarreau:
			printf("Carreau");
			break;
		case ceCoeur:
			printf("Coeur");
			break;
		case ceTrefle:
			printf("Trefle");
			break;
		default:
			printf("Non défini");
			break;
	}
}
