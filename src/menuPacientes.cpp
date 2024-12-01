#include <iostream>
#include <locale.h> //admita caracteres especiales y tildes
#include "../include/menuPacientes.h"
#include "../include/limpiarPantalla.h"

void submenuPacientes() {
	setlocale(LC_CTYPE, "Spanish");
	int opcion;
	while (true) {
		limpiarPantalla();
		std::cout << "\n";
		std::cout << "***********************************************\n";
		std::cout << "             GESTIÓN DE PACIENTES\n";
		std::cout << "***********************************************\n";
		std::cout << "\n";
		std::cout << "1. Agregar paciente\n";
		std::cout << "2. Modificar paciente\n";
		std::cout << "3. Buscar paciente\n";
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
			std::cout << "Opción inválida, introduzca un número del 0 al 3.\n";
		}
	}

}
