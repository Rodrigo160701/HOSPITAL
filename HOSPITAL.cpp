#include <iostream>
#include <string>
#include "Paciente.h"
#include "Medico.h"
#include "Cita.h"
#include "Servicio.h"

int main() {
    int id, urgencia;
    std::string nombre, fecha_ingreso, historial_clinico, DNI, especialidad, descripcion, fecha;

    // Crear un paciente
    std::cout << "Ingrese los datos del paciente:\n";
    std::cout << "ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Nombre: ";
    std::getline(std::cin, nombre);
    std::cout << "Fecha de Ingreso (YYYY-MM-DD): ";
    std::getline(std::cin, fecha_ingreso);
    std::cout << "Historial Clínico: ";
    std::getline(std::cin, historial_clinico);
    std::cout << "DNI: ";
    std::getline(std::cin, DNI);

    Paciente paciente1(id, nombre, fecha_ingreso, historial_clinico, DNI);
    paciente1.registrarPaciente();
    paciente1.mostrarDatos();

    // Crear un médico
    bool disponibilidad;
    std::cout << "\nIngrese los datos del médico:\n";
    std::cout << "ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Nombre: ";
    std::getline(std::cin, nombre);
    std::cout << "Especialidad: ";
    std::getline(std::cin, especialidad);
    std::cout << "Disponibilidad (1 para disponible, 0 para no disponible): ";
    std::cin >> disponibilidad;

    Medico medico1(id, nombre, especialidad, disponibilidad);
    medico1.registrarMedico();
    medico1.mostrarDatos();

    // Crear una cita
    std::cout << "\nIngrese los datos de la cita:\n";
    std::cout << "ID de la cita: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Fecha de la cita (YYYY-MM-DD): ";
    std::getline(std::cin, fecha);
    std::cout << "Nivel de urgencia (1-5): ";
    std::cin >> urgencia;

    Cita cita1(id, fecha, urgencia, &paciente1, &medico1);
    cita1.asignarCita();
    cita1.mostrarDatos();

    // Crear un servicio
    std::cout << "\nIngrese los datos del servicio:\n";
    std::cout << "ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Nombre del servicio: ";
    std::getline(std::cin, nombre);
    std::cout << "Descripción del servicio: ";
    std::getline(std::cin, descripcion);

    Servicio servicio1(id, nombre, descripcion);
    servicio1.agregarServicio();
    servicio1.mostrarDatos();

    return 0;
}
