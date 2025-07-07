#pragma once
#ifndef CUENTA_H
#define CUENTA_H

#include <iostream>
#include <string>
#include <fstream>
#include <regex> // Incluye la libreria regex para validacion de fecha
#include "Validar.h" // Incluye la clase de validacion
#include "Fecha.h" // Incluye la clase Fecha para manejar fechas

/**
 * @brief Clase abstracta base para cuentas bancarias, usando templates y listas doblemente enlazadas.
 * @tparam T Tipo de dato para el saldo (por ejemplo, double).
 */
template <typename T>
class Cuenta {
protected:
    std::string numeroCuenta;      ///< Número de cuenta bancaria.
    T saldo;                       ///< Saldo de la cuenta.
    Fecha fechaApertura;           ///< Fecha de apertura de la cuenta.
    std::string estadoCuenta;      ///< Estado de la cuenta (activa, cerrada, etc.).
    Cuenta<T>* siguiente;          ///< Puntero al siguiente nodo en la lista.
    Cuenta<T>* anterior;           ///< Puntero al nodo anterior en la lista.

    /**
     * @brief Constructor protegido por defecto.
     */
    Cuenta()
        : numeroCuenta(""), saldo(0), fechaApertura(), estadoCuenta(""), siguiente(nullptr), anterior(nullptr) {
    }

    /**
     * @brief Constructor protegido con parámetros.
     * @param numeroCuenta Número de cuenta.
     * @param saldo Saldo inicial.
     * @param fechaStr Fecha de apertura en formato string.
     * @param estadoCuenta Estado de la cuenta.
     */
    Cuenta(std::string numeroCuenta, T saldo, const std::string& fechaStr, std::string estadoCuenta)
        : numeroCuenta(numeroCuenta), saldo(saldo), fechaApertura(fechaStr),
        estadoCuenta(estadoCuenta), siguiente(nullptr), anterior(nullptr) {
    }

    /**
     * @brief Destructor virtual para permitir liberación de recursos en clases derivadas.
     */
    virtual ~Cuenta() {}

public:
    // Getters

    /**
     * @brief Obtiene el número de cuenta.
     * @return Número de cuenta como string.
     */
    std::string getNumeroCuenta() const { return numeroCuenta; }

    /**
     * @brief Obtiene el saldo de la cuenta.
     * @return Saldo de la cuenta.
     */
    T getSaldo() const { return saldo; }

    /**
     * @brief Obtiene la fecha de apertura de la cuenta.
     * @return Objeto Fecha con la fecha de apertura.
     */
    Fecha getFechaApertura() const { return fechaApertura; }

    /**
     * @brief Obtiene el estado de la cuenta.
     * @return Estado de la cuenta como string.
     */
    std::string getEstadoCuenta() const { return estadoCuenta; }

    /**
     * @brief Obtiene el puntero al siguiente nodo en la lista.
     * @return Puntero al siguiente nodo.
     */
    Cuenta<T>* getSiguiente() const { return siguiente; }

    /**
     * @brief Obtiene el puntero al nodo anterior en la lista.
     * @return Puntero al nodo anterior.
     */
    Cuenta<T>* getAnterior() const { return anterior; }
    
    // Setters

    /**
     * @brief Establece el número de cuenta.
     * @param numero Nuevo número de cuenta.
     * @return El número de cuenta asignado.
     */
    std::string setNumeroCuenta(const std::string& numero) { numeroCuenta = numero; return numeroCuenta; }

    /**
     * @brief Establece el saldo de la cuenta.
     * @param nuevoSaldo Nuevo saldo.
     * @return El saldo asignado.
     */
    T setSaldo(T nuevoSaldo) { saldo = nuevoSaldo; return saldo; }

    /**
     * @brief Establece la fecha de apertura de la cuenta.
     * @param fechaStr Fecha en formato string.
     * @return Objeto Fecha asignado.
     */
    Fecha setFechaApertura(const std::string& fechaStr) { fechaApertura = Fecha(fechaStr); return fechaApertura; }

    /**
     * @brief Establece el estado de la cuenta.
     * @param estado Nuevo estado.
     * @return El estado asignado.
     */
    std::string setEstadoCuenta(const std::string& estado) { estadoCuenta = estado; return estadoCuenta; }

    /**
     * @brief Establece el puntero al siguiente nodo.
     * @param sig Puntero al siguiente nodo.
     */
    void setSiguiente(Cuenta<T>* sig) { siguiente = sig; }

    /**
     * @brief Establece el puntero al nodo anterior.
     * @param ant Puntero al nodo anterior.
     */
    void setAnterior(Cuenta<T>* ant) { anterior = ant; }

    // Métodos virtuales puros

    /**
     * @brief Deposita una cantidad en la cuenta.
     * @param cantidad Cantidad a depositar.
     */
    virtual void depositar(T cantidad) = 0;

    /**
     * @brief Retira una cantidad de la cuenta.
     * @param cantidad Cantidad a retirar.
     */
    virtual void retirar(T cantidad) = 0;

    /**
     * @brief Consulta el saldo actual de la cuenta.
     * @return Saldo actual.
     */
    virtual double consultarSaldo() const = 0;

    /**
     * @brief Consulta el estado actual de la cuenta.
     * @return Estado de la cuenta como string.
     */
    virtual std::string consultarEstado() const = 0;

    /**
     * @brief Guarda la información de la cuenta en un archivo.
     * @param nombreArchivo Nombre del archivo de destino.
     */
    virtual void guardarEnArchivo(const std::string& nombreArchivo) const = 0;

    /**
     * @brief Carga la información de la cuenta desde un archivo.
     * @param nombreArchivo Nombre del archivo de origen.
     */
    virtual void cargarDesdeArchivo(const std::string& nombreArchivo) = 0;

    /**
     * @brief Muestra la información de la cuenta.
     * @param cedula (Opcional) Cédula del titular.
     * @param limpiarPantalla (Opcional) Si es true, limpia la pantalla antes de mostrar.
     */
    virtual void mostrarInformacion(const std::string& cedula = "", bool limpiarPantalla = true) const = 0;
};
#endif // CUENTA_H
