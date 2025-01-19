#include <iostream>
#include <string>
#include <locale.h> //admita caracteres especiales y tildes
#include "../include/funciones_comunes.h"

#ifdef _WIN32
	#include <windows.h>
#endif

// Función para comprobar que introduce números y no caracteres
// valor (string) --> valor introducido 
// longitudEsperada (int) --> el número de dígitos que debería contener el valor introducido
// Retorna --> True si es Numero y longitud correcta, y False de lo contrario
bool esNumero(const std::string& valor, int longitudEsperada) {
	if (valor.length() != longitudEsperada) {
		return false;  
	}
	for (char caracter : valor) {
		if (!isdigit(caracter)) {
			return false;
		}
	}
	return true;
}


// Función para convertir el valor introducido tipo string en int
// input (string) --> valor introducido 
int string2int(const std::string& input) {
	if (!input.empty()) {
		return std::stoi(input);
	}
	else {
		return 0;
	}
}

// Función limpiar pantalla
void limpiarPantalla() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

// Función salir
bool deseaSalir() {
	char opcion; // Para que solo acepte un carácter
	do {
		std::cout << "\n";
		std::cout << "¿Desea salir? [S|N]: ";
		std::cin >> opcion;
		opcion = toupper(opcion); // Pasar el valor dado a mayúscula

		if (opcion == 'S') {
			return true;
		}
		else if (opcion == 'N') {
			return false;
		}
		else {
			std::cout << "Opción inválida. Por favor, ingrese 'S' o 'N'.\n";
		}
	} while (opcion != 'S' && opcion != 'N');
	return false;
}

void salir() {
	if (deseaSalir()) {
		exit(0);
	}
}

// Función pausa
void pausa() {
	system("pause");
	return;
}

// Función para que admita caracteres especiales y tildes al imprimir por consola.
// Tipo de texto UTF-8
void codificacionArchivos() {
	setlocale(LC_CTYPE, "Spanish");
	#if !defined(_WIN32)
		setlocale(LC_CTYPE, ".UTF-8");
	#endif
}

// Función para quitar los espacios entre una string pasada
std::string trim(const std::string& str) {
	size_t start = str.find_first_not_of(" \t\n\r\f\v");
	size_t end = str.find_last_not_of(" \t\n\r\f\v");
	return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}