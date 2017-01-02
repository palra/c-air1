/**
 * \file carte.h
 * \brief Définition des fonctions et types de cartes
 * \author Loïc Payol <loicpayol@gmail.com>
 */

#pragma once
#include <stdbool.h>

/**
 * \enum carte_enseigne
 * \brief Définit les enseigne d'une carte
 */
typedef enum carte_enseigne {
	ceNull = 0,
	cePique,
	ceCarreau,
	ceCoeur,
	ceTrefle
} carte_enseigne;

/**
 * \enum carte_valeur
 * \brief Définit les valeurs d'une carte
 */
enum carte_valeur {
	cvNull = 0, /*!< Permet de renvoyer une valeur nulle */
	cvAs,
	cv2,
	cv3,
	cv4,
	cv5,
	cv6,
	cv7,
	cv8,
	cv9,
	cv10,
	cvValet,
	cvDame,
	cvRoi
};

/**
 * \struct carte
 * \brief Définit une carte
 */
typedef struct carte {
	struct carte_prop *prop; /*!< Pointeur vers la première propriété */
} carte;

/**
 * \enum carte_prop_type
 * \brief Enumération pour le champ discriminant de l'union
 */
enum carte_prop_type {
	cptEnseigne,
	cptValeur,
	cptPeutBattre /*!< Permet d'indiquer qu'une carte peut en battre une autre */
};

/**
 * \struct carte_prop
 * \brief Définit une propriété d'une carte
 */
typedef struct carte_prop {
	union {
		enum carte_enseigne enseigne; /*!< Enseigne d'une carte (pique, carreaux ...) */
		enum carte_valeur valeur; /*!< Valeur (2, 3, as, roi ...) */
		carte *peut_battre; /*!< Pointeur vers une carte que la carte courante peut battre */
	} val;
	enum carte_prop_type type; /*!< Champ discriminant pour savoir quel champ de l'union lire */
	struct carte_prop *suiv; /*!< Pointeur vers la propriété suivante */
} carte_prop;

// Fonctions de manipulation de cartes
// doc. dans carte.c

carte_prop* air_carte_prop_find_type(carte_prop *ptr, enum carte_prop_type type);
carte_prop* air_carte_prop_creer();
int air_carte_prop_ajouter(carte *c, carte_prop *p);
int air_carte_prop_init(carte_prop *p);

carte* air_carte_creer();
void air_carte_free(carte *c);
int air_carte_init(carte *c);

enum carte_valeur air_carte_valeur_get(carte *c);
int air_carte_valeur_set(carte *c, enum carte_valeur valeur);
enum carte_enseigne air_carte_enseigne_get(carte *c);
int air_carte_enseigne_set(carte *c, enum carte_enseigne enseigne);
bool air_carte_peut_battre(carte *c, carte *peut_battre);
int air_carte_bat_add(carte *c, carte *peut_battre);

void air_carte_printf(carte *c);
void air_carte_affiche_valeur(enum carte_valeur valeur);
void air_carte_affiche_enseigne(enum carte_enseigne enseigne);
