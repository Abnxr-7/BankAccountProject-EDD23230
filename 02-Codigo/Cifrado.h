#pragma once
#ifndef CIFRADO_H
#define CIFRADO_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

/**
 * @class Cifrado
 * @brief Proporciona métodos para cifrar y descifrar archivos y datos del banco usando XOR.
 */
class Cifrado {
public:
    /**
     * @brief Cifra un archivo usando el algoritmo XOR.
     * @param rutaEntrada Ruta del archivo de entrada.
     * @param rutaSalida Ruta del archivo de salida cifrado.
     * @param clave Clave de cifrado (carácter).
     */
    static void CifrarArchivo(const std::string& rutaEntrada, const std::string& rutaSalida, char clave);

    /**
     * @brief Descifra un archivo previamente cifrado con XOR.
     * @param rutaEntrada Ruta del archivo cifrado de entrada.
     * @param rutaSalida Ruta del archivo de salida descifrado.
     * @param valor Clave de descifrado (carácter).
     */
    static void desifrarArchivo(const std::string& rutaEntrada, const std::string& rutaSalida, char valor);

    /**
     * @brief Cifra y guarda los datos del banco en un archivo.
     * @param banco Referencia al objeto Banco cuyos datos se van a cifrar y guardar.
     * @param nombreArchivo Nombre del archivo de salida.
     * @param claveCifrado Clave de cifrado (carácter).
     */
    static void cifrarYGuardarDatos(const class Banco& banco, const std::string& nombreArchivo, char claveCifrado);

    /**
     * @brief Descifra y carga los datos del banco desde un archivo.
     * @param banco Referencia al objeto Banco donde se cargarán los datos.
     * @param nombreArchivo Nombre del archivo cifrado.
     * @param claveCifrado Clave de descifrado (carácter).
     * @return true si la operación fue exitosa, false en caso contrario.
     */
    static bool descifrarYCargarDatos(class Banco& banco, const std::string& nombreArchivo, char claveCifrado);

    /**
     * @brief Descifra los datos del banco sin cargarlos, según la opción indicada.
     * @param banco Referencia constante al objeto Banco.
     * @param nombreArchivo Nombre del archivo cifrado.
     * @param claveCifrado Clave de descifrado (carácter).
     * @param opcion Opción de operación adicional.
     * @return true si la operación fue exitosa, false en caso contrario.
     */
    static bool descifrarSinCargarDatos(const Banco& banco, const std::string& nombreArchivo, char claveCifrado, int opcion);
};

#endif // CIFRADO_H