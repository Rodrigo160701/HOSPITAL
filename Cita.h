#ifndef CITA_H
#define CITA_H

#include <string>

class Cita {
public:
    static void inicializarArchivo();
    static void asignar();
    static int buscar();
    static void menuCitaSeleccionada(int citaId);
    static void modificar(int citaId);
    static void cancelar(int citaId);

private:
    static int generarId(const std::string& archivo);
    static bool validarFecha(const std::string& fecha); 
    static bool validarDatos(const std::string& fecha, int urgencia, int pacienteId, int medicoId);
};

#endif