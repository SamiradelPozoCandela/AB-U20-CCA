#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>
#include <fstream>
#include "../include/menuMedico.h"
#include "../include/Medicos.h"
#include "../include/funciones_comunes.h"


void submenuMedicos(const std::string& fichMedicos, std::vector<Medicos>& listaMedicos) {
	// Textos en UTF-8
	codificacionArchivos();

	Medicos medico;

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
		std::cout << "3. Listar médicos por Disponibilidad [D] o Especialidad [E]\n";
		std::cout << "0. Volver\n";
		std::cout << "\n";
		std::cout << "Seleccione una opción válida [0-3]: ";
		std::cin >> opcion;

		switch (opcion) {
		case 1:
			medico.agregarMedico(fichMedicos);
			salir();
			break;
		case 2:
			medico.editarMedico(fichMedicos, listaMedicos);
			salir();
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