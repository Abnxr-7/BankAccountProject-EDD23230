#pragma once
// Validar.h
#ifndef VALIDAR_H
#define VALIDAR_H

#include <iostream>
#include <string>
#include <regex>
#include <stdexcept>
#include <Windows.h>

/**
 * @enum TipoEntrada
 * @brief Tipos de entrada para validaci�n de teclas.
 */
enum class TipoEntrada {
    NUMERICO_CEDULA,   ///< Solo n�meros para c�dula.
    NUMERICO_CUENTA,   ///< Solo n�meros para cuenta.
    ALFABETICO,        ///< Solo letras.
    ALFANUMERICO,      ///< Letras y n�meros.
    CORREO,            ///< Formato de correo electr�nico.
    TELEFONO           ///< Formato de tel�fono.
};

/**
 * @class Validar
 * @brief Clase con m�todos est�ticos para validaci�n de datos y utilidades de entrada/salida.
 */
class Validar {
public:
#pragma region VALIDACIONES PARA CUENTA
    /**
     * @brief Valida que el n�mero de cuenta sea v�lido.
     * @param numero N�mero de cuenta a validar.
     * @return true si es v�lido, false en caso contrario.
     */
    static bool ValidarNumeroCuenta(const std::string numero);

    /**
     * @brief Valida que el saldo sea v�lido (entero, no decimal).
     * @param saldoStr Saldo a validar como string.
     * @return true si es v�lido, false en caso contrario.
     */
    static bool ValidarSaldo(const std::string& saldoStr);

    /**
     * @brief Valida el estado de la cuenta.
     * @param estado Estado a validar.
     * @return true si es v�lido, false en caso contrario.
     */
    static bool ValidarEstadoCuenta(const std::string& estado);

    /**
     * @brief Valida el tipo de cuenta (ahorros o corriente).
     * @param tipo Tipo de cuenta.
     * @return true si es v�lido, false en caso contrario.
     */
    static bool ValidarTipoCuenta(const std::string& tipo);

    /**
     * @brief Valida el tipo de transacci�n (retiro o dep�sito).
     * @param tipo Tipo de transacci�n.
     * @return true si es v�lido, false en caso contrario.
     */
    static bool ValidarTipoTransaccion(const std::string& tipo);

    /**
     * @brief Valida el monto/n�mero de transacci�n (solo n�meros enteros).
     * @param monto Monto a validar.
     * @return true si es v�lido, false en caso contrario.
     */
    static bool ValidarMontoTransaccion(int monto);
#pragma endregion

    /**
     * @brief Valida el formato de la fecha.
     * @param fecha Fecha a validar.
     * @return true si es v�lida, false en caso contrario.
     */
    static bool ValidarFecha(const std::string& fecha);

    /**
     * @brief Valida un n�mero con dos decimales (para monto o saldo).
     * @param monto Monto a validar como string.
     * @return true si es v�lido, false en caso contrario.
     */
    static bool ValidarNumeroConDosDecimales(const std::string& monto);

    /**
     * @brief Lee un valor num�rico desde el portapapeles.
     * @return Valor le�do como string.
     */
    static std::string leerDesdePortapapeles();

#pragma region VALIDACIONES PARA PERSONA
    /**
     * @brief Valida que el nombre del cliente sea v�lido (solo letras y espacios).
     * @param nombre Nombre a validar.
     * @return true si es v�lido, false en caso contrario.
     */
    static bool ValidarNombrePersona(const std::string& nombre);

    /**
     * @brief Valida el n�mero de c�dula (10 d�gitos).
     * @param cedula C�dula a validar.
     * @return true si es v�lida, false en caso contrario.
     */
    static bool ValidarCedula(const std::string& cedula);

    /**
     * @brief Verifica si todos los d�gitos de la c�dula son iguales.
     * @param cedula C�dula a verificar.
     * @return true si todos los d�gitos son iguales, false en caso contrario.
     */
    static bool todosLosDigitosIguales(const std::string& cedula);

    // M�todos comentados (puedes documentar si los usas):
    /*
    static bool ValidarCelular(const std::string& celular);
    static bool ValidarCorreo(const std::string& correo);
    static bool ValidarFechaNacimiento(const std::string& fechaNacimiento);
    */

    /**
     * @brief Valida la tecla ingresada seg�n el tipo de entrada.
     * @param tecla Tecla a validar.
     * @param tipo Tipo de entrada.
     * @return true si la tecla es v�lida, false en caso contrario.
     */
    static bool ValidarTecla(char tecla, TipoEntrada tipo);

    /**
     * @brief Solicita y valida la lectura de un n�mero de cuenta.
     * @return N�mero de cuenta v�lido como string.
     */
    static std::string ValidarLeerNumeroCuenta();
#pragma endregion

    /**
     * @brief Verifica si un archivo ya existe.
     * @param rutaArchivo Ruta del archivo.
     * @return true si el archivo existe, false en caso contrario.
     */
    static bool archivoExiste(const std::string& rutaArchivo);

    /**
     * @brief Genera un nombre de respaldo �nico.
     * @param rutaDirectorio Ruta del directorio.
     * @param fechaFormateada Fecha formateada para el nombre.
     * @return Nombre de respaldo �nico como string.
     */
    static std::string generarNombreConIndice(const std::string& rutaDirectorio, const std::string& fechaFormateada);
};

#endif // VALIDAR_H