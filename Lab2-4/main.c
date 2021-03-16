#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <malloc.h>
#include "Tests.h"
#include "console.h"
#include "service.h"
#include "ingrediente_repo.h"

int main() {
	tests_run();

	Service* service = malloc(sizeof(Service));
	RepoIngrediente* repo = malloc(sizeof(RepoIngrediente));
	service_init(service, repo);

	Console* console = malloc(sizeof(Console));
	console_init(console, service);
	run_console(console);


	console_destroy(console);
	free(console);
	free(service);
	free(repo);

	int a = _CrtDumpMemoryLeaks();
	printf("Memory leaks: %d\n", a);
	return 0;
}