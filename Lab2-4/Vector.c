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
		printf("Se incearca accesarea unei pozitii in afara vectorului.");
		return;
	}
	int i;
	for (i = poz; i < vector->size; i++)
		vector->elements[i] = vector->elements[i + 1];
	vector->size--;
	vector->elements = realloc(vector->elements, vector->size * sizeof(void*));
}

void* vector_at(Vector* vector, int poz) {
	return vector->elements[poz];
}