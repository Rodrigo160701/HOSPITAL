#ifndef MEDICO_H
#define MEDICO_H

#include <string>

class Medico {
public:
    static void inicializarArchivo();
    static void registrar();
    static int buscar();
    static void menuMedicoSeleccionado(int medicoId);
    static void modificar(int medicoId);
    static void eliminar(int medicoId);

private:
    static int generarId(const std::string& archivo);
    static bool validarDatos(const std::string& nombre, const std::string& especialidad, const std::string& dni);
};

#endif
