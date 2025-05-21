#pragma once
#ifndef CUENTACORRIENTE_H
#define CUENTACORRIENTE_H
#include <iostream>
#include <string>
#include <fstream>
#include "Cuenta.h"
#include "Validar.h" // Incluye la clase de validación
#include "Cifrado.h" // Incluye la clase de cifrado
#include "Fecha.h" // Incluye la clase Fecha
#include "NodoCuentaCorriente.h" // Incluye la clase NodoCuentaCorriente


// clase cuentaCorriente con herencia de la clase cuenta con metodos template, funciones lambda
template <typename T>
class CuentaCorriente : public Cuenta<T> {
private:
	T montoMinimo; // Monto mínimo requerido para la cuenta corriente
	// Puntero a la lista de cuentas
	NodoCuentaCorriente<std::string>* listaCuentas = nullptr;

public:
	// Constructor por defecto
	CuentaCorriente() : Cuenta<T>(), montoMinimo(0) {
	}
	// Constructor con parámetros
	CuentaCorriente(T numCuenta, T sal, std::string fecha, std::string estado, T monto)
		: Cuenta<T>(numCuenta, sal, fecha, estado), montoMinimo(monto) {
	}
	// Método para depositar
	void depositar(T cantidad) override {
		this->saldo += cantidad;
	}
	// Método para retirar
	void retirar(T cantidad) override {
		if (cantidad <= this->saldo) {
			this->saldo -= cantidad;
		}
		else {
			std::cout << "Fondos insuficientes." << std::endl;
		}
	}

	// Método para consultar el saldo
	T consultarSaldo() const override {
		return this->saldo;
	}

	// Método para consultar el estado de la cuenta
	std::string consultarEstado() const override {
		return this->estadoCuenta;
	}

	// Método para mostrar la informacion de la cuenta 
	void mostrarInformacion() const override {
		std::cout << "Cuenta Corriente:" << std::endl;
		std::cout << *this; // Llama al operador de salida sobrecargado
		std::cout << "Monto Minimo: " << montoMinimo << std::endl;
	}

	// Método para guardar la cuenta en un archivo
	void guardarEnArchivo(const std::string& nombreArchivo) const override {
		std::ofstream archivo(nombreArchivo, std::ios::binary);
		if (archivo.is_open()) {
			archivo.write(reinterpret_cast<const char*>(this), sizeof(CuentaCorriente<T>));
			archivo.close();
		}
		else {
			std::cerr << "Error al abrir el archivo para guardar." << std::endl;
		}
	}

	// Método para cargar la cuenta desde un archivo
	void cargarDesdeArchivo(const std::string& nombreArchivo) override {
		std::ifstream archivo(nombreArchivo, std::ios::binary);
		if (archivo.is_open()) {
			archivo.read(reinterpret_cast<char*>(this), sizeof(CuentaCorriente<T>));
			archivo.close();
		}
		else {
			std::cerr << "Error al abrir el archivo para cargar." << std::endl;
		}
	}

	// Método para validar si existe el numero de cuenta en la lista de cuentas
	bool existeCuentaEnLista(const std::string numeroCuenta) {
		NodoCuentaCorriente<std::string>* actual = listaCuentas;
		while (actual != nullptr) {
			if (actual->numeroCuenta == numeroCuenta) {
				return true; // La cuenta ya existe
			}
			actual = actual->siguiente;
		}
		return false; // La cuenta no existe
	}

	// Método para agregar la cuenta a la lista de cuentas
	void agregarCuentaLista(const std::string numeroCuenta) { 
		auto crearNodo = [](std::string numeroCuenta) -> NodoCuentaCorriente<std::string>*{ 
			return new NodoCuentaCorriente<std::string>(numeroCuenta); // Crear un nuevo nodo
			};

		if (listaCuentas == nullptr) { // Si la lista está vacía, simplemente asigna el primer nodo
			listaCuentas = crearNodo(numeroCuenta);
		}
		else { // Si la lista no está vacía, recorre hasta el final y agrega el nuevo nodo
			NodoCuentaCorriente<std::string>* actual = listaCuentas; 
			while (actual->siguiente != nullptr) {
				actual = actual->siguiente;
			}
			actual->siguiente = crearNodo(numeroCuenta);
			actual->siguiente->anterior = actual;
		}
	}


	// Método para crear cuenta
	void crearCuenta() override {

		// Se crea un numero de cuenta aleatorio de 10 digitos y se valida, de no ser valido se vuelve a generar
		// el numero de cuenta aleatorio de 10 digitos y se valida, de no ser valido se vuelve a generar
		// ademas se valida que el numero de cuenta no se repita en la lista de cuentas
		// Generar y validar número de cuenta único
		do {
			this->numeroCuenta = rand() % 10000000000;
		} while (!Validar::ValidarNumeroCuenta(std::to_string(this->numeroCuenta)) || existeCuentaEnLista(std::to_string(this->numeroCuenta)));
		agregarCuentaLista(std:: to_string(this->numeroCuenta)); // Agregar la cuenta a la lista de cuentas
		// Se muestra el numero de cuenta
		std::cout << "Numero de cuenta: " << this->numeroCuenta << std::endl;



		// Se indica que el saldo inicial es cero (0)
		this->saldo = 0;
		std::cout << "Saldo inicial: " << this->saldo << std::endl;
		// No se valida por que el saldo inicial es cero (0)

		// Se obtiene la fecha del sistema con la clase Fecha.cpp
		Fecha fechaSistema;
		this->fechaApertura = fechaSistema.obtenerFechaFormateada();
		std::cout << "Fecha de apertura: " << this->fechaApertura << std::endl;


		// Al crear una nueva cuenta se le asigna el estado de la cuenta como activa
		this->estadoCuenta = "Activa";
		std::cout << "Estado de la cuenta: " << this->estadoCuenta << std::endl;
		// No se valida por que el estado de la cuenta es activa por defecto

		// Se pide el monto minimo requerido para la cuenta corriente
		std::cout << "Ingrese el monto para la cuenta: ";
		std::cin >> montoMinimo;
		while (!Validar::ValidarMontoTransaccion(montoMinimo)) {
			std::cout << "Monto inválido. Ingrese nuevamente: ";
			std::cin >> montoMinimo;
		}
		this->montoMinimo = montoMinimo;
		std::cout << "Monto minimo: " << this->montoMinimo << std::endl;

		// Se muestra la informacion de la cuenta final
		mostrarInformacion();
	}



};
#endif // CUENTACORRIENTE_H
