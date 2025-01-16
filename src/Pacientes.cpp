#include <iostream>
#include <cctype>
#include <vector>
#include <fstream>
#include "../include/Pacientes.h"
#include "../include/funciones_comunes.h"

void Pacientes::agregarPaciente(const std::string& fichPacientes) {
	
	string inputTelefono,inputCp,inputAltaBaja,inputEnfermedadCronica;
	char siNo, respuesta;

	// Textos en UTF-8
	codificacionArchivos();
	limpiarPantalla();

	// Formulario nuevo paciente
	std::cout << "Introduce los datos del nuevo paciente\n\n";

	std::cout << "DNI: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Para evitar que DNI y Nombre se impriman a la vez, se limpia la entrada de datos
	std::getline(std::cin, dni);
	
	std::cout << "Nombre: ";
	std::getline(std::cin,nombre);

	std::cout << "Apellidos: ";
	std::getline(std::cin,apellidos);

	do { // Bucle para controlar que introduce 9 digitos
		std::cout << "Tel�fono: ";
		std::getline(std::cin, inputTelefono); 
		if (esNumero(inputTelefono, 9)) {
			telefono = string2int(inputTelefono); // Convertir la string a int
			break;
		}
		else {
			std::cout << "\nError: n�mero de tel�fono inv�lido. Debe tener 9 d�gitos y solo contener n�meros.\n";
		} 
	}while(true);

	std::cout << "Direcci�n: ";
	std::getline(std::cin,direccion);

	do { // Bucle para controlar que introduce 5 digitos
		std::cout << "CP: ";
		std::getline(std::cin, inputCp);
		if (esNumero(inputCp, 5)){
			cp = string2int(inputCp); // Convertir la string a int
			break;
		}
		else {
			std::cout << "\nError: n�mero de c�digo postal inv�lido. Debe tener 5 d�gitos y solo contener n�meros.\n";
		}
	} while (true);

	std::cout << "Localidad: ";
	std::getline(std::cin, localidad);

	std::cout << "Nacionalidad: ";
	std::getline(std::cin, nacionalidad);

	do { // Bucle para controlar que introduce 1 caracter y que solo es A|a o B|b
		std::cout << "Estado [Alta (A) | Baja (B)]: ";
		std::getline(std::cin, inputAltaBaja);
		altaBaja = toupper(inputAltaBaja[0]); // Por si acaso, solo coger el primer caracter para pasarlo a may�sculas
		if (altaBaja != "A" && altaBaja != "B") {
			std::cout << "Por favor, introduce 'A' para Alta o 'B' para Baja.\n";
		}
	} while (altaBaja != "A" && altaBaja != "B");
	
	do { // Bucle para controlar que introduce 1 car�cter y que solo es S|s o N|n
		std::cout << "�Enfermedad cr�nica? [S|N]: ";
		std::getline(std::cin, inputEnfermedadCronica);
		respuesta = toupper(inputEnfermedadCronica[0]); // Por si acaso, solo coger el primer car�cter para pasarlo a may�sculas
		if (respuesta != 'S') {
			enfermedadCronica = true;
			break;
		}
		else if(respuesta != 'N') {
			enfermedadCronica = false;
			break;
		}
		else{
			std::cout << "Por favor, introduce 'S' para S� o 'N' para No.\n";
		}
	} while (true);
	

	std::cout << "�Desea conservar los cambios? [S|N]: ";
	std::cin >> siNo;
	siNo = toupper(siNo);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer nuevamente

	if (siNo == 'S') {
		// Abrir fichero Pacientes.csv
		std::ofstream archivo(fichPacientes, std::ios::app);
		if (archivo.is_open()) {
			archivo << dni << "," 
					<< nombre << "," 
					<< apellidos << "," 
					<< telefono << ","
					<< direccion << "," 
					<< cp << "," 
					<< localidad << "," 
					<< nacionalidad << ","
					<< (altaBaja == "A" ? "Alta" : "Baja") << ","
					<< (enfermedadCronica == 1 ? "true" : "false") << "\n";
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
	char respuesta;
	bool encontrado = false;
	std::ifstream archivo(fichPacientes);
	std::vector<Pacientes> pacientesActualizados;

	// Textos en UTF-8
	codificacionArchivos();

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
		std::getline(ss, dniPaciente, ','); // Leer solo el DNI

		if (dniPaciente == dniBuscar) {
			encontrado = true;
			Pacientes pacienteModificado = Pacientes::fromCSV(linea); // Cargar el paciente actual

			std::cout << pacienteModificado.telefono;

			// Ver los datos del paciente
			std::cout << "\nDatos del paciente:\n" << linea << "\n";

			// Formulario modificar paciente. En todos los elementos se controlan los vac�os
			std::cout << "\nIntroduce nuevos datos (deja vac�o para mantener el actual):\n";

			std::cout << "DNI: ";
			std::getline(std::cin, nuevoDNI);
			if (!nuevoDNI.empty()) pacienteModificado.dni = nuevoDNI;

			std::cout << "Nombre: ";
			std::getline(std::cin, nuevoNombre);
			if (!nuevoNombre.empty()) pacienteModificado.nombre = nuevoNombre;

			std::cout << "Apellidos: ";
			std::getline(std::cin, nuevoApellido);
			if (!nuevoApellido.empty()) pacienteModificado.apellidos = nuevoApellido;

			do { // Bucle para controlar que introduce 9 digitos
				std::cout << "Tel�fono: ";
				std::getline(std::cin, nuevoTelefono);
				if (!nuevoTelefono.empty()) {
					if (esNumero(nuevoTelefono, 9)) {
						pacienteModificado.telefono = string2int(nuevoTelefono);
						break;
					}
					else {
						std::cout << "\nError: n�mero de tel�fono inv�lido. Debe tener 9 d�gitos y solo contener n�meros.\n";
					}
				}else{
					break;
				}
			} while (true);
			
			std::cout << "Direcci�n: ";
			std::getline(std::cin, nuevaDireccion);
			if (!nuevaDireccion.empty()) pacienteModificado.direccion = nuevaDireccion;

			do { // Bucle para controlar que introduce 5 digitos
				std::cout << "CP: ";
				std::getline(std::cin, nuevaCP);
				if (!nuevaCP.empty()) {
					if (esNumero(nuevaCP, 5)) {
						pacienteModificado.cp = string2int(nuevaCP);
						break;
					}
					else {
						std::cout << "\nError: n�mero de c�digo postal inv�lido. Debe tener 5 d�gitos y solo contener n�meros.\n";
					}
				}
				else {
					break;
				}
			} while (true);

			std::cout << "Localidad: ";
			std::getline(std::cin, nuevaLocalidad);
			if (!nuevaLocalidad.empty()) localidad = nuevaLocalidad;

			std::cout << "Nacionalidad: ";
			std::getline(std::cin, nuevaNacionalidad);
			if (!nuevaNacionalidad.empty()) pacienteModificado.nacionalidad = nuevaNacionalidad;

			do { // Bucle para controlar que introduce 1 caracter y que solo es A|a o B|b
				std::cout << "Estado [Alta (A) | Baja (B)]: ";
				std::getline(std::cin, nuevaAltaBaja);
				if (!inputAltaBaja.empty()) {
					inputAltaBaja = toupper(nuevaAltaBaja[0]); // Por si acaso, solo coger el primer caracter para pasarlo a may�sculas
					if (inputAltaBaja != "A" && inputAltaBaja != "B") {
						std::cout << "Por favor, introduce 'A' para Alta o 'B' para Baja.\n";
					}
					else {
						pacienteModificado.altaBaja = inputAltaBaja;
						break;
					}
				}
				else {
					break;
				}
			} while (inputAltaBaja != "A" && inputAltaBaja != "B");

			do { // Bucle para controlar que introduce 1 car�cter y que solo es S|s o N|n
				std::cout << "�Enfermedad cr�nica? [S|N]: ";
				std::string nuevaEnfermedadCronica;
				std::getline(std::cin, nuevaEnfermedadCronica);
				if (!nuevaEnfermedadCronica.empty()) {
					respuesta = toupper(nuevaEnfermedadCronica[0]); // Por si acaso, solo coger el primer caracter para pasarlo a may�sculas
					if (respuesta != 'S') {
						pacienteModificado.enfermedadCronica = true;
						break;
					}
					else if (respuesta != 'N') {
						break;
					}
					else {
						std::cout << "Por favor, introduce 'S' para S� o 'N' para No.\n";
					}
				}
				else {
					break;
				}
			} while (true);

			std::cout << "\nModificaci�n guardada para el paciente con DNI: " << dniPaciente << std::endl;
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
		archivoSalida << paciente.toCSV() << std::endl; // Cr�alo seg�n tu implementaci�n
	}
	archivoSalida.close();
}


void Pacientes::buscarPaciente(const std::string& fichPacientes) {
	string dniBuscar, linea, dniPaciente;
	bool encontrado = false;

	// Textos en UTF-8
	codificacionArchivos();

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
		std::getline(ss, dniPaciente, ','); // Leer solo el DNI

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
		std::cout << "\nPaciente no encontrado." << std::endl;
	}	
}

// Funciones comunes Pacientes

std::string Pacientes::buscarDNI(const std::string& fichPacientes, const std::string& dniBuscar) {
	std::ifstream archivo(fichPacientes);
	std::string linea, dniPaciente;

	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo: " << fichPacientes << std::endl;
		return ""; // Devuelve una l�nea vac�a en caso de error
	}

	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		std::getline(ss, dniPaciente, ','); // Leer solo el DNI

		if (dniPaciente == dniBuscar) {
			archivo.close();
			return linea; // Devuelve la l�nea del paciente encontrado
		}
	}

	archivo.close();
	return ""; // Devuelve una l�nea vac�a si no se encuentra el paciente
}