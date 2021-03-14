#ifndef INGREDIENT_H_
#define INGREDIENT_H_

typedef struct{
	char* nume;
	char* producator;
	unsigned int cantitate;
} Ingredient;

void ingredient_init(Ingredient* ingredient, char* nume, char* producator, unsigned int cantitate);
void ingredient_destroy(Ingredient* ingredient);


//getters
char* ingredient_get_nume(Ingredient* ingredient);
char* ingredient_get_producator(Ingredient* ingredient);
unsigned int ingredient_get_cantitate(Ingredient* ingredient);

//setters
void ingredient_set_nume(Ingredient* ingredient, char* nume);
void ingredient_set_producator(Ingredient* ingredient, char* producator);
void ingredient_set_cantitate(Ingredient* ingredient, unsigned int cantitate);

void ingredient_inc_quantity(Ingredient* ingredient, unsigned int new_quantity);

#endif