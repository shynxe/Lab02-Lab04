#include "Vector.h"
#include <malloc.h>
#include <stdio.h>


void vector_init(Vector* vector)
{
	vector->size = 0;
	vector->capacity = MAX_CAP;
	vector->elements = malloc(MAX_CAP * sizeof(void*));
}

void vector_destroy(Vector* vector) {
	vector->size = 0;
	vector->capacity = 0;
	free(vector->elements);
}

void vector_pushback(Vector* vector, void* element) {
	vector->size++;
	if (vector->size > vector->capacity) {
		vector->elements = realloc(vector->elements, vector->capacity * sizeof(void*));
	}
	//vector->elements = realloc(vector->elements, vector->size * sizeof(void*));
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

void vector_sort(Vector* vector, int(*compareFunc)(void* a, void* b), int invers)
{
	if (vector_size(vector) < 2)
		return;
	int sortat = 0;
	while (!sortat) {
		sortat = 1;
		int i;
		for (i = 1; i < vector->size; i++)
			if ((!compareFunc(vector->elements[i - 1], vector->elements[i]) && !invers) ||  (compareFunc(vector->elements[i-1], vector->elements[i]) && invers)){
				vector_swap(vector, i - 1, i);
				sortat = 0;
			}
	}
}

void* vector_at(Vector* vector, int poz) {
	return vector->elements[poz];
}