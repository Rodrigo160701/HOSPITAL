#ifndef CITA_H
#define CITA_H

#include <string>

class Cita {
public:
    static void inicializarArchivo();
    static void asignar();
    static void buscar();
    static void modificar(const std::string& citaId);
    static void reportePorFecha(const std::string& fechaInicio, const std::string& fechaFin);
    static void reportePorUrgencia(int nivelUrgencia);

private:
    static std::string generarCitaId(int secuencial, int urgencia);
    static int generarId(const std::string& archivo);
};

#endif
