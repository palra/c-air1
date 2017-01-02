/**
 * \file test.c
 * \brief Programme de suite de tests
 * \author Loïc Payol <loicpayol@gmail.com>
 * \version 0.1.0
 */

#include "greatest.h"
#include "../src/carte.h"
#include "../src/bdd.h"
#include <stdlib.h>


/**
 * La carte crée et initialisée
 * c->prop doit être initialisé à NULL
 */
TEST air_carte_init_should_reset_prop(void) {
	carte* c = air_carte_creer();
	air_carte_init(c);
	ASSERT_EQ(NULL, c->prop);
	PASS();
}

/**
 * La carte crée et initialisée
 * air_carte_valeur_get doit renvoyer cvNull
 */
TEST air_carte_valeur_get_should_be_cvNull(void) {
	carte c;
	air_carte_init(&c);
	ASSERT_EQ(cvNull, air_carte_valeur_get(&c));
	PASS();
}

/**
 * La carte crée et initialisée
 * air_carte_valeur_set doit affecter correctement la valeur
 * et doit aussi remplacer la valeur précédente si nécessaire
 */
TEST air_carte_valeur_set_should_assign_value(void) {
	carte c;
	air_carte_init(&c);
	air_carte_valeur_set(&c, cvAs);
	ASSERT_EQ(cvAs, air_carte_valeur_get(&c));
	air_carte_valeur_set(&c, cv10);
	ASSERT_EQ(cv10, air_carte_valeur_get(&c));
	PASS();
}

/**
 * La carte crée et initialisée
 * air_carte_enseigne_get doit renvoyer cvNull
 */
TEST air_carte_enseigne_get_should_be_ceNull(void) {
	carte c;
	air_carte_init(&c);
	ASSERT_EQ(ceNull, air_carte_enseigne_get(&c));
	PASS();
}

/**
 * La carte crée et initialisée
 * air_carte_enseigne_set doit affecter correctement la valeur
 * et doit aussi remplacer la valeur précédente si nécessaire
 */
TEST air_carte_enseigne_set_should_assign_value(void) {
	carte c;
	air_carte_init(&c);
	air_carte_enseigne_set(&c, cePique);
	ASSERT_EQ(cePique, air_carte_enseigne_get(&c));
	air_carte_enseigne_set(&c, ceCoeur);
	ASSERT_EQ(ceCoeur, air_carte_enseigne_get(&c));
	PASS();
}

/**
 * Les cartes crées et initialisée
 * air_carte_bat_add doit ajouter une référence à la liste des propriétés
 * sans remplacer les précédentes valeurs
 */
TEST air_carte_bat_add_should_assign_value(void) {
	carte c1, c2, c3;
	air_carte_init(&c1);
	air_carte_init(&c2);
	air_carte_init(&c3);

	air_carte_bat_add(&c1, &c2);
	ASSERT_EQ(true, air_carte_peut_battre(&c1, &c2));
	ASSERT_EQ(false, air_carte_peut_battre(&c1, &c3));
	air_carte_bat_add(&c1, &c3);
	ASSERT_EQ(true, air_carte_peut_battre(&c1, &c2));
	ASSERT_EQ(true, air_carte_peut_battre(&c1, &c3));

	PASS();
}


SUITE(carte_suite) {
	RUN_TEST(air_carte_init_should_reset_prop);
	RUN_TEST(air_carte_valeur_get_should_be_cvNull);
	RUN_TEST(air_carte_valeur_set_should_assign_value);
	RUN_TEST(air_carte_enseigne_get_should_be_ceNull);
	RUN_TEST(air_carte_enseigne_set_should_assign_value);
	RUN_TEST(air_carte_bat_add_should_assign_value);
}

TEST air_bdd_liste_ajouter_retirer(void) {
	carte c1, c2, c3;
	air_carte_init(&c1);
	air_carte_init(&c2);
	air_carte_init(&c3);

	carte_liste *liste = air_bdd_liste_creer();

	ASSERT_EQ(0, air_bdd_liste_taille(liste));

	air_bdd_liste_ajouter(liste, &c1);

	ASSERT_EQ(1, air_bdd_liste_taille(liste));
	ASSERT_EQ(&c1, liste->premier->c);
	ASSERT_EQ(&c1, liste->dernier->c);

	air_bdd_liste_ajouter(liste, &c2);

	ASSERT_EQ(2, air_bdd_liste_taille(liste));
	ASSERT_EQ(&c1, liste->premier->c);
	ASSERT_EQ(&c2, liste->dernier->c);

	air_bdd_liste_ajouter(liste, &c3);

	ASSERT_EQ(3, air_bdd_liste_taille(liste));
	ASSERT_EQ(&c1, liste->premier->c);
	ASSERT_EQ(&c3, liste->dernier->c);

	air_bdd_liste_retirer(liste, &c3);
	ASSERT_EQ(2, air_bdd_liste_taille(liste));
	ASSERT_EQ(&c1, liste->premier->c);
	ASSERT_EQ(&c2, liste->dernier->c);

	air_bdd_liste_retirer(liste, &c1);
	ASSERT_EQ(1, air_bdd_liste_taille(liste));
	ASSERT_EQ(&c2, liste->premier->c);
	ASSERT_EQ(&c2, liste->dernier->c);

	air_bdd_liste_free(liste);

	PASS();
}

TEST air_bdd_liste_recherche_par_valeur_should_return_list(void) {
	carte *c1 = air_carte_creer(),
		  *c2 = air_carte_creer(),
		  *c3 = air_carte_creer();

	air_carte_valeur_set(c1, cvAs);
	air_carte_valeur_set(c2, cv3);
	air_carte_valeur_set(c3, cv3);

	air_carte_enseigne_set(c1, ceTrefle);
	air_carte_enseigne_set(c2, ceTrefle);
	air_carte_enseigne_set(c3, ceCoeur);

	air_carte_bat_add(c1, c3);
	air_carte_bat_add(c2, c1);
	air_carte_bat_add(c2, c3);

	carte_liste *l = air_bdd_liste_creer();
	air_bdd_liste_ajouter(l, c1);
	air_bdd_liste_ajouter(l, c2);
	air_bdd_liste_ajouter(l, c3);

	carte_liste *res1 = air_bdd_liste_recherche_par_valeur(l, cv3);
	ASSERT_EQ(2, air_bdd_liste_taille(res1));

	carte_liste *res2 = air_bdd_liste_recherche_par_valeur(l, cv10);
	ASSERT_EQ(0, air_bdd_liste_taille(res2));


	air_bdd_liste_free(l);
	air_bdd_liste_free(res1);
	air_bdd_liste_free(res2);

	air_carte_free(c1);
	air_carte_free(c2);
	air_carte_free(c3);
	PASS();
}

TEST air_bdd_liste_recherche_par_enseigne_should_return_list(void) {
	carte *c1 = air_carte_creer(),
		  *c2 = air_carte_creer(),
		  *c3 = air_carte_creer();

	air_carte_valeur_set(c1, cvAs);
	air_carte_valeur_set(c2, cv3);
	air_carte_valeur_set(c3, cv3);

	air_carte_enseigne_set(c1, ceTrefle);
	air_carte_enseigne_set(c2, ceTrefle);
	air_carte_enseigne_set(c3, ceCoeur);

	air_carte_bat_add(c1, c3);
	air_carte_bat_add(c2, c1);
	air_carte_bat_add(c2, c3);

	carte_liste *l = air_bdd_liste_creer();
	air_bdd_liste_ajouter(l, c1);
	air_bdd_liste_ajouter(l, c2);
	air_bdd_liste_ajouter(l, c3);

	carte_liste *res1 = air_bdd_liste_recherche_par_enseigne(l, ceTrefle);
	ASSERT_EQ(2, air_bdd_liste_taille(res1));

	carte_liste *res2 = air_bdd_liste_recherche_par_enseigne(l, cePique);
	ASSERT_EQ(0, air_bdd_liste_taille(res2));


	air_bdd_liste_free(l);
	air_bdd_liste_free(res1);
	air_bdd_liste_free(res2);

	air_carte_free(c1);
	air_carte_free(c2);
	air_carte_free(c3);
	PASS();
}

TEST air_bdd_liste_recherche_attaquants_should_return_list(void) {
	carte *c1 = air_carte_creer(),
		  *c2 = air_carte_creer(),
		  *c3 = air_carte_creer();

	air_carte_valeur_set(c1, cvAs);
	air_carte_valeur_set(c2, cv3);
	air_carte_valeur_set(c3, cv3);

	air_carte_enseigne_set(c1, ceTrefle);
	air_carte_enseigne_set(c2, ceTrefle);
	air_carte_enseigne_set(c3, ceCoeur);

	air_carte_bat_add(c1, c3);
	air_carte_bat_add(c2, c1);
	air_carte_bat_add(c2, c3);

	carte_liste *l = air_bdd_liste_creer();
	air_bdd_liste_ajouter(l, c1);
	air_bdd_liste_ajouter(l, c2);
	air_bdd_liste_ajouter(l, c3);

	carte_liste *res1 = air_bdd_liste_recherche_attaquants(l, c3);
	ASSERT_EQ(2, air_bdd_liste_taille(res1));

	carte_liste *res2 = air_bdd_liste_recherche_attaquants(l, c2);
	ASSERT_EQ(0, air_bdd_liste_taille(res2));


	air_bdd_liste_free(l);
	air_bdd_liste_free(res1);
	air_bdd_liste_free(res2);

	air_carte_free(c1);
	air_carte_free(c2);
	air_carte_free(c3);
	PASS();
}

SUITE(bdd_suite) {
	RUN_TEST(air_bdd_liste_ajouter_retirer);
	RUN_TEST(air_bdd_liste_recherche_par_valeur_should_return_list);
	RUN_TEST(air_bdd_liste_recherche_par_enseigne_should_return_list);
	RUN_TEST(air_bdd_liste_recherche_attaquants_should_return_list);
}

//----- main() -----//

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(carte_suite);
	RUN_SUITE(bdd_suite);

	GREATEST_MAIN_END();
}
