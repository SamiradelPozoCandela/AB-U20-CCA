#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>
#include "../include/Pacientes.h"  
#include "../include/menuPacientes.h" 
#include "../include/Medicos.h"  
#include "../include/menuMedico.h" 
#include "../include/Citas.h"  
#include "../include/menuCitas.h" 
//#include "../include/Reportes.h"  
//#include "../include/menuReportes.h" 
//#include "../include/Backup.h"  
//#include "../include/menuBackup.h" 

void submenuPacientes(const std::string& fichPacientes,std::vector<Pacientes>& listaPacientes); 
void submenuMedicos(const std::string& fichMedicos, std::vector<Medicos>& listaMedicos);
void submenuCitas(const std::string& fichCitas, std::vector<Citas>& listaCitas);
//void submenuReportes(const std::string& fichReportes, std::vector<Reportes>& listaReportes);
//void submenuBackup(const std::string& fichBackup, std::vector<Backup>& listaBackup);

#endif
