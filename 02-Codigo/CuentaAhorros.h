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
#include <climits> // For INT_MAX
#include <cmath>
#include "Cuenta.h"
#include "Validar.h" // Include validation class
#include "Cifrado.h" // Include encryption class
#include "Fecha.h"   // Include date class
#include "Utilidades.h" // Include utilities class
#include "NodoCuentaAhorros.h" // Add this include for the full node definition

// CuentaAhorros class that inherits from Cuenta<int>
class CuentaAhorros : public Cuenta<int> {
private:
	// Tasa de interes anual para la cuenta de ahorros
    int tasaInteres = 5;

	// Monto minimo requerido para la cuenta de ahorros
    double montoMinimo = 0;

public:
	// Contructor por defecto
    CuentaAhorros() : Cuenta<int>(), tasaInteres(0), montoMinimo(0) {}

	// Constructor con parametros
    CuentaAhorros(int numCuenta, int sal, std::string fecha, std::string estado, int tasa, double monto)
        : Cuenta<int>(numCuenta, sal, fecha, estado), tasaInteres(tasa), montoMinimo(monto) {}

	// Metodo para depositar dinero en una cuenta
    void depositar(int cantidad) override {
        this->saldo += cantidad;
    }

	// Metodo para retirar dinero de la cuenta
    void retirar(int cantidad) override {
        if (cantidad <= this->saldo) {
            this->saldo -= cantidad;
        }
        else {
            std::cout << "Fondos insuficientes." << std::endl;
        }
    }

	// Metodo para consultar el saldo de la cuenta
    int consultarSaldo() const override {
        return this->saldo;
    }

	// Metodo para consultar el estado de la cuenta
    std::string consultarEstado() const override {
        return this->estadoCuenta;
    }

	// Metodo para calcular el interes anual
    int calcularInteres() const {
        return static_cast<int>((this->saldo * tasaInteres) / 100); // Dividimos por 100
    }

	// Metodo sobreescrito para guardar la cuenta en un archivo
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

	// Metodo para cargar la cuenta desde un archivo
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

    // Metodo para crear una cuenta de ahorros
    void crearCuenta() override {
        system("cls");
        std::cout << "\n----- DATOS DE LA CUENTA -----\n" << std::endl;

        // Generar un numero de cuenta unico que se pueda almacenar en un int (maximo 9 digitos)
        // El valor maximo de int es aproximadamente 2.147.483.647 (unos 10 digitos)
        std::string numeroCuentaStr;
        numeroCuentaStr.clear();

        // Generamos un numero de 9 digitos para evitar overflow en int
        for (int i = 0; i < 9; ++i) {
            char digito = '0' + (rand() % 10);
            // El primer digito no debe ser cero
            if (i == 0 && digito == '0') {
                digito = '1' + (rand() % 9);
            }
            numeroCuentaStr += digito;
        }

        try {
            // Convertimos usando stoi que guarda directamente como int
            // stoll convierte a long long y luego el static_cast puede causar overflow
            this->numeroCuenta = std::stoi(numeroCuentaStr);

            // Verificamos que el numero sea positivo
            if (this->numeroCuenta <= 0) {
                // Si por alguna razon el numero es negativo o cero, usamos un valor predeterminado
                this->numeroCuenta = 100000000 + (rand() % 899999999); // Entre 100M y 999M
            }

            // Actualizamos la cadena para mostrar el numero real almacenado
            numeroCuentaStr = std::to_string(this->numeroCuenta);
        }
        catch (const std::exception& e) {
            std::cerr << "Error al convertir el numero de cuenta: " << e.what() << "\n";
            // Generamos un numero seguro en caso de error
            this->numeroCuenta = 100000000 + (rand() % 899999999); // Entre 100M y 999M
            numeroCuentaStr = std::to_string(this->numeroCuenta);
        }

        std::cout << "Numero de cuenta: " << numeroCuentaStr << std::endl;

        // Saldo inicial de la cuenta
        this->saldo = 0;
        std::cout << "Saldo inicial: $" << formatearConComas(this->saldo) << std::endl;

        // Fecha de apertura de la cuenta
        Fecha fechaSistema;
        this->fechaApertura = fechaSistema.obtenerFechaFormateada();
        std::cout << "Fecha de apertura: " << this->fechaApertura << std::endl;

        // Estado de la cuenta
        this->estadoCuenta = "Activa";
        std::cout << "Estado de la cuenta: " << this->estadoCuenta << std::endl;

        // 5% de interes anual
        this->saldo += calcularInteres();
        std::cout << "Interes aplicado: $" << formatearConComas(calcularInteres()) << std::endl;
        std::cout << "Saldo total: $" << formatearConComas(this->saldo) << std::endl;

        // Preguntar si desea ingresar un monto inicial a la cuenta
        std::cout << "\nDesea ingresar un monto inicial a su cuenta? " << std::endl;

        // Opciones para el menu
        int opcionSeleccionada = 0;
        bool continuar = true;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);

        while (continuar) {
            // Mostrar las opciones
            for (int i = 0; i < 2; i++) {
                COORD pos = { 5, static_cast<SHORT>(csbi.dwCursorPosition.Y + i + 1) };
                SetConsoleCursorPosition(hConsole, pos);

                if (i == opcionSeleccionada) {
                    SetConsoleTextAttribute(hConsole, 0x70); // Fondo gris, texto negro
                }

                std::string opcion = (i == 0) ? "Si" : "No";
                std::cout << opcion;

                SetConsoleTextAttribute(hConsole, 0x07); // Restaurar colores
            }

            // Capturar tecla
            int tecla = _getch();

            // Procesar la tecla
            if (tecla == 224 || tecla == 0) { // Tecla especial
                tecla = _getch();
                if (tecla == 72) { // Flecha arriba
                    opcionSeleccionada = (opcionSeleccionada > 0) ? opcionSeleccionada - 1 : 0;
                }
                else if (tecla == 80) { // Flecha abajo
                    opcionSeleccionada = (opcionSeleccionada < 1) ? opcionSeleccionada + 1 : 1;
                }
            }
            else if (tecla == 13) { // Enter
                continuar = false;
            }
        }

        // Si selecciono "Si", permitir ingreso de monto
        if (opcionSeleccionada == 0) {
            system("cls");
            std::cout << "Ingresando monto inicial a la cuenta..." << std::endl;
            std::cout << "Cuenta: " << this->numeroCuenta << std::endl;

            // Solicitar y validar el monto a ingresar
            double montoDeposito = ingresarMonto();

            // Validar que el monto sea valido
            while (montoDeposito <= 0) {
                std::cout << "El monto debe ser mayor a cero. ";
                montoDeposito = ingresarMonto();
            }

            // Realizar el deposito - Corregimos la conversion a centavos
            std::string entradaStr = std::to_string(montoDeposito);
            int centavos = 0;

            size_t puntoPos = entradaStr.find('.');
            if (puntoPos != std::string::npos) {
                // Si tiene punto decimal, procesamos por separado parte entera y decimal
                std::string parteEntera = entradaStr.substr(0, puntoPos);
                std::string parteDecimal = entradaStr.substr(puntoPos + 1);

                // Ajustamos la parte decimal a 2 digitos
                if (parteDecimal.length() == 1) parteDecimal += "0";
                else if (parteDecimal.length() > 2) parteDecimal = parteDecimal.substr(0, 2);

                // Convertimos a centavos
                centavos = std::stoi(parteEntera) * 100;
                if (!parteDecimal.empty()) {
                    centavos += std::stoi(parteDecimal);
                }
            }
            else {
                // Si es un numero entero, multiplicamos por 100
                centavos = static_cast<int>(montoDeposito * 100);
            }

            this->saldo += centavos;
            std::cout << "Deposito realizado con exito." << std::endl;
            std::cout << "Nuevo saldo: $" << formatearConComas(this->saldo) << std::endl;

            // Mostrar informacion actualizada
            std::cout << "\nPresione cualquier tecla para continuar...";
            int tecla = _getch();
            (void)tecla; // Ignora el valor de retorno explicitamente
        }

        // Setear los datos de la cuenta 
        setNumeroCuenta(this->numeroCuenta);
        setSaldo(this->saldo);
        setFechaApertura(this->fechaApertura);
        setEstadoCuenta(this->estadoCuenta);

        system("cls");
    }

	// Funcion para formatear el valor con comas y dos decimales
    std::string formatearConComas(int valorEnCentavos) const {
        // Convertir de centavos a valor decimal
        double valorReal = valorEnCentavos / 100.0;
        std::ostringstream oss;
        oss.imbue(std::locale("en_US.UTF-8")); // Usar formato americano: 1,234.56
        oss << std::fixed << std::setprecision(2) << valorReal;
        return oss.str();
    }
    std::string formatearConComas(double valor) const {
        std::ostringstream oss;
        oss.imbue(std::locale(""));
        oss << std::fixed << std::setprecision(2) << valor;
        return oss.str();
    }

	// Funcion para ingresar el monto minimo requerido para la cuenta
    double ingresarMonto() {
        std::string entrada;
        bool tienePunto = false;
        int digitosDecimales = 0;
        // Definimos el limite maximo de dinero permitido (15,000.00)
        const double LIMITE_MAXIMO = 15000.00;
        
        std::cout << "Ingrese el monto para la cuenta (max. $15,000.00): ";
        while (true) {
            char tecla = _getch();

            // Detecta Ctrl+V
            if (tecla == 22) {
                std::string pegado = Validar::leerDesdePortapapeles();
                if (Validar::ValidarNumeroConDosDecimales(pegado)) {
                    try {
                        double valor = std::stod(pegado);
                        if (valor > 0 && valor <= LIMITE_MAXIMO) {
                            entrada = pegado;
                            std::cout << "\rIngrese el monto para la cuenta (max. $15,000.00): " << entrada;
                            std::cout << std::endl;
                            return valor;
                        } else if (valor > LIMITE_MAXIMO) {
                            std::cout << "\nEl monto no puede exceder $15,000.00 \nIngrese nuevamente: ";
                            entrada.clear();
                            tienePunto = false;
                            digitosDecimales = 0;
                        }
                    }
                    catch (...) {}
                }
                std::cout << "\nFormato invalido (portapapeles). Ingrese nuevamente: ";
                entrada.clear();
                tienePunto = false;
                digitosDecimales = 0;
                continue;
            }

            // ENTER - Validamos y convertimos la entrada
            if (tecla == 13) {
                if (!entrada.empty()) {
                    if (Validar::ValidarNumeroConDosDecimales(entrada)) {
                        try {
                            double valor = std::stod(entrada);
                            if (valor > 0) {
                                // Validacion del limite maximo
                                if (valor > LIMITE_MAXIMO) {
                                    std::cout << "\nEl monto no puede exceder $15,000.00 \nIngrese nuevamente: ";
                                    entrada.clear();
                                    tienePunto = false;
                                    digitosDecimales = 0;
                                    continue;
                                }
                                std::cout << std::endl;
                                return valor;
                            }
                        }
                        catch (...) {}
                    }
                }
                std::cout << "\nFormato invalido o monto menor o igual a cero. \nIngrese nuevamente: ";
                entrada.clear();
                tienePunto = false;
                digitosDecimales = 0;
                continue;
            }

            // BACKSPACE - Borramos el ultimo caracter
            if (tecla == 8 && !entrada.empty()) {
                if (entrada.back() == '.') {
                    tienePunto = false;
                }
                else if (tienePunto && digitosDecimales > 0) {
                    --digitosDecimales;
                }
                entrada.pop_back();
                std::cout << "\rIngrese el monto para la cuenta (max. $15,000.00): " << std::string(40, ' ') << "\r";
                std::cout << "Ingrese el monto para la cuenta (max. $15,000.00): " << entrada;
                continue;
            }

            // Ignoramos teclas especiales
            if (tecla == 0 || tecla == -32) {
                int teclaCualquiera = _getch();
                (void)teclaCualquiera;
                continue;
            }

            // Digitos - Prevalidamos si el valor excede el limite
            if (isdigit(tecla)) {
                // Verificamos si al agregar este digito el numero excederia el limite
                std::string tmpEntrada = entrada + tecla;
                
                // Si hay punto decimal, solo verificamos si hay mas de 2 decimales
                if (tienePunto && digitosDecimales == 2) continue;
                
                // Si es un numero entero, verificamos si excede el limite
                if (!tienePunto && tmpEntrada.length() > 5) {
                    // Verificamos si es mayor a 15000
                    double tmpValor = std::stod(tmpEntrada);
                    if (tmpValor > LIMITE_MAXIMO) continue;
                }
                
                // Si tiene punto, verificamos considerando la parte decimal
                if (tienePunto) {
                    if (entrada.length() - entrada.find('.') - 1 >= 2) continue; // Ya tiene 2 decimales
                    if (entrada.length() > 0 && entrada.find('.') != std::string::npos) {
                        std::string parteEntera = entrada.substr(0, entrada.find('.'));
                        if (parteEntera.length() >= 5 && std::stod(parteEntera) >= 15000) continue;
                    }
                }
                
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
        return 0.0;
    }

    // En la clase CuentaAhorros, implementamos nuestro metodo para formatear el saldo
    std::string formatearSaldo() const override {
        return formatearConComas(this->saldo);
    }

    // Y modificamos mostrarInformacion para llamar a la version base y agregar informacion especifica
    void mostrarInformacion(const std::string& cedula = "", bool limpiarPantalla = true) const override {
        // Validacion basica
        if (this == nullptr) {
            return;
        }
        
        // Limpieza de pantalla solo si se solicita
        if (limpiarPantalla) {
            system("cls");
        }

        
        // Titulo con formato especifico para CuentaAhorros
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "          INFORMACION DE CUENTA DE AHORROS" << std::endl;
        std::cout << std::string(50, '=') << "\n" << std::endl;
        
        // Informacion del titular si esta disponible
        if (!cedula.empty()) {
            std::cout << "Cedula del titular: " << cedula << std::endl;
            std::cout << std::string(30, '-') << std::endl;
        }
        
        // Informacion comun
        std::cout << "Tipo de cuenta: AHORROS" << std::endl;
        std::cout << "Numero de cuenta: " << this->numeroCuenta << std::endl;
        std::cout << "Fecha de apertura: " << this->fechaApertura << std::endl;
        std::cout << "Estado: " << this->estadoCuenta << std::endl;
        std::cout << "Saldo actual: $" << formatearConComas(this->saldo) << std::endl;
        
        // Informacion especifica de CuentaAhorros
        std::cout << "Tasa de interes anual: " << tasaInteres << "%" << std::endl;
        
        // Pie de pagina
        std::cout << "\n" << std::string(50, '-') << std::endl;
        std::cout << "Presione cualquier tecla para continuar..." << std::endl;
        int tecla = _getch();
        (void)tecla; // Ignora el valor de retorno explicitamente
    }
};

#endif // CUENTAAHORROS_H
