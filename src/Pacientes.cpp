#include <iostream>
#include <cctype>
#include <vector>
#include <fstream>
#include "../include/Pacientes.h"
#include "../include/funciones_comunes.h"

void Pacientes::agregarPaciente(const std::string& fichPacientes) {
	char siNo;

	// Textos en UTF-8
	codificacionArchivos();
	limpiarPantalla();

	// Formulario nuevo paciente
	std::cout << "Introduce los datos del nuevo paciente\n\n";
	Pacientes nuevoPaciente = formularioDatosPaciente(false);

	std::cout << "¿Desea conservar los cambios? [S|N]: ";
	std::cin >> siNo;
	siNo = toupper(siNo);
	// Limpiar buffer nuevamente
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

	if (siNo == 'S') {
		// Abrir fichero Pacientes.csv
		std::ofstream archivo(fichPacientes, std::ios::app);
		if (archivo.is_open()) {
			archivo << nuevoPaciente.toCSV() << "\n";
			archivo.close();
			std::cout << "\nEl paciente se ha registrado correctamente.\n";
		}
		else {
			std::cerr << "Error: No se ha podido registrar al paciente.\n";
		}
	}
	else {
		std::cout << "Los cambios no se han guardado.\n";
	}
}


void Pacientes::editarPaciente(const std::string& fichPacientes,std::vector<Pacientes>& listaPacientes) {
	string dniBuscar,linea,dniPaciente,nuevoDNI,nuevoNombre,nuevoApellido,nuevoTelefono,nuevaDireccion,nuevaCP,nuevaAltaBaja,inputAltaBaja,nuevaLocalidad,nuevaNacionalidad;
	bool encontrado = false;
	std::vector<Pacientes> pacientesActualizados;

	// Textos en UTF - 8
	codificacionArchivos();
	limpiarPantalla();

	// Abrir archivo
	std::ifstream archivo(fichPacientes);

	// Verificar que el archivo se abre correctamente
	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo." << fichPacientes  << std::endl;
		return;
	}

	// Solicitar DNI
	std::cout << "\nIntroduce el DNI del paciente a modificar: ";
	std::getline(std::cin >> std::ws, dniBuscar);


	// Buscar DNI en el csv
	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		// Leer solo el DNI
		std::getline(ss, dniPaciente, ','); 

		if (dniPaciente == dniBuscar) {
			encontrado = true;
			// Cargar el paciente actual
			Pacientes pacienteModificado = Pacientes::fromCSV(linea); 

			// Ver los datos del paciente
			std::cout << "\nDatos del paciente:\n" << linea << "\n";

			// Formulario modificar paciente. En todos los elementos se controlan los vacíos
			std::cout << "\nIntroduce nuevos datos (deja vacío para mantener el actual):\n";

			Pacientes nuevosDatos = Pacientes::formularioDatosPaciente(true);

			// Actualizar los campos del paciente con los nuevos datos solo si no están vacíos
			if (!nuevosDatos.dni.empty()) pacienteModificado.dni = nuevosDatos.dni;
			if (!nuevosDatos.nombre.empty()) pacienteModificado.nombre = nuevosDatos.nombre;
			if (!nuevosDatos.apellidos.empty()) pacienteModificado.apellidos = nuevosDatos.apellidos;
			if (!nuevosDatos.telefono.empty()) pacienteModificado.telefono = nuevosDatos.telefono;
			if (!nuevosDatos.direccion.empty()) pacienteModificado.direccion = nuevosDatos.direccion;
			if (!nuevosDatos.cp.empty()) pacienteModificado.cp = nuevosDatos.cp;
			if (!nuevosDatos.localidad.empty()) pacienteModificado.localidad = nuevosDatos.localidad;
			if (!nuevosDatos.nacionalidad.empty()) pacienteModificado.nacionalidad = nuevosDatos.nacionalidad;
			if (!nuevosDatos.altaBaja.empty()) pacienteModificado.altaBaja = nuevosDatos.altaBaja;
			pacienteModificado.enfermedadCronica = nuevosDatos.enfermedadCronica;

			std::cout << "\nModificación guardada para el paciente con DNI: " << dniPaciente << std::endl;
			pacientesActualizados.push_back(pacienteModificado); // Agregar paciente modificado
		}
		else {
			// Agregar el paciente no modificado
			pacientesActualizados.push_back(Pacientes::fromCSV(linea));
		}
	}
	archivo.close();

	if (!encontrado) {
		std::cout << "\nPaciente no encontrado.";
		return;
	}

	// Guardar todos los pacientes de nuevo en el archivo
	std::ofstream archivoSalida(fichPacientes, std::ios::trunc);
	for (const auto& paciente : pacientesActualizados) {
		archivoSalida << paciente.toCSV() << std::endl; // Créalo según tu implementación
	}
	archivoSalida.close();
}


void Pacientes::buscarPaciente(const std::string& fichPacientes) {
	string dniBuscar, linea, dniPaciente;
	bool encontrado = false;

	// Textos en UTF-8
	codificacionArchivos();
	limpiarPantalla();

	// Abrir archivo
	std::ifstream archivo(fichPacientes);

	// Verificar si el archivo csv esta abierto
	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo: " << fichPacientes << std::endl;
		return;
	}

	// Introducir el dni para buscar el paciente
	std::cout << "\nIntroduce el DNI del paciente a buscar: ";
	std::getline(std::cin >> std::ws, dniBuscar);

	// Bucle que recorre linea por linea del archivo
	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		// Leer solo el DNI
		std::getline(ss, dniPaciente, ','); 

		if (dniPaciente == dniBuscar) {
			encontrado = true;
			// Cargar el paciente encontrado
			Pacientes pacienteEncontrado = Pacientes::fromCSV(linea);

			// Mostrar los datos del paciente
			std::cout << "\nDatos del paciente:\n" << linea << "\n";
			break; 
		}
	}

	// Cerrar el archivo
	archivo.close(); 

	if (!encontrado) {
		std::cout << "\nPaciente no encontrado.";
		return;
	}	
}

// Funciones comunes Pacientes

Pacientes Pacientes::formularioDatosPaciente(bool editarCampos) {
	Pacientes paciente;
	string input;

	// DNI
	std::cout << "DNI: ";
	// Para evitar que DNI y Nombre se impriman a la vez, se limpia la entrada de datos
	if (!editarCampos) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		paciente.dni = input;
	}

	// Nombre
	std::cout << "Nombre: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		paciente.nombre = input;
	}

	// Apellidos
	std::cout << "Apellidos: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		paciente.apellidos = input;
	}

	// Teléfono
	do {
		std::cout << "Teléfono (9 dígitos): ";
		std::getline(std::cin, input);
		if (input.empty() && editarCampos) break;
		if (!editarCampos || (editarCampos && !input.empty())) {
			if (esNumero(input, 9)) {
				paciente.telefono = input;
				break;
			}
		}
		std::cout << "Error: número de teléfono inválido. Debe tener 9 dígitos.\n";
	} while (true);

	// Dirección
	std::cout << "Dirección: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		paciente.direccion = input;
	}

	// Código Postal
	do {
		std::cout << "CP (5 dígitos): ";
		std::getline(std::cin, input);
		if (input.empty() && editarCampos) break;
		if (!editarCampos || (editarCampos && !input.empty())) {
			if (esNumero(input, 5)) {
				paciente.cp = input;
				break;
			}
		}
		std::cout << "Error: CP inválido. Debe tener 5 dígitos.\n";
	} while (true);

	// Localidad
	std::cout << "Localidad: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		paciente.localidad = input;
	}

	// Nacionalidad
	std::cout << "Nacionalidad: ";
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		paciente.nacionalidad = input;
	}

	// Alta/Baja
	do {
		std::cout << "Estado [Alta (A) | Baja (B)]: ";
		std::getline(std::cin, input);
		if (input.empty() && editarCampos) break;
		if (!editarCampos || (editarCampos && !input.empty())) {
			input = toupper(input[0]);
			if (input == "A" || input == "B") {
				paciente.altaBaja = input;
				break;
			}
		}
		std::cout << "Por favor, introduce 'A' para Alta o 'B' para Baja.\n";
	} while (true);

	// Enfermedad Crónica
	do {
		std::cout << "¿Enfermedad crónica? [S|N]: ";
		std::getline(std::cin, input);
		if (input.empty() && editarCampos) break;
		if (!editarCampos || (editarCampos && !input.empty())) {
			char respuesta = toupper(input[0]);
			if (respuesta == 'S') {
				paciente.enfermedadCronica = true;
				break;
			}
			else if (respuesta == 'N') {
				paciente.enfermedadCronica = false;
				break;
			}
		}
		std::cout << "Por favor, introduce 'S' para Sí o 'N' para No.\n";
	} while (true);


	return paciente;
}

// En pruebas
std::string Pacientes::buscarDNI(const std::string& fichPacientes, const std::string& dniBuscar) {
	std::ifstream archivo(fichPacientes);
	std::string linea, dniPaciente;

	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo: " << fichPacientes << std::endl;
		// Devolver una línea vacía en caso de error
		return "";
	}

	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		// Leer solo el DNI
		std::getline(ss, dniPaciente, ',');

		if (dniPaciente == dniBuscar) {
			// Cerrar archivo
			archivo.close();
			// Devolver la línea del paciente encontrado
			return linea;
		}
	}

	archivo.close();
	return ""; // Devuelve una línea vacía si no se encuentra el paciente
} // En proceso