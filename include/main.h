#ifndef MAIN_H
#define MAIN_H

#include <string>
#include "../include/Pacientes.h"  
#include "../include/menuPacientes.h" 

void submenuPacientes(const std::string& fichPacientes,std::vector<Pacientes> listaPacientes); // Necesario declarar el paso del fichero en todos los archivos .cpp que lo emplean

#endif
