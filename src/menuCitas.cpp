#include <iostream>
#include <locale.h> //admita caracteres especiales y tildes
#include "../include/menuCitas.h"
#include "../include/funciones_comunes.h"

void submenuCitas() {
	setlocale(LC_CTYPE, "Spanish");
	int opcion;
	while (true) {
		limpiarPantalla();
		std::cout << "\n";
		std::cout << "***********************************************\n";
		std::cout << "             GESTIÓN DE CITAS\n";
		std::cout << "***********************************************\n";
		std::cout << "\n";
		std::cout << "1. Nueva cita\n";
		std::cout << "2. Modificar cita\n";
		std::cout << "3. Cancelar cita\n";
		std::cout << "4. Listar citas\n";
		std::cout << "0. Volver\n";
		std::cout << "\n";
		std::cout << "Seleccione una opción válida [0-4]: ";
		std::cin >> opcion;

		switch (opcion) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 0:
			return;
		default:
			std::cout << "\n";
			std::cout << "Opción inválida, introduzca un número del 0 al 4.\n";
			pausa();
			
		}
	}
}
