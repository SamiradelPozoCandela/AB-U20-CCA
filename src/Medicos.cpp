#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include "../include/Medicos.h"
#include "../include/funciones_comunes.h"

void Medicos::agregarMedico(const std::string& fichMedicos) {
	char siNo;

	// Textos en UTF-8
	codificacionArchivos();
	limpiarPantalla();

	// Formulario nuevo médico
	std::cout << "Introduce los datos del nuevo médico\n\n";
	Medicos nuevoMedico = formularioDatosMedico(false);

	std::cout << "\n¿Desea conservar los cambios? [S|N]: ";
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
			std::cout << "\nEl médico se ha registrado correctamente.\n";
		}
		else {
			std::cerr << "Error: No se ha podido registrar al médico.\n";
		}
	}
	else {
		std::cout << "Los cambios no se han guardado.\n";
	}
}


void Medicos::editarMedico(const std::string& fichMedicos, std::vector<Medicos>& listaMedicos) {
	string bucarUser, linea, user_id;
	bool encontrado = false;
	std::vector<Medicos> medicoActualizado;

	// Textos en UTF - 8
	codificacionArchivos();
	limpiarPantalla();

	// Abrir archivo
	std::ifstream archivo(fichMedicos);

	// Verificar que el archivo se abre correctamente
	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo." << fichMedicos << std::endl;
		return;
	}

	// Solicitar user_id
	std::cout << "\nIntroduce el user_id del médico a modificar: ";
	std::getline(std::cin >> std::ws, bucarUser);


	// Buscar user_id en el csv
	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		// Leer solo el user_id
		std::getline(ss, user_id, ',');

		if (user_id == bucarUser) {
			encontrado = true;
			// Cargar el médico actual
			Medicos medicoModificado = Medicos::fromCSV(linea);

			// Ver los datos del user_id
			std::cout << "\nDatos del médico:\n" << linea << "\n";

			// Formulario modificar user_id. En todos los elementos se controlan los vacíos
			std::cout << "\nIntroduce los nuevos datos (deja vacío para mantener el actual):\n\n";

			Medicos nuevosDatos = Medicos::formularioDatosMedico(true);

			// Actualizar los campos del paciente con los nuevos datos solo si no están vacíos
			if (!nuevosDatos.user_id.empty()) medicoModificado.user_id = nuevosDatos.user_id;
			if (!nuevosDatos.nombre.empty()) medicoModificado.nombre = nuevosDatos.nombre;
			if (!nuevosDatos.apellidos.empty()) medicoModificado.apellidos = nuevosDatos.apellidos;
			if (!nuevosDatos.categoria.empty()) medicoModificado.categoria = nuevosDatos.categoria;
			if (!nuevosDatos.especialidad.empty()) medicoModificado.especialidad = nuevosDatos.especialidad;
			if (!nuevosDatos.altaBaja.empty()) medicoModificado.altaBaja = nuevosDatos.altaBaja;
			if (!nuevosDatos.disponibilidad.empty()) medicoModificado.disponibilidad = nuevosDatos.disponibilidad;

			std::cout << "\nModificación guardada para el médico con user_id: " << user_id << std::endl;
			// Agregar médico modificado
			medicoActualizado.push_back(medicoModificado); 
		}
		else {
			// Agregar el médico no modificado
			medicoActualizado.push_back(Medicos::fromCSV(linea));
		}
	}
	archivo.close();

	if (!encontrado) {
		std::cout << "\nPaciente no encontrado.";
		return;
	}

	// Guardar todos los médicos de nuevo en el archivo
	std::ofstream archivoSalida(fichMedicos, std::ios::trunc);
	for (const auto& medico : medicoActualizado) {
		archivoSalida << medico.toCSV() << std::endl; 
	}
	archivoSalida.close();
}


void Medicos::buscarMedico(const std::string & fichMedicos) {
	string tipoBusqueda, linea, input;
	bool encontrado = false;

	// Textos en UTF-8
	codificacionArchivos();
	limpiarPantalla();

	// Abrir archivo
	std::ifstream archivo(fichMedicos);

	// Verificar si el archivo CSV está abierto
	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo: " << fichMedicos << std::endl;
		return;
	}

	// Seleccionar el tipo de búsqueda: Disponibilidad o Especialidad
	do {
		std::cout << "\n¿Desea buscar por Disponibilidad [D] o Especialidad [E]?: ";
		std::getline(std::cin >> std::ws, input);
		input = toupper(input[0]);

		if (input == "D") {
			std::cout << "\nIntroduce la disponibilidad (Disponible [D] | No disponible [N]): ";
			std::getline(std::cin, input);
			input = toupper(input[0]);
			if (input == "D") {
				tipoBusqueda = "Disponible";
				break;
			} else if (input == "N") {
				tipoBusqueda = "No disponible";
				break;
			} else {
				std::cout << "\nPor favor, introduce 'D' para Disponible o 'N' para No disponible.\n";
			}
		}
		else if (input == "E") {
			// Seleccione el tipo de especialidad
			tipoBusqueda = tipoEspecialidad();
			break;
		}
		std::cout << "Por favor, introduce 'D' para Disponibilidad o 'E' para Especialidad.\n";
	} while (true);

	// Bucle que recorre línea por línea del archivo
	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		Medicos medico = Medicos::fromCSV(linea); // Cargar datos del médico desde la línea

		// Filtrar según la disponibilidad o especialidad
		if ((toupper(input[0]) == 'D' && medico.disponibilidad == tipoBusqueda) ||
			(toupper(input[0]) == 'E' && medico.especialidad == tipoBusqueda)) {
			encontrado = true;
			std::cout << "\n" << medico.toCSV() << "\n"; // Mostrar datos del médico
		}
	}

	// Cerrar el archivo
	archivo.close();

	if (!encontrado) {
		std::cout << "\nNo se encontraron médicos que coincidan con el criterio de búsqueda.\n";
	}
	else {
		std::cout << "\n";
		pausa();
	}
}


// Funciones comunes Médicos

Medicos Medicos::formularioDatosMedico(bool editarCampos) {
	Medicos medico;
	std::string input;

	// USER_ID
	std::cout << "USER_ID (inical del nombre + primer apellido. Ej: Manolo Gafotas = mgafotas): ";
	// Para evitar que USER_ID y Nombre se impriman a la vez, se limpia la entrada de datos
	if (!editarCampos) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		// Convertir cada carácter a minúscula
		for (char& c : input) {
			c = std::tolower(c);
		}
		medico.user_id = input;
	}

	// Nombre
	std::cout << "Nombre: ";
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

	// Categoría
	std::cout << "Categoría: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		medico.categoria = input;
	}

	// Especialidad
	medico.especialidad = medico.tipoEspecialidad();

	// Alta/Baja
	if (!editarCampos) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

	// Disponibilidad
	if (!editarCampos) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	do {
		std::cout << "¿Disponible? [S|N]: ";
		std::getline(std::cin, input);
		if (input.empty() && editarCampos) break;
		if (!editarCampos || (editarCampos && !input.empty())) {
			char respuesta = toupper(input[0]);
			if (respuesta == 'S') {
				medico.disponibilidad = "Disponible";
				break;
			}
			else if (respuesta == 'N') {
				medico.disponibilidad = "No disponible";
				break;
			}
		}
		std::cout << "Por favor, introduce 'S' para Sí o 'N' para No.\n";
	} while (true);

	return medico;
}


// Función para devolver una especialidad 
std::string Medicos::tipoEspecialidad() {
	// Textos en UTF-8
	codificacionArchivos();

	Medicos medico;

	int opcion;
	while (true) {
		std::cout << "(Obligatorio) Seleccione una especialidad:\n";
		std::cout << "1. Cardiología\n";
		std::cout << "2. Pediatría\n";
		std::cout << "3. Neurología\n";
		std::cout << "4. Ginecología y Obstetricia\n";
		std::cout << "5. Dermatología\n";
		std::cout << "6. Oftalmología\n";
		std::cout << "7. Otorrinolaringología\n";
		std::cout << "8. Traumatología y Ortopedia\n";
		std::cout << "9. Cirugía General\n";
		std::cout << "10. Oncología\n";
		std::cout << "11. Psiquiatría\n";
		std::cout << "12. Urología\n";
		std::cout << "13. Endocrinología y Nutrición\n";
		std::cout << "14. Neumología\n";
		std::cout << "15. Nefrología\n";
		std::cout << "Seleccione una opción válida [1-15]: ";
		std::cin >> opcion;

		switch (opcion) {
		case 1: return "Cardiología";
		case 2: return "Pediatría";
		case 3: return "Neurología";
		case 4: return "Ginecología y Obstetricia";
		case 5: return "Dermatología";
		case 6: return "Oftalmología";
		case 7: return "Otorrinolaringología";
		case 8: return "Traumatología y Ortopedia";
		case 9: return "Cirugía General";
		case 10: return "Oncología";
		case 11: return "Psiquiatría";
		case 12: return "Urología";
		case 13: return "Endocrinología y Nutrición";
		case 14: return "Neumología";
		case 15: return "Nefrología";
		default:
			std::cout << "\n";
			std::cout << "Opción inválida, introduzca un número del 1 al 15.\n";
			pausa();
		}
	}

}