#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include <sstream>
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

    static Pacientes fromCSV(const std::string& linea) {
        std::stringstream ss(linea);
        Pacientes p;
        std::string token;
        std::getline(ss, p.dni, ',');
        std::getline(ss, p.nombre, ',');
        std::getline(ss, p.apellidos, ',');
        std::getline(ss, token, ',');
        p.telefono = std::stoi(token);
        std::getline(ss, p.direccion, ',');
        std::getline(ss, token, ',');
        p.cp = std::stoi(token);
        std::getline(ss, p.localidad, ',');
        std::getline(ss, p.nacionalidad, ',');
        std::getline(ss, p.estado, ',');
        std::getline(ss, token);
        p.enfermedadCronica = (token == "true");

        return p;
    }

    std::string toCSV() const {
        return dni + "," + nombre + "," + apellidos + "," + std::to_string(telefono) + "," +
            direccion + "," + std::to_string(cp) + "," + localidad + "," + nacionalidad + "," +
            estado + "," + (enfermedadCronica ? "true" : "false");
    }

    void agregarPaciente(const std::string& fichPacientes);
    void editarPaciente(const std::string& fichPacientes,std::vector<Pacientes>& listaPacientes);
    void buscarPaciente(std::vector<Pacientes>& listaPacientes);
};

#endif
