#ifndef VECTOR_H_
#define VECTOR_H_


typedef struct{
	void** elements;
	int size;
}Vector;

/*
Functie de constructor a unui vector dinamic
Aloca spatiu in memorie
vector- referinta la self ( vector != null )
return: void
*/
void vector_init(Vector* vector);
/*
Functie de constructor a unui vector dinamic
vector- referinta la self ( vector != null )
return: void
*/
void vector_destroy(Vector* vector);

/*
Functie de adaugare ingredient in repository
vector- referinta la self ( vector != null )
element - tip de data generic
return: void;
*/
void vector_pushback(Vector* vector, void* element);
/*
Functie de obtinere a dimensiunii repositoryului
vector - referinta la self ( vector != null )
return: int size_t, dimensiunea vectorului (POST: size_t >= 0)
*/
int vector_size(Vector* vector);

/*
Functie de obtinere a dimensiunii repositoryului
vector - referinta la self ( vector != null )
poz - pozitia accesarii ( poz > 0 && poz < vector->size )
return: int size_t, dimensiunea vectorului (POST: size_t >= 0)
*/
void* vector_at(Vector* vector, int poz);

/*
Functie de obtinere a dimensiunii repositoryului
vector - referinta la self ( vector != null )
poz - pozitia accesarii ( poz > 0 && poz < vector->size )
return: int size_t, dimensiunea vectorului (POST: size_t >= 0)
*/
void vector_remove(Vector* vector, int poz);

#endif
