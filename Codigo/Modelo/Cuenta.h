#pragma once
#ifndef CUENTA_H
#define CUENTA_H

#include <iostream>
#include <string>
#include <fstream>
#include "Validar.h" // Incluye la clase de validación

// clase de cabecera para la clase Cuenta
// clase Cuenta abstracta, haciendo uso de templates, memoria dinamica
template <typename T>
class Cuenta {
protected:
    T numeroCuenta;
    T saldo;
    std::string fechaApertura;
    std::string estadoCuenta;

    Cuenta<T>* siguiente;
    Cuenta<T>* anterior;

    // Constructores protegidos para herencia
    Cuenta()
        : numeroCuenta(0), saldo(0), fechaApertura(""), estadoCuenta(""), siguiente(nullptr), anterior(nullptr) {
    }

	// Constructor con parámetros
    Cuenta(T numCuenta, T sal, std::string fecha, std::string estado)
        : numeroCuenta(numCuenta), saldo(sal), fechaApertura(fecha), estadoCuenta(estado), siguiente(nullptr), anterior(nullptr) {
    }

public:
    virtual ~Cuenta() {}

    // Métodos virtuales puros
	virtual void depositar(T cantidad) = 0; // Método para depositar
	virtual void retirar(T cantidad) = 0; // Método para retirar
	virtual T consultarSaldo() const = 0; // Método para consultar saldo
	virtual std::string consultarEstado() const = 0; // Método para consultar estado
	virtual void mostrarInformacion() const = 0; // Método para mostrar información de la cuenta
	virtual void guardarEnArchivo(const std::string& nombreArchivo) const = 0; // Método para guardar en archivo
	virtual void cargarDesdeArchivo(const std::string& nombreArchivo) = 0; // Método para cargar desde archivo
	virtual void crearCuenta() = 0; // Método para crear cuenta

	// Sobrecarga del operador de asignación para copiar los atributos de una cuenta a otra
    Cuenta<T>& operator=(const Cuenta<T>& otra) {
        if (this != &otra) {
            numeroCuenta = otra.numeroCuenta;
            saldo = otra.saldo;
            fechaApertura = otra.fechaApertura;
            estadoCuenta = otra.estadoCuenta;
            siguiente = otra.siguiente;
            anterior = otra.anterior;
        }
        return *this;
    }

	// Sobrecarga del operador de salida para imprimir la información de la cuenta
    friend std::ostream& operator<<(std::ostream& os, const Cuenta<T>& cuenta) {
        os << "Numero de cuenta: " << cuenta.numeroCuenta << "\n"
            << "Saldo: " << cuenta.saldo << "\n"
            << "Fecha de apertura: " << cuenta.fechaApertura << "\n"
            << "Estado de la cuenta: " << cuenta.estadoCuenta << "\n"
            << "Siguiente cuenta: " << (cuenta.siguiente ? std::to_string(cuenta.siguiente->numeroCuenta) : "N/A") << "\n"
            << "Cuenta anterior: " << (cuenta.anterior ? std::to_string(cuenta.anterior->numeroCuenta) : "N/A") << "\n";
        return os;
    }

    // Getters y Setters
    T getNumeroCuenta() const { return numeroCuenta; }
    void setNumeroCuenta(T numCuenta) { numeroCuenta = numCuenta; }

    T getSaldo() const { return saldo; }
    void setSaldo(T sal) { 
        // validar que el ingreso de saldo no pueda ingresarse ningun signo, solamente el punto para 
        // diferenciar los 0.99 centavos del dolar 1.00 
		Validar::ValidarSaldo(sal);
		saldo = sal;
	}

    std::string getFechaApertura() const { return fechaApertura; }
    void setFechaApertura(const std::string& fecha) { fechaApertura = fecha; }

    std::string getEstadoCuenta() const { return estadoCuenta; }
    void setEstadoCuenta(const std::string& estado) { estadoCuenta = estado; }

    Cuenta<T>* getSiguiente() const { return siguiente; }
    void setSiguiente(Cuenta<T>* sig) { siguiente = sig; }

    Cuenta<T>* getAnterior() const { return anterior; }
    void setAnterior(Cuenta<T>* ant) { anterior = ant; }
};

#endif // CUENTA_H
