#include "greatest.h"
#include "../src/carte.h"
#include <stdlib.h>

//----- **** SUITE(carte) ***** -----//

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

//----- main() -----//

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(carte_suite);

	GREATEST_MAIN_END();
}
