#include <iostream>
#include <locale.h> //admita caracteres especiales y tildes
#include "../include/menuMedico.h"
#include "../include/funciones_comunes.h"

void submenuMedicos() {
	setlocale(LC_CTYPE, "Spanish");
	int opcion;
	while (true) {
		limpiarPantalla();
		std::cout << "\n";
		std::cout << "***********************************************\n";
		std::cout << "             GESTIÓN DE MÉDICOS\n";
		std::cout << "***********************************************\n";
		std::cout << "\n";
		std::cout << "1. Agregar médico\n";
		std::cout << "2. Modificar médico\n";
		std::cout << "3. Listar médicos\n";
		std::cout << "0. Volver\n";
		std::cout << "\n";
		std::cout << "Seleccione una opción válida [0-3]: ";
		std::cin >> opcion;

		switch (opcion) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 0:
			return;
		default:
			std::cout << "\n";
			std::cout << "Opción inválida, introduzca un número del 0 al 3.\n";
			pausa();
		}
	}

}