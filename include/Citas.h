#ifndef CITAS_H
#define CITAS_H

#include <string>
#include <sstream>
using namespace std;

class Citas {
private:

    string idCita;
    string paciente;
    string medico;
    string fecha;
    string hora;
    string motivo;
    string estado;
    string urgencia;
    string sala;

public:

    static Citas fromCSV(const std::string& linea) {
        std::stringstream ss(linea);
        Citas c;
        std::getline(ss, c.idCita, ',');
        std::getline(ss, c.paciente, ',');
        std::getline(ss, c.medico, ',');
        std::getline(ss, c.fecha, ',');
        std::getline(ss, c.hora, ',');
        std::getline(ss, c.motivo, ',');
        std::getline(ss, c.estado, ',');
        std::getline(ss, c.urgencia, ',');
        std::getline(ss, c.sala, ',');

        return c;
    }

    std::string toCSV() const {
        return idCita + ',' + paciente + "," + medico + "," + fecha + "," +
               hora + "," + motivo + "," + estado + "," + urgencia + "," + sala;
    }

    void nuevaCita(const std::string& fichCitas);
    void editarCancelarCita(const std::string& fichCitas, std::vector<Citas>& listaCitas);
    void listarCitas(const std::string& fichCitas);
    static Citas formularioDatosCita(bool editarCampos);
};

#endif