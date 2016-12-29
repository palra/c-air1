#pragma once

/**
 * Définit les enseigne d'une carte
 */
enum carte_enseigne {
	ceNull = 0,
	cePique,
	ceCarreau,
	ceCoeur,
	ceTrefle
};

/**
 * Définit les valeurs d'une carte
 */
enum carte_valeur {
	cvNull = 0, // Permet de renvoyer une valeur nulle
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
 * La carte à proprement parler
 */
typedef struct carte {
	struct carte_prop *prop; // Pointeur vers la première propriété
} carte;

/**
 * Enumération pour le champ discriminant de l'union
 */
enum carte_prop_type {
	cptEnseigne,
	cptValeur,
	cptPoints
};

/**
 * Définit une propriété d'une carte
 */
typedef struct carte_prop {
	union {
		enum carte_enseigne enseigne; // Enseigne d'une carte (pique, carreaux ...)
		enum carte_valeur valeur; // Valeur (2, 3, as, roi ...)
		int points; // Valeur arbitraire, peut servir à stocker
		            // les propriétés d'un jeu de carte particulier
	} val;
	enum carte_prop_type type; // Champ discriminant pour savoir quel champ de l'union lire
	struct carte_prop *suiv; // Pointeur vers la propriété suivante
} carte_prop;

// Fonctions de manipulation de cartes
// doc. dans carte.c

carte_prop* air_carte_prop_find_type(carte *c, enum carte_prop_type type);
carte_prop* air_carte_prop_creer();
void air_carte_prop_ajouter(carte *c, carte_prop *p);
void air_carte_prop_init(carte_prop *p);
carte* air_carte_creer();
void air_carte_init(carte *c);
enum carte_valeur air_carte_valeur_get(carte *c);
void air_carte_valeur_set(carte *c, enum carte_valeur valeur);
enum carte_enseigne air_carte_enseigne_get(carte *c);
