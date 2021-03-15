#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "Tests.h"
#include "ingredient.h"
#include "ingrediente_repo.h"
#include "service.h"
#include "Vector.h"
#include "Utils.h"

void tests_run() {
	test_vector();
	test_vector_sort();

	test_ingrediente();

	test_adauga_repo();
	test_find_repo();
	test_sterge_repo();
	test_modifica_repo();

	test_service_add();
	test_service_remove();
	test_service_edit();
	test_service_getall_litera();
	test_service_getall_cantitate();
	test_service_sort_nume();
	test_service_sort_cantitate();
}

void test_vector() {
	Vector* v = (Vector*)malloc(sizeof(Vector));
	vector_init(v);
	int a = 2;
	int b = 5;
	vector_pushback(v, &a);
	assert(vector_size(v) == 1);
	vector_pushback(v, &b);
	assert(vector_size(v) == 2);
	assert(vector_at(v, 0) == &a);
	assert(vector_at(v, 1) == &b);
	vector_remove(v, 100);
	assert(vector_size(v) == 2);
	vector_remove(v, 0);
	assert(vector_size(v) == 1);
	assert(vector_at(v, 0) == &b);
	vector_pushback(v, &a);
	assert(vector_swap(v, 0, 2) == 0);
	assert(vector_swap(v, 0, 1) == 1);
	assert(vector_at(v, 0) == &a);
	assert(vector_at(v, 1) == &b);
	vector_destroy(v);
	free(v);
}

void test_vector_sort()
{
	/*
	Vector* vector = (Vector*)malloc(sizeof(Vector));;
	vector_init(vector);
	int a = 5;
	int b = 2;
	vector_pushback(vector, &a);
	//vector_sort(vector, compare_int, 0);
	vector_pushback(vector, &b);
	vector_sort(0, compare_int, 0);
	vector_sort(vector, compare_int, 0);
	assert(vector_at(vector, 0) == &b);
	assert(vector_at(vector, 1) == &a);
	vector_sort(vector, compare_int, 1);
	assert(vector_at(vector, 0) == &a);
	assert(vector_at(vector, 1) == &b);
	vector_destroy(vector);
	free(vector);
	*/
}

void test_ingrediente() {
	Ingredient* ingred_test = (Ingredient*)malloc(sizeof(Ingredient));
	ingredient_init(ingred_test, "rumegus", "armand", 20);
	assert(strcmp(ingredient_get_nume(ingred_test), "rumegus") == 0);
	assert(strcmp(ingredient_get_producator(ingred_test), "armand") == 0);
	assert(ingredient_get_cantitate(ingred_test)==20);
	ingredient_inc_quantity(ingred_test, 1);
	assert(ingredient_get_cantitate(ingred_test) == 21);
	ingredient_destroy(ingred_test);
	free(ingred_test);
}

void test_find_repo() {
	RepoIngrediente* repo = (RepoIngrediente*)malloc(sizeof(RepoIngrediente));
	repo_init(repo);
	Ingredient* ingred = (Ingredient*)malloc(sizeof(Ingredient));
	ingredient_init(ingred, "ingredient test", "producator smecher", 30);
	repo_add_ingredient(repo, ingred);
	assert(repo_find_ingredient(repo, "ingredient test"));
	assert(!repo_find_ingredient(repo, "asdfads"));
	assert(!repo_find_ingredient(0, "ingredient test"));
	repo_destroy(repo);
	free(repo);
}

void test_adauga_repo() {
	RepoIngrediente* repo = (RepoIngrediente*)malloc(sizeof(RepoIngrediente));
	repo_init(repo);
	Ingredient* ingred = (Ingredient*)malloc(sizeof(Ingredient));
	Ingredient* ingred_copie = (Ingredient*)malloc(sizeof(Ingredient));
	Ingredient* ingred2 = (Ingredient*)malloc(sizeof(Ingredient));
	ingredient_init(ingred, "ingredient test", "producator smecher", 30);
	ingredient_init(ingred_copie, "ingredient test", "producator smecher", 30);
	ingredient_init(ingred2, "paul", "producator smecher", 41);
	
	assert(repo_add_ingredient(repo, ingred));
	assert(ingredient_get_cantitate(ingred) == 30);
	assert(repo_add_ingredient(repo, ingred_copie)==2);
	assert(ingredient_get_cantitate(ingred) == 30+30);
	assert(!repo_add_ingredient(0, ingred));
	assert(!repo_add_ingredient(repo, 0));
	assert(repo_size(repo) == 1);
	repo_add_ingredient(repo, ingred2);
	assert(repo_size(repo) == 2);

	repo_destroy(repo);
	free(repo);
}

void test_sterge_repo() {
	RepoIngrediente* repo = (RepoIngrediente*)malloc(sizeof(RepoIngrediente));
	repo_init(repo);
	Ingredient* ingred = (Ingredient*)malloc(sizeof(Ingredient));
	ingredient_init(ingred, "ingredient test", "producator smecher", 30);
	repo_add_ingredient(repo, ingred);
	assert(repo_size(repo) == 1);
	assert(repo_remove_ingredient(repo, "ingredient test"));
	assert(repo_size(repo) == 0);
	assert(!repo_remove_ingredient(repo, "ingreasdfasedf"));
	assert(!repo_remove_ingredient(0, "ingreasdfasedf"));
	repo_destroy(repo);
	free(repo);
}

void test_modifica_repo() {
	RepoIngrediente* repo = (RepoIngrediente*)malloc(sizeof(RepoIngrediente));
	Ingredient* ingred = (Ingredient*)malloc(sizeof(Ingredient));
	repo_init(repo);
	ingredient_init(ingred, "ingredient test", "producator smecher", 30);
	repo_add_ingredient(repo, ingred);
	repo_edit_ingredient(repo, ingred, "modif nume", "modif producator", 10);
	repo_edit_ingredient(0, ingred, "modif nume", "modif producator", 10);
	repo_edit_ingredient(repo, 0, "modif nume", "modif producator", 10);
	assert(ingredient_get_cantitate(ingred) == 10);
	assert(strcmp(ingredient_get_nume(ingred), "modif nume") == 0);
	assert(strcmp(ingredient_get_producator(ingred), "modif producator") == 0);
	repo_destroy(repo);
	free(repo);
}

void test_service_add() {
	Service* service = malloc(sizeof(Service));
	RepoIngrediente* repo = malloc(sizeof(RepoIngrediente));
	service_init(service, repo);
	service_add_ingredient(service, "test", "prod", 20);
	assert(repo_size(repo) == 1);
	assert(ingredient_get_cantitate(vector_at(repo->lista_ingrediente, 0)) == 20);
	service_add_ingredient(service, "test", "prod", 24);
	assert(ingredient_get_cantitate(vector_at(repo->lista_ingrediente, 0)) == 44);
	service_destroy(service);
	free(service);
	free(repo);
}

void test_service_remove() {
	Service* service = malloc(sizeof(Service));
	RepoIngrediente* repo = malloc(sizeof(RepoIngrediente));
	service_init(service, repo);
	service_add_ingredient(service, "test", "prod", 20);
	assert(!service_remove_ingredient(0, "test"));
	assert(repo_size(service->repo) == 1);
	service_remove_ingredient(service, "test");
	assert(repo_size(service->repo) == 0);
	service_destroy(service);
	free(service);
	free(repo);
}

void test_service_edit() {
	Service* service = malloc(sizeof(Service));
	RepoIngrediente* repo = malloc(sizeof(RepoIngrediente));
	service_init(service, repo);
	service_add_ingredient(service, "test", "prod", 20);
	int res;
	res = service_modifica_ingredient(service, "test", "nou test", "nou prod", 30);
	assert(!service_modifica_ingredient(service, "test_inexistent", "nou test", "nou prod", 30));
	assert(!service_modifica_ingredient(0, "test", "test", "test", 30));
	assert(!repo_find_ingredient(service->repo, "test"));
	assert(repo_find_ingredient(service->repo, "nou test"));
	service_destroy(service);
	free(service);
	free(repo);
}

void test_service_getall_litera() {
	Service* service = malloc(sizeof(Service));
	RepoIngrediente* repo = malloc(sizeof(RepoIngrediente));
	service_init(service, repo);
	service_add_ingredient(service, "ingred1", "prod", 20);
	service_add_ingredient(service, "ingred2", "prod", 24);
	service_add_ingredient(service, "zagreb3", "prod", 28);

	Vector* lista_ingrediente_litera = service_getall_litera(service, 'i');
	assert(lista_ingrediente_litera);
	assert(!service_getall_litera(0, 'i'));
	assert(vector_size(lista_ingrediente_litera) == 2);
	assert(ingredient_get_cantitate(vector_at(lista_ingrediente_litera, 0)) == 20);
	assert(ingredient_get_cantitate(vector_at(lista_ingrediente_litera, 1)) == 24);

	vector_destroy(lista_ingrediente_litera);
	free(lista_ingrediente_litera);
	service_destroy(service);
	free(service);
	free(repo);
}

void test_service_getall_cantitate() {
	Service* service = malloc(sizeof(Service));
	RepoIngrediente* repo = malloc(sizeof(RepoIngrediente));
	Vector* lista_ingrediente_cantitate;
	service_init(service, repo);
	service_add_ingredient(service, "ingred1", "prod", 20);
	service_add_ingredient(service, "ingred2", "prod", 24);
	service_add_ingredient(service, "zagreb3", "prod", 28);

	
	lista_ingrediente_cantitate = service_getall_cantitate(service, 25);
	assert(lista_ingrediente_cantitate);
	assert(!service_getall_cantitate(0, 25));
	assert(vector_size(lista_ingrediente_cantitate) == 2);
	assert(ingredient_get_cantitate(vector_at(lista_ingrediente_cantitate, 0)) == 20);
	assert(ingredient_get_cantitate(vector_at(lista_ingrediente_cantitate, 1)) == 24);

	vector_destroy(lista_ingrediente_cantitate);
	free(lista_ingrediente_cantitate);
	service_destroy(service);
	free(service);
	free(repo);

}

void test_service_sort_nume() {
	Service* service = malloc(sizeof(Service));
	RepoIngrediente* repo = malloc(sizeof(RepoIngrediente));
	Vector* lista_sortata;
	service_init(service, repo);
	service_add_ingredient(service, "ingred1", "prod", 13);
	lista_sortata = service_sort_nume(service, 1);
	vector_destroy(lista_sortata);
	free(lista_sortata);
	service_add_ingredient(service, "zagreb3", "prod", 5);
	service_add_ingredient(service, "ingred2", "prod", 24);

	assert(!service_sort_nume(0, 1));
	lista_sortata = service_sort_nume(service, 1);
	assert(ingredient_get_cantitate(vector_at(lista_sortata, 0)) == 5);
	assert(ingredient_get_cantitate(vector_at(lista_sortata, 1)) == 24);
	assert(ingredient_get_cantitate(vector_at(lista_sortata, 2)) == 13);


	vector_destroy(lista_sortata);
	free(lista_sortata);
	service_destroy(service);
	free(service);
	free(repo);
}

void test_service_sort_cantitate() {
	Service* service = malloc(sizeof(Service));
	RepoIngrediente* repo = malloc(sizeof(RepoIngrediente));
	service_init(service, repo);
	service_add_ingredient(service, "ingred1", "prod", 13);
	service_add_ingredient(service, "zagreb3", "prod", 5);
	service_add_ingredient(service, "ingred2", "prod", 24);

	Vector* lista_sortata = service_sort_cantitate(service, 0);
	assert(!service_sort_cantitate(0, 0));
	assert(ingredient_get_cantitate(vector_at(lista_sortata, 0)) == 5);
	assert(ingredient_get_cantitate(vector_at(lista_sortata, 1)) == 13);
	assert(ingredient_get_cantitate(vector_at(lista_sortata, 2)) == 24);


	vector_destroy(lista_sortata);
	free(lista_sortata);
	service_destroy(service);
	free(service);
	free(repo);
}