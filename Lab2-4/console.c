#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"

void print_menu() {
	printf("Menu: \n");
	printf("1. Adauga ingredient\n");
	printf("2. Sterge ingredient\n");
	printf("3. Modifica ingredient\n");
	printf("4. Vizualizare materii prime care satisfac un criteriu\n");
	printf("5. Vizualizare materii prime din stoc ordonat dupa un criteriu\n");
	printf("0. Exit\n");
	printf("Introduceti comanda: ");
}

void console_init(Console* console, Service* service) {
	console->service = service;
}

void console_destroy(Console* console) {
	service_destroy(console->service);
}

void run_console(Console* console) {
	int input = -1;
	while (input != 0) {
		print_menu();
		scanf("%d", &input);
		switch (input) {
		case 1:
		{
			// 1. Adauga ingredient
			char name[20];
			char producator[20];
			int cantitate;
			printf("Introduceti numele ingredientului: ");
			scanf("%s", &name);
			printf("Introduceti numele producatorului: ");
			scanf("%s", &producator);
			printf("Introduceti cantitatea dorita: ");
			scanf("%d", &cantitate);
			if (cantitate < 0) {
				printf("Eroare: Cantitatea trebuie sa fie un numar pozitiv!\n");
				break;
			}
			int rezultat = service_add_ingredient(console->service, name, producator, (unsigned int)cantitate);
			if (rezultat == 0) {
				printf("Nu s-a realizat nicio modificare.\n");
			} else if (rezultat == 1) {
				printf("Ingredientul nou a fost adaugat cu succes!\n");
			}
			else if (rezultat == 2) {
				Ingredient* cautat = repo_find_ingredient(console->service->repo, name);
				printf("Ingredient existent - se adauga la cantitatea veche.\nCantitatea noua a ingredientului %s este: %u\n", ingredient_get_nume(cautat), ingredient_get_cantitate(cautat));
			}
			break;
		}
		case 2:
		{
			// 2. Sterge ingredient
			char name[20];
			printf("Introduceti numele: ");
			scanf("%s", &name);
			int rezultat_stergere = service_remove_ingredient(console->service, name);
			if (rezultat_stergere == 0)
				printf("Nu s-a realizat nicio steregere.\n");
			else if (rezultat_stergere == 1)
				printf("Ingredientul %s a fost sters cu succes!\n", name);
			break;
		}
		case 3:
		{
			char name[20], new_name[20], new_prod[20];
			int new_cantitate;
			printf("Introduceti numele: ");
			scanf("%s", &name);
			printf("Introduceti noul nume: ");
			scanf("%s", &new_name);
			printf("Introduceti noul producator: ");
			scanf("%s", &new_prod);
			printf("Introduceti noua cantitate: ");
			scanf("%d", &new_cantitate);
			if (new_cantitate < 0) {
				printf("Eroare: Cantitatea trebuie sa fie un numar pozitiv!\n");
				break;
			}
			int rezultat_modificare = service_modifica_ingredient(console->service, name, new_name, new_prod, (unsigned int)new_cantitate);
			if (rezultat_modificare == 0)
				printf("Nu s-a realizat nicio modificare.\n");
			else if (rezultat_modificare == 1)
				printf("Modificarea a fost realizata cu succes!\n");
			break;
		}
		case 4:
		{
			int suboptiune;
			printf("-----\n1.Nume incepe cu o anumita litera data\n2.Cantitate disponibila este mai mica decat un numar dat\n: ");
			scanf("%d", &suboptiune);
			switch (suboptiune) {
			case 1:
			{
				char litera;
				printf("Introduceti litera: ");
				scanf(" %c", &litera);
				Vector* lista_rezultat = service_getall_litera(console->service, litera);
				int iterator;
				for (iterator = 0; iterator < vector_size(lista_rezultat); iterator++)
					printf("%s, %s, %u\n", ingredient_get_nume(vector_at(lista_rezultat, iterator)), ingredient_get_producator(vector_at(lista_rezultat, iterator)), ingredient_get_cantitate(vector_at(lista_rezultat, iterator)));
				vector_destroy(lista_rezultat);
				free(lista_rezultat);
				break;
			}
			case 2:
			{
				int cantitate;
				printf("Introduceti cantitatea: ");
				scanf("%d", &cantitate);
				if (cantitate < 0) {
					printf("Eroare: Cantitatea trebuie sa fie un numar pozitiv!\n");
					break;
				}
				Vector* lista_rezultat = service_getall_cantitate(console->service, (unsigned int)cantitate);
				int iterator;
				for (iterator = 0; iterator < vector_size(lista_rezultat); iterator++)
					printf("%s, %s, %u\n", ingredient_get_nume(vector_at(lista_rezultat, iterator)), ingredient_get_producator(vector_at(lista_rezultat, iterator)), ingredient_get_cantitate(vector_at(lista_rezultat, iterator)));
				vector_destroy(lista_rezultat);
				free(lista_rezultat);
				break;
			}
			default:
				printf("Nu exista criteriul!\n");
			}
			break;
		}
		case 42:
		{
			int i;
			printf("\n42. DEBUGGING: ");
			if (repo_size(console->service->repo) == 0)
				printf("Repository gol.");
			for (i = 0; i < repo_size(console->service->repo); i++)
			{
				Ingredient* curent_iterat = vector_at(console->service->repo->lista_ingrediente, i);
				printf("\n%s, %s, %u", ingredient_get_nume(curent_iterat), ingredient_get_producator(curent_iterat), ingredient_get_cantitate(curent_iterat));
			}
			printf("\n");
			break;
		}
		default:
			printf("Nu exista comanda!\n");
		}
		printf("\n");
	}
	printf("Program terminat.\n");
}
