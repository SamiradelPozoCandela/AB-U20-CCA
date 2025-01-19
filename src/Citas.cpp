#include <iostream>
#include <cctype>
#include <string>
#include <limits>
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

	std::cout << "\n�Desea conservar los cambios? [S|N]: ";
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
			std::cout << "\nLa cita se ha registrado correctamente.\n";
		}
		else {
			std::cerr << "Error: No se ha podido registrar la cita.\n";
		}
	}
	else {
		std::cout << "Los cambios no se han guardado.\n";
	}
}


void Citas::editarCancelarCita(const std::string& fichCitas, std::vector<Citas>& listaCitas) {
	string input, buscarDNI, buscarFecha, buscarHora, linea, dni, fecha, hora;
	char opcion;
	bool encontrado = false;
	std::vector<Citas> citasActualizadas;

	// Textos en UTF - 8
	codificacionArchivos();
	limpiarPantalla();

	// Abrir archivo
	std::ifstream archivo(fichCitas);

	// Verificar que el archivo se abre correctamente
	if (!archivo.is_open()) {
		std::cerr << "\nError al abrir el archivo." << fichCitas << std::endl;
		return;
	}

	// Para buscar la cita indicar el dni, fecha y hora
	std::cout << "\nIntroduce el dni, fecha y hora de la cita del paciente\n\n";

	std::cout << "DNI: ";
	std::getline(std::cin >> std::ws, buscarDNI);
	std::cout << "Fecha (dd/mm/aaaa): ";
	std::getline(std::cin >> std::ws, buscarFecha);
	std::cout << "Hora (hh:mm): ";
	std::getline(std::cin >> std::ws, buscarHora);

	// Buscar en el archivo
	while (std::getline(archivo, linea)) {
		Citas cita = Citas::fromCSV(linea);

		// Limpiar espacios en blanco con trim
		if (trim(cita.dni) == trim(buscarDNI) && trim(cita.fecha) == trim(buscarFecha) && trim(cita.hora) == trim(buscarHora)) {
			encontrado = true;

			// Cargar la cita actual
			Citas citaModificada = Citas::fromCSV(linea);

			// Mostrar datos actuales
			std::cout << "\nDatos de la cita:\n" << linea << "\n";

			// Preguntar qu� desea modificar
			std::cout << "\n�Quieres modificar los datos (M) o solo el estado (E)? ";
			std::cin >> opcion;
			opcion = toupper(opcion);

			if (opcion == 'M') {
				// Modificar datos de la cita
				modificarDatosCita(citaModificada);
			}
			else if (opcion == 'E') {
				// Modificar solo el estado de la cita
				modificarEstadoCita(citaModificada);
			}
			else {
				std::cout << "\nOpci�n no v�lida, no se realizaron cambios." << std::endl;
				return;
			}

			// Agregar la cita modificada
			citasActualizadas.push_back(citaModificada);
		}
		else {
			// Agregar citas no modificadas
			citasActualizadas.push_back(Citas::fromCSV(linea));
		}
	}
	archivo.close();

	if (!encontrado) {
		std::cout << "\nCita no encontrada." << std::endl;
		return;
	}

	// Guardar todas las citas actualizadas de nuevo en el archivo
	std::ofstream archivoSalida(fichCitas, std::ios::trunc);
	for (const auto& cita : citasActualizadas) {
		archivoSalida << cita.toCSV() << std::endl;
	}
	archivoSalida.close();
	std::cout << "\nCitas actualizadas correctamente." << std::endl;
}


void Citas::listarCitas(const std::string& fichCitas) {
	string tipoBusqueda, linea, input, opcion;
	bool encontrado = false;

	// Textos en UTF-8
	codificacionArchivos();
	limpiarPantalla();

	// Abrir archivo
	std::ifstream archivo(fichCitas);

	// Verificar si el archivo CSV est� abierto
	if (!archivo.is_open()) {
		std::cerr << "\nError al abrir el archivo: " << fichCitas << std::endl;
		return;
	}

	// Seleccionar el tipo de b�squeda: Fecha o Urgencia
	do {
		std::cout << "\n�Desea buscar por Fecha [F] o Urgencia [U]?: ";
		std::getline(std::cin >> std::ws, opcion);
		opcion = toupper(opcion[0]);

		if (opcion == "F") {
			std::cout << "\nIntroduce la fecha (dd/mm/aaaa): ";
			std::getline(std::cin, input);
			tipoBusqueda = input;  // Guardar la fecha para buscarla
			break;
		}
		else if (opcion == "U") {
			std::cout << "\nIntroduce la urgencia (Alta [A] | Baja [B]): ";
			std::getline(std::cin, input);
			input = toupper(input[0]);
			if (input == "A" || input == "B") {
				tipoBusqueda = input;
				break;
			}
			else {
				std::cout << "\nPor favor, introduce 'A' para Alta o 'B' para Baja.\n";
			}
		}
		std::cout << "\nPor favor, introduce 'F' para Fecha o 'U' para Urgencia.\n";
	} while (true);

	// Vector para almacenar las citas que coincidan con el criterio de b�squeda
	std::vector<Citas> citasEncontradas;

	// Bucle que recorre l�nea por l�nea del archivo
	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		Citas cita = Citas::fromCSV(linea); // Cargar datos de la cita desde la l�nea

		// Filtrar seg�n la fecha o urgencia
		if ((opcion[0] == 'F' && cita.fecha == tipoBusqueda && cita.estado != "Cancelada") ||
			(opcion[0] == 'U' && cita.urgencia == tipoBusqueda && cita.estado != "Cancelada")) {
			encontrado = true;
			citasEncontradas.push_back(cita);  // Guardar la cita encontrado
		}
	}

	// Cerrar el archivo
	archivo.close();

	// Mostrar las citas encontradas
	if (encontrado) {
		std::cout << "\n\nCitas encontradas:\n";
		for (const auto& cita : citasEncontradas) {
			std::cout << cita.toCSV() << "\n";  // Mostrar cada cita encontrada
		}
	}
	else {
		std::cout << "\nNo se encontraron citas que coincidan con el criterio de b�squeda.\n";
	}

	// Pausa al final
	pausa();
}


void Citas::modificarDatosCita(Citas& cita) {
	// Llamamos al formulario de edici�n de cita
	Citas nuevosDatos = Citas::formularioDatosCita(true);

	// Modificamos los campos de la cita con los nuevos datos solo si no est�n vac�os
	if (!nuevosDatos.paciente.empty()) cita.paciente = nuevosDatos.paciente;
	if (!nuevosDatos.medico.empty()) cita.medico = nuevosDatos.medico;
	if (!nuevosDatos.fecha.empty()) cita.fecha = nuevosDatos.fecha;
	if (!nuevosDatos.hora.empty()) cita.hora = nuevosDatos.hora;
	if (!nuevosDatos.motivo.empty()) cita.motivo = nuevosDatos.motivo;
	if (!nuevosDatos.estado.empty()) cita.estado = nuevosDatos.estado;
	if (!nuevosDatos.urgencia.empty()) cita.urgencia = nuevosDatos.urgencia;
	if (!nuevosDatos.sala.empty()) cita.sala = nuevosDatos.sala;

	std::cout << "\nDatos de la cita modificados correctamente." << std::endl;
}


void Citas::modificarEstadoCita(Citas& cita) {
	std::string nuevoEstado;
	std::cout << "\nIntroduce el nuevo estado [En espera (E) | Atendido (A) | Cancelada (C)]: ";
	std::getline(std::cin >> std::ws, nuevoEstado);
	
	nuevoEstado = toupper(nuevoEstado[0]);
	if (nuevoEstado == "E") {
		cita.estado = "En espera";
	}
	else if (nuevoEstado == "A") {
		cita.estado = "Atendido"; 
	}
	else if (nuevoEstado == "C") {
		cita.estado = "Cancelada";
	} 
	else {
		std::cout << "\nPor favor, introduce 'E' para En espera, 'A' para Atendido o 'C' para Cancelar.\n" << std::endl;
	}
	std::cout << "\nEl estado de la cita se ha modificado correctamente" << std::endl;
}

// Funciones comunes Citas

Citas Citas::formularioDatosCita(bool editarCampos) {
	Citas cita;
	std::string input;

	// idCita se genera solo (num aleatorio)
	// Crear el generador y la distribuci�n
	std::random_device rd;        // Fuente de entrop�a
	std::mt19937 generar(rd());       // Motor de generaci�n
	std::uniform_int_distribution<> distrib(1, 100); // Rango [1, 100]

	// Generar un n�mero
	if (!editarCampos) {
		int numeroAleatorio = distrib(generar);
		cita.idCita = to_string(numeroAleatorio);
	}

	// DNI
	std::cout << "DNI: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		cita.dni = input;
	}
             
	// Paciente
	std::cout << "Paciente: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		cita.paciente = input;
	}

	// M�dico
	std::cout << "M�dico (user_id): ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		// Convertir cada car�cter a min�scula
		for (char& c : input) {
			c = std::tolower(c);
		}
		cita.medico = input;
	}

	// Fecha
	std::cout << "Fecha (dd/mm/aaaa): ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		cita.fecha = input;
	}

	// Hora
	std::cout << "Hora (hh:mm): ";
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
		
		// Cuando presione "Enter" (input est� vac�o)
		if (input.empty() && !editarCampos) {
			cita.estado = ""; break;
		}

		// Cuando el input no est� vac�o
		if (!input.empty()) {
			// Convertir el primer car�cter a may�scula
			char opcion = toupper(input[0]); 
			if (opcion == 'E') {
				cita.estado = "En espera"; break;
			}
			else if (opcion == 'A') {
				cita.estado = "Atendido"; break;
			}
			else if (opcion == 'C') {
				cita.estado = "Cancelada"; break;
			}
		}
		std::cout << "Por favor, introduce 'E' para En espera, 'A' para Atendido, 'C' para Cancelar o presiona 'intro' si es una cita nueva.\n";
	} while (true);

	// Urgencia
	do {
		std::cout << "Urgencia [Alta (A) | Baja (B)]: ";
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
	std::cout << "Sala: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		cita.sala = input;
	}

	return cita;
}

