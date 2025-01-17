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

	// Declarar la ruta donde se almacenarán los datos csv
	std::string fichPacientes = "../../../csv/Pacientes.csv";
	std::string fichMedicos = "../../../csv/Medicos.csv";
	std::string fichCitas = "../../../csv/Citas.csv";
	std::string fichReportes = "../../../csv/Reportes.csv";
	std::string fichBackup = "../../../csv/Backup.csv";

	// Declarar el vector donde se almacenaran las filas de los datos de los csv
	std::vector<Pacientes> listaPacientes;
	std::vector<Medicos> listaMedicos;
	//std::vector<Citas> listaCitas;
	//std::vector<Reportes> listaReportes;
	//std::vector<Backup> listaBackup;

	int opcion = -1;
	while (opcion != 0) {
		limpiarPantalla();
		std::cout << "\n";
		std::cout << "***********************************************\n";
		std::cout << "       SIMULADOR DE GESTIÓN HOSPITALARIA\n";
		std::cout << "***********************************************\n";
		std::cout << "\n";
		std::cout << "1. Gestión de pacientes\n";
		std::cout << "2. Gestión de médicos\n";
		std::cout << "3. Gestión de citas\n";
		std::cout << "4. Generar reportes\n";
		std::cout << "5. Backup\n";
		std::cout << "0. Salir\n";
		std::cout << "\n";
		std::cout << "Seleccione una opción válida [0-5]: ";
		std::cin >> opcion;

		switch (opcion) {
			case 1: 
				// Necesario compartir el fichero para que pueda ser usado en el resto de .cpp y el vector creado
				submenuPacientes(fichPacientes,listaPacientes); 
				break;
			case 2: 
				submenuMedicos(fichMedicos,listaMedicos);
				break;
			case 3: 
				/*submenuCitas(fichCitas,listaCitas);*/
				break;
			case 4: 
				/*submenuReportes(fichReportes,listaReportes);*/
				break;
			case 5: 
				/*submenuBackup(fichBackup,listaBackup);*/
				break;
			case 0: 
				salir();
				break;
			default: 
				std::cout << "\n";
				std::cout << "Opción inválida, introduzca un número del 0 al 5. "; 
				pausa();
		}
	}
}
