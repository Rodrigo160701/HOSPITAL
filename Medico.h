#ifndef MEDICO_H
#define MEDICO_H

#include <string>

class Medico {
public:
    static void inicializarArchivo(); // Inicializa el archivo CSV de m�dicos
    static void registrar();          // Registra un nuevo m�dico
    static int buscar();              // Busca un m�dico por ID, nombre, DNI o especialidad
    static void menuMedicoSeleccionado(int medicoId); // Muestra el men� para un m�dico seleccionado
    static void modificar(int medicoId); // Modifica los datos de un m�dico
    static void eliminar(int medicoId);  // Elimina un m�dico

private:
    static int generarId(const std::string& archivo); // Genera un ID �nico para cada m�dico
    static bool validarDatos(const std::string& nombre, const std::string& especialidad, const std::string& dni); // Valida los datos de entrada
};

#endif
