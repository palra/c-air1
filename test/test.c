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
 * La carte crée et initialisé
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

SUITE(carte_suite) {
	RUN_TEST(air_carte_init_should_reset_prop);
	RUN_TEST(air_carte_valeur_get_should_be_cvNull);
	RUN_TEST(air_carte_valeur_set_should_assign_value);
}

//----- main() -----//

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(carte_suite);

	GREATEST_MAIN_END();
}
