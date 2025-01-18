#ifndef MEDICOS_H
#define MEDICOS_H

#include <string>
#include <sstream>
using namespace std;

class Medicos {
private:

    string user_id;
    string nombre;
    string apellidos;
    string categoria;
    string especialidad;
    string altaBaja;
    string disponibilidad;


public:

    static Medicos fromCSV(const std::string& linea) {
        std::stringstream ss(linea);
        Medicos m;
        std::getline(ss, m.user_id, ',');
        std::getline(ss, m.nombre, ',');
        std::getline(ss, m.apellidos, ',');
        std::getline(ss, m.categoria, ',');
        std::getline(ss, m.especialidad, ',');
        std::getline(ss, m.altaBaja, ',');
        std::getline(ss, m.disponibilidad, ',');

        return m;
    }

    std::string toCSV() const {
        return user_id + ',' + nombre + "," + apellidos + "," + categoria + "," +
               especialidad + "," + altaBaja + "," + disponibilidad;
    }

    void agregarMedico(const std::string& fichMedicos);
    void editarMedico(const std::string& fichMedicos, std::vector<Medicos>& listaMedicos);
    static Medicos formularioDatosMedico(bool editarCampos);
};

#endif
