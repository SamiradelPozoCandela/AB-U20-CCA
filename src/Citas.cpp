#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include "../include/Citas.h"
#include "../include/funciones_comunes.h"

void Citas::nuevaCita(const std::string& fichCitas) {
	char siNo;

	// Textos en UTF-8
	codificacionArchivos();
	limpiarPantalla();

	// Formulario nueva cita
	std::cout << "Introduce los datos de la nueva cita:\n\n";
	Citas nuevaCita = formularioDatosCita(false);

	std::cout << "\n¿Desea conservar los cambios? [S|N]: ";
	std::cin >> siNo;
	siNo = toupper(siNo);
	// Limpiar buffer nuevamente
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (siNo == 'S') {
		// Abrir fichero Citas.csv
		std::ofstream archivo(fichCitas, std::ios::app);
		if (archivo.is_open()) {
			archivo << nuevaCita.toCSV() << "\n";
			archivo.close();
			std::cout << "\nEl médico se ha registrado correctamente.\n";
		}
		else {
			std::cerr << "Error: No se ha podido registrar la cita.\n";
		}
	}
	else {
		std::cout << "Los cambios no se han guardado.\n";
	}
}


void Citas::editarCita(const std::string& fichCitas, std::vector<Citas>& listaCitas) {}
void Citas::cancelarCita(const std::string& fichCitas, std::vector<Citas>& listaCitas) {}
void Citas::listarCitas(const std::string& fichCitas) {}

Citas Citas::formularioDatosCita(bool editarCampos) {
	Citas cita;
	std::string input;

	// idCita se genera solo (num aleatorio)
	// Crear el generador y la distribución
	std::random_device rd;        // Fuente de entropía
	std::mt19937 generar(rd());       // Motor de generación (Mersenne Twister)
	std::uniform_int_distribution<> distrib(1, 100); // Rango [1, 100]

	// Generar un número
	int numeroAleatorio = distrib(generar);
	cita.idCita = numeroAleatorio;
             
	// Paciente
	std::cout << "Paciente: ";
	if (!editarCampos) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		cita.paciente = input;
	}

	// Médico
	std::cout << "Médico: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		cita.medico = input;
	}

	// Fecha
	std::cout << "Fecha: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		cita.fecha = input;
	}

	// Hora
	std::cout << "Hora: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		cita.hora = input;
	}

	// Motivo
	std::cout << "Motivo: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		cita.motivo = input;
	}

	// Estado
	do {
		std::cout << "Estado [En blanco para nueva cita (intro) |  En espera (E) | Atendido (A) | Cancelada (C)]: ";
		std::getline(std::cin, input);
		if (input.empty() && editarCampos) break;
		if (!editarCampos || (editarCampos && !input.empty())) {
			input = toupper(input[0]);
			if (input == "E") {
				cita.estado = "En espera"; break;
			} else if (input == "A") {
				cita.estado = "Atendido"; break;
			} else if (input == "C") {
				cita.estado = "Cancelada"; break;
			}
		}
		std::cout << "Por favor, introduce 'E' para En espera, 'A' para Atendido, 'C' para Cancelada e 'intro' si es una cita nueva.\n";
	} while (true);

	// Urgencia
	do {
		std::cout << "Estado [Alta (A) | Baja (B)]: ";
		std::getline(std::cin, input);
		if (input.empty() && editarCampos) break;
		if (!editarCampos || (editarCampos && !input.empty())) {
			input = toupper(input[0]);
			if (input == "A" || input == "B") {
				cita.urgencia = input;
				break;
			}
		}
		std::cout << "Por favor, introduce 'A' para Alta o 'B' para Baja.\n";
	} while (true);

	// Sala
	std::cout << "Motivo: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		cita.sala = input;
	}

	return cita;
}