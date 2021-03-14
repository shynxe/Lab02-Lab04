#ifndef SERVICE_H_
#define SERVICE_H_
#include "ingrediente_repo.h"

typedef struct {
	RepoIngrediente* repo;
} Service;

/*
Constructor service
service - referinta la self
repo - referinta la repo - se initializeaza
return: void;
*/
void service_init(Service* service, RepoIngrediente* repo);

/*
Destructor service - se elibereaza memoria
service - referinta la self
return: void;
*/
void service_destroy(Service* service);

/*
Service de adaugare ingredient la Repository
service - referinta la self
name - numele ingredientului
producator - producatorul ingredientului
cantitate - cantitatea ingredientului (cantitate > 0)
return: 0 - eroare
		1 - daca ingredientul a fost adaugat cu succes
		2 - daca ingredientul exista si a fost incrementata cantitatea
*/
int service_add_ingredient(Service* service, char* name, char* producator, unsigned int cantitate);

/*
Service de stergere ingredient din Repository
service - referinta la self (service != null)
name - numele ingredientului de sters
return: 0 - eroare, repo null sau nu a fost gasit ingredientul
		1 - daca ingredientul a fost sters cu succes
*/
int service_remove_ingredient(Service* service, char* name);

/*
Service de modificare ingredient din Repository
service - referinta la self
name - numele ingredientului de modificat
new_name - numele nou
new_prod - producator nou
new_cantitate - cantitate noua (suprascrisa peste cea veche)
return: 0 - eroare, service null sau nu a fost gasit ingredientul
		1 - daca ingredientul a fost modificat cu succes
*/
int service_modifica_ingredient(Service* service, char* name, char* new_name, char* new_prod, unsigned int new_cantitate);


#endif