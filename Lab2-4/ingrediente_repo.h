#ifndef REPOSITORY_INGREDIENTE_H_
#define REPOSITORY_INGREDIENTE_H_

#include "ingredient.h"
#include "Vector.h"

typedef struct {
	Vector* lista_ingrediente;
} RepoIngrediente;

/*
Functie de constructor a repository-ului
repo - referinta la repository (PRE: repo != null )
return: void
*/
void repo_init(RepoIngrediente* repo);

/*
Functie de desstructor a repository-ului, elibereaza memoria
repo - referinta la repository (PRE: repo != null )
return: void
*/
void repo_destroy(RepoIngrediente* repo);

/*
Functie de obtinere a dimensiunii repositoryului
repo - referinta la repository (PRE: repo != null )
return: int size_t, dimensiunea vectorului (POST: size_t >= 0)
*/
int repo_size(RepoIngrediente* repo);

/*
Functie de adaugare ingredient in repository
repo - referinta la repository ( repo != null )
ingredient - referinta la ingredientul de adaugat ( ingredient != null )
return: 0 - eroare
		1 - daca ingredientul a fost adaugat cu succes
		2 - daca ingredientul exista si a fost incrementata cantitatea
*/
int repo_add_ingredient(RepoIngrediente* repo, Ingredient* ingredient);

/*
Functie de adaugare ingredient in repository
repo - referinta la repository ( repo != null )
name - numele ingredientului de sters
return: 0 - eroare, repo null sau nu a fost gasit ingredientul
		1 - daca ingredientul a fost sters cu succes
*/
int repo_remove_ingredient(RepoIngrediente* repo, char* name);

/*
Functie de modificare ingredient din repository
repo - referinta la repository ( repo != null )
ingredient - referinta la ingredientul de modificat ( ingredient != null )
new_name - noul nume al modificarii
new_prod - noul producator al modificarii
new_cantitate - noua cantitate a modificarii (suprascrisa)
return: void;
*/
void repo_edit_ingredient(RepoIngrediente* repo, Ingredient* ingredient, char* new_name, char* new_prod, unsigned int new_cantitate);


/*
Functie de cautare ingredient in repository
repo - referinta la repository ( repo != null )
name - numele ingredientului cautat
return: 0 - repo null sau nu exista ingredientul cu numele dat in repo
		Ingredient* - referinta la ingredientul cautat
*/
Ingredient* repo_find_ingredient(RepoIngrediente* repo, char* name);

#endif