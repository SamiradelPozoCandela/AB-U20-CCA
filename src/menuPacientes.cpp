#include <iostream>
#include <locale.h> //admita caracteres especiales y tildes
#include <vector>
#include <cctype>
#include <sstream>
#include <fstream>
#include "../include/menuPacientes.h"
#include "../include/Pacientes.h"
#include "../include/funciones_comunes.h"


void submenuPacientes(const std::string& fichPacientes, std::vector<Pacientes>& listaPacientes) {
	// Textos en UTF-8
	codificacionArchivos();

	Pacientes pacientes;

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
			pacientes.agregarPaciente(fichPacientes);
			salir();
			break;
		case 2:
			pacientes.editarPaciente(fichPacientes,listaPacientes);
			salir();
			break;
		case 3:
			pacientes.buscarPaciente(listaPacientes);
			salir();
			break;
		case 0:
			return;
		default:
			std::cout << "Opción inválida, introduzca un número del 0 al 3.\n";
		}
	}

}

