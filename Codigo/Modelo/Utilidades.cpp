#include "Utilidades.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <regex>
#include <iostream>

Utilidades::Utilidades() {
    // Constructor vacío
}

Utilidades::~Utilidades() {
    // Destructor vacío
}

// Método para convertir un string a double
double Utilidades::ConvertirADouble(const std::string& texto) {
    // Verificar si el texto está vacío
    if (texto.empty()) {
        std::cout << "Texto vacío, retornando 0.0" << std::endl;
        return 0.0;
    }

    // Eliminar caracteres no numéricos excepto el punto decimal y signo negativo
    std::string soloNumeros;
    bool puntoEncontrado = false;

    for (char c : texto) {
        if (std::isdigit(c)) {
            soloNumeros += c;
        }
        else if (c == '.' && !puntoEncontrado) {
            soloNumeros += c;
            puntoEncontrado = true;
        }
        else if (c == '-' && soloNumeros.empty()) {
            // Solo permitir el signo negativo al principio
            soloNumeros += c;
        }
    }

    // Si la cadena resultante está vacía o solo tiene un signo negativo
    if (soloNumeros.empty() || soloNumeros == "-") {
        std::cout << "No se encontraron dígitos válidos, retornando 0.0" << std::endl;
        return 0.0;
    }

	// Bloque para manejar excepciones
    try {
        // Convertir la cadena limpia a double
        double resultado = std::stod(soloNumeros);
        std::cout << "Conversión exitosa: " << std::fixed << std::setprecision(2) << resultado << std::endl;
        return resultado;
    }
    catch (const std::invalid_argument&) {
        std::cout << "Error: argumento inválido en la conversión" << std::endl;
        return 0.0;
    }
    catch (const std::out_of_range&) {
        std::cout << "Error: valor fuera de rango" << std::endl;
        return 0.0;
    }
    catch (const std::exception& e) {
        std::cout << "Error desconocido: " << e.what() << std::endl;
        return 0.0;
    }
}

// Método para formatear un monto a string con separadores de miles y decimales
std::string Utilidades::FormatearMonto(double monto, int decimales) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(decimales) << monto;

    std::string resultado = oss.str();

    // Agregar separadores de miles
    size_t posDecimal = resultado.find('.');
    if (posDecimal == std::string::npos) {
        posDecimal = resultado.length();
    }

    for (int i = posDecimal - 3; i > 0; i -= 3) {
        resultado.insert(i, ",");
    }

    return resultado;
}

// Metodo para formatear la fecha 
std::string Utilidades::FormatearFecha(int dia, int mes, int anio) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << dia << "/"
        << std::setfill('0') << std::setw(2) << mes << "/"
        << anio;

    return oss.str();
}

// metodo para comprobar si es numerico
bool Utilidades::EsNumerico(const std::string& texto) {
    if (texto.empty()) {
        return false;
    }

    bool puntoDecimal = false;
    bool tieneDigito = false;

    for (size_t i = 0; i < texto.length(); i++) {
        if (i == 0 && texto[i] == '-') {
            // Permitir signo negativo al inicio
            continue;
        }

        if (texto[i] == '.') {
            if (puntoDecimal) {
                // Más de un punto decimal
                return false;
            }
            puntoDecimal = true;
        }
        else if (!std::isdigit(texto[i])) {
            return false;
        }
        else {
            tieneDigito = true;
        }
    }

    return tieneDigito;
}

// metodo para validar el correo 
bool Utilidades::EsCorreoValido(const std::string& correo) {
    // Expresión regular simple para validar correos electrónicos
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(correo, pattern);
}

// Metodo para eliminar espacios 
std::string Utilidades::EliminarEspacios(const std::string& texto) {
    std::string resultado = texto;
    resultado.erase(std::remove_if(resultado.begin(), resultado.end(),
        [](unsigned char c) { return std::isspace(c); }),
        resultado.end());
    return resultado;
}

// Metodo para convertir a mayusculas 
std::string Utilidades::ConvertirAMayusculas(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return resultado;
}

// Metodo para convertir a minusculas 
std::string Utilidades::ConvertirAMinusculas(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return resultado;
}


// metodo para regresar al menu
std::string Utilidades::Regresar() {
	return "Regresar al menu principal";
}
