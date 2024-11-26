#include <iostream>
#include <cctype>
#include <locale.h> //admita caracteres especiales y tildes
#include "main.h"
//#include "menuPacientes.h"
//#include "menuMedico.h"
//#include "menuCitas.h"
//#include "menuReportes.h"
//#include "menuBackup.h"

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


int main() {
	setlocale(LC_CTYPE, "Spanish");
	int opcion = 0;
	while (opcion != 5) {
		clear
		std::cout << "***********************************************\n";
		std::cout << "       SIMULADOR DE GESTI�N HOSPITALARIA\n";
		std::cout << "***********************************************\n";
		std::cout << "\n";
		std::cout << "1. Gesti�n de pacientes\n";
		std::cout << "2. Gesti�n de m�dicos\n";
		std::cout << "3. Gesti�n de citas\n";
		std::cout << "4. Generar reportes\n";
		std::cout << "5. Backup\n";
		std::cout << "0. Salir\n";
		std::cout << "\n";
		std::cout << "Seleccione una opci�n v�lida [0-5]: ";
		std::cin >> opcion;

		switch (opcion) {
			case 1: 
				std::cout << ""; 
				break;
			case 2: 
				std::cout << ""; 
				break;
			case 3: 
				std::cout << ""; 
				break;
			case 4: 
				std::cout << ""; 
				break;
			case 5: 
				std::cout << ""; 
				break;
			case 0: 
				salir();
				break;
		default: std::cout << "Opci�n invalida, introduzca un n�mero del 0 al 5.\n";
		}
	}
}

//case 1: submenuPacientes(); salir(); break;
//case 2: submenuMedicos(); salir(); break;
//case 3: submenuCitas(); salir(); break;
//case 4: submenuReportes(); salir(); break;
//case 5: submenuBackup(); salir(); break;