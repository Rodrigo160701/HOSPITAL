#ifndef REPORTE_H
#define REPORTE_H

class Reporte {
public:
    static void menuReportes();
    static void menuReportesPacientes();
    static void menuReportesMedicos();
    static void menuReportesCitas();
    static void reportePorFechasIngreso();
    static void reportePacientesSinHistorial();
    static void pacientesConEnfermedadCronica();
    static void reporteMedicosPorEspecialidad();
    static void reporteMedicosConPacientes();
    static void reporteCitasPorFecha();
    static void reporteCitasPorPrioridad();

};

#endif // REPORTE_H
