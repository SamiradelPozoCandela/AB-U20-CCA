#ifndef MEDICOS_H
#define MEDICOS_H

#include <string>
#include <sstream>
using namespace std;

class Medicos {
private:

    string nombre;
    string apellidos;
    string categoria;
    string especialidad;
    string altaBaja;

public:

    static Medicos fromCSV(const std::string& linea) {
        std::stringstream ss(linea);
        Medicos m;
        std::getline(ss, m.nombre, ',');
        std::getline(ss, m.apellidos, ',');
        std::getline(ss, m.categoria, ',');
        std::getline(ss, m.especialidad, ',');
        std::getline(ss, m.altaBaja, ',');

        return m;
    }

    std::string toCSV() const {
        return nombre + "," + apellidos + "," + categoria + "," +
               especialidad + "," + altaBaja);
    }

    void agregarMedico(const std::string& fichMedicos);

};

#endif
