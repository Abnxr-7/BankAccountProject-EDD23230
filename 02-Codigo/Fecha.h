#pragma once
#ifndef FECHA_H
#define FECHA_H

#include <string>
#include <vector>

/**
 * @class Fecha
 * @brief Clase para el manejo y validación de fechas.
 */
class Fecha {
private:
    int dia;   ///< Día de la fecha.
    int mes;   ///< Mes de la fecha.
    int anio;  ///< Año de la fecha.

public:
    // SETTERS

    /**
     * @brief Establece el día.
     * @param d Día a establecer.
     */
    void setDia(int d) { dia = d; }

    /**
     * @brief Establece el mes.
     * @param m Mes a establecer.
     */
    void setMes(int m) { mes = m; }

    /**
     * @brief Establece el año.
     * @param a Año a establecer.
     */
    void setAnio(int a) { anio = a; }

    // GETTERS

    /**
     * @brief Obtiene el día.
     * @return Día de la fecha.
     */
    int getDia() const { return dia; }

    /**
     * @brief Obtiene el mes.
     * @return Mes de la fecha.
     */
    int getMes() const { return mes; }

    /**
     * @brief Obtiene el año.
     * @return Año de la fecha.
     */
    int getAnio() const { return anio; }

    /**
     * @brief Constructor por defecto.
     */
    Fecha();

    /**
     * @brief Constructor con parámetros.
     * @param d Día.
     * @param m Mes.
     * @param a Año.
     */
    Fecha(int d, int m, int a);

    /**
     * @brief Constructor a partir de una fecha formateada como string.
     * @param fechaFormateada Fecha en formato string (ejemplo: "01/01/2024").
     */
    Fecha(const std::string& fechaFormateada);

    /**
     * @brief Verifica si un año es bisiesto.
     * @param a Año a verificar.
     * @return true si es bisiesto, false en caso contrario.
     */
    bool esBisiesto(int a) const;

    /**
     * @brief Verifica si una fecha corresponde a fin de semana.
     * @param d Día.
     * @param m Mes.
     * @param a Año.
     * @return true si es fin de semana, false en caso contrario.
     */
    bool esFinDeSemana(int d, int m, int a) const;

    /**
     * @brief Verifica si una fecha es feriado.
     * @param d Día.
     * @param m Mes.
     * @param a Año.
     * @return true si es feriado, false en caso contrario.
     */
    bool esFeriado(int d, int m, int a) const;

    /**
     * @brief Corrige la fecha si no es laborable (fin de semana o feriado).
     */
    void corregirSiNoLaborable();

    /**
     * @brief Avanza la fecha al siguiente día laborable.
     */
    void avanzarADiaLaborable();

    /**
     * @brief Obtiene la fecha formateada como string.
     * @return Fecha en formato string (ejemplo: "01/01/2024").
     */
    std::string obtenerFechaFormateada() const;

    /**
     * @brief Verifica si la fecha del sistema ha sido manipulada.
     * @return true si la fecha fue manipulada, false en caso contrario.
     */
    bool esFechaSistemaManipulada() const;

    /**
     * @brief Establece la fecha completa.
     * @param d Día.
     * @param m Mes.
     * @param a Año.
     */
    void setFecha(int d, int m, int a);

    /**
     * @brief Obtiene el estado de manipulación de la fecha del sistema.
     * @return true si la fecha fue manipulada, false en caso contrario.
     */
    bool getEsFechaSistemaManipulada() const;

    /**
     * @brief Obtiene la fecha actual del sistema como string.
     * @return Fecha actual en formato string.
     */
    std::string obtenerFechaActual() const;

    /**
     * @brief Convierte la fecha a string.
     * @return Fecha en formato string.
     */
    std::string toString() const;
};
#endif // FECHA_H
