#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

class Paciente {
public:
    static void inicializarArchivo();
    static void registrar();
    static int buscar();
    static void menuPacienteSeleccionado(int pacienteId);
    static void modificar(int pacienteId);
    static void eliminar(int pacienteId);
    static void agregarHistorial(int pacienteId);

private:
    static int generarId(const std::string& archivo);
    static bool validarDatos(const std::string& nombre, const std::string& dni, const std::string& fechaIngreso);
};

#endif
