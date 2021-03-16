#include <malloc.h>
#include "ingredient.h"
#include <string.h>

void ingredient_init(Ingredient* ingredient, char* nume, char* producator, unsigned int cantitate) {
	ingredient->nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(ingredient->nume, nume);
	ingredient->producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(ingredient->producator, producator);
	ingredient->cantitate = cantitate;
}

void ingredient_destroy(Ingredient* ingredient) {
	free(ingredient->nume);
	free(ingredient->producator);
}

char* ingredient_get_nume(Ingredient* ingredient) {
	return ingredient->nume;
}

char* ingredient_get_producator(Ingredient* ingredient) {
	return ingredient->producator;
}

unsigned int ingredient_get_cantitate(Ingredient* ingredient) {
	return ingredient->cantitate;
}

void ingredient_set_nume(Ingredient* ingredient, char* nume) {
	free(ingredient->nume);
	ingredient->nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(ingredient->nume, nume);
}

void ingredient_set_producator(Ingredient* ingredient, char* producator) {
	free(ingredient->producator);
	ingredient->producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(ingredient->producator, producator);
}

void ingredient_set_cantitate(Ingredient* ingredient, unsigned int cantitate) {
	ingredient->cantitate = cantitate;
}

void ingredient_inc_quantity(Ingredient* ingredient, unsigned int new_quantity)
{
	ingredient->cantitate += new_quantity;
}
