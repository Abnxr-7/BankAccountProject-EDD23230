#pragma once
#ifndef CIFRADO_H
#define CIFRADO_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

// Clase Cifrado con la lógica para cifrar y descifrar el archivo binario usando XOR
class Cifrado {
public:
    static void CifrarArchivo(const std::string& rutaEntrada, const std::string& rutaSalida, char clave);
    static void desifrarArchivo(const std::string& rutaEntrada, const std::string& rutaSalida, char valor);
};

#endif // CIFRADO_H
