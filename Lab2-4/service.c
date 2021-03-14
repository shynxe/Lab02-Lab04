#include <malloc.h>
#include "service.h"

void service_init(Service* service, RepoIngrediente* repo)
{
	service->repo = repo;
	repo_init(service->repo);
}

void service_destroy(Service* service)
{
	repo_destroy(service->repo);
}


int service_add_ingredient(Service* service, char* name, char* producator, unsigned int cantitate)
{
	Ingredient* ingred = malloc(sizeof(Ingredient));
	ingredient_init(ingred, name, producator, cantitate);
	return repo_add_ingredient(service->repo, ingred);
}

int service_remove_ingredient(Service* service, char* name)
{
	if (!service)
	{
		printf("Parametru service null la apelul functiei de remove ingredient in Service.");
		return 0;
	}
	return repo_remove_ingredient(service->repo, name);
}

int service_modifica_ingredient(Service* service, char* name, char* new_name, char* new_prod, unsigned int new_cantitate)
{
	Ingredient* ingredient_de_modificat = repo_find_ingredient(service->repo, name);
	if (!ingredient_de_modificat) {
		printf("Eroare: Nu exista ingredientul dat pentru modificare service.");
		return 0;
	}
	repo_edit_ingredient(service->repo, ingredient_de_modificat, new_name, new_prod, new_cantitate);
	return 1;
}
