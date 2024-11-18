#ifndef CITA_H
#define CITA_H

#include <string>

class Cita {
public:
    static void inicializarArchivo();
    static void asignar();
    static void buscar();
    static void modificar();
    static void cancelar();
    static void reportePorFecha();
    static void reportePorUrgencia();
private:
    static int generarId(const std::string& archivo);
    static bool validarDatos(const std::string& fecha, int urgencia, int pacienteId, int medicoId);
    static std::string generarIdUnico(const std::string& pacienteNombre, int secuencia, int urgencia);
};

#endif
