#include "Cita.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Cita::inicializarArchivo() {
    std::ofstream archivo("citas.csv", std::ios::app);
    if (archivo.tellp() == 0) {
        archivo << "id_cita,paciente_id,medico_id,fecha,urgencia\n";
    }
    archivo.close();
}

void Cita::asignar() {
    std::ofstream archivo("citas.csv", std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return;
    }

    int pacienteId, medicoId, urgencia;
    std::string fecha, pacienteNombre;

    std::cout << "Ingrese el ID del paciente: ";
    std::cin >> pacienteId;
    std::cin.ignore();
    std::cout << "Ingrese el nombre del paciente: ";
    std::getline(std::cin, pacienteNombre);
    std::cout << "Ingrese el ID del médico: ";
    std::cin >> medicoId;
    std::cin.ignore();
    std::cout << "Ingrese la fecha de la cita (YYYY-MM-DD): ";
    std::getline(std::cin, fecha);
    std::cout << "Ingrese el nivel de urgencia (1-5): ";
    std::cin >> urgencia;
    std::cin.ignore();

    if (!validarDatos(fecha, urgencia, pacienteId, medicoId)) {
        std::cerr << "Datos inválidos. Intente nuevamente." << std::endl;
        return;
    }

    int idSecuencial = generarId("citas.csv");
    std::string idCita = generarIdUnico(pacienteNombre, idSecuencial, urgencia);

    archivo << idCita << "," << pacienteId << "," << medicoId << "," << fecha << "," << urgencia << "\n";
    archivo.close();

    std::cout << "Cita asignada correctamente con ID " << idCita << "." << std::endl;
}

void Cita::buscar() {
    std::ifstream archivo("citas.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return;
    }

    std::string criterio;
    std::cout << "Ingrese el ID de cita, fecha, paciente o médico a buscar: ";
    std::getline(std::cin, criterio);

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivo, linea)) {
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

void Cita::modificar() {
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

    std::string idCita, nuevaFecha;
    int nuevaUrgencia, nuevoMedicoId;
    std::cout << "Ingrese el ID de la cita a modificar: ";
    std::getline(std::cin, idCita);

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivoEntrada, linea)) {
        std::stringstream ss(linea);
        std::string citaId, pacienteId, medicoId, fecha, urgenciaStr;

        std::getline(ss, citaId, ',');
        std::getline(ss, pacienteId, ',');
        std::getline(ss, medicoId, ',');
        std::getline(ss, fecha, ',');
        std::getline(ss, urgenciaStr, ',');

        if (citaId == idCita) {
            encontrado = true;
            std::cout << "Cita encontrada: " << linea << std::endl;

            std::cout << "Ingrese la nueva fecha de la cita (YYYY-MM-DD): ";
            std::getline(std::cin, nuevaFecha);
            std::cout << "Ingrese el nuevo nivel de urgencia (1-5): ";
            std::cin >> nuevaUrgencia;
            std::cin.ignore();
            std::cout << "Ingrese el nuevo ID del médico: ";
            std::cin >> nuevoMedicoId;
            std::cin.ignore();

            if (!validarDatos(nuevaFecha, nuevaUrgencia, std::stoi(pacienteId), nuevoMedicoId)) {
                std::cerr << "Datos inválidos. No se realizó la modificación." << std::endl;
                archivoTemporal << linea << "\n";
            }
            else {
                archivoTemporal << citaId << "," << pacienteId << "," << nuevoMedicoId << "," << nuevaFecha << "," << nuevaUrgencia << "\n";
                std::cout << "Cita modificada correctamente." << std::endl;
            }
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
    std::remove("citas.csv");
    std::rename("citas_temp.csv", "citas.csv");
}

void Cita::cancelar() {
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

    std::string idCita;
    std::cout << "Ingrese el ID de la cita a cancelar: ";
    std::getline(std::cin, idCita);

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivoEntrada, linea)) {
        std::stringstream ss(linea);
        std::string citaId;
        std::getline(ss, citaId, ',');

        if (citaId == idCita) {
            encontrado = true;
            std::cout << "Cita cancelada: " << linea << std::endl;
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
    std::remove("citas.csv");
    std::rename("citas_temp.csv", "citas.csv");
}

void Cita::reportePorFecha() {
    std::cout << "Función de reporte por fecha aún en desarrollo." << std::endl;
}

void Cita::reportePorUrgencia() {
    std::cout << "Función de reporte por urgencia aún en desarrollo." << std::endl;
}

int Cita::generarId(const std::string& archivo) {
    std::ifstream entrada(archivo);
    std::string linea;
    int ultimoId = 0;

    while (std::getline(entrada, linea)) {
        std::stringstream ss(linea);
        std::string id;
        std::getline(ss, id, ',');
        if (!id.empty() && id != "id_cita") {
            ultimoId++;
        }
    }

    return ultimoId + 1;
}

bool Cita::validarDatos(const std::string& fecha, int urgencia, int pacienteId, int medicoId) {
    if (fecha.size() != 10 || fecha[4] != '-' || fecha[7] != '-' || urgencia < 1 || urgencia > 5 || pacienteId <= 0 || medicoId <= 0) {
        return false;
    }
    return true;
}

std::string Cita::generarIdUnico(const std::string& pacienteNombre, int secuencia, int urgencia) {
    std::string iniciales;
    for (const char& c : pacienteNombre) {
        if (std::isupper(c)) {
            iniciales += c;
        }
    }
    return iniciales + std::to_string(secuencia) + std::to_string(urgencia);
}
