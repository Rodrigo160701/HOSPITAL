#ifndef SERVICIO_H
#define SERVICIO_H

#include <string>

class Servicio {
public:
    static void inicializarArchivo();
    static void registrar();
    static int buscar();
    static void menuServicioSeleccionado(int servicioId);
    static void modificar(int servicioId);
    static void eliminar(int servicioId);

private:
    static int generarId(const std::string& archivo);
    static bool validarDatos(const std::string& nombre, const std::string& descripcion);

    // Nuevas funciones privadas
    static int buscarPorCriterio();
    static void mostrarListaCompleta();
};

#endif
