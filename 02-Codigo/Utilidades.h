#pragma once
#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "CodigoQR.h"

class NodoPersona;
class Persona;

/**
 * @class Utilidades
 * @brief Clase con métodos utilitarios para conversión, validación, formateo, manejo de archivos, QR y operaciones de consola.
 */
class Utilidades {
public:
    /**
     * @brief Constructor por defecto.
     */
    Utilidades();

    /**
     * @brief Destructor.
     */
    ~Utilidades();

    /**
     * @brief Convierte un string a double.
     * @param texto Texto a convertir.
     * @return Valor double convertido.
     */
    static double ConvertirADouble(const std::string& texto);

    /**
     * @brief Formatea un monto a string con decimales.
     * @param monto Monto a formatear.
     * @param decimales Número de decimales (por defecto 2).
     * @return Monto formateado como string.
     */
    static std::string FormatearMonto(double monto, int decimales = 2);

    /**
     * @brief Formatea una fecha a string.
     * @param dia Día.
     * @param mes Mes.
     * @param anio Año.
     * @return Fecha formateada como string.
     */
    static std::string FormatearFecha(int dia, int mes, int anio);

    /**
     * @brief Verifica si un texto es numérico.
     * @param texto Texto a verificar.
     * @return true si es numérico, false en caso contrario.
     */
    static bool EsNumerico(const std::string& texto);

    /**
     * @brief Verifica si un correo es válido.
     * @param correo Correo a verificar.
     * @return true si es válido, false en caso contrario.
     */
    static bool EsCorreoValido(const std::string& correo);

    /**
     * @brief Elimina espacios de un texto.
     * @param texto Texto a procesar.
     * @return Texto sin espacios.
     */
    static std::string EliminarEspacios(const std::string& texto);

    /**
     * @brief Convierte un texto a mayúsculas.
     * @param texto Texto a convertir.
     * @return Texto en mayúsculas.
     */
    static std::string ConvertirAMayusculas(const std::string& texto);

    /**
     * @brief Convierte un texto a minúsculas.
     * @param texto Texto a convertir.
     * @return Texto en minúsculas.
     */
    static std::string ConvertirAMinusculas(const std::string& texto);

    /**
     * @brief Muestra la opción para regresar al menú principal.
     * @return Texto de opción de regreso.
     */
    static std::string Regresar();

    /**
     * @brief Mueve el cursor a la posición (x, y) en la consola.
     * @param x Posición horizontal.
     * @param y Posición vertical.
     */
    static void gotoxy(int x, int y);

    /**
     * @brief Muestra el menú de ayuda en consola.
     */
    static void mostrarMenuAyuda();

    /**
     * @brief Ordena un vector de punteros usando el algoritmo burbuja.
     * @tparam T Tipo de los elementos.
     * @param vec Vector de punteros a ordenar.
     * @param criterio Función de comparación.
     */
    template<typename T>
    static void burbuja(std::vector<T*>& vec, std::function<bool(const T*, const T*)> criterio) {
        for (size_t i = 0; i < vec.size(); ++i) {
            for (size_t j = 0; j < vec.size() - i - 1; ++j) {
                if (!criterio(vec[j], vec[j + 1])) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        }
    }

    /**
     * @brief Ordena una lista enlazada simple de nodos usando burbuja.
     * @tparam Nodo Tipo del nodo.
     * @tparam T Tipo de los datos.
     * @param cabeza Puntero a la cabeza de la lista.
     * @param criterio Función de comparación.
     */
    template<typename Nodo, typename T>
    static void burbujaLista(Nodo* cabeza, std::function<bool(const T*, const T*)> criterio) {
        int n = 0;
        for (Nodo* tmp = cabeza; tmp; tmp = tmp->siguiente) ++n;
        if (n < 2) return;

        for (int i = 0; i < n - 1; ++i) {
            Nodo* actual = cabeza;
            for (int j = 0; j < n - i - 1; ++j) {
                if (!criterio(actual->persona, actual->siguiente->persona)) {
                    std::swap(actual->persona, actual->siguiente->persona);
                }
                actual = actual->siguiente;
            }
        }
    }

    /**
     * @brief Calcula el hash SHA1 de un archivo.
     * @param rutaArchivo Ruta del archivo.
     * @return Hash SHA1 como string.
     */
    static std::string calcularSHA1(const std::string& rutaArchivo);

    /**
     * @brief Verifica el hash SHA1 de un archivo.
     * @param rutaArchivo Ruta del archivo.
     * @param hashEsperado Hash esperado.
     * @return true si el hash coincide, false en caso contrario.
     */
    static bool verificarSHA1(const std::string& rutaArchivo, const std::string& hashEsperado);

    /**
     * @brief Guarda el hash en un archivo.
     * @param rutaArchivo Ruta del archivo.
     * @param hash Hash a guardar.
     */
    static void guardarHashArchivo(const std::string& rutaArchivo, const std::string& hash);

    /**
     * @brief Lee el hash de un archivo.
     * @param rutaHashArchivo Ruta del archivo de hash.
     * @return Hash leído como string.
     */
    static std::string leerHashArchivo(const std::string& rutaHashArchivo);

    /**
     * @brief Demostración didáctica de recorrido por Árbol B.
     * @param cabeza Puntero a la cabeza de la lista de personas.
     */
    static void PorArbolB(NodoPersona* cabeza);

    /**
     * @brief Genera un código QR para una persona y número de cuenta.
     * @param persona Referencia a la persona.
     * @param numeroCuenta Número de cuenta.
     * @return true si se generó correctamente, false en caso contrario.
     */
    static bool generarQRPersona(const Persona& persona, const std::string& numeroCuenta);

    /**
     * @brief Inicia una operación crítica para la marquesina.
     */
    static void iniciarOperacionCritica();

    /**
     * @brief Finaliza una operación crítica para la marquesina.
     */
    static void finalizarOperacionCritica();

    /**
     * @brief Limpia la pantalla preservando la marquesina.
     * @param lineasMarquesina Número de líneas de la marquesina (por defecto 2).
     */
    static void limpiarPantallaPreservandoMarquesina(int lineasMarquesina = 2);

    /**
     * @brief Genera un código QR y PDF para una persona y número de cuenta.
     * @param persona Referencia a la persona.
     * @param numeroCuenta Número de cuenta.
     * @return true si se generó correctamente, false en caso contrario.
     */
    static bool generarQR(const Persona& persona, const std::string& numeroCuenta);
};

#endif // UTILIDADES_H