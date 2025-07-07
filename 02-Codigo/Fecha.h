#pragma once
#ifndef FECHA_H
#define FECHA_H

#include <string>
#include <vector>

/**
 * @class Fecha
 * @brief Clase para el manejo y validaci�n de fechas.
 */
class Fecha {
private:
    int dia;   ///< D�a de la fecha.
    int mes;   ///< Mes de la fecha.
    int anio;  ///< A�o de la fecha.

public:
    // SETTERS

    /**
     * @brief Establece el d�a.
     * @param d D�a a establecer.
     */
    void setDia(int d) { dia = d; }

    /**
     * @brief Establece el mes.
     * @param m Mes a establecer.
     */
    void setMes(int m) { mes = m; }

    /**
     * @brief Establece el a�o.
     * @param a A�o a establecer.
     */
    void setAnio(int a) { anio = a; }

    // GETTERS

    /**
     * @brief Obtiene el d�a.
     * @return D�a de la fecha.
     */
    int getDia() const { return dia; }

    /**
     * @brief Obtiene el mes.
     * @return Mes de la fecha.
     */
    int getMes() const { return mes; }

    /**
     * @brief Obtiene el a�o.
     * @return A�o de la fecha.
     */
    int getAnio() const { return anio; }

    /**
     * @brief Constructor por defecto.
     */
    Fecha();

    /**
     * @brief Constructor con par�metros.
     * @param d D�a.
     * @param m Mes.
     * @param a A�o.
     */
    Fecha(int d, int m, int a);

    /**
     * @brief Constructor a partir de una fecha formateada como string.
     * @param fechaFormateada Fecha en formato string (ejemplo: "01/01/2024").
     */
    Fecha(const std::string& fechaFormateada);

    /**
     * @brief Verifica si un a�o es bisiesto.
     * @param a A�o a verificar.
     * @return true si es bisiesto, false en caso contrario.
     */
    bool esBisiesto(int a) const;

    /**
     * @brief Verifica si una fecha corresponde a fin de semana.
     * @param d D�a.
     * @param m Mes.
     * @param a A�o.
     * @return true si es fin de semana, false en caso contrario.
     */
    bool esFinDeSemana(int d, int m, int a) const;

    /**
     * @brief Verifica si una fecha es feriado.
     * @param d D�a.
     * @param m Mes.
     * @param a A�o.
     * @return true si es feriado, false en caso contrario.
     */
    bool esFeriado(int d, int m, int a) const;

    /**
     * @brief Corrige la fecha si no es laborable (fin de semana o feriado).
     */
    void corregirSiNoLaborable();

    /**
     * @brief Avanza la fecha al siguiente d�a laborable.
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
     * @param d D�a.
     * @param m Mes.
     * @param a A�o.
     */
    void setFecha(int d, int m, int a);

    /**
     * @brief Obtiene el estado de manipulaci�n de la fecha del sistema.
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
