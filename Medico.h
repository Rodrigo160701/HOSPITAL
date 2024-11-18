#ifndef MEDICO_H
#define MEDICO_H

#include <string>

class Medico {
public:
    static void inicializarArchivo();
    static void registrar();
    static void buscar();
    static void modificar();
    static void eliminar();
private:
    static int generarId(const std::string& archivo);
    static bool validarDatos(const std::string& nombre, const std::string& especialidad, const std::string& dni);
};

#endif
