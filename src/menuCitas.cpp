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

	Citas citas;

	int opcion;
	while (true) {
		limpiarPantalla();
		std::cout << "\n";
		std::cout << "***********************************************\n";
		std::cout << "             GESTIÓN DE CITAS MÉDICAS\n";
		std::cout << "***********************************************\n";
		std::cout << "\n";
		std::cout << "1. Nueva cita\n";
		std::cout << "2. Modificar o cancelar cita\n";
		std::cout << "3. Listar citas por urgencia o fecha\n";
		std::cout << "0. Volver\n";
		std::cout << "\n";
		std::cout << "Seleccione una opción válida [0-4]: ";
		std::cin >> opcion;

		switch (opcion) {
		case 1:
			citas.nuevaCita(fichCitas);
			salir();
			break;
		case 2:
			citas.editarCancelarCita(fichCitas,listaCitas);
			salir();
			break;
		case 3:
			citas.listarCitas(fichCitas);
			salir();
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