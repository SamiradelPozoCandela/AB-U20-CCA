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

	std::cout << "\n�Desea conservar los cambios? [S|N]: ";
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
	std::cout << "\nIntroduce el user_id del m�dico a modificar: ";
	std::getline(std::cin >> std::ws, bucarUser);


	// Buscar user_id en el csv
	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		// Leer solo el user_id
		std::getline(ss, user_id, ',');

		if (user_id == bucarUser) {
			encontrado = true;
			// Cargar el m�dico actual
			Medicos medicoModificado = Medicos::fromCSV(linea);

			// Ver los datos del user_id
			std::cout << "\nDatos del m�dico:\n" << linea << "\n";

			// Formulario modificar user_id. En todos los elementos se controlan los vac�os
			std::cout << "\nIntroduce los nuevos datos (deja vac�o para mantener el actual):\n\n";

			Medicos nuevosDatos = Medicos::formularioDatosMedico(true);

			// Actualizar los campos del paciente con los nuevos datos solo si no est�n vac�os
			if (!nuevosDatos.user_id.empty()) medicoModificado.user_id = nuevosDatos.user_id;
			if (!nuevosDatos.nombre.empty()) medicoModificado.nombre = nuevosDatos.nombre;
			if (!nuevosDatos.apellidos.empty()) medicoModificado.apellidos = nuevosDatos.apellidos;
			if (!nuevosDatos.categoria.empty()) medicoModificado.categoria = nuevosDatos.categoria;
			if (!nuevosDatos.especialidad.empty()) medicoModificado.especialidad = nuevosDatos.especialidad;
			if (!nuevosDatos.altaBaja.empty()) medicoModificado.altaBaja = nuevosDatos.altaBaja;
			if (!nuevosDatos.disponibilidad.empty()) medicoModificado.disponibilidad = nuevosDatos.disponibilidad;

			std::cout << "\nModificaci�n guardada para el m�dico con user_id: " << user_id << std::endl;
			// Agregar m�dico modificado
			medicoActualizado.push_back(medicoModificado); 
		}
		else {
			// Agregar el m�dico no modificado
			medicoActualizado.push_back(Medicos::fromCSV(linea));
		}
	}
	archivo.close();

	if (!encontrado) {
		std::cout << "\nPaciente no encontrado.";
		return;
	}

	// Guardar todos los m�dicos de nuevo en el archivo
	std::ofstream archivoSalida(fichMedicos, std::ios::trunc);
	for (const auto& medico : medicoActualizado) {
		archivoSalida << medico.toCSV() << std::endl; 
	}
	archivoSalida.close();
}



// Funciones comunes M�dicos

Medicos Medicos::formularioDatosMedico(bool editarCampos) {
	Medicos medico;
	string input;

	// USER_ID
	std::cout << "USER_ID (inical del nombre + primer apellido. Ej: Manolo Gafotas = mgafotas): ";
	// Para evitar que USER_ID y Nombre se impriman a la vez, se limpia la entrada de datos
	if (!editarCampos) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, input);
	if (!editarCampos || (editarCampos && !input.empty())) {
		// Convertir cada car�cter a min�scula
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

	// Disponibilidad
	do {
		std::cout << "�Disponible? [S|N]: ";
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
		std::cout << "Por favor, introduce 'S' para S� o 'N' para No.\n";
	} while (true);

	return medico;
}
