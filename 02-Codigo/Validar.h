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
 * @brief Tipos de entrada para validación de teclas.
 */
enum class TipoEntrada {
    NUMERICO_CEDULA,   ///< Solo números para cédula.
    NUMERICO_CUENTA,   ///< Solo números para cuenta.
    ALFABETICO,        ///< Solo letras.
    ALFANUMERICO,      ///< Letras y números.
    CORREO,            ///< Formato de correo electrónico.
    TELEFONO           ///< Formato de teléfono.
};

/**
 * @class Validar
 * @brief Clase con métodos estáticos para validación de datos y utilidades de entrada/salida.
 */
class Validar {
public:
#pragma region VALIDACIONES PARA CUENTA
    /**
     * @brief Valida que el número de cuenta sea válido.
     * @param numero Número de cuenta a validar.
     * @return true si es válido, false en caso contrario.
     */
    static bool ValidarNumeroCuenta(const std::string numero);

    /**
     * @brief Valida que el saldo sea válido (entero, no decimal).
     * @param saldoStr Saldo a validar como string.
     * @return true si es válido, false en caso contrario.
     */
    static bool ValidarSaldo(const std::string& saldoStr);

    /**
     * @brief Valida el estado de la cuenta.
     * @param estado Estado a validar.
     * @return true si es válido, false en caso contrario.
     */
    static bool ValidarEstadoCuenta(const std::string& estado);

    /**
     * @brief Valida el tipo de cuenta (ahorros o corriente).
     * @param tipo Tipo de cuenta.
     * @return true si es válido, false en caso contrario.
     */
    static bool ValidarTipoCuenta(const std::string& tipo);

    /**
     * @brief Valida el tipo de transacción (retiro o depósito).
     * @param tipo Tipo de transacción.
     * @return true si es válido, false en caso contrario.
     */
    static bool ValidarTipoTransaccion(const std::string& tipo);

    /**
     * @brief Valida el monto/número de transacción (solo números enteros).
     * @param monto Monto a validar.
     * @return true si es válido, false en caso contrario.
     */
    static bool ValidarMontoTransaccion(int monto);
#pragma endregion

    /**
     * @brief Valida el formato de la fecha.
     * @param fecha Fecha a validar.
     * @return true si es válida, false en caso contrario.
     */
    static bool ValidarFecha(const std::string& fecha);

    /**
     * @brief Valida un número con dos decimales (para monto o saldo).
     * @param monto Monto a validar como string.
     * @return true si es válido, false en caso contrario.
     */
    static bool ValidarNumeroConDosDecimales(const std::string& monto);

    /**
     * @brief Lee un valor numérico desde el portapapeles.
     * @return Valor leído como string.
     */
    static std::string leerDesdePortapapeles();

#pragma region VALIDACIONES PARA PERSONA
    /**
     * @brief Valida que el nombre del cliente sea válido (solo letras y espacios).
     * @param nombre Nombre a validar.
     * @return true si es válido, false en caso contrario.
     */
    static bool ValidarNombrePersona(const std::string& nombre);

    /**
     * @brief Valida el número de cédula (10 dígitos).
     * @param cedula Cédula a validar.
     * @return true si es válida, false en caso contrario.
     */
    static bool ValidarCedula(const std::string& cedula);

    /**
     * @brief Verifica si todos los dígitos de la cédula son iguales.
     * @param cedula Cédula a verificar.
     * @return true si todos los dígitos son iguales, false en caso contrario.
     */
    static bool todosLosDigitosIguales(const std::string& cedula);

    // Métodos comentados (puedes documentar si los usas):
    /*
    static bool ValidarCelular(const std::string& celular);
    static bool ValidarCorreo(const std::string& correo);
    static bool ValidarFechaNacimiento(const std::string& fechaNacimiento);
    */

    /**
     * @brief Valida la tecla ingresada según el tipo de entrada.
     * @param tecla Tecla a validar.
     * @param tipo Tipo de entrada.
     * @return true si la tecla es válida, false en caso contrario.
     */
    static bool ValidarTecla(char tecla, TipoEntrada tipo);

    /**
     * @brief Solicita y valida la lectura de un número de cuenta.
     * @return Número de cuenta válido como string.
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
     * @brief Genera un nombre de respaldo único.
     * @param rutaDirectorio Ruta del directorio.
     * @param fechaFormateada Fecha formateada para el nombre.
     * @return Nombre de respaldo único como string.
     */
    static std::string generarNombreConIndice(const std::string& rutaDirectorio, const std::string& fechaFormateada);
};

#endif // VALIDAR_H