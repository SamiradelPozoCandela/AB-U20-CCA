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


void Medicos::buscarMedico(const std::string & fichMedicos) {
	string tipoBusqueda, linea, input;
	bool encontrado = false;

	// Textos en UTF-8
	codificacionArchivos();
	limpiarPantalla();

	// Abrir archivo
	std::ifstream archivo(fichMedicos);

	// Verificar si el archivo CSV est� abierto
	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo: " << fichMedicos << std::endl;
		return;
	}

	// Seleccionar el tipo de b�squeda: Disponibilidad o Especialidad
	do {
		std::cout << "\n�Desea buscar por Disponibilidad [D] o Especialidad [E]?: ";
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

	// Bucle que recorre l�nea por l�nea del archivo
	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		Medicos medico = Medicos::fromCSV(linea); // Cargar datos del m�dico desde la l�nea

		// Filtrar seg�n la disponibilidad o especialidad
		if ((toupper(input[0]) == 'D' && medico.disponibilidad == tipoBusqueda) ||
			(toupper(input[0]) == 'E' && medico.especialidad == tipoBusqueda)) {
			encontrado = true;
			std::cout << "\n" << medico.toCSV() << "\n"; // Mostrar datos del m�dico
		}
	}

	// Cerrar el archivo
	archivo.close();

	if (!encontrado) {
		std::cout << "\nNo se encontraron m�dicos que coincidan con el criterio de b�squeda.\n";
	}
	else {
		std::cout << "\n";
		pausa();
	}
}


// Funciones comunes M�dicos

Medicos Medicos::formularioDatosMedico(bool editarCampos) {
	Medicos medico;
	std::string input;

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


// Funci�n para devolver una especialidad 
std::string Medicos::tipoEspecialidad() {
	// Textos en UTF-8
	codificacionArchivos();

	Medicos medico;

	int opcion;
	while (true) {
		std::cout << "(Obligatorio) Seleccione una especialidad:\n";
		std::cout << "1. Cardiolog�a\n";
		std::cout << "2. Pediatr�a\n";
		std::cout << "3. Neurolog�a\n";
		std::cout << "4. Ginecolog�a y Obstetricia\n";
		std::cout << "5. Dermatolog�a\n";
		std::cout << "6. Oftalmolog�a\n";
		std::cout << "7. Otorrinolaringolog�a\n";
		std::cout << "8. Traumatolog�a y Ortopedia\n";
		std::cout << "9. Cirug�a General\n";
		std::cout << "10. Oncolog�a\n";
		std::cout << "11. Psiquiatr�a\n";
		std::cout << "12. Urolog�a\n";
		std::cout << "13. Endocrinolog�a y Nutrici�n\n";
		std::cout << "14. Neumolog�a\n";
		std::cout << "15. Nefrolog�a\n";
		std::cout << "Seleccione una opci�n v�lida [1-15]: ";
		std::cin >> opcion;

		switch (opcion) {
		case 1: return "Cardiolog�a";
		case 2: return "Pediatr�a";
		case 3: return "Neurolog�a";
		case 4: return "Ginecolog�a y Obstetricia";
		case 5: return "Dermatolog�a";
		case 6: return "Oftalmolog�a";
		case 7: return "Otorrinolaringolog�a";
		case 8: return "Traumatolog�a y Ortopedia";
		case 9: return "Cirug�a General";
		case 10: return "Oncolog�a";
		case 11: return "Psiquiatr�a";
		case 12: return "Urolog�a";
		case 13: return "Endocrinolog�a y Nutrici�n";
		case 14: return "Neumolog�a";
		case 15: return "Nefrolog�a";
		default:
			std::cout << "\n";
			std::cout << "Opci�n inv�lida, introduzca un n�mero del 1 al 15.\n";
			pausa();
		}
	}

}