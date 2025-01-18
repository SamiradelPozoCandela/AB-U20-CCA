#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>
#include <fstream>
#include "../include/menuCitas.h"
#include "../include/Citas.h"
#include "../include/funciones_comunes.h"

void submenuCitas(const std::string& fichCitas, std::vector<Citas>& listaCitas) {
	// Textos en UTF-8
	codificacionArchivos();

	int opcion;
	while (true) {
		limpiarPantalla();
		std::cout << "\n";
		std::cout << "***********************************************\n";
		std::cout << "             GESTIÓN DE CITAS MÉDICAS\n";
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
			nuevaCita(const std::string & fichCitas);
			break;
		case 2:
			editarCita(const std::string & fichCitas, std::vector<Citas>&listaCitas);
			break;
		case 3:
			cancelarCita(const std::string & fichCitas, std::vector<Citas>&listaCitas);
			break;
		case 4:
			listarCitas(const std::string & fichCitas);
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