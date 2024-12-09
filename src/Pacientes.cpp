#include <iostream>

#include <cctype>
#include "../include/Pacientes.h"
#include "../include/funciones_comunes.h"

void Pacientes::agregarPaciente() {
	
	string inputTelefono;
	string inputCp;
	string inputAltaBaja;
	string inputEnfermedadCronica;
	char siNo;

	limpiarPantalla();
	std::cout << "Introduce los datos del nuevo paciente\n\n";

	std::cout << "DNI: ";
	// Para evitar que DNI y Nombre se impriman a la vez, se limpia la entrada de datos
	std::getline(std::cin, dni);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

	std::cout << "Nombre: ";
	std::getline(std::cin,nombre);

	std::cout << "Apellidos: ";
	std::getline(std::cin,apellidos);

	do {
		std::cout << "Teléfono: ";
		std::getline(std::cin, inputTelefono); 
		esNumero(inputTelefono,9);
		telefono = string2int(inputTelefono); // Convertir la string a int 
	}while(true);

	std::cout << "Dirección: ";
	std::getline(std::cin,direccion);

	do {
		std::cout << "CP: ";
		std::getline(std::cin, inputCp);
		esNumero(inputCp, 5);
		cp = string2int(inputCp); // Convertir la string a int 
	} while (true);

	std::cout << "Localidad: ";
	std::getline(std::cin, localidad);

	std::cout << "Nacionalidad: ";
	std::getline(std::cin, nacionalidad);

	do {
		std::cout << "Estado [Alta (A) | Baja (B)]: ";
		std::getline(std::cin, inputAltaBaja);
		altaBaja = toupper(inputAltaBaja[0]); // Por si acaso, solo coger el primer caracter para pasarlo a mayúsculas
		if (altaBaja != "A" && altaBaja != "B") {
			std::cout << "Por favor, introduce 'A' para Alta o 'B' para Baja.\n";
		}
	} while (altaBaja != "A" && altaBaja != "B");
	
	do {
		std::cout << "¿Enfermedad crónica? [S|N]: ";
		std::getline(std::cin, inputEnfermedadCronica);
		char respuesta = toupper(inputEnfermedadCronica[0]); // Por si acaso, solo coger el primer caracter para pasarlo a mayúsculas
		if (respuesta != 'S') {
			enfermedadCronica = true;
			break;
		}
		else if(respuesta != 'N') {
			enfermedadCronica = false;
			break;
		}
		else{
			std::cout << "Por favor, introduce 'S' para Sí o 'N' para No.\n";
		}
	} while (true);
	

	std::cout << "¿Desea conservar los cambios? [S|N]: ";
	std::cin >> siNo;
	siNo = toupper(siNo);

	if (siNo == 'S') {
		std::cout << "Entra" << "\n";
		std::cout << "\n"
				  << dni << "," 
				  << nombre << "," 
				  << apellidos << "," 
				  << telefono << ","
				  << direccion << "," 
				  << cp << "," 
				  << localidad << "," 
				  << nacionalidad << ","
				  << (altaBaja == "A" ? "Alta" : "Baja") << ","
				  << (enfermedadCronica == 1 ? "true" : "false");
		std::cout << "\nEl paciente se ha registrado correctamente.\n";
	}
	else {
		std::cout << "Los cambios no se han guardado.\n";
	}
}

void Pacientes::editarPaciente() {

}

void Pacientes::buscarPaciente() {

}


