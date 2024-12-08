#include <iostream>
#include <string>
#include "../include/funciones_comunes.h"

// Funci�n para convertir strings en int
int string2int(const std::string& input) {
	if (!input.empty()) {
		return std::stoi(input);
	}
	else {
		return 0;
	}
}

// Funci�n limpiar pantalla
#ifdef _WIN32
#include<windows.h>
#endif  

void limpiarPantalla() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

// Funci�n salir
bool deseaSalir() {
	char opcion; // Para que solo acepte un caracter
	do {
		std::cout << "\n";
		std::cout << "�Desea salir? [S|N]: ";
		std::cin >> opcion;
		opcion = toupper(opcion); // Pasar el valor dado a may�scula

		if (opcion == 'S') {
			return true;
		}
		else if (opcion == 'N') {
			return false;
		}
		else {
			std::cout << "Opci�n inv�lida. Por favor, ingrese 'S' o 'N'.\n";
		}
	} while (opcion != 'S' && opcion != 'N');
	return false;
}

void salir() {
	if (deseaSalir()) {
		exit(0);
	}
}

// Funci�n pausa
void pausa() {
	system("pause");
	return;
}
