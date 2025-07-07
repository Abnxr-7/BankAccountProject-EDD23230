#pragma once  
#ifndef PERSONA_H  
#define PERSONA_H  

#include <iostream>
#include <string>  
#include "CuentaAhorros.h"  
#include "CuentaCorriente.h"  
#include <functional>

/**
 * @namespace PersonaUI
 * @brief Funciones utilitarias para la interacci�n de usuario en la gesti�n de personas.
 */
namespace PersonaUI {
    /**
     * @brief Muestra un men� de selecci�n S�/No.
     * @param mensaje Mensaje a mostrar al usuario.
     * @return true si el usuario selecciona "S�", false si selecciona "No".
     */
    extern const std::function<bool(const std::string&)> seleccionarSiNo;

    /**
     * @brief Solicita el ingreso de un monto con validaci�n en tiempo real.
     * @param min Valor m�nimo permitido.
     * @param max Valor m�ximo permitido.
     * @param mensaje Mensaje a mostrar al usuario.
     * @return Monto ingresado por el usuario.
     */
    extern const std::function<double(double, double, const std::string&)> ingresarMonto;
}

using namespace std;

/**
 * @class Persona
 * @brief Representa una persona con datos personales y cuentas bancarias.
 */
class Persona {
private:
    string cedula;                  ///< C�dula de la persona.
    string nombres;                 ///< Nombres de la persona.
    string apellidos;               ///< Apellidos de la persona.
    string fechaNacimiento;         ///< Fecha de nacimiento.
    string correo;                  ///< Correo electr�nico.
    string direccion;               ///< Direcci�n.
    CuentaAhorros* cabezaAhorros;   ///< Puntero a la cabeza de la lista de cuentas de ahorros.
    CuentaCorriente* cabezaCorriente; ///< Puntero a la cabeza de la lista de cuentas corrientes.
    int numCuentas = 0;             ///< N�mero de cuentas de ahorros.
    int numCorrientes = 0;          ///< N�mero de cuentas corrientes.
    bool isDestroyed = false;       ///< Indicador para evitar uso despu�s de destrucci�n.

public:
    /**
     * @brief Constructor por defecto.
     */
    Persona() : cabezaAhorros(nullptr), cabezaCorriente(nullptr), numCuentas(0), numCorrientes(0), isDestroyed(false) {}

    /**
     * @brief Constructor con par�metros.
     * @param cedula C�dula de la persona.
     * @param nombres Nombres de la persona.
     * @param apellidos Apellidos de la persona.
     * @param fechaNacimiento Fecha de nacimiento.
     * @param correo Correo electr�nico.
     * @param direccion Direcci�n.
     */
    Persona(const string& cedula, const string& nombres, const string& apellidos,
        const string& fechaNacimiento, const string& correo, const string& direccion)
        : cedula(cedula), nombres(nombres), apellidos(apellidos),
        fechaNacimiento(fechaNacimiento), correo(correo), direccion(direccion),
        cabezaAhorros(nullptr), cabezaCorriente(nullptr), numCuentas(0), numCorrientes(0), isDestroyed(false) {
    }

    /**
     * @brief Destructor. Libera la memoria de las cuentas asociadas.
     */
    ~Persona() {
        // Liberar memoria de las cuentas de ahorros  
        while (cabezaAhorros != nullptr) {
            CuentaAhorros* temp = cabezaAhorros;
            cabezaAhorros = static_cast<CuentaAhorros*>(cabezaAhorros->getSiguiente());
            delete temp;
        }

        // Liberar memoria de las cuentas corrientes
        while (cabezaCorriente != nullptr) {
            CuentaCorriente* temp = cabezaCorriente;
            cabezaCorriente = static_cast<CuentaCorriente*>(cabezaCorriente->getSiguiente());
            delete temp;
        }
        isDestroyed = true; // Marcar como destruido  
    }

    /**
     * @brief Verifica si la instancia es v�lida (no destruida).
     * @return true si la instancia es v�lida, false si fue destruida.
     */
    bool isValidInstance() const { return !isDestroyed; }

    // Setters  
    /**
     * @brief Establece la c�dula de la persona.
     * @param cedula Nueva c�dula.
     * @return true si se asign� correctamente.
     */
    bool setCedula(const string& cedula) { this->cedula = cedula; return true; }

    /**
     * @brief Establece los nombres de la persona.
     * @param nombres Nuevos nombres.
     * @return true si se asign� correctamente.
     */
    bool setNombres(const string& nombres) { this->nombres = nombres; return true; }

    /**
     * @brief Establece los apellidos de la persona.
     * @param apellidos Nuevos apellidos.
     * @return true si se asign� correctamente.
     */
    bool setApellidos(const string& apellidos) { this->apellidos = apellidos; return true; }

    /**
     * @brief Establece la fecha de nacimiento.
     * @param fechaNacimiento Nueva fecha de nacimiento.
     * @return true si se asign� correctamente.
     */
    bool setFechaNacimiento(const string& fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; return true; }

    /**
     * @brief Establece el correo electr�nico.
     * @param correo Nuevo correo.
     * @return true si se asign� correctamente.
     */
    bool setCorreo(const string& correo) { this->correo = correo; return true; }

    /**
     * @brief Establece la direcci�n.
     * @param direccion Nueva direcci�n.
     * @return true si se asign� correctamente.
     */
    bool setDireccion(const string& direccion) { this->direccion = direccion; return true; }

    /**
     * @brief Establece el n�mero de cuentas de ahorros.
     * @param numCuentas Nuevo n�mero de cuentas.
     */
    void setNumeCuentas(int numCuentas) { this->numCuentas = numCuentas; }

    /**
     * @brief Establece el n�mero de cuentas corrientes.
     * @param numCorrientes Nuevo n�mero de cuentas corrientes.
     */
    void setNumCorrientes(int numCorrientes) { this->numCorrientes = numCorrientes; }

    /**
     * @brief Establece la cabeza de la lista de cuentas de ahorros.
     * @param nuevaCabeza Puntero a la nueva cabeza.
     * @return Puntero a la cabeza de la lista.
     */
    CuentaAhorros* setCabezaAhorros(CuentaAhorros* nuevaCabeza) {
        if (nuevaCabeza) {
            nuevaCabeza->setSiguiente(cabezaAhorros);
            nuevaCabeza->setAnterior(nullptr);

            if (cabezaAhorros)
                cabezaAhorros->setAnterior(nuevaCabeza);
        }

        cabezaAhorros = nuevaCabeza;
        return cabezaAhorros;
    }

    /**
     * @brief Establece la cabeza de la lista de cuentas corrientes.
     * @param nuevaCabeza Puntero a la nueva cabeza.
     * @return Puntero a la cabeza de la lista.
     */
    CuentaCorriente* setCabezaCorriente(CuentaCorriente* nuevaCabeza) {
        if (nuevaCabeza)
        {
            nuevaCabeza->setSiguiente(cabezaCorriente);
            nuevaCabeza->setAnterior(nullptr);
            if (cabezaCorriente)
                cabezaCorriente->setAnterior(nuevaCabeza);
        }
        cabezaCorriente = nuevaCabeza;
        return cabezaCorriente;
    }

    // Getters  
    /**
     * @brief Obtiene la c�dula de la persona.
     * @return C�dula.
     */
    string getCedula() const { return this->cedula; }

    /**
     * @brief Obtiene los nombres de la persona.
     * @return Nombres.
     */
    string getNombres() const { return this->nombres; }

    /**
     * @brief Obtiene los apellidos de la persona.
     * @return Apellidos.
     */
    string getApellidos() const { return this->apellidos; }

    /**
     * @brief Obtiene la fecha de nacimiento.
     * @return Fecha de nacimiento.
     */
    string getFechaNacimiento() const { return this->fechaNacimiento; }

    /**
     * @brief Obtiene el correo electr�nico.
     * @return Correo electr�nico.
     */
    string getCorreo() const { return this->correo; }

    /**
     * @brief Obtiene la direcci�n.
     * @return Direcci�n.
     */
    string getDireccion() const { return this->direccion; }

    /**
     * @brief Obtiene el n�mero de cuentas de ahorros.
     * @return N�mero de cuentas de ahorros.
     */
    int getNumCuentas() const { return this->numCuentas; }

    /**
     * @brief Obtiene el n�mero de cuentas corrientes.
     * @return N�mero de cuentas corrientes.
     */
    int getNumCorrientes() const { return this->numCorrientes; }

    /**
     * @brief Obtiene el puntero a la cabeza de la lista de cuentas de ahorros.
     * @return Puntero a la cabeza de la lista de cuentas de ahorros.
     */
    CuentaAhorros* getCabezaAhorros() const { return this->cabezaAhorros; }

    /**
     * @brief Obtiene el puntero a la cabeza de la lista de cuentas corrientes.
     * @return Puntero a la cabeza de la lista de cuentas corrientes.
     */
    CuentaCorriente* getCabezaCorriente() const { return this->cabezaCorriente; }

    /**
     * @brief M�todo para ingresar los datos de la persona.
     */
    void ingresarDatos();

    /**
     * @brief M�todo para ingresar los datos de la persona, validando la c�dula ingresada previamente.
     * @param cedulaEsperada C�dula que se espera validar.
     */
    void ingresarDatos(const std::string& cedulaEsperada);

    /**
     * @brief M�todo para ingresar la c�dula de la persona.
     * @param cedula Referencia a la c�dula a ingresar.
     * @return C�dula ingresada.
     */
    std::string ingresarCedula(std::string& cedula);

    /**
     * @brief M�todo para ingresar los nombres de la persona.
     * @param nombres Referencia a los nombres a ingresar.
     * @return Nombres ingresados.
     */
    std::string ingresarNombres(std::string& nombres) const;

    /**
     * @brief M�todo para ingresar los apellidos de la persona.
     * @param apellidos Referencia a los apellidos a ingresar.
     * @return Apellidos ingresados.
     */
    std::string ingresarApellidos(std::string& apellidos) const;

    /**
     * @brief M�todo para ingresar la fecha de nacimiento de la persona.
     * @param fechaNacimiento Referencia a la fecha de nacimiento a ingresar.
     * @return Fecha de nacimiento ingresada.
     */
    std::string ingresarFechaNacimiento(std::string& fechaNacimiento);

    /**
     * @brief M�todo para ingresar el correo de la persona.
     * @param correo Referencia al correo a ingresar.
     * @return Correo ingresado.
     */
    std::string ingresarCorreo(std::string& correo) const;

    /**
     * @brief M�todo para ingresar la direcci�n de la persona.
     * @param direccion Referencia a la direcci�n a ingresar.
     * @return Direcci�n ingresada.
     */
    std::string ingresarDireccion(std::string& direccion) const;

    /**
     * @brief M�todo para corregir los datos de la persona.
     * @return true si se repite el ingreso de datos, false si se finaliza.
     */
    bool corregirDatos();

    /**
     * @brief Muestra los datos de la persona.
     */
    void mostrarDatos() const;

    /**
     * @brief Muestra las cuentas de la persona, filtrando por tipo de cuenta.
     * @param tipoCuenta Tipo de cuenta a mostrar ("Ahorros", "Corriente", "Ambas").
     * @return N�mero de cuentas encontradas.
     */
    int mostrarCuentas(const std::string& tipoCuenta) const;

    /**
     * @brief Guarda los datos de la persona en un archivo.
     */
    void guardarEnArchivo() const;

    /**
     * @brief Busca cuentas por un criterio espec�fico.
     * @param criterioBusqueda Criterio de b�squeda.
     * @param numeroCuenta N�mero de cuenta a buscar.
     * @param fechaApertura Fecha de apertura a buscar.
     * @param saldo Saldo m�nimo a buscar.
     * @return N�mero de cuentas encontradas.
     */
    int buscarPersonaPorCriterio(const std::string& criterioBusqueda, const std::string& numeroCuenta, const std::string& fechaApertura, double saldo) const;

    /**
     * @brief Busca cuentas por fecha de apertura.
     * @param fechaApertura Fecha de apertura a buscar.
     */
    void buscarPersonaPorFecha(const std::string& fechaApertura) const;

    /**
     * @brief Busca una persona por n�mero de cuenta.
     * @param numeroCuenta N�mero de cuenta a buscar.
     * @return N�mero de cuentas encontradas.
     */
    int buscarPersonaPorCuentas(const string& numeroCuenta) const;

    /**
     * @brief Guarda las cuentas de la persona en un archivo.
     * @param archivo Flujo de archivo de salida.
     * @param tipo Tipo de cuenta ("AHORROS" o "CORRIENTE").
     * @return N�mero de cuentas guardadas.
     */
    int guardarCuentas(std::ofstream& archivo, std::string tipo) const;

    /**
     * @brief Crea y agrega una cuenta de ahorros a la persona.
     * @param nuevaCuenta Puntero a la nueva cuenta de ahorros.
     * @param cedulaEsperada C�dula que se espera validar.
     * @return true si la cuenta fue creada y agregada correctamente.
     */
    bool crearAgregarCuentaAhorros(CuentaAhorros* nuevaCuenta, const std::string& cedulaEsperada);

    /**
     * @brief Crea y agrega una cuenta corriente a la persona.
     * @param nuevaCuenta Puntero a la nueva cuenta corriente.
     * @param cedulaEsperada C�dula que se espera validar.
     * @return true si la cuenta fue creada y agregada correctamente.
     */
    bool crearAgregarCuentaCorriente(CuentaCorriente* nuevaCuenta, const std::string& cedulaEsperada);

    /**
     * @brief Crea una cuenta de ahorros sin ingresar datos de la persona.
     * @param nuevaCuenta Puntero a la nueva cuenta de ahorros.
     * @param cedulaEsperada C�dula que se espera validar.
     * @return true si la cuenta fue creada correctamente.
     */
    bool crearSoloCuentaAhorros(CuentaAhorros* nuevaCuenta, const std::string& cedulaEsperada);

    /**
     * @brief Crea una cuenta corriente sin ingresar datos de la persona.
     * @param nuevaCuenta Puntero a la nueva cuenta corriente.
     * @param cedulaEsperada C�dula que se espera validar.
     * @return true si la cuenta fue creada correctamente.
     */
    bool crearSoloCuentaCorriente(CuentaCorriente* nuevaCuenta, const std::string& cedulaEsperada);

    /**
     * @brief Crea un n�mero de cuenta �nico para una nueva cuenta.
     * @param nuevaCuenta Puntero a la nueva cuenta.
     * @param sucursal C�digo de la sucursal.
     * @return N�mero de cuenta generado.
     */
    std::string crearNumeroCuenta(Cuenta<double>* nuevaCuenta, const std::string& sucursal);

    /**
     * @brief Permite seleccionar la sucursal de la cuenta.
     * @return C�digo de la sucursal seleccionada.
     */
    std::string seleccionSucursal();

    /**
     * @brief Devuelve el mensaje de ingreso de datos.
     * @return Mensaje de ingreso de datos.
     */
    std::string msgIngresoDatos() const;

    /*
    // Metodo unificado para crear y agregar cuenta de ahorros
    bool crearYAgregarCuentaAhorros(Persona* persona) {
        // Verificar limite
        if (numCuentas >= 5) {
            std::cout << "No puede tener mas de 5 cuentas de ahorros.\n";
            return false;
        }

        // Crear la cuenta directamente como objeto dinamico
        CuentaAhorros* nuevaCuenta;

        // Llamar al metodo crearCuenta() del objeto nuevaCuenta
        // que configura numero de cuenta, fecha, saldo inicial, etc.
        nuevaCuenta->crearCuenta(persona);

        // Crear el nodo y agregarlo a la lista directamente
        NodoCuentaAhorros* nuevo = new NodoCuentaAhorros(nuevaCuenta);

        // Verificacion de seguridad
        if (nuevo->cuenta == nullptr) {
            std::cout << "[ERROR] Cuenta no inicializada" << std::endl;
            delete nuevo;
            return false;
        }

        // Agregar a la lista con las validaciones normales
        nuevo->siguiente = cabezaAhorros;
        nuevo->anterior = nullptr;
        if (cabezaAhorros != nullptr) {
            cabezaAhorros->anterior = nuevo;
        }
        cabezaAhorros = nuevo;
        numCuentas++;

        std::cout << "Cuenta de Ahorros creada y agregada con exito." << std::endl;
        return true;
    }

    // Metodo unificado para crear y agregar cuenta corriente
    bool crearYAgregarCuentaCorriente(Persona* persona) {
        // No hay limite para cuentas corrientes (a diferencia de las de ahorro)

        // Crear la cuenta directamente como objeto dinamico
        CuentaCorriente* nuevaCuenta;

        // Llamar al metodo crearCuenta() del objeto nuevaCuenta
        // que configura numero de cuenta, fecha, saldo inicial, etc.
        nuevaCuenta->crearCuenta(persona);

        // Crear el nodo y agregarlo a la lista directamente
        //NodoCuentaCorriente* nuevo = new NodoCuentaCorriente(nuevaCuenta);

        // Verificacion de seguridad
        if (nuevo->cuenta == nullptr) {
            std::cout << "[ERROR] Cuenta corriente no inicializada" << std::endl;
            delete nuevo;
            return false;
        }

        // Agregar a la lista con las validaciones normales
        nuevo->siguiente = cabezaCorriente;
        nuevo->anterior = nullptr;
        if (cabezaCorriente != nullptr) {
            cabezaCorriente->anterior = nuevo;
        }
        cabezaCorriente = nuevo;

        std::cout << "Cuenta Corriente creada y agregada con exito." << std::endl;
        return true;
    }

    void seleccionarFecha();
    }; */
};
#endif // PERSONA_H
