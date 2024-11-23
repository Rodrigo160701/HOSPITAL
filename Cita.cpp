#include "Cita.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Cita::inicializarArchivo() {
    std::ofstream archivo("citas.csv", std::ios::app);
    if (archivo.tellp() == 0) {
        archivo << "id,fecha,urgencia,paciente_id,medico_id\n"; // Cabecera del archivo
    }
    archivo.close();
}

void Cita::asignar() {
    std::ofstream archivo("citas.csv", std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return;
    }

    std::string fecha, urgenciaStr, pacienteIdStr, medicoIdStr;
    int urgencia, pacienteId, medicoId;

    std::cout << "Ingrese la fecha de la cita (YYYY-MM-DD): ";
    std::getline(std::cin, fecha);
    std::cout << "Ingrese el nivel de urgencia (1-5): ";
    std::getline(std::cin, urgenciaStr);

    try {
        urgencia = std::stoi(urgenciaStr);
        if (urgencia < 1 || urgencia > 5) {
            throw std::out_of_range("Nivel de urgencia fuera de rango.");
        }
    }
    catch (const std::exception&) {
        std::cerr << "Error: El nivel de urgencia debe ser un número entre 1 y 5." << std::endl;
        return;
    }

    std::cout << "Ingrese el ID del paciente: ";
    std::getline(std::cin, pacienteIdStr);
    try {
        pacienteId = std::stoi(pacienteIdStr);
    }
    catch (const std::exception&) {
        std::cerr << "Error: El ID del paciente debe ser un número válido." << std::endl;
        return;
    }

    std::cout << "Ingrese el ID del médico: ";
    std::getline(std::cin, medicoIdStr);
    try {
        medicoId = std::stoi(medicoIdStr);
    }
    catch (const std::exception&) {
        std::cerr << "Error: El ID del médico debe ser un número válido." << std::endl;
        return;
    }

    int id = generarId("citas.csv");
    std::string citaId = generarCitaId(id, urgencia);

    archivo << citaId << "," << fecha << "," << urgencia << "," << pacienteId << "," << medicoId << "\n";
    archivo.close();

    std::cout << "Cita creada correctamente con ID: " << citaId << "." << std::endl;
}

std::string Cita::generarCitaId(int secuencial, int urgencia) {
    std::stringstream ss;
    ss << "C" << secuencial << urgencia; // Formato del ID: C<secuencial><urgencia>
    return ss.str();
}

int Cita::generarId(const std::string& archivo) {
    std::ifstream entrada(archivo);
    std::string linea;
    int ultimoId = 0;

    while (std::getline(entrada, linea)) {
        if (linea.empty() || linea.find("id") == 0) continue; // Ignora líneas vacías o la cabecera

        std::stringstream ss(linea);
        std::string idStr;
        std::getline(ss, idStr, ',');
        try {
            int id = std::stoi(idStr.substr(1)); // Extrae el número del formato C<secuencial><urgencia>
            if (id > ultimoId) {
                ultimoId = id;
            }
        }
        catch (const std::exception&) {
            continue; // Si no es un número válido, ignorar
        }
    }

    return ultimoId + 1;
}

void Cita::buscar() {
    std::ifstream archivo("citas.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return;
    }

    std::string criterio;
    std::cout << "Ingrese el criterio de búsqueda (ID, fecha, paciente o médico): ";
    std::getline(std::cin, criterio);

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivo, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            continue; // Ignora líneas vacías o la cabecera
        }

        if (linea.find(criterio) != std::string::npos) {
            std::cout << linea << std::endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron citas con el criterio dado." << std::endl;
    }

    archivo.close();
}

void Cita::modificar(const std::string& citaId) {
    std::ifstream archivoEntrada("citas.csv");
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return;
    }

    std::ofstream archivoTemporal("citas_temp.csv");
    if (!archivoTemporal) {
        std::cerr << "Error al crear el archivo temporal." << std::endl;
        return;
    }

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivoEntrada, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            archivoTemporal << linea << "\n"; // Copia la cabecera
            continue;
        }

        std::stringstream ss(linea);
        std::string id, fecha, urgenciaStr, pacienteIdStr, medicoIdStr;
        std::getline(ss, id, ',');
        std::getline(ss, fecha, ',');
        std::getline(ss, urgenciaStr, ',');
        std::getline(ss, pacienteIdStr, ',');
        std::getline(ss, medicoIdStr);

        if (id == citaId) {
            encontrado = true;
            std::cout << "Cita encontrada: " << linea << std::endl;

            std::cout << "Ingrese la nueva fecha de la cita (deje vacío para no modificar): ";
            std::string nuevaFecha;
            std::getline(std::cin, nuevaFecha);
            if (!nuevaFecha.empty()) fecha = nuevaFecha;

            std::cout << "Ingrese el nuevo nivel de urgencia (deje vacío para no modificar): ";
            std::string nuevaUrgenciaStr;
            std::getline(std::cin, nuevaUrgenciaStr);
            if (!nuevaUrgenciaStr.empty()) {
                try {
                    int nuevaUrgencia = std::stoi(nuevaUrgenciaStr);
                    if (nuevaUrgencia >= 1 && nuevaUrgencia <= 5) {
                        urgenciaStr = nuevaUrgenciaStr;
                    }
                    else {
                        std::cerr << "Nivel de urgencia fuera de rango. No se modifica." << std::endl;
                    }
                }
                catch (const std::exception&) {
                    std::cerr << "Error: Nivel de urgencia inválido. No se modifica." << std::endl;
                }
            }

            archivoTemporal << id << "," << fecha << "," << urgenciaStr << "," << pacienteIdStr << "," << medicoIdStr << "\n";
            std::cout << "Cita modificada correctamente." << std::endl;
        }
        else {
            archivoTemporal << linea << "\n";
        }
    }

    if (!encontrado) {
        std::cout << "No se encontró ninguna cita con el ID proporcionado." << std::endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

    if (std::remove("citas.csv") == 0) {
        std::cout << "Archivo original eliminado correctamente." << std::endl;
    }
    else {
        std::cerr << "Advertencia: No se pudo eliminar el archivo original." << std::endl;
    }

    if (std::rename("citas_temp.csv", "citas.csv") != 0) {
        perror("Error al renombrar el archivo temporal");
    }
}

void Cita::reportePorFecha(const std::string& fechaInicio, const std::string& fechaFin) {
    std::ifstream archivo("citas.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return;
    }

    std::string linea;
    bool encontrado = false;

    std::cout << "Citas entre " << fechaInicio << " y " << fechaFin << ":\n";
    while (std::getline(archivo, linea)) {
        if (linea.empty() || linea.find("id") == 0) continue;

        std::stringstream ss(linea);
        std::string id, fecha, urgencia, pacienteId, medicoId;
        std::getline(ss, id, ',');
        std::getline(ss, fecha, ',');

        if (fecha >= fechaInicio && fecha <= fechaFin) {
            std::cout << linea << std::endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron citas en el rango de fechas especificado." << std::endl;
    }

    archivo.close();
}
