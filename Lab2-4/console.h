#ifndef UI_H_
#define UI_H_
#include "service.h"

typedef struct {
	Service* service;
} Console;


void console_init(Console* console, Service* service);
void console_destroy(Console* console);

void run_console(Console* console);
void print_menu();

#endif