#include <malloc.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
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
		printf("Parametru service null la apelul functiei de remove ingredient in Service.\n");
		return 0;
	}
	return repo_remove_ingredient(service->repo, name);
}

int service_modifica_ingredient(Service* service, char* name, char* new_name, char* new_prod, unsigned int new_cantitate)
{
	if (!service)
	{
		printf("Parametru service null la apelul functiei de edit ingredient in Service.\n");
		return 0;
	}
	Ingredient* ingredient_de_modificat = repo_find_ingredient(service->repo, name);
	if (!ingredient_de_modificat) {
		printf("Eroare: Nu exista ingredientul dat pentru modificare service.\n");
		return 0;
	}
	repo_edit_ingredient(service->repo, ingredient_de_modificat, new_name, new_prod, new_cantitate);
	return 1;
}

Vector* service_getall_litera(Service* service, char litera) {
	if (!service)
	{
		printf("Parametru service null la apelul functiei de getall_litera in Service.\n");
		return 0;
	}
	Vector* lista_ingrediente_litera = (Vector*)malloc(sizeof(Vector));
	vector_init(lista_ingrediente_litera);
	int i;
	for (i = 0; i < repo_size(service->repo); i++)
	{
		Ingredient* curent = vector_at(service->repo->lista_ingrediente, i);
		if (tolower(ingredient_get_nume(curent)[0]) == tolower(litera))
			vector_pushback(lista_ingrediente_litera, curent);
	}
	return lista_ingrediente_litera;
}

Vector* service_getall_cantitate(Service* service, unsigned int cantitate)  {
	if (!service)
	{
		printf("Parametru service null la apelul functiei de getall_cantitate in Service.\n");
		return 0;
	}
	Vector* lista_ingrediente_cantitate = (Vector*)malloc(sizeof(Vector));
	vector_init(lista_ingrediente_cantitate);
	int i;
	for (i = 0; i < repo_size(service->repo); i++)
	{
		Ingredient* curent = vector_at(service->repo->lista_ingrediente, i);
		if (ingredient_get_cantitate(curent) < cantitate)
			vector_pushback(lista_ingrediente_cantitate, curent);
	}
	return lista_ingrediente_cantitate;
}

Vector* service_sort_nume(Service* service, int invers)
{
	if (!service)
	{
		printf("Parametru service null la apelul functiei de getall_cantitate in Service.\n");
		return 0;
	}
	// creez copie shallow a repoului
	Vector* shallow_copy_repo = (Vector*)malloc(sizeof(Vector));
	vector_init(shallow_copy_repo);
	int i;
	for (i = 0; i < repo_size(service->repo); i++)
		vector_pushback(shallow_copy_repo, vector_at(service->repo->lista_ingrediente,i));

	// sortam copia shallow
	vector_sort(shallow_copy_repo, service_sort_nume_util, invers);

	// returnam copia shallow
	return shallow_copy_repo;
}

Vector* service_sort_cantitate(Service* service, int invers)
{
	if (!service)
	{
		printf("Parametru service null la apelul functiei de getall_cantitate in Service.\n");
		return 0;
	}
	// creez copie shallow a repoului
	Vector* shallow_copy_repo = (Vector*)malloc(sizeof(Vector));
	vector_init(shallow_copy_repo);
	int i;
	for (i = 0; i < repo_size(service->repo); i++)
		vector_pushback(shallow_copy_repo, vector_at(service->repo->lista_ingrediente, i));

	// sortam copia shallow
	vector_sort(shallow_copy_repo, service_sort_cantitate_util, invers);

	// returnam copia shallow
	return shallow_copy_repo;
}

int service_sort_nume_util(Ingredient* a, Ingredient* b) {
	if (strcmp(a->nume, b->nume) < 0) return 1;
	else return 0;
}

int service_sort_cantitate_util(Ingredient* a, Ingredient* b) {
	if (a->cantitate < b->cantitate) return 1;
	else return 0;
}