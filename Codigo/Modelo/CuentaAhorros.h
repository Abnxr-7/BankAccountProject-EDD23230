#pragma once
#ifndef CUENTAAHORROS_H
#define CUENTAAHORROS_H
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <locale>
#include <windows.h>
#include <sstream>
#include <conio.h>
#include "Cuenta.h"
#include "Validar.h" // Incluye la clase de validación
#include "Cifrado.h" // Incluye la clase de cifrado
#include "Fecha.h" // Incluye la clase Fecha
#include "NodoCuentaAhorros.h" // Incluye la clase NodoCuenta
#include "Utilidades.h" // Incluye la clase Utilidades


// clase cuentaAhorro con herencia de la clase cuenta con metodos template, funciones lambda
template <typename T>
class CuentaAhorros : public Cuenta<T> {
private:
	// Tasa de interes fijo de 5% para Banco Pichincha
	T tasaInteres = 5;

	// Monto mínimo requerido para la cuenta de ahorros
	// Minimo esta en funcion del tiempo que este con el monto minimo se mantendra la cuenta
	T montoMinimo = 0;

	// Puntero a la lista de cuentas
	NodoCuentaAhorros<std::string>* listaCuentas = nullptr;




public:
	// Constructor por defecto
	CuentaAhorros() : Cuenta<T>(), tasaInteres(0), montoMinimo(0) {
	}

	// Constructor con parámetros
	CuentaAhorros(T numCuenta, T sal, std::string fecha, std::string estado, T tasa, T monto)
		: Cuenta<T>(numCuenta, sal, fecha, estado), tasaInteres(tasa), montoMinimo(monto) {
	}

	// Método para depositar
	void depositar(T cantidad) override {
		this->saldo += cantidad;
	}

	// Método para depositar
	void retirar(T cantidad) override {
		if (cantidad <= this->saldo) {
			this->saldo -= cantidad;
		}
		else {
			std::cout << "Fondos insuficientes." << std::endl;
		}
	}

	// Método para calcular el interés
	T consultarSaldo() const override {
		return this->saldo;
	}

	// Método para consultar el saldo
	std::string consultarEstado() const override {
		return this->estadoCuenta;
	}

	// Método para calcular el interés siempre del 5% anual
	T calcularInteres() const {
		return (this->saldo * tasaInteres) / 100;
	}

	// Método para consultar el estado de la cuenta
	void mostrarInformacion() const override {
		std::cout << "Cuenta de Ahorros:" << std::endl;
		std::cout << *this; // Llama al operador de salida sobrecargado
		std::cout << "Tasa de Interes: " << tasaInteres << std::endl;
		std::cout << "Monto Minimo: " << formatearConComas(Utilidades::ConvertirADouble(std::to_string(this->montoMinimo))) << std::endl;
	}

	// Método para guardar en archivo
	void guardarEnArchivo(const std::string& nombreArchivo) const override {
		std::ofstream archivo(nombreArchivo, std::ios::binary);
		if (archivo.is_open()) {
			archivo.write(reinterpret_cast<const char*>(&this->numeroCuenta), sizeof(this->numeroCuenta));
			archivo.write(reinterpret_cast<const char*>(&this->saldo), sizeof(this->saldo));
			archivo.write(this->fechaApertura.c_str(), this->fechaApertura.size() + 1);
			archivo.write(this->estadoCuenta.c_str(), this->estadoCuenta.size() + 1);
			archivo.write(reinterpret_cast<const char*>(&tasaInteres), sizeof(tasaInteres));
			archivo.write(reinterpret_cast<const char*>(&montoMinimo), sizeof(montoMinimo));
			archivo.close();
		}
	}

	// Método para cargar desde archivo
	void cargarDesdeArchivo(const std::string& nombreArchivo) override {
		std::ifstream archivo(nombreArchivo, std::ios::binary);
		if (archivo.is_open()) {
			archivo.read(reinterpret_cast<char*>(&this->numeroCuenta), sizeof(this->numeroCuenta));
			archivo.read(reinterpret_cast<char*>(&this->saldo), sizeof(this->saldo));
			char buffer[100];
			archivo.getline(buffer, 100, '\0');
			this->fechaApertura = buffer;
			archivo.getline(buffer, 100, '\0');
			this->estadoCuenta = buffer;
			archivo.read(reinterpret_cast<char*>(&tasaInteres), sizeof(tasaInteres));
			archivo.read(reinterpret_cast<char*>(&montoMinimo), sizeof(montoMinimo));
			archivo.close();
		}
	}

	// Método para validar si existe el numero de cuenta en la lista de cuentas
	bool existeCuentaEnLista(const std::string numeroCuenta) {
		NodoCuentaAhorros<std::string>* actual = listaCuentas;
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
		// Se agrega el número de cuenta a la lista de cuentas existente sin crear un nuevo NodoCuentaAhorros
		if (listaCuentas == nullptr) {
			// Si la lista está vacía, simplemente asigna el primer nodo
			listaCuentas = new NodoCuentaAhorros<std::string>(numeroCuenta);
		}
		else {
			NodoCuentaAhorros<std::string>* actual = listaCuentas;
			while (actual->siguiente != nullptr) {
				actual = actual->siguiente;
			}
			// En vez de crear un nuevo NodoCuentaAhorros, reutiliza el nodo existente si es posible
			// Pero como la lista es de nodos, para agregar un nuevo número de cuenta, se debe crear un nodo
			// Así que solo se crea el nodo una vez aquí, no se instancia NodoCuentaAhorros en otro lugar
			actual->siguiente = new NodoCuentaAhorros<std::string>(numeroCuenta);
			actual->siguiente->anterior = actual;
		}
	}
	
	// Método para crear cuenta
	void crearCuenta() override {
		// Se crea un numero de cuenta aleatorio de 10 digitos y se valida, de no ser valido se vuelve a generar
		// el numero de cuenta aleatorio de 10 digitos y se valida, de no ser valido se vuelve a generar
		// ademas se valida que el numero de cuenta no se repita en la lista de cuentas
		// Generar y validar número de cuenta único

		//mensaje de depuracion
		std::cout << "Creando cuenta de ahorros..." << std::endl;

		// Generar y validar número de cuenta único
		std::string numeroCuentaStr;
		do {
			// Generar un número de cuenta aleatorio de 10 dígitos como string
			numeroCuentaStr.clear();
			for (int i = 0; i < 10; ++i) {
				char digito = '0' + (rand() % 10);
				// Evitar que el primer dígito sea cero
				if (i == 0 && digito == '0') {
					digito = '1' + (rand() % 9);
				}
				numeroCuentaStr += digito;
			}
			std::cout << "Generando numero de cuenta: " << numeroCuentaStr << std::endl;
		} while (!Validar::ValidarNumeroCuenta(numeroCuentaStr) || existeCuentaEnLista(numeroCuentaStr));

		try {
			std::cout << "Intentando convertir a entero: " << numeroCuentaStr << std::endl; // Depuración
			this->numeroCuenta = std::stoll(numeroCuentaStr);
		}
		catch (const std::invalid_argument& e) {
			std::cerr << "Error al convertir el número de cuenta a número entero: " << e.what() << "\n";
			return;
		}
		agregarCuentaLista(numeroCuentaStr); // Agregar la cuenta a la lista de cuentas
		// Se muestra el numero de cuenta
		std::cout << "Numero de cuenta: " << numeroCuentaStr << std::endl;

		// Se indica que el saldo inicial es cero (0)
		this->saldo = 0;
		std::cout << "Saldo inicial: " << formatearConComas(this->saldo) << std::endl;
		// No se valida por que el saldo inicial es cero (0)

		// Se obtiene la fecha del sistema con la clase Fecha.cpp
		Fecha fechaSistema;
		this->fechaApertura = fechaSistema.obtenerFechaFormateada();
		std::cout << "Fecha de apertura: " << this->fechaApertura << std::endl;

		// Al crear una nueva cuenta se le asigna el estado de la cuenta como activa
		this->estadoCuenta = "Activa";
		std::cout << "Estado de la cuenta: " << this->estadoCuenta << std::endl;
		// No se valida por que el estado de la cuenta es activa por defecto

		// Se aplica automaticamente el interes a la cuenta del 5% anual
		this->saldo += calcularInteres();
		std::cout << "Interes aplicado: " << formatearConComas(calcularInteres()) << std::endl;
		std::cout << "Saldo total: " << formatearConComas(this->saldo) << std::endl;

		// Se pide el monto minimo requerido para la cuenta de ahorros
		// CORRECCIÓN: ingresarMonto() ya retorna un double, no necesitamos convertirlo
		double montoMinimoVal = ingresarMonto();

		// Validar que el monto sea positivo
		while (montoMinimoVal < 0) {
			std::cout << "El monto debe ser mayor a cero. ";
			montoMinimoVal = ingresarMonto();
		}

		this->montoMinimo = static_cast<T>(montoMinimoVal);

		// Se muestra el monto minimo requerido para la cuenta de ahorros
		auto formatearConComas = [](double valor) -> std::string {
			std::ostringstream oss;
			oss.imbue(std::locale("en_US.UTF-8")); // Configura la localización para manejar separadores de miles
			oss << std::fixed;
			oss << std::setprecision(2); // Establece la precisión a 2 decimales
			oss << valor; // Aplica formato con precisión de 2 decimales
			return oss.str();
			};
		// usando la funcion lambda formatearConComas
		std::cout << "Monto minimo: " << formatearConComas(this->montoMinimo) << std::endl;

		// Se muestra la informacion de la cuenta final
		mostrarInformacion();
	}


	// Función que formatea con comas y 2 decimales
	std::string formatearConComas(double valor) const {
		std::ostringstream oss;
		oss.imbue(std::locale("")); // Usa la configuración local del sistema
		oss << std::fixed << std::setprecision(2) << valor;
		return oss.str();
	}

	bool esNumeroValido(const std::string& str) {
		bool tienePunto = false;
		if (str.empty()) return false;
		for (size_t i = 0; i < str.length(); ++i) {
			if (isdigit(str[i])) continue;
			if (str[i] == '.' && !tienePunto && i != 0) {
				tienePunto = true;
				continue;
			}
			return false; // Caracter inválido
		}
		return true;
	}

	// Función para ingresar monto con formato
	double ingresarMonto() {
		std::string entrada;
		bool tienePunto = false;
		int digitosDecimales = 0;
		RegresarMenu();

		std::cout << "Ingrese el monto para la cuenta (ejemplo: 1000.23): ";

		while (true) {
			char tecla = _getch();

			// Detectar Ctrl+V
			if (tecla == 22) {
				std::string pegado = Validar::leerDesdePortapapeles();
				if (Validar::ValidarNumeroConDosDecimales(pegado)) {
					try {
						double valor = std::stod(pegado);
						if (valor > 0) {
							entrada = pegado;
							std::cout << "\rIngrese el monto para la cuenta (ejemplo: 1000.23): " << entrada;
							std::cout << std::endl;
							return valor;
						}
					}
					catch (const std::exception& e) {
						std::cout << "\nError en conversión del portapapeles: " << e.what() << std::endl;
					}
				}
				std::cout << "\nFormato inválido (portapapeles). Ingrese nuevamente (ejemplo: 1000.23): ";
				entrada.clear();
				tienePunto = false;
				digitosDecimales = 0;
				continue;
			}

			// ENTER
			if (tecla == 13) {
				if (!entrada.empty()) {
					if (Validar::ValidarNumeroConDosDecimales(entrada)) {
						try {
							double valor = std::stod(entrada);
							if (valor > 0) {
								std::cout << std::endl;
								return valor;
							}
						}
						catch (const std::exception& e) {
							std::cout << "\nError en conversión: " << e.what() << std::endl;
						}
					}
				}

				std::cout << "\nFormato inválido o monto <= 0. Ingrese nuevamente (ejemplo: 1000.23): ";
				entrada.clear();
				tienePunto = false;
				digitosDecimales = 0;
				continue;
			}

			// BACKSPACE
			if (tecla == 8 && !entrada.empty()) {
				if (entrada.back() == '.') {
					tienePunto = false;
				}
				else if (tienePunto && digitosDecimales > 0) {
					--digitosDecimales;
				}
				entrada.pop_back();
				std::cout << "\rIngrese el monto para la cuenta (ejemplo: 1000.23): " << std::string(20, ' ') << "\r";
				std::cout << "Ingrese el monto para la cuenta (ejemplo: 1000.23): " << entrada;
				continue;
			}

			// Ignorar teclas especiales
			if (tecla == 0 || tecla == -32) {
                // Replace the line causing the error with the following code to handle the return value of _getch():
                char tecla = _getch(); // Capture the return value of _getch()
				continue;
			}

			// Dígitos
			if (isdigit(tecla)) {
				if (tienePunto && digitosDecimales == 2) continue;
				if (tienePunto) ++digitosDecimales;
				entrada += tecla;
				std::cout << tecla;
			}

			// Punto decimal
			else if (tecla == '.' && !tienePunto && !entrada.empty()) {
				tienePunto = true;
				entrada += tecla;
				std::cout << tecla;
			}
		}

		// Este punto no debería alcanzarse normalmente
		return 0.0;
	}

	// Función para formatear el monto con comas y 2 decimales
	std::string formatearMonto(double monto) {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << monto;
		std::string str = oss.str();

		int punto = str.find('.');
		std::string parteEntera = str.substr(0, punto);
		std::string decimales = str.substr(punto); // incluye el punto

		std::string resultado;
		int count = 0;
		for (int i = parteEntera.length() - 1; i >= 0; --i) {
			resultado.insert(0, 1, parteEntera[i]);
			count++;
			if (count == 3 && i != 0) {
				resultado.insert(0, 1, ',');
				count = 0;
			}
		}

		return resultado + decimales;
	}

	// Función para copiar texto al portapapeles
	std::string leerDesdePortapapeles() {
		if (!OpenClipboard(nullptr)) return "";
		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData == nullptr) {
			CloseClipboard();
			return "";
		}

		char* pszText = static_cast<char*>(GlobalLock(hData));
		if (pszText == nullptr) {
			CloseClipboard();
			return "";
		}

		std::string text(pszText);
		GlobalUnlock(hData);
		CloseClipboard();

		return text;
	}

	// función para regresar al menú inicial
	void RegresarMenu() {
		char opcion;
		std::cout << "Si desea regresar ingrese R, sino E: ";
		std::cin >> opcion;
		if (opcion == 'R' || opcion == 'r') {
			// Aquí podrías limpiar pantalla o pausar si lo deseas
			return; // Regresa al menú (sale de la función)
		}
		// Si el usuario ingresa 'E' o cualquier otra cosa, simplemente continúa
	}

};
#endif // CUENTAAHORROS_H
