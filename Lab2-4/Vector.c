#include "Vector.h"

void vector_init(Vector* vector)
{
	vector->size = 0;
	vector->elements = malloc(1 * sizeof(void*));
}

void vector_destroy(Vector* vector) {
	vector->size = 0;
	free(vector->elements);
}

void vector_pushback(Vector* vector, void* element) {
	vector->size++;
	vector->elements = realloc(vector->elements, vector->size * sizeof(void*));
	vector->elements[vector->size-1] = element;
}

int vector_size(Vector* vector) {
	return vector->size;
}

void vector_remove(Vector* vector, int poz) {
	if (poz >= vector->size || poz < 0) {
		printf("Se incearca accesarea unei pozitii in afara vectorului la stergerea unui element.\n");
		return;
	}
	int i;
	for (i = poz; i < vector->size; i++)
		vector->elements[i] = vector->elements[i + 1];
	vector->size--;
	vector->elements = realloc(vector->elements, vector->size * sizeof(void*));
}

int vector_swap(Vector* vector, int poz1, int poz2)
{
	if (poz1 >= vector->size || poz1 < 0 || poz2 >= vector->size || poz2 < 0) {
		printf("Se incearca accesarea unei pozitii in afara vectorului la interschimbarea a doua elemente.\n");
		return 0;
	}
	void* aux = vector->elements[poz1];
	vector->elements[poz1] = vector->elements[poz2];
	vector->elements[poz2] = aux;
	return 1;
}

void* vector_at(Vector* vector, int poz) {
	return vector->elements[poz];
}