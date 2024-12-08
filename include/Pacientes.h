#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
using namespace std;

class Pacientes {
private:
    string dni;
    string nombre;
    string apellidos;
    int telefono;
    string direccion;
    int cp;
    string localidad;
    string nacionalidad;
    string estado;
    string altaBaja;
    bool enfermedadCronica;

public:
    void agregarPaciente();
    void editarPaciente();
    void buscarPaciente();
};

#endif
