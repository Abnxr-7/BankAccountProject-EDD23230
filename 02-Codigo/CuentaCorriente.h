#pragma once
#ifndef CUENTACORRIENTE_H
#define CUENTACORRIENTE_H

#include "Cuenta.h"
#include "Validar.h"
#include "Cifrado.h"
#include "Fecha.h"

/**
 * @class CuentaCorriente
 * @brief Representa una cuenta corriente bancaria, derivada de Cuenta<double>.
 */
class CuentaCorriente : public Cuenta<double> {
private:
    double montoMinimo;      ///< Monto m�nimo requerido para la cuenta corriente.
    Fecha fechaApertura;     ///< Fecha de apertura de la cuenta.

public:
    /**
     * @brief Constructor por defecto.
     */
    CuentaCorriente() : Cuenta<double>(), montoMinimo(0.00) {}

    /**
     * @brief Constructor con par�metros.
     * @param numeroCuenta N�mero de cuenta.
     * @param saldo Saldo inicial.
     * @param fechaApertura Fecha de apertura (formato string).
     * @param estadoCuenta Estado de la cuenta.
     * @param montoMinimo Monto m�nimo requerido.
     */
    CuentaCorriente(std::string numeroCuenta, double saldo, const std::string& fechaApertura, const std::string estadoCuenta, double montoMinimo)
        : Cuenta<double>(numeroCuenta, saldo, fechaApertura, estadoCuenta), montoMinimo(montoMinimo) {}

    // SETTERS

    /**
     * @brief Establece el monto m�nimo requerido.
     * @param montoMinimo Nuevo monto m�nimo.
     */
    void setMontoMinimo(double montoMinimo) { this->montoMinimo = montoMinimo; }

    /**
     * @brief Establece el n�mero de cuenta.
     * @param numeroCuenta Nuevo n�mero de cuenta.
     */
    void setNumeroCuenta(std::string numeroCuenta) { this->numeroCuenta = numeroCuenta; }

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
     * @param estadoCuenta Nuevo estado de la cuenta.
     */
    void setEstadoCuenta(const std::string& estadoCuenta) { this->estadoCuenta = estadoCuenta; }

    /**
     * @brief Devuelve el puntero a esta cuenta corriente.
     * @param cuentaCorriente Puntero a cuenta corriente (no se usa).
     * @return Puntero a esta cuenta.
     */
    CuentaCorriente* setCuentaCorriente(CuentaCorriente* cuentaCorriente) { return this; }

    /**
     * @brief Establece el puntero al siguiente nodo.
     * @param cuentaSiguiente Puntero al siguiente nodo.
     * @return Puntero a esta cuenta.
     */
    CuentaCorriente* setSiguiente(CuentaCorriente* cuentaSiguiente) { this->siguiente = siguiente; return this; }

    /**
     * @brief Establece el puntero al nodo anterior.
     * @param cuentaAnterior Puntero al nodo anterior.
     * @return Puntero a esta cuenta.
     */
    CuentaCorriente* setAnterior(CuentaCorriente* cuentaAnterior) { this->anterior = anterior; return this; }

    // GETTERS

    /**
     * @brief Obtiene el monto m�nimo requerido.
     * @return Monto m�nimo.
     */
    double getMontoMinimo() const { return this->montoMinimo; }

    /**
     * @brief Obtiene el n�mero de cuenta.
     * @return N�mero de cuenta como string.
     */
    std::string getNumeroCuenta() const { return this->numeroCuenta; }

    /**
     * @brief Obtiene el saldo de la cuenta.
     * @return Saldo de la cuenta.
     */
    double getSaldo() const { return this->saldo; }

    /**
     * @brief Obtiene la fecha de apertura.
     * @return Fecha de apertura como string.
     */
    std::string getFechaApertura() const { return this->fechaApertura.toString(); }

    /**
     * @brief Obtiene el estado de la cuenta.
     * @return Estado de la cuenta como string.
     */
    std::string getEstadoCuenta() const { return this->estadoCuenta; }

    /**
     * @brief Devuelve el puntero a esta cuenta corriente.
     * @return Puntero a esta cuenta.
     */
    CuentaCorriente* getCuentaCorriente() { return this; }

    /**
     * @brief Obtiene el puntero al siguiente nodo de la lista.
     * @return Puntero al siguiente CuentaCorriente, o nullptr si no hay.
     */
    CuentaCorriente* getSiguiente() const { 
        Cuenta<double>* sig = this->siguiente;
        return sig ? dynamic_cast<CuentaCorriente*>(sig) : nullptr;
    }

    /**
     * @brief Obtiene el puntero al nodo anterior de la lista.
     * @return Puntero al anterior CuentaCorriente, o nullptr si no hay.
     */
    CuentaCorriente* getAnterior() const { return dynamic_cast<CuentaCorriente*>(this->anterior); }

    // M�todos espec�ficos de CuentaCorriente

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
     * @brief Verifica si el monto cumple con el m�nimo requerido.
     * @param montoMinimo Monto a verificar.
     */
    void esMontoMinimo(double montoMinimo);

};
#endif // CUENTACORRIENTE_H