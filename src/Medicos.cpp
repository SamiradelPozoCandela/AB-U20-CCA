#include <iostream>
#include <cctype>
#include <vector>
#include <fstream>
#include "../include/Medicos.h"
#include "../include/funciones_comunes.h"

void Medicos::agregarMedico(const std::string& fichMedicos) {
	char siNo;

	// Textos en UTF-8
	codificacionArchivos();
	limpiarPantalla();

	// Formulario nuevo m�dico
	std::cout << "Introduce los datos del nuevo m�dico\n\n";
	Medicos nuevoMedico = formularioDatosMedico(false);

	std::cout << "�Desea conservar los cambios? [S|N]: ";
	std::cin >> siNo;
	siNo = toupper(siNo);
	// Limpiar buffer nuevamente
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (siNo == 'S') {
		// Abrir fichero Medicos.csv
		std::ofstream archivo(fichMedicos, std::ios::app);
		if (archivo.is_open()) {
			archivo << nuevoMedico.toCSV() << "\n";
			archivo.close();
			std::cout << "\nEl m�dico se ha registrado correctamente.\n";
		}
		else {
			std::cerr << "Error: No se ha podido registrar al m�dico.\n";
		}
	}
	else {
		std::cout << "Los cambios no se han guardado.\n";
	}
}

// Funciones comunes M�dicos

Medicos Medicos::formularioDatosMedico(bool editarCampos) {
	Medicos medico;
	string input;

	// Nombre
	std::cout << "Nombre: ";
	// Para evitar que Nombre y Apellido se impriman a la vez, se limpia la entrada de datos
	if (!editarCampos) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		medico.nombre = input;
	}

	// Apellidos
	std::cout << "Apellidos: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		medico.apellidos = input;
	}

	// Categor�a
	std::cout << "Categor�a: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		medico.categoria = input;
	}

	// Especialidad
	std::cout << "Especialidad: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		medico.especialidad = input;
	}

	// Alta/Baja
	do {
		std::cout << "Estado [Alta (A) | Baja (B)]: ";
		std::getline(std::cin, input);
		if (input.empty() && editarCampos) break;
		if (!editarCampos || (editarCampos && !input.empty())) {
			input = toupper(input[0]);
			if (input == "A" || input == "B") {
				medico.altaBaja = input;
				break;
			}
		}
		std::cout << "Por favor, introduce 'A' para Alta o 'B' para Baja.\n";
	} while (true);

	return medico;
}
