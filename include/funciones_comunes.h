#ifndef FUNCIONES_COMUNES_H
#define FUNCIONES_COMUNES_H

// Declarar las funciones que hay en funciones_comunes.cpp
void limpiarPantalla();
void salir();
void pausa();
int string2int(const std::string& input); 
bool esNumero(const std::string& valor, int longitudEsperada);
void codificacionArchivos();
std::string trim(const std::string& str);

#endif
