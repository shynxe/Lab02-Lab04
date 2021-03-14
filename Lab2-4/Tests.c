#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "Tests.h"
#include "ingredient.h"
#include "ingrediente_repo.h"
#include "service.h"
#include "Vector.h"

void tests_run() {
	test_vector();

	test_ingrediente();

	test_adauga_repo();
	test_sterge_repo();
	test_find_repo();
	test_modifica_repo();

	test_service_add();
	test_service_remove();
	test_service_edit();
}

void test_vector() {
	Vector v;
	vector_init(&v);
	int a = 3;
	int b = 5;
	vector_pushback(&v, a);
	assert(vector_size(&v) == 1);
	vector_pushback(&v, b);
	assert(vector_size(&v) == 2);
	assert(vector_at(&v, 0) == a);
	assert(vector_at(&v, 1) == b);
	vector_remove(&v, 100);
	assert(vector_size(&v) == 2);
	vector_remove(&v, 0);
	assert(vector_size(&v) == 1);
	assert(vector_at(&v, 0) == b);
}

void test_ingrediente() {
	Ingredient ingred_test;
	ingredient_init(&ingred_test, "rumegus", "armand", 20);
	assert(strcmp(ingredient_get_nume(&ingred_test), "rumegus") == 0);
	assert(strcmp(ingredient_get_producator(&ingred_test), "armand") == 0);
	assert(ingredient_get_cantitate(&ingred_test)==20);
	ingredient_inc_quantity(&ingred_test, 1);
	assert(ingredient_get_cantitate(&ingred_test) == 21);
	ingredient_destroy(&ingred_test);
}

void test_find_repo() {
	RepoIngrediente repo;
	repo_init(&repo);
	Ingredient ingred;
	ingredient_init(&ingred, "ingredient test", "producator smecher", 30);
	repo_add_ingredient(&repo, &ingred);
	assert(repo_find_ingredient(&repo, "ingredient test"));
	assert(!repo_find_ingredient(&repo, "asdfads"));
	assert(!repo_find_ingredient(0, "ingredient test"));
}

void test_adauga_repo() {
	RepoIngrediente repo;
	repo_init(&repo);
	Ingredient ingred, ingred2;
	ingredient_init(&ingred, "ingredient test", "producator smecher", 30);
	ingredient_init(&ingred2, "paul", "producator smecher", 41);
	assert(repo_add_ingredient(&repo, &ingred));
	assert(ingredient_get_cantitate(&ingred) == 30);
	assert(repo_add_ingredient(&repo, &ingred)==2);
	assert(ingredient_get_cantitate(&ingred) == 30+30);
	assert(!repo_add_ingredient(0, &ingred));
	assert(!repo_add_ingredient(&repo, 0));
	assert(repo_size(&repo) == 1);
	repo_add_ingredient(&repo, &ingred2);
	assert(repo_size(&repo) == 2);
	repo_destroy(&repo);
}

void test_sterge_repo() {
	RepoIngrediente repo;
	repo_init(&repo);
	Ingredient ingred;
	ingredient_init(&ingred, "ingredient test", "producator smecher", 30);
	repo_add_ingredient(&repo, &ingred);
	assert(repo_size(&repo) == 1);
	assert(repo_remove_ingredient(&repo, "ingredient test"));
	assert(repo_size(&repo) == 0);
	assert(!repo_remove_ingredient(&repo, "ingreasdfasedf"));
	assert(!repo_remove_ingredient(0, "ingreasdfasedf"));
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
	free(repo);
	free(ingred);
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
	int res = service_modifica_ingredient(service, "test", "nou test", "nou prod", 30);
	assert(!service_modifica_ingredient(service->repo, "test_inexistent", "nou test", "nou prod", 30));
	assert(!repo_find_ingredient(service->repo, "test"));
	assert(repo_find_ingredient(service->repo, "nou test"));
	service_destroy(service);
	free(service);
	free(repo);
}