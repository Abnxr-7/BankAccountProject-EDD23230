#pragma once
#ifndef CUENTAAHORROS_H
#define CUENTAAHORROS_H

#include "Cuenta.h"
#include "Validar.h" // Include validation class
#include "Cifrado.h" // Include encryption class
#include "Fecha.h"   // Include date class
#include "Utilidades.h" // Include utilities class

/**
 * @class CuentaAhorros
 * @brief Representa una cuenta de ahorros, derivada de Cuenta<double>.
 */
class CuentaAhorros : public Cuenta<double> {
private:
    double tasaInteres;      ///< Tasa de inter�s de la cuenta de ahorros.
    Fecha fechaApertura;     ///< Fecha de apertura de la cuenta.

public:
    /**
     * @brief Constructor por defecto.
     */
    CuentaAhorros() : Cuenta<double>(), tasaInteres(0.0) {}

    /**
     * @brief Constructor con par�metros.
     * @param numCuenta N�mero de cuenta.
     * @param saldo Saldo inicial.
     * @param fecha Fecha de apertura (formato string).
     * @param estado Estado de la cuenta.
     * @param tasa Tasa de inter�s.
     */
    CuentaAhorros(std::string numCuenta, double saldo, const std::string& fecha, const std::string& estado, double tasa)
        : Cuenta<double>(numCuenta, saldo, fecha, estado), tasaInteres(tasa) {}

    /**
     * @brief Destructor.
     */
    ~CuentaAhorros() {}

    // Setters

    /**
     * @brief Establece la tasa de inter�s.
     * @param tast Nueva tasa de inter�s.
     */
    void setTasaInteres(double tast) { this->tasaInteres = tast; }

    /**
     * @brief Establece el n�mero de cuenta.
     * @param numCuenta Nuevo n�mero de cuenta.
     */
    void setNumeroCuenta(std::string numCuenta) { this->numeroCuenta = numCuenta; }

    /**
     * @brief Establece el saldo de la cuenta.
     * @param saldo Nuevo saldo.
     */
    void setSaldo(double saldo) { this->saldo = saldo; }

    /**
     * @brief Establece la fecha de apertura.
     * @param fecha Fecha de apertura (formato string).
     */
    void setFechaApertura(const std::string& fecha) { this->fechaApertura = fecha; }

    /**
     * @brief Establece el estado de la cuenta.
     * @param estado Nuevo estado.
     */
    void setEstadoCuenta(const std::string& estado) { this->estadoCuenta = estado; }

    /**
     * @brief Devuelve el puntero a esta cuenta de ahorros.
     * @param cuenta Puntero a cuenta de ahorros (no se usa).
     * @return Puntero a esta cuenta.
     */
    CuentaAhorros* setCuentaAhorros(CuentaAhorros* cuenta) { return this; }

    /**
     * @brief Establece el puntero al siguiente nodo.
     * @param siguiente Puntero al siguiente nodo.
     * @return Puntero a esta cuenta.
     */
    CuentaAhorros* setSiguiente(CuentaAhorros* siguiente) { this->siguiente = siguiente; return this; }

    /**
     * @brief Establece el puntero al nodo anterior.
     * @param anterior Puntero al nodo anterior.
     * @return Puntero a esta cuenta.
     */
    CuentaAhorros* setAnterior(CuentaAhorros* anterior) { this->anterior = anterior; return this; }

    // Getters

    /**
     * @brief (Setter mal nombrado) Establece la tasa de inter�s.
     * @param tasa Nueva tasa de inter�s.
     */
    void getTasaInteres(double tasa) { this->tasaInteres = tasa; }

    /**
     * @brief Obtiene el n�mero de cuenta.
     * @return N�mero de cuenta como string.
     */
    std::string getNumeroCuenta() const { return this->numeroCuenta; }

    /**
     * @brief Obtiene la fecha de apertura.
     * @return Fecha de apertura como string.
     */
    std::string getFechaApertura() const { return this->fechaApertura.toString(); }

    /**
     * @brief Obtiene el saldo de la cuenta.
     * @return Saldo de la cuenta.
     */
    double getSaldo() const { return this->saldo; }

    /**
     * @brief Obtiene el estado de la cuenta.
     * @return Estado de la cuenta como string.
     */
    std::string getEstadoCuenta() const { return this->estadoCuenta; }

    /**
     * @brief Devuelve el puntero a esta cuenta de ahorros.
     * @return Puntero a esta cuenta.
     */
    CuentaAhorros* getCuentaAhorros() { return this; }

    /**
     * @brief Obtiene el puntero al siguiente nodo de la lista.
     * @return Puntero al siguiente CuentaAhorros, o nullptr si no hay.
     */
    CuentaAhorros* getSiguiente() const {
        Cuenta<double>* sig = this->siguiente;
        return sig ? dynamic_cast<CuentaAhorros*>(sig) : nullptr;
    }

    /**
     * @brief Obtiene el puntero al nodo anterior de la lista.
     * @return Puntero al anterior CuentaAhorros, o nullptr si no hay.
     */
    CuentaAhorros* getAnterior() const { return dynamic_cast<CuentaAhorros*>(this->anterior); }

    // M�todos de la clase CuentaAhorros

    /**
     * @brief Deposita una cantidad en la cuenta.
     * @param cantidad Cantidad a depositar.
     */
    void depositar(double cantidad);

    /**
     * @brief Retira una cantidad de la cuenta.
     * @param cantidad Cantidad a retirar.
     */
    void retirar(double cantidad);

    /**
     * @brief Consulta el saldo actual de la cuenta.
     * @return Saldo actual.
     */
    double consultarSaldo() const;

    /**
     * @brief Consulta el estado actual de la cuenta.
     * @return Estado de la cuenta como string.
     */
    std::string consultarEstado() const;

    /**
     * @brief Formatea el saldo como string.
     * @return Saldo formateado como string.
     */
    std::string formatearSaldo() const;

    /**
     * @brief Formatea un valor con comas.
     * @param saldo Valor a formatear.
     * @return Valor formateado como string.
     */
    std::string formatearConComas(double saldo) const;

    /**
     * @brief Muestra la informaci�n de la cuenta.
     * @param cedula C�dula del titular.
     * @param limpiarPantalla Si es true, limpia la pantalla antes de mostrar.
     */
    void mostrarInformacion(const std::string& cedula, bool limpiarPantalla) const;

    /**
     * @brief Guarda la informaci�n de la cuenta en un archivo.
     * @param nombreArchivo Nombre del archivo de destino.
     */
    void guardarEnArchivo(const std::string& nombreArchivo) const override;

    /**
     * @brief Carga la informaci�n de la cuenta desde un archivo.
     * @param nombreArchivo Nombre del archivo de origen.
     */
    void cargarDesdeArchivo(const std::string& nombreArchivo) override;

    /**
     * @brief Calcula el inter�s generado por la cuenta.
     * @return Inter�s calculado como entero.
     */
    int calcularInteres() const;
};

#endif // CUENTAAHORROS_H
