#pragma once
#ifndef CIFRADO_H
#define CIFRADO_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

/**
 * @class Cifrado
 * @brief Proporciona m�todos para cifrar y descifrar archivos y datos del banco usando XOR.
 */
class Cifrado {
public:
    /**
     * @brief Cifra un archivo usando el algoritmo XOR.
     * @param rutaEntrada Ruta del archivo de entrada.
     * @param rutaSalida Ruta del archivo de salida cifrado.
     * @param clave Clave de cifrado (car�cter).
     */
    static void CifrarArchivo(const std::string& rutaEntrada, const std::string& rutaSalida, char clave);

    /**
     * @brief Descifra un archivo previamente cifrado con XOR.
     * @param rutaEntrada Ruta del archivo cifrado de entrada.
     * @param rutaSalida Ruta del archivo de salida descifrado.
     * @param valor Clave de descifrado (car�cter).
     */
    static void desifrarArchivo(const std::string& rutaEntrada, const std::string& rutaSalida, char valor);

    /**
     * @brief Cifra y guarda los datos del banco en un archivo.
     * @param banco Referencia al objeto Banco cuyos datos se van a cifrar y guardar.
     * @param nombreArchivo Nombre del archivo de salida.
     * @param claveCifrado Clave de cifrado (car�cter).
     */
    static void cifrarYGuardarDatos(const class Banco& banco, const std::string& nombreArchivo, char claveCifrado);

    /**
     * @brief Descifra y carga los datos del banco desde un archivo.
     * @param banco Referencia al objeto Banco donde se cargar�n los datos.
     * @param nombreArchivo Nombre del archivo cifrado.
     * @param claveCifrado Clave de descifrado (car�cter).
     * @return true si la operaci�n fue exitosa, false en caso contrario.
     */
    static bool descifrarYCargarDatos(class Banco& banco, const std::string& nombreArchivo, char claveCifrado);

    /**
     * @brief Descifra los datos del banco sin cargarlos, seg�n la opci�n indicada.
     * @param banco Referencia constante al objeto Banco.
     * @param nombreArchivo Nombre del archivo cifrado.
     * @param claveCifrado Clave de descifrado (car�cter).
     * @param opcion Opci�n de operaci�n adicional.
     * @return true si la operaci�n fue exitosa, false en caso contrario.
     */
    static bool descifrarSinCargarDatos(const Banco& banco, const std::string& nombreArchivo, char claveCifrado, int opcion);
};

#endif // CIFRADO_H