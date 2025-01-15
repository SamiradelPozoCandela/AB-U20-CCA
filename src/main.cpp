#include <iostream>
#include <cctype>
#include <vector>
#include <filesystem>
#include "../include/main.h"
#include "../include/menuPacientes.h"
#include "../include/Pacientes.h"
#include "../include/menuMedico.h"
#include "../include/menuCitas.h"
#include "../include/menuReportes.h"
#include "../include/menuBackup.h"
#include "../include/funciones_comunes.h"


int main() {
	// Textos en UTF-8
	codificacionArchivos();

	// Declarar la ruta donde se almacenar�n los datos de los Pacientes
	std::string fichPacientes = "../../../csv/Pacientes.csv";

	// Declarar el vector donde se almacenaran las filas de usuarios
	std::vector<Pacientes> listaPacientes;

	int opcion = -1;
	while (opcion != 0) {
		limpiarPantalla();
		std::cout << "\n";
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
				submenuPacientes(fichPacientes,listaPacientes); // Necesario compartir el fichero para que pueda ser usado en el resto de .cpp
				break;
			case 2: 
				submenuMedicos();
				break;
			case 3: 
				submenuCitas();
				break;
			case 4: 
				submenuReportes();
				break;
			case 5: 
				submenuBackup();
				break;
			case 0: 
				salir();
				break;
			default: 
				std::cout << "\n";
				std::cout << "Opci�n inv�lida, introduzca un n�mero del 0 al 5. "; 
				pausa();
		}
	}
}
