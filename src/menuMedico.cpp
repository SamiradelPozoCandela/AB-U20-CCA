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
		std::cout << "             GESTI�N DE M�DICOS\n";
		std::cout << "***********************************************\n";
		std::cout << "\n";
		std::cout << "1. Agregar m�dico\n";
		std::cout << "2. Modificar m�dico\n";
		std::cout << "3. Listar m�dicos\n";
		std::cout << "0. Volver\n";
		std::cout << "\n";
		std::cout << "Seleccione una opci�n v�lida [0-3]: ";
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
			std::cout << "Opci�n inv�lida, introduzca un n�mero del 0 al 3.\n";
			pausa();
		}
	}

}