#include <iostream>
#include <locale.h> //admita caracteres especiales y tildes
#include "../include/menuBackup.h"
#include "../include/funciones_comunes.h"

void submenuBackup() {
	// Textos en UTF-8
	codificacionArchivos();

	int opcion;
	while (true) {
		limpiarPantalla();
		std::cout << "\n";
		std::cout << "***********************************************\n";
		std::cout << "             COPIAS DE SEGURIDAD\n";
		std::cout << "***********************************************\n";
		std::cout << "\n";
		std::cout << "1. Realizar backup\n";
		std::cout << "0. Volver\n";
		std::cout << "\n";
		std::cout << "Seleccione una opción válida [0-1]: ";
		std::cin >> opcion;

		switch (opcion) {
		case 1:
			break;
		case 0:
			return;
		default:
			std::cout << "\n";
			std::cout << "Opción inválida, introduzca un número del 0 al 1.\n";
			pausa();
		}
	}
}