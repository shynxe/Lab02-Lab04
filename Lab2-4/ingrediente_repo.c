#include "ingrediente_repo.h"
#include <malloc.h>


void repo_init(RepoIngrediente* repo) {
	repo->lista_ingrediente = malloc(sizeof(Vector));
	vector_init(repo->lista_ingrediente);
}

void repo_destroy(RepoIngrediente* repo) {
	int i;
	for (i = 0; i < vector_size(repo->lista_ingrediente); i++) {
		ingredient_destroy(vector_at(repo->lista_ingrediente, i));
		free(vector_at(repo->lista_ingrediente, i));
	}
	vector_destroy(repo->lista_ingrediente);
	free(repo->lista_ingrediente);
}

int repo_size(RepoIngrediente* repo) {
	return vector_size(repo->lista_ingrediente);
}

int repo_add_ingredient(RepoIngrediente* repo, Ingredient* ingredient)
{
	if (!repo) {
		printf("Eroare: repo = null\n");
		return 0;
	}
	if (!ingredient) {
		printf("Eroare: ingredi1ent = null\n");
		return 0;
	}
	Ingredient* exists = repo_find_ingredient(repo, ingredient_get_nume(ingredient));
	if (exists) {
		ingredient_inc_quantity(exists, ingredient->cantitate);
		ingredient_destroy(ingredient);
		free(ingredient);
		return 2;
	}
	vector_pushback(repo->lista_ingrediente, ingredient);
	return 1;
}

int repo_remove_ingredient(RepoIngrediente* repo, char* name)
{
	if (!repo) {
		printf("Eroare: repo = null la remove_ingredient\n");
		return 0;
	}
	int i;
	for (i = 0; i < repo_size(repo); i++) {
		if (strcmp(ingredient_get_nume(vector_at(repo->lista_ingrediente, i)), name) == 0) {
			Ingredient* ingred_de_sters = vector_at(repo->lista_ingrediente, i);
			ingredient_destroy(ingred_de_sters);
			free(ingred_de_sters);
			vector_remove(repo->lista_ingrediente, i);
			return 1;
		}
	}
	printf("Eroare: Nu a fost gasit ingredientul cu numele dat in lista pentru a il elimina.\n");
	return 0;
}


void repo_edit_ingredient(RepoIngrediente* repo, Ingredient* ingredient, char* new_name, char* new_prod, unsigned int new_cantitate)
{
	if (!repo)
	{
		printf("Eroare: repo = null la edit_ingredient\n");
		return;
	}
	if (!ingredient)
	{
		printf("Eroare: ingredient = null la edit_ingredient\n");
		return;
	}

	ingredient_set_nume(ingredient, new_name);
	ingredient_set_producator(ingredient, new_prod);
	ingredient_set_cantitate(ingredient, new_cantitate);
}

Ingredient* repo_find_ingredient(RepoIngrediente* repo, char* name)
{
	if (!repo) {
		printf("Eroare: repo este null in get_ingredient\n");
		return 0;
	}
	int i;
	for (i = 0; i < vector_size(repo->lista_ingrediente); i++) {
		if (strcmp(ingredient_get_nume(vector_at(repo->lista_ingrediente, i)), name) == 0) {
			return vector_at(repo->lista_ingrediente, i);
		}
	}
	return 0;
}

