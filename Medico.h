#ifndef MEDICO_H
#define MEDICO_H

#include <string>

class Medico {
public:
    static void inicializarArchivo(); // Inicializa el archivo CSV de médicos
    static void registrar();          // Registra un nuevo médico
    static int buscar();              // Busca un médico por ID, nombre, DNI o especialidad
    static void menuMedicoSeleccionado(int medicoId); // Muestra el menú para un médico seleccionado
    static void modificar(int medicoId); // Modifica los datos de un médico
    static void eliminar(int medicoId);  // Elimina un médico

private:
    static int generarId(const std::string& archivo); // Genera un ID único para cada médico
    static bool validarDatos(const std::string& nombre, const std::string& especialidad, const std::string& dni); // Valida los datos de entrada
};

#endif
