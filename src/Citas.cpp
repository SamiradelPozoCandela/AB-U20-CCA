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
		std::cerr << "Error al abrir el archivo." << fichCitas << std::endl;
		return;
	}

	// Para buscar la cita indicar el dni, fecha y hora
	std::cout << "\nIntroduce el dni, fecha y hora de la cita del paciente";

	std::cout << "n\DNI: ";
	std::getline(std::cin >> std::ws, buscarDNI);
	std::cout << "Fecha (dd/mm/aaaa): ";
	std::getline(std::cin >> std::ws, buscarFecha);
	std::cout << "Hora (hh:mm): ";
	std::getline(std::cin >> std::ws, buscarHora);

	// Buscar en el archivo
	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		// Leer los campos del archivo
		std::getline(ss, dni, ',');    
		std::getline(ss, fecha, ',');   
		std::getline(ss, hora, ',');    

		if (dni == buscarDNI && fecha == buscarFecha && hora == buscarHora) {
			encontrado = true;

			// Cargar la cita actual
			Citas citaModificada = Citas::fromCSV(linea);

			// Mostrar datos actuales
			std::cout << "\nDatos de la cita:\n" << linea << "\n";

			// Preguntar qué desea modificar
			std::cout << "¿Quieres modificar los datos (M) o solo el estado (E)? ";
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
				std::cout << "Opción no válida, no se realizaron cambios." << std::endl;
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
	std::cout << "Citas actualizadas correctamente." << std::endl;
}


void Citas::listarCitas(const std::string& fichCitas) {
	std::string tipoBusqueda, linea, input;
	bool encontrado = false;

	// Textos en UTF-8
	codificacionArchivos();
	limpiarPantalla();

	// Abrir archivo
	std::ifstream archivo(fichCitas);

	// Verificar si el archivo CSV está abierto
	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo: " << fichCitas << std::endl;
		return;
	}

	// Seleccionar el tipo de búsqueda: Fecha o Urgencia
	do {
		std::cout << "\n¿Desea buscar por Fecha [F] o Urgencia [U]?: ";
		std::getline(std::cin >> std::ws, input);
		input = toupper(input[0]);

		if (input == "F") {
			std::cout << "\nIntroduce la fecha (dd/mm/aaaa): ";
			std::getline(std::cin, input);
			tipoBusqueda = input;  // Guardar la fecha para buscarla
			break;
		}
		else if (input == "U") {
			std::cout << "\nIntroduce la urgencia (Alta [A] | Baja [B]): ";
			std::getline(std::cin, input);
			input = toupper(input[0]);
			if (input == "A") {
				tipoBusqueda = "Alta";
				break;
			}
			else if (input == "B") {
				tipoBusqueda = "Baja";
				break;
			}
			else {
				std::cout << "\nPor favor, introduce 'A' para Alta o 'B' para Baja.\n";
			}
		}
		std::cout << "Por favor, introduce 'F' para Fecha o 'U' para Urgencia.\n";
	} while (true);

	// Vector para almacenar las citas que coincidan con el criterio de búsqueda
	std::vector<Citas> citasEncontradas;

	// Bucle que recorre línea por línea del archivo
	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		Citas cita = Citas::fromCSV(linea); // Cargar datos de la cita desde la línea

		// Filtrar según la fecha o urgencia
		if ((toupper(input[0]) == 'F' && cita.fecha == tipoBusqueda) ||
			(toupper(input[0]) == 'U' && cita.urgencia == tipoBusqueda)) {
			encontrado = true;
			citasEncontradas.push_back(cita);  // Guardar la cita encontrada
		}
	}

	// Cerrar el archivo
	archivo.close();

	// Mostrar las citas encontradas
	if (encontrado) {
		std::cout << "\nCitas encontradas:\n";
		for (const auto& cita : citasEncontradas) {
			std::cout << cita.toCSV() << "\n";  // Mostrar cada cita encontrada
		}
	}
	else {
		std::cout << "\nNo se encontraron citas que coincidan con el criterio de búsqueda.\n";
	}

	// Pausa al final
	pausa();
}


void Citas::modificarDatosCita(Citas& cita) {
	// Llamamos al formulario de edición de cita
	Citas nuevosDatos = Citas::formularioDatosCita(true); // Permitir edición de campos

	// Modificamos los campos de la cita con los nuevos datos solo si no están vacíos
	if (!nuevosDatos.paciente.empty()) cita.paciente = nuevosDatos.paciente;
	if (!nuevosDatos.medico.empty()) cita.medico = nuevosDatos.medico;
	if (!nuevosDatos.fecha.empty()) cita.fecha = nuevosDatos.fecha;
	if (!nuevosDatos.hora.empty()) cita.hora = nuevosDatos.hora;
	if (!nuevosDatos.motivo.empty()) cita.motivo = nuevosDatos.motivo;
	if (!nuevosDatos.estado.empty()) cita.estado = nuevosDatos.estado;
	if (!nuevosDatos.urgencia.empty()) cita.urgencia = nuevosDatos.urgencia;
	if (!nuevosDatos.sala.empty()) cita.sala = nuevosDatos.sala;

	std::cout << "Datos de la cita modificados correctamente." << std::endl;
}


void Citas::modificarEstadoCita(Citas& cita) {
	std::string nuevoEstado;
	std::cout << "Introduce el nuevo estado [En espera (E) | Atendido (A) | Cancelada (C)]: ";
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
		std::cout << "Por favor, introduce 'E' para En espera, 'A' para Atendido o 'C' para Cancelar.\n" << std::endl;
	}
	std::cout << "El estado de la cita se ha modificado correctamente" << std::endl;
}

// Funciones comunes Citas

Citas Citas::formularioDatosCita(bool editarCampos) {
	Citas cita;
	std::string input;

	// idCita se genera solo (num aleatorio)
	// Crear el generador y la distribución
	std::random_device rd;        // Fuente de entropía
	std::mt19937 generar(rd());       // Motor de generación
	std::uniform_int_distribution<> distrib(1, 100); // Rango [1, 100]

	// Generar un número
	int numeroAleatorio = distrib(generar);
	cita.idCita = to_string(numeroAleatorio);

	// DNI
	std::cout << "DNI: ";
	if (!editarCampos) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

	// Médico
	std::cout << "Médico (user_id): ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		// Convertir cada carácter a minúscula
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
		
		// Cuando presione "Enter" (input está vacío)
		if (input.empty() && !editarCampos) cita.estado = ""; break;

		// Cuando el input no esté vacío
		if (!input.empty()) {
			// Convertir el primer carácter a mayúscula
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