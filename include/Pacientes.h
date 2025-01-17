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
    string telefono;
    string direccion;
    string cp;
    string localidad;
    string nacionalidad;
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
        std::getline(ss, p.telefono, ',');
        std::getline(ss, p.direccion, ',');
        std::getline(ss, p.cp, ',');
        std::getline(ss, p.localidad, ',');
        std::getline(ss, p.nacionalidad, ',');
        std::getline(ss, p.altaBaja, ',');
        std::getline(ss, token);
        p.enfermedadCronica = (token == "true");

        return p;
    }

    std::string toCSV() const {
        return dni + "," + nombre + "," + apellidos + "," + telefono + "," +
            direccion + "," + cp + "," + localidad + "," + nacionalidad + "," +
            altaBaja + "," + (enfermedadCronica ? "true" : "false");
    }

    void agregarPaciente(const std::string& fichPacientes);
    void editarPaciente(const std::string& fichPacientes,std::vector<Pacientes>& listaPacientes);
    void buscarPaciente(const std::string& fichPacientes);
    static Pacientes formularioDatosPaciente(bool editarCampos);
    std::string buscarDNI(const std::string& fichPacientes, const std::string& dniBuscar);
    
};

#endif
